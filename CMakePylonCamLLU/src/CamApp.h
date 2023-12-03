// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "GUI_generated/CamAppMainFrame.h"
// Include files to use the pylon API.
#include <pylon/PylonIncludes.h>
#include <pylon/BaslerUniversalInstantCamera.h>
#include <LLU/LLU.h>
#include "wstp.h"

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
    ~MyApp();
private:
    CBaslerUniversalInstantCamera* camera;
};
