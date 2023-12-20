#include "WolframEngine.h"

EXTERN_C DLLEXPORT int WolframLibrary_initialize(WolframLibraryData libData) { LLU::LibraryData::setLibraryData(libData); return 0; }

WolframEngine::WolframEngine()
{
	WolframState = Idle;
	// WSTP Initialise
	env = WSInitialize((char*)0);
	if (env == (WSENV)0)
	{
		wxLogMessage("Wolfram Engine communication unable to initialize!");
		Initialised = false;
		return;
	}
	else
		wxLogMessage("Wolfram Engine communication initialized!");

	// WSTP Open a connection to the wolfram kernel
	link = WSOpenString(env, "-linklaunch \"C:\\Program Files\\Wolfram Research\\Wolfram Engine\\13.3\\mathkernel.exe\"", &error);

	if (link == (WSLINK)0 || error != WSEOK)
	{
		wxLogMessage("Wolfram Engine communication unable to create link!");
		Initialised = false;
		return;
	}
	else
		wxLogMessage("Wolfram Engine communication Link created!");

	// WSTP Activate link
	if (!WSActivate(link))
	{
		wxLogMessage("Wolfram Engine communication link not activated!");
		Initialised = false;
		return;
	}
	else
	{
		wxLogMessage("Wolfram Engine communication link activated!");
		Initialised = true;
		pStreamObject = new LLU::WSStream<LLU::WS::Encoding::UTF8, LLU::WS::Encoding::UTF8>(link);
	}
	if (!Initialised)
		WolframState = Error;
	else
		WolframState = Processing;
}

WolframEngine::State WolframEngine::PollEngine()
{
	if (WolframState == Processing)
		CheckInput();
	return WolframState;
}
void WolframEngine::CheckInput()
{
	StackSize = 0;
	while (WolframState!=WaitingForInput)
	{
		CheckInputRecursive(0);
	}

}
void WolframEngine::CheckInputRecursive(int NrOfArguments)
{
	int argCount = 0;
	int totalArgCount = NrOfArguments;
	int arg1;
	float arg2;
	std::string arg3;
	LLU::WS::Function* function;
	LLU::WS::Symbol* symbol;
	const char* errorMessage;
	std::string head;
	int type = 0;
	bool initialCall = true;
	wxLogMessage("==== Stack nesting level ===== : %i NrOfArguments %i", ++StackSize, totalArgCount);
	do
	{
		type = WSGetType(link);
		switch (type)
		{
		case WSTKINT:
			/* read the integer */
			*pStreamObject >> arg1;
			totalArgCount -= 1;
			wxLogMessage(" Integer : %i", arg1);
			break;
		case WSTKREAL:
			/* read the floating point number */
			*pStreamObject >> arg2;
			totalArgCount -= 1;
			wxLogMessage(" Real : %f", arg2);
			break;
		case WSTKSTR:
			/* read the string. */
			*pStreamObject >> arg3;
			totalArgCount -= 1;
			wxLogMessage(" String : %s", arg3);
			break;

		case WSTKFUNC:
			function = new LLU::WS::Function();
			*pStreamObject >> *function;
			argCount = function->getArgc();
			head = function->getHead();
			if (StackSize==1)
				totalArgCount = argCount;
			wxLogMessage("Function  Head : %s Nr. of arguments : %i", head, argCount);


			if (head == "InputNamePacket")
			{
				WolframState = WaitingForInput;
				wxLogMessage("Total was: %i", totalArgCount);
			}
			if (argCount > 0)
			{
				CheckInputRecursive(argCount);
				totalArgCount -= 1;
			}

			delete function;
			break;
			//case WSTKERROR:
			//	break;
		case WSTKSYM:
			symbol = new LLU::WS::Symbol();
			*pStreamObject >> *symbol;
			head = symbol->getHead();
			totalArgCount -= 1;
			wxLogMessage("Symbol : %s", head);
			delete symbol;
			break;
		case WSTKERROR:
			errorMessage = WSErrorMessage(link);
			totalArgCount -= 1;
			wxLogMessage("Error : %s", errorMessage);
			break;
		default:
			throw new std::exception("Not implemeneted type %i ", type);
			break;
		}
	} while (totalArgCount>0);
	wxLogMessage("==== Stack nesting level ===== : %i", --StackSize);
}

