// CMakePylonCamLLU.cpp : Defines the entry point for the application.
//

#include "CMakePylonCamLLU.h"

using namespace std;

int main(int argc, char* argv[])
{
	st_WolframLibraryData libData;
	st_DataStore st_ds();
	DataStore ds=;
	//DataStoreNode_t dsn_t();
	//DataStoreNode dsn = (DataStoreNode) dsn_t;
	LLU::DataList<LLU::NodeType::Image> cont(ds, LLU::Ownership::LibraryLink);
	//cont.push_back();
	std::vector<vector<uint8_t>> vector;

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
	
	// Data exchange -->> MyProblem
	try
	{
		LLU::LibraryData::setLibraryData(&libData);
	}
	catch (LLU::LibraryLinkError e)
	{
		std::cout << e.message();
	}
	std::cout << "Create the stream object" << std::endl;
	LLU::WSStream<LLU::WS::Encoding::UTF8, LLU::WS::Encoding::UTF8> test(link);

	while (true)
	{

		try
		{
			//DataStore datastore = new DataStore();
			LLU::Image<uint8_t> image(100, 100, 1, colorspace_t::MImage_CS_Gray,false);
			/*
				Copy the data from the camera in the image object
			*/
			test << LLU::WS::Function("test =  Image[]", 1) << image;
		}
		catch (LLU::LibraryLinkError e)
		{
			std::cout << e.message() << std::endl;
		}

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
				if (Head == "ReturnExpressionPacket")
				{
					int result;
					test >> result;
					cout << result;
				}
				else
				{
					test >> inputNameString;
					cout << inputNameString;
				}
			}
		}
		if (Head == "InputNamePacket")
		{
			string inputTextString;
			std::cin >> inputTextString;
			//std::cout << "Add Integrate[x, {x, 0, 10}] to the stream" << std::endl;
			LLU::WS::Function enterTextFunction("Image", 1);
			//test << LLU::WS::Function("EnterExpressionPacket", 1) << LLU::WS::Function("Image", 1) << "{{ 255, 0, 255}, { 0, 255, 0}, {255, 0, 255}}}";
			test << LLU::WS::Function("EnterTextPacket", 1) << inputTextString << vector;
		}

	}

	std::cout << "Close the connection..." << std::endl;
	
	// WSTP Close gracefully
	WSClose(link);
	WSDeinitialize(env);
	return 0;
}
