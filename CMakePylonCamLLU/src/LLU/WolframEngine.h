#include <wx/log.h>
#include <LLU/LLU.h>
#include "wstp.h"
#include "../Utils/ItCGrabResulPtr.h"
#include <pylon/PylonIncludes.h>
#include <vector>
#include <string>
#include <array>
class WolframEngine
{
	public:
		enum State { Idle, WaitingForInput, Processing, Error };
		WolframEngine();
		State PollEngine();
		void CheckInput();
		void CreateImage(Pylon::CGrabResultPtr ptrGrabResult);
		bool WolframEngine::CheckInputRecursive(bool initialCall, int NrOfArguments);
		~WolframEngine();

	private:
		int error;
		WSLINK link;
		WSENV env;
		State WolframState;
		bool Initialised;
		LLU::WSStream<LLU::WS::Encoding::UTF8, LLU::WS::Encoding::UTF8>* pStreamObject;
		std::vector<std::vector<uint8_t>> imageAsArray;
		uint8_t** Array;
		uint8_t* Array1;
		int StackSize = 0;
		LLU::WS::ReleaseArray<uint8_t> hello;
		LLU::WS::ArrayData<uint8_t> arrayData;
		struct stack_st
		{
			enum stack_stType { Root=0, Parameter=1 };
			stack_stType type;
			int argCount;
			int total=0;
			std::string head="";
			using elementType = stack_stType;
		};
		stack_st* pStack_st;
};