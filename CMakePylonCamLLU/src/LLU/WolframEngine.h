#include <wx/log.h>
#include <LLU/LLU.h>
#include "wstp.h"

class WolframEngine
{
	public:
		WolframEngine();
		void CreateImage();
		~WolframEngine();
	private:
		int error;
		WSLINK link;
		WSENV env;
		bool Initialised;
};