///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-383-g4d0443f5)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/frame.h>

#include <wx/log.h>
#include <wx/timer.h>
#include <wx/rawbmp.h>
#include <wx/wx.h>
#include <wx/gbsizer.h>
#include <wx/generic/statbmpg.h>
#include "../OutputCamImages/OutputCamImages.h"
#include <LLU/LLU.h>
#include <wstp.h>

// Include files to use the pylon API.
#include <pylon/PylonIncludes.h>
#ifdef PYLON_WIN_BUILD
#    include <pylon/PylonGUI.h>
#endif

// Namespace for using pylon objects.
using namespace Pylon;

// Settings to use any camera type.
#include <pylon/BaslerUniversalInstantCamera.h>
///////////////////////////////////////////////////////////////////////////

constexpr int ID_1 = 1000;
constexpr int ID_2 = 1001;
constexpr int FPS = 2;
constexpr int TIMERVALUE = (1000 / FPS);

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame
{
	private:
		wxLog* logger;
		wxTimer m_timer;
		wxGridBagSizer *gbSizer1;
		CBaslerUniversalInstantCamera* camera;
		OutputCamImages Output;

		bool cameraConnected;
	protected:
		wxMenuBar* m_MainMenuBar;
		wxMenu* m_MainMenu;
		wxStaticText* m_Header;
	
   		void OnConnect(wxCommandEvent& event);
    	void OnDisconnect(wxCommandEvent& event);
		void OnTimer(wxTimerEvent& event);
		void OnPaint(wxPaintEvent &event);
    	wxDECLARE_EVENT_TABLE();

	public:
		MainFrame(WSLINK wolframLLULink, CBaslerUniversalInstantCamera* cam, wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Barts first wxWidgets application"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1000, 600), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL | wxBORDER_RAISED | wxHSCROLL | wxVSCROLL);
		~MainFrame();

};



