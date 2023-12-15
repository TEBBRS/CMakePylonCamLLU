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
		LLU::WS::ReleaseArray<uint8_t> hello;
		LLU::WS::ArrayData<uint8_t> arrayData;
		struct stack_st
		{
			int total=0;
			std::string head="";
		};
		stack_st* pStack_st;
};