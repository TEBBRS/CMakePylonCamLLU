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
	const std::vector<uint32_t> dimensions{ ptrGrabResult->GetHeight(), ptrGrabResult->GetHeight() };
	LLU::MArrayDimensions imageDimensions(dimensions);
	LLU::NumericArray<uint8_t> imageData(ItPtr.begin(), ItPtr.end(),imageDimensions);
	LLU::WS::ReleaseArray<uint8_t> destructor();
	std::allocator<uint8_t> allocator();
	std::unique_ptr<uint8_t> ptrImage((uint8_t*)ptrGrabResult->GetBuffer());
	LLU::WS::ReleaseArray<uint8_t> release();
	LLU::WS::ArrayData<uint8_t> bart((uint8_t *) ptrGrabResult->GetBuffer());
	const std::vector<uint8_t, std::allocator<uint8_t>> test(ItPtr.begin(), ItPtr.end());
	*ptrStreamObject << bart;
}
WolframEngine::~WolframEngine()
{
	delete ptrStreamObject;
	WSClose(link);
	WSDeinitialize(env);
}
