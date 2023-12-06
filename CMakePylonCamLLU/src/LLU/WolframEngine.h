#include <wx/log.h>
#include <LLU/LLU.h>
#include "wstp.h"

class WolframEngine
{
	public:
		WolframEngine();
		~WolframEngine();
	private:
		int error;
		WSLINK link;
		bool Initialised;
};