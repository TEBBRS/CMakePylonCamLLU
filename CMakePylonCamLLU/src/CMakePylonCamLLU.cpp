// CMakePylonCamLLU.cpp : Defines the entry point for the application.
//

#include "CMakePylonCamLLU.h"

using namespace std;

int main(int argc, char* argv[])
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
	//link = WSOpenArgcArgv(env, argc, argv, &error);
	link = WSOpenString(env, "-linklaunch \"C:\\Program Files\\Wolfram Research\\Wolfram Engine\\13.3\\mathkernel.exe\"", &error);

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
	
	std::cout << "Create the stream object" << std::endl;
	LLU::WSStream<LLU::WS::Encoding::UTF8, LLU::WS::Encoding::UTF8> test(link);

	while (true)
	{
		int argCount = 0;
		int totalArgCount = 0;
		int arg1;
		float arg2;
		std::string arg3;
		LLU::WS::Function* function;
		LLU::WS::Symbol* symbol;
		std::string head;
		do
		{
			switch (WSGetType(link))
			{
			case WSTKINT:
				/* read the integer */
				test >> arg1;
				totalArgCount -= 1;
				std::cout << " Integer : " << arg1;
				break;
			case WSTKREAL:
				/* read the floating point number */
				test >> arg2;
				totalArgCount -= 1;
				std::cout << " Real : " << arg2;
				break;
			case WSTKSTR:
				test >> arg3;
				totalArgCount -= 1;
				std::cout << " String : " << arg3;
				break;
				/* read the string. */
			case WSTKFUNC:
				function = new LLU::WS::Function();
				test >> *function;
				argCount += function->getArgc();
				head = function->getHead();
				totalArgCount += argCount;
				std::cout << "Function  Head : " << head << " Nr. of arguments : " << argCount << std::endl;
				delete function;
				break;
			case WSTKARRAY:
				break;
			case WSTKERROR:
				break;
			case WSTKSYM:
				symbol = new LLU::WS::Symbol();
				test >> *symbol;
				argCount -= 1;
				head = symbol->getHead();
				totalArgCount += argCount;
				std::cout << "Symbol : " << head;
				delete symbol;
			}

		} 
		while (totalArgCount > 0);

		string inputTextString;
		std::cin >> inputTextString;
		//std::cout << "Add Integrate[x, {x, 0, 10}] to the stream" << std::endl;
		LLU::WS::Function enterTextFunction(inputTextString, 0);
		//test << LLU::WS::Function("EnterExpressionPacket", 1) << LLU::WS::Function("Image", 1) << "{{ 255, 0, 255}, { 0, 255, 0}, {255, 0, 255}}}";
		test << LLU::WS::Function("EnterTextPacket", 0) << inputTextString;


	}

	std::cout << "Close the connection..." << std::endl;
	
	// WSTP Close gracefully
	WSClose(link);
	WSDeinitialize(env);
	return 0;
}
