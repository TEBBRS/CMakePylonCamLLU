#include <wx/log.h>
#include <LLU/LLU.h>
#include "wstp.h"
#include "../Utils/ItCGrabResulPtr.h"
#include <pylon/PylonIncludes.h>

class WolframEngine
{
	public:
		WolframEngine();
		void CreateImage(Pylon::CGrabResultPtr ptrGrabResult);
		~WolframEngine();
	private:
		int error;
		WSLINK link;
		WSENV env;
		bool Initialised;
		LLU::WSStream<LLU::WS::Encoding::UTF8, LLU::WS::Encoding::UTF8>* pStreamObject;
		LLU::Image<uint8_t>* pImage = nullptr;
};