#include <wx/log.h>
#include <LLU/LLU.h>
#include "wstp.h"
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
};