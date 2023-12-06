///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-383-g4d0443f5)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "CamAppMainFrame.h"

///////////////////////////////////////////////////////////////////////////
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(ID_1, MainFrame::OnConnect)
	EVT_MENU(ID_2, MainFrame::OnDisconnect)
	EVT_MENU(ID_3, MainFrame::OnQuit)
	EVT_TIMER(wxID_ANY, MainFrame::OnTimer)
	//EVT_PAINT(MainFrame::OnPaint)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	logger = new wxLogWindow(NULL, "Log window", true, false);
	wxLog::SetActiveTarget(logger);

	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	
	Output.Initialize(this);
	camera = new Camera();
	engine = new WolframEngine();

	m_MainMenuBar = new wxMenuBar(0);
	m_MainMenu = new wxMenu();
	wxMenuItem *m_Connect;
	m_Connect = new wxMenuItem(m_MainMenu, ID_1, wxString(wxT("Connect to Camera")), wxEmptyString, wxITEM_NORMAL);
	m_MainMenu->Append(m_Connect);

	wxMenuItem *m_Disconnect;
	m_Disconnect = new wxMenuItem(m_MainMenu, ID_2, wxString(wxT("Disconnect from camera")), wxEmptyString, wxITEM_NORMAL);
	m_MainMenu->Append(m_Disconnect);

	wxMenuItem* m_Quit;
	m_Quit = new wxMenuItem(m_MainMenu, ID_3, wxString(wxT("Quit the application")), wxEmptyString, wxITEM_NORMAL);
	m_MainMenu->Append(m_Quit);

	m_MainMenuBar->Append(m_MainMenu, wxT("MainMenu"));

	this->SetMenuBar(m_MainMenuBar);

	//wxGridBagSizer *gbSizer1;
	gbSizer1 = new wxGridBagSizer( 0, 0 );
	gbSizer1->SetFlexibleDirection( wxBOTH );
	gbSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_Header = new wxStaticText(this, wxID_ANY, wxT("Barts camera application"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL);
	m_Header->SetLabelMarkup(wxT("Barts camera application"));
	m_Header->Wrap(-1);
	gbSizer1->Add( m_Header, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	
	gbSizer1->Add( Output.getGenBitmap(0), wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	gbSizer1->Add( Output.getGenBitmap(1), wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	gbSizer1->Add( Output.getGenBitmap(2), wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	gbSizer1->Add( Output.getGenBitmap(3), wxGBPosition( 2, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	gbSizer1->Add( Output.getGenBitmap(4), wxGBPosition( 3, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	gbSizer1->Add( Output.getGenBitmap(5), wxGBPosition( 3, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	gbSizer1->Add( Output.getGenBitmap(6), wxGBPosition( 4, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	gbSizer1->Add( Output.getGenBitmap(7), wxGBPosition( 4, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );
	//this->SetScrollbar(wxHORIZONTAL || wxVERTICAL, 0, )
	this->SetSizer(gbSizer1);
	this->Layout();

	this->Centre(wxBOTH);

	// Start the timer
	m_timer.SetOwner(this);
	m_timer.Start(TIMERVALUE, true);
	cameraConnected = false;
}
void MainFrame::OnConnect(wxCommandEvent &event)
{
	wxLogMessage("OnConnect");
	camera->Open();
}
void MainFrame::OnQuit(wxCommandEvent& event)
{
	wxLogMessage("OnQuit");
	wxExit();
}


void MainFrame::OnTimer(wxTimerEvent &event)
{

	if (camera->Connected())
	{

		Pylon::CGrabResultPtr grabResult = camera->GrabOne();
		if (grabResult.IsValid())
			if (grabResult->GrabSucceeded())
			{	bool rePaintFrame=false;
				int w = grabResult->GetWidth();
				int h = grabResult->GetHeight();
				Pylon::EPixelType p = grabResult->GetPixelType();
				Output.CheckAndCreateOutputImage(0, grabResult);
				Output.CheckAndCreateOutputImage(1, grabResult);
				Output.CheckAndCreateOutputImage(2, grabResult);
				Output.CheckAndCreateOutputImage(3, grabResult);

				Output.CopyToOutputImage(0, grabResult);
				Output.SetGenericBitmap(0);
	
				//HoughLines.ConvertGrabToMat(grabResult);
				//HoughLines.CannyEdgeDetection();
				//HoughLines.HoughLineDetection();
				//HoughLines.HoughCircleDetection();

				//Output.CopyToOutputImage(1, HoughLines.EdgeDetectedImage);
				//Output.SetGenericBitmap(1);
				//Output.CopyToOutputImage(2, HoughLines.HoughLines);
				//Output.SetGenericBitmap(2);
				//Output.CopyToOutputImage(3, HoughLines.HoughCircles);
				//Output.SetGenericBitmap(3);

				if (Output.getRepaintFrame())
					gbSizer1->Layout();
			}
			else
				wxLogMessage("Grab failed!");
	}
	this->Refresh();
	m_timer.Start(TIMERVALUE, true);
}
void MainFrame::OnDisconnect(wxCommandEvent &event)
{
	wxLogMessage("OnDisconnect");
	camera->Disconnect();
}
void MainFrame::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
}




MainFrame::~MainFrame()
{ // delete decompressor;
	delete engine;
	delete camera;
	wxLog::SetActiveTarget(nullptr);
	delete logger;
}
