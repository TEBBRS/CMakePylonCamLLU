#include "CamApp.h"
#include <stdio.h>

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{

    // Before using any pylon methods, the pylon runtime must be initialized.
	PylonInitialize();
    // Wolfram variables
    int error;
    WSLINK link;
     try
    {
        // Create an instant camera object with the first found camera device.
         camera = new CBaslerUniversalInstantCamera ( CTlFactory::GetInstance().CreateFirstDevice());

        // Print the model name of the camera.
        std::cout << "Using device " << camera->GetDeviceInfo().GetModelName() << std::endl;

        // WSTP Initialise
        WSENV env = WSInitialize((char*)0);
        if (env == (WSENV)0)
        {
            std::cout << "Unable to initialize!";
            return false;
        }
        else
            std::cout << "Initialized!";

        // WSTP Open a connection to the wolfram kernel

        //link = WSOpenArgcArgv(env, argc, argv, &error);
        link = WSOpenString(env, "-linklaunch \"C:\\Program Files\\Wolfram Research\\Wolfram Engine\\13.3\\mathkernel.exe\"", &error);

        if (link == (WSLINK)0 || error != WSEOK)
        {
            std::cout << "Unable to create link!";
            return false;
        }
        else
            std::cout << "Link created!";

        // WSTP Activate link
        if (!WSActivate(link))
        {
            std::cout << "Link not activated!";
            return false;
        }
        else
            std::cout << "Link activated!";

    }
       catch (const GenericException &e)
    {
        // Error handling.
        std::cerr << "An exception occurred." << std::endl
        << e.GetDescription() << std::endl;
        return false;
    }

    MainFrame *frame = new MainFrame(link, camera, NULL );
    frame->Show( true );
    return true;
}
MyApp::~MyApp()
{
    delete camera;
    // When exited release all resources
    PylonTerminate();

}
