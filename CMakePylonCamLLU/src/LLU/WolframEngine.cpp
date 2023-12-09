#include "WolframEngine.h"

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
		ptrStreamObject = new LLU::WSStream<LLU::WS::Encoding::UTF8, LLU::WS::Encoding::UTF8>(link);
	}

}
void WolframEngine::CreateImage(Pylon::CGrabResultPtr ptrGrabResult)
{
	// use raw bitmap access to write MONO8 data directly into the bitmap
	ItCGrabResultPtr ItPtr(ptrGrabResult);
	LLU:colorspace_t cs(MImage_CS_Type::MImage_CS_Gray);
	LLU::Image<uint8_t> image(ptrGrabResult->GetWidth(), ptrGrabResult->GetHeight(), 1, cs, true);
	uint8_t* ptr = (uint8_t *) image.rawData();

	for (auto it = ItPtr.begin(); it != ItPtr.end(); it++)
	{
		*ptr = *it;
		ptr++;
	}
	*ptrStreamObject << image;
}
WolframEngine::~WolframEngine()
{
	delete ptrStreamObject;
	WSClose(link);
	WSDeinitialize(env);
}
