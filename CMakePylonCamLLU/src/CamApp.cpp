#include "CamApp.h"

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MainFrame *frame = new MainFrame(NULL );
    frame->Show( true );
    return true;
}
MyApp::~MyApp()
{
}

