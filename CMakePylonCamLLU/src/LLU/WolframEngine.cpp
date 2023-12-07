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
	}

}
void WolframEngine::CreateImage(Pylon::CGrabResultPtr ptrGrabResult)
{
	// use raw bitmap access to write MONO8 data directly into the bitmap
	const uint8_t* pImageBuffer = (uint8_t*)ptrGrabResult->GetBuffer();
	const std::vector<uint32_t> dimensions{ ptrGrabResult->GetHeight(), ptrGrabResult->GetHeight() };
	LLU::MArrayDimensions imageDimensions(dimensions);
	LLU::NumericArray<unsigned char> imageData();
}
WolframEngine::~WolframEngine()
{
	WSClose(link);
	WSDeinitialize(env);
}
