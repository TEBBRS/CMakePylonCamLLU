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
	link = WSOpenString(env, " -linklaunch \"C:\\Program Files\\Wolfram Research\\Wolfram Engine\\13.3\\mathkernel.exe\"", &error);

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
	LLU::WSStream<LLU::WS::Encoding::Native, LLU::WS::Encoding::Native> test(link);
	//LLU::WSStream<LLU::WS::Encoding::UTF8, LLU::WS::Encoding::UTF8>::BidirStreamToken bidirToken=LLU::WS::Direction::;
	LLU::WS::Function function;
	string inputNameString;
	test >> function >> inputNameString;
	cout << "Function head:"  << function.getHead() << " Arguments :" << function.getArgc() <<" String : " << inputNameString << endl;
	
	std::cout << "Add 2+2 to the stream" << std::endl;
	
	//test << (mint) 1 << LLU::WS::BeginExpr::BeginExpr("1") << "2+2" << LLU::WS::EndExpr();
	//LLU::WS::String<LLU::WS::Encoding::UTF8> expression = "2+2";
	//test << LLU::WS::NewPacket << "2+2" << LLU::WS::EndPacket;
	WSPutString(test.get(), "2+2");
	std::cout << "Wait for output packet" << std::endl;
	LLU::WS::Function function1;
	string outputNameString;
	test >> function1 >> outputNameString;
	cout << "Function head:" << function.getHead() << " Arguments :" << function.getArgc() << " String : " << outputNameString << endl;

	std::cout << "Wait for a reply" << std::endl;
	int result1;
	//LLU::WS::GetAs <LLU::WS::Encoding::UTF8, int> result(result1);
	//std::cout << WSGetType(test.get());

	//	LLU::WS::Encoding::UTF8, int>(result1);
	cout << "Hello CMake. Error : " << error << " Result : " << function.getHead() << " Arguments :" << function.getArgc() << endl;
	std::cout << "Close the connection..." << std::endl;
	

	/*if (!WSEvaluate(link, (char*)"2+2;"))
		std::cout << "Didn't send an expression to eveluate" << std::endl;
	*/

	// WSTP Close gracefully
	WSClose(link);
	WSDeinitialize(env);
	return 0;
}
