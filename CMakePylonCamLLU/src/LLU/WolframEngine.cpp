#include "WolframEngine.h"

EXTERN_C DLLEXPORT int WolframLibrary_initialize(WolframLibraryData libData) { LLU::LibraryData::setLibraryData(libData); return 0; }

WolframEngine::WolframEngine()
{

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

}
void WolframEngine::CreateImage(Pylon::CGrabResultPtr ptrGrabResult)
{
	// use raw bitmap access to write MONO8 data directly into the bitmap
	ItCGrabResultPtr ItPtr(ptrGrabResult);
	//LLU:colorspace_t cs(MImage_CS_Type::MImage_CS_Gray);
	
	mint w = (mint) ptrGrabResult->GetWidth();
	mint h = (mint) ptrGrabResult->GetHeight();
	try
	{
		pImage = new LLU::Image<uint8_t>(w, h, 1, colorspace_t::MImage_CS_Gray, false);
		uint8_t* ptr = (uint8_t*)pImage->rawData();

		for (auto it = ItPtr.begin(); it != ItPtr.end(); it++)
		{
			*ptr = *it;
			ptr++;
		}
		*pStreamObject << LLU::WS::Function("test =  Image[]", 1) << *pImage;
	}
	catch (LLU::LibraryLinkError e)
	{
		wxLogMessage("%s", e.message());
	}
	//
}
WolframEngine::~WolframEngine()
{
	if (pImage != nullptr)
		delete pImage;
	delete pStreamObject;
	WSClose(link);
	WSDeinitialize(env);
}
