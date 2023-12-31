﻿// CMakePylonCamLLU.cpp : Defines the entry point for the application.
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
	link = WSOpenArgcArgv(env, argc, argv, &error);
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

	while (true)
	{
		// Wait for the prompt In[1]:=

		string inputNameString;
		LLU::WS::Function inputPacketFunction;
		test >> inputPacketFunction;
		string Head = inputPacketFunction.getHead();
		int ArgCount = inputPacketFunction.getArgc();
		cout << "-->> Function head:" << Head << " Arguments :" << ArgCount << endl;
		if (ArgCount < 10)
		{
			for (int i = 0; i < ArgCount; i++)
			{
				test >> inputNameString;
				cout << inputNameString;
			}
		}
		if (Head == "InputNamePacket")
		{
			string inputTextString;
			std::cin >> inputTextString;
			//std::cout << "Add Integrate[x, {x, 0, 10}] to the stream" << std::endl;
			LLU::WS::Function enterTextFunction("EnterTextPacket", 1);
			test << enterTextFunction << inputTextString;

		}

	}


	std::cout << "Close the connection..." << std::endl;
	
	// WSTP Close gracefully
	WSClose(link);
	WSDeinitialize(env);
	return 0;
}
