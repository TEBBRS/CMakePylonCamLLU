// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include "GUI_generated/CamAppMainFrame.h"
// Include files to use the pylon API.



class MyApp: public wxApp
{
public:
    virtual bool OnInit();
    ~MyApp();
};
