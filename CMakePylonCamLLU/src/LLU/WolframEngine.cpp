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
	std::string args;
	LLU::WS::Function ReturnExpressionFunction;
	LLU::WS::Function inputPacketFunction;
	*pStreamObject >> inputPacketFunction;
	std::string Head = inputPacketFunction.getHead();
	int ArgCount = inputPacketFunction.getArgc();
	wxLogMessage ("-->> Packet received from wolfram -->> head: %s Arguments : %i", Head, ArgCount);
	for (int i = 0; i < ArgCount; i++)
		{
			if (Head == "ReturnExpressionPacket")
			{
				*pStreamObject >> ReturnExpressionFunction;
				wxLogMessage("Head: %s", ReturnExpressionFunction.getHead());
				//LLU::WS::Flush<LLU::WS::Encoding::UTF8, LLU::WS::Encoding::UTF8>(*pStreamObject);
				for (int j = 0; j < ReturnExpressionFunction.getArgc(); j++)
				{
					switch (WSGetType(link))
					{
					case WSTKINT:
						/* read the integer */
						int result1;
						*pStreamObject >> result1;
						break;
					case WSTKREAL:
						/* read the floating point number */
						float result2;
						*pStreamObject >> result2;
						break;
					case WSTKSTR:
						*pStreamObject >> args;
						break;
						/* read the string. */
					case WSTKFUNC:
						LLU::WS::Function function;
						*pStreamObject >> function;
						break;

					}
				}
			}
			else
			{
				*pStreamObject >> args;
				wxLogMessage("Arguments: %s", args);
			}
		}
	if (Head == "InputNamePacket")
	{
		WolframState = WaitingForInput;
	}
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
			*pStreamObject << LLU::WS::Function("EnterExpressionPacket", 1) << LLU::WS::Function("Image", 1) << arrayData;//<< "Byte";
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