void WolframEngine::CreateImage(Pylon::CGrabResultPtr ptrGrabResult)
{
	if (WolframState == WaitingForInput)
	{
		// use raw bitmap access to write MONO8 data directly into the bitmap
		ItCGrabResultPtr ItPtr(ptrGrabResult);
		const int w = 3; // ptrGrabResult->GetWidth();
		const int h = 3; // ptrGrabResult->GetHeight();

		auto it = ItPtr.begin();
		uint8_t* ptr = (uint8_t*) ptrGrabResult->GetBuffer();
		Array = new uint8_t[w*h];
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				Array[i*h+j] = *it;
				//wxLogMessage("i : %i ; j : %i; grayvalue : %i", i, j, Array[i][j]);
				it++;
			}
		}
		hello(Array);

		int* dims1{ new int[2] { h, w } };
		hello.setDims(dims1);
		hello.setRank(2);
		std::string array[] = { "Automatic" };
		std::vector<char*> vec;
		std::transform(std::begin(array), std::end(array),
			std::back_inserter(vec),
			[](std::string& s) { s.push_back(0); return &s[0]; });
		vec.push_back(nullptr);
		char** head = vec.data();

		hello.setHeads(head);
		int* dims = hello.getDims();
		arrayData = std::unique_ptr<uint8_t[], LLU::WS::ReleaseArray<uint8_t>>(Array, hello);

		try
		{
			//*pStreamObject << LLU::WS::Function("EnterExpressionPacket", 1) << LLU::WS::Function("Set", 2) << LLU::WS::Symbol("test") << "10";
			*pStreamObject << LLU::WS::Function("EnterExpressionPacket", 1) << LLU::WS::Function("Set", 2) << LLU::WS::Symbol("test") << LLU::WS::Function("RawArray",2)<< "Integer8" << arrayData;

		}
		catch (LLU::LibraryLinkError e)
		{
			wxLogMessage("%s", e.message());
		}
		arrayData.release();
		WolframState = Processing;
	}
}
void WolframEngine::CreateImageAsString(Pylon::CGrabResultPtr ptrGrabResult)
{
	if (WolframState == WaitingForInput)
	{
		// use raw bitmap access to write MONO8 data directly into the bitmap
		ItCGrabResultPtr ItPtr(ptrGrabResult);
		const int w = ptrGrabResult->GetWidth();
		const int h = ptrGrabResult->GetHeight();

		auto it = ItPtr.begin();
		uint8_t* ptr = (uint8_t*)ptrGrabResult->GetBuffer();
		std::stringstream data;
		data << "{";
		for (int i = 0; i < h; i++)
		{
			data << "{";
			for (int j = 0; j < w; j++)
			{
				data << int(*it);
				//wxLogMessage("i : %i ; j : %i; grayvalue : %i", i, j, Array[i][j]);
				it++;
				if (j < (w - 1))
					data << ",";
			}
			if (i < (h - 1))
				data << "}, ";
			else
				data << "}";

		}
		data << "}";

		try
		{
			//*pStreamObject << LLU::WS::Function("EnterExpressionPacket", 1) << LLU::WS::Function("Set", 2) << LLU::WS::Symbol("test") << "10";
			*pStreamObject << LLU::WS::Function("EvaluatePacket", 1) << ((std::string) ("bart = ")).append(data.str());

		}
		catch (LLU::LibraryLinkError e)
		{
			wxLogMessage("%s", e.message());
		}
		//arrayData.release();
		WolframState = Processing;
	}
}

WolframEngine::~WolframEngine()
{
	delete pStreamObject;
	WSClose(link);
	WSDeinitialize(env);
}
