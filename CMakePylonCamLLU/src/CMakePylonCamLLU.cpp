// CMakePylonCamLLU.cpp : Defines the entry point for the application.
//

#include "CMakePylonCamLLU.h"

using namespace std;

int main()
{
	// WSTP Initialise
	WSENV env = WSInitialize((char*)0);
	if (env == (WSENV)0)
	{
		std::cout << "Unable to initialize!";
		return 1;
	}
	else
		std::cout << "Iniialized!";

	// WSTP Open a connection to the wolfram kernel
	int error;
	WSLINK link;
	link = WSOpenString(env, "-linklaunch", &error);
	//link = WSOpenString(env, "-linklaunch \"C:\\Program Files\\Wolfram Research\\Wolfram Engine\\13.3\\mathkernel.exe\"", &error);

	if(link == (WSLINK)0 || error != WSEOK)
	{
		std::cout << "Unable to create link!";
		return 1;
	}
	else
		std::cout << "Link created!";

	// WSTP Activate link
	if (!WSActivate(link))
	{
		std::cout << "Link not activated!";
		return 1;
	}
	else
		std::cout << "Link activated!";
	
	// Data exchange -->> MyProblem
	std::cout << "Create the stream object" << std::endl;
	LLU::WSStream<LLU::WS::Encoding::UTF8, LLU::WS::Encoding::UTF8> test(link);
	
	// Wait for the prompt In[1]:=
	LLU::WS::Function inputPacketFunction;
	string inputNameString;
	test >> inputPacketFunction >> inputNameString;
	cout << "Function head:"  << inputPacketFunction.getHead() << " Arguments :" << inputPacketFunction.getArgc() <<" String : " << inputNameString << endl;
	
	// Write the expression to the stream
	std::cout << "Add 2+2+2 to the stream" << std::endl;
	LLU::WS::Function enterExpressionFunction;
	enterExpressionFunction.setHead("EnterExpressionPacket");
	enterExpressionFunction.setArgc(1);

	test << enterExpressionFunction << "2+2+2";

	// Wait for output packet Out[1]:= and the computed results
	std::cout << "Wait for output packet" << std::endl;
	LLU::WS::Function outputPacketFunction;
	string outputNameString;
	LLU::WS::Function returnExpressionPacket;
	string result;
	test >> outputPacketFunction >> outputNameString >> returnExpressionPacket >> result;
	cout << "Function head:" << outputPacketFunction.getHead() << " Arguments :" << outputPacketFunction.getArgc() << " String : " << outputNameString << endl;
	cout << "Function head:" << returnExpressionPacket.getHead() << " Arguments :" << returnExpressionPacket.getArgc() << " String : " << result << endl;


	std::cout << "Close the connection..." << std::endl;
	
	// WSTP Close gracefully
	WSClose(link);
	WSDeinitialize(env);
	return 0;
}
