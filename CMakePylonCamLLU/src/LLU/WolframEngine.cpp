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
	const char* errorMessage;
	std::string head;
	int type = 0;
	int prevType=0;
	std::stack<stack_st*, std::deque<stack_st*, std::allocator<stack_st*>>> stack;
	bool exit = false;

	do
	{
		prevType = type;
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
			if (WolframState == WaitingForInput && totalArgCount == 0)
				exit = true;
			break;
			
		case WSTKFUNC:
			function = new LLU::WS::Function();
			*pStreamObject >> *function;
			argCount = function->getArgc();
			head = function->getHead();
			if (totalArgCount == 0)
				totalArgCount = argCount;
			else
				if (argCount > 0)
				{	
					pStack_st = new stack_st{ totalArgCount - 1, head };
					wxLogMessage("Written to stack head : %s , total %i, stacksize %i", pStack_st->head, pStack_st->total, stack.size()+1);
					stack.push(pStack_st);
					totalArgCount = argCount;
				}
			

			/*if (prevType == WSTKFUNC)
				totalArgCount -= 1;*/
			
			wxLogMessage("Function  Head : %s Nr. of arguments : %i", head, argCount);
			if (head == "InputNamePacket")
			{
				WolframState = WaitingForInput;
				wxLogMessage("Total was: %i", totalArgCount);
				//totalArgCount = 1;
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
		if (totalArgCount == 0 && !exit)
			if (!stack.empty())
			{
				delete pStack_st;
				stack.pop();
				pStack_st = stack.top(); 
				wxLogMessage("Read from stack head : %s , total %i, stack size %i", pStack_st->head, pStack_st->total, stack.size());

					
			}
	} while (!exit);//!stack.empty()||totalArgCount>0);

}
void WolframEngine::CreateImage(Pylon::CGrabResultPtr ptrGrabResult)
{
	if (WolframState == WaitingForInput)
	{
		// use raw bitmap access to write MONO8 data directly into the bitmap
		ItCGrabResultPtr ItPtr(ptrGrabResult);
		const int w = 2; // ptrGrabResult->GetWidth();
		const int h = 2; // ptrGrabResult->GetHeight();

		auto it = ItPtr.begin();
		uint8_t* ptr = (uint8_t*) ptrGrabResult->GetBuffer();
		Array = new uint8_t*[h];
		for (int i = 0; i < h; i++)
		{
			Array[i] = new uint8_t[w];
			for (int j = 0; j < w; j++)
			{
				Array[i][j] = *it;
				//wxLogMessage("i : %i ; j : %i; grayvalue : %i", i, j, Array[i][j]);
				it++;
			}
		}
		hello(&Array[0][0]);
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

		//hello.setHeads(head);
		int* dims = hello.getDims();
		arrayData = std::unique_ptr<uint8_t[], LLU::WS::ReleaseArray<uint8_t>>(&Array[0][0], hello);

		try
		{
			*pStreamObject << LLU::WS::Function("EnterExpressionPacket", 1) << LLU::WS::Function("Set", 2) << LLU::WS::Symbol("test") << LLU::WS::Function("Image", 2) << arrayData << "Byte";
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
