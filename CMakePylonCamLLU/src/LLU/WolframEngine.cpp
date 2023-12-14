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
	int argCount = 0;
	int totalArgCount = 0;
	int arg1;
	float arg2;
	std::string arg3;
	LLU::WS::Function* function;
	LLU::WS::Symbol* symbol;
	std::string head;
	do
	{
		switch (WSGetType(link))
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
			*pStreamObject >> arg3;
			totalArgCount -= 1;
			wxLogMessage(" String : %s", arg3);
			break;
			/* read the string. */
		case WSTKFUNC:
			function = new LLU::WS::Function();
			*pStreamObject >> *function;
			argCount += function->getArgc();
			head = function->getHead();
			totalArgCount += argCount;
			wxLogMessage("Function  Head : %s Nr. of arguments : %i", head, argCount);
			if (head == "InputNamePacket")
			{
				WolframState = WaitingForInput;
			}
			delete function;
			break;
		case WSTKARRAY:
			break;
		case WSTKERROR:
			break;
		case WSTKSYM:
			symbol = new LLU::WS::Symbol();
			*pStreamObject >> *symbol;
			argCount -= 1;
			head = symbol->getHead();
			totalArgCount += argCount;
			wxLogMessage("Symbol : %s", head);
			delete symbol;
		}

	} while (totalArgCount > 0);

}
void WolframEngine::CreateImage(Pylon::CGrabResultPtr ptrGrabResult)
{
	if (WolframState == WaitingForInput)
	{
		// use raw bitmap access to write MONO8 data directly into the bitmap
		ItCGrabResultPtr ItPtr(ptrGrabResult);
		//LLU:colorspace_t cs(MImage_CS_Type::MImage_CS_Gray);

		const int w = ptrGrabResult->GetWidth();
		const int h = ptrGrabResult->GetHeight();
		//imageAsArray.resize(h);
		auto it = ItPtr.begin();
		uint8_t* ptr = (uint8_t*) ptrGrabResult->GetBuffer();
		Array = new uint8_t*[h];
		for (int i = 0; i < h; i++)
		{
			//auto imLine = imageAsArray[i];
			//imLine.resize(w);
			//uint8_t* ptr = (uint8_t*)imLine.data();
			//uint8_t* ptr = (uint8_t*)Array[h,0];
			Array[i] = new uint8_t[w];
			for (int j = 0; j < w; j++)
			{
				Array[i][j] = *it;
				//wxLogMessage("i : %i ; j : %i; grayvalue : %i", i, j, Array[i][j]);
				it++;
			}
		}
		hello(&Array[0][0]);
		hello.setDims(new int[2] {h, w});
		hello.setRank(2);
		auto dims = hello.getDims();
		arrayData = std::unique_ptr<uint8_t[], LLU::WS::ReleaseArray<uint8_t>>(&Array[0][0], hello);

		try
		{
			*pStreamObject << LLU::WS::Function("EnterExpressionPacket", 1) << LLU::WS::Function("Image", 0);// << arrayData;
		}
		catch (LLU::LibraryLinkError e)
		{
			wxLogMessage("%s", e.message());
		}
		WolframState = Processing;
	}
}
WolframEngine::~WolframEngine()
{
	delete pStreamObject;
	WSClose(link);
	WSDeinitialize(env);
}
