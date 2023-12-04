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
	EVT_TIMER(wxID_ANY, MainFrame::OnTimer)
	//EVT_PAINT(MainFrame::OnPaint)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(WSLINK wolframWTSPLink, CBaslerUniversalInstantCamera *cam, wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	logger = new wxLogWindow(NULL, "Log window", true, false);
	wxLog::SetActiveTarget(logger);
	if (wxIsMainThread)
		wxLogMessage("MainFrame = running on main thread.");
	else
		wxLogMessage("MainFrame = running on different thread.");

	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	
	Output.Initialize(this);

	m_MainMenuBar = new wxMenuBar(0);
	m_MainMenu = new wxMenu();
	wxMenuItem *m_Connect;
	m_Connect = new wxMenuItem(m_MainMenu, ID_1, wxString(wxT("Connect to Camera")), wxEmptyString, wxITEM_NORMAL);
	m_MainMenu->Append(m_Connect);

	wxMenuItem *m_Disconnect;
	m_Disconnect = new wxMenuItem(m_MainMenu, ID_2, wxString(wxT("Disconnect from camera")), wxEmptyString, wxITEM_NORMAL);
	m_MainMenu->Append(m_Disconnect);

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

	camera = cam;

	// Start the timer
	m_timer.SetOwner(this);
	m_timer.Start(TIMERVALUE, true);
	cameraConnected = false;
}
void MainFrame::OnConnect(wxCommandEvent &event)
{
	wxLogMessage("OnConnect");
	if (wxIsMainThread)
		wxLogMessage("MainFrame = running on main thread.");
	else
		wxLogMessage("MainFrame = running on different thread.");

#ifndef WEBCAM
	try
	{

		if (!cameraConnected);
		{

			// Open the camera for accessing the parameters.
			camera->Open();
			camera->TestImageSelector.SetValue(Basler_UniversalCameraParams::TestImageSelectorEnums::TestImageSelector_Off);
			wxLogMessage("GrabOne");
			Pylon::CGrabResultPtr grabResult;
			camera->PixelFormat.SetValue("Mono8");
			camera->GevSCPD.SetValue(10000);
			camera->GainRaw.SetValue(90);
			//wxLogMessage("camera.GevSCPD = %li", camera->GevSCPD.GetValue());
			//camera->GevSCPD.SetValue()
			camera->GrabOne(1000, grabResult);
			//ImageFormatConvertor.Initialize(grabResult->GetPixelType());

			//ImageFormatConvertor.OutputPixelFormat = EPixelType::PixelType_Mono8;
			//ImageFormatConvertor.OutputBitAlignment = "MsbAligned";

			cameraConnected = true;
		}
		wxLogMessage("camera.AcquisitionFrameRate = %s", camera->AcquisitionFrameRate.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.AcquisitionFrameRateEnable = %s", camera->AcquisitionFrameRateEnable.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.AcquisitionMode = %s", camera->AcquisitionMode.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.AcquisitionStart = %s", camera->AcquisitionStart.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.AcquisitionStatus = %s", camera->AcquisitionStatus.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.AcquisitionStatusSelector = %s", camera->AcquisitionStatusSelector.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.AcquisitionStop = %s", camera->AcquisitionStop.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.BinningHorizontal = %s", camera->BinningHorizontal.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.BinningHorizontalMode = %s", camera->BinningHorizontalMode.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.BinningVertical = %s", camera->BinningVertical.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.BinningVerticalMode = %s", camera->BinningVerticalMode.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.BlackLevel = %s", camera->BlackLevel.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.BslCenterX = %s", camera->BslCenterX.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.BslCenterY = %s", camera->BslCenterY.ToStringOrDefault("<not readable>").c_str());
		// wxLogMessage("camera.BslImageCompressionBCBDecompressedImageSize = %s", camera->BslImageCompressionBCBDecompressedImageSize.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.DeviceFirmwareVersion = %s", camera->DeviceFirmwareVersion.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.DeviceLinkThroughputLimit = %s", camera->DeviceLinkThroughputLimit.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.DeviceLinkThroughputLimitMode = %s", camera->DeviceLinkThroughputLimitMode.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.DeviceManufacturerInfo = %s", camera->DeviceManufacturerInfo.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.DeviceModelName = %s", camera->DeviceModelName.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.DeviceTemperatureSelector = %s", camera->DeviceTemperatureSelector.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.DeviceUserID = %s", camera->DeviceUserID.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.DeviceVendorName = %s", camera->DeviceVendorName.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.DeviceVersion = %s", camera->DeviceVersion.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.DigitalShift = %s", camera->DigitalShift.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.ExposureAuto = %s", camera->ExposureAuto.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.ExposureMode = %s", camera->ExposureMode.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.ExposureTime = %s", camera->ExposureTime.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.ExposureTimeAbs = %s", camera->ExposureTimeAbs.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.ExposureTimeBaseAbs = %s", camera->ExposureTimeBaseAbs.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.ExposureTimeRaw = %s", camera->ExposureTimeRaw.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.ForceFailedBuffer = %s", camera->ForceFailedBuffer.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.ForceFailedBufferCount = %s", camera->ForceFailedBufferCount.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.Gain = %s", camera->Gain.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.GainAuto = %s", camera->GainAuto.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.GainRaw = %s", camera->GainRaw.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.Gamma = %s", camera->Gamma.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.GevSCBWR = %s", camera->GevSCBWR.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.GevSCBWRA = %s", camera->GevSCBWRA.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.GevSCFTD = %s", camera->GevSCFTD.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.GevSCPD = %s", camera->GevSCPD.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.GevSCPSPacketSize = %s", camera->GevSCPSPacketSize.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.Height = %s", camera->Height.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.HeightMax = %s", camera->HeightMax.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.ImageFileMode = %s", camera->ImageFileMode.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.ImageFilename = %s", camera->ImageFilename.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.LineInverter = %s", camera->LineInverter.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.LineMode = %s", camera->LineMode.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.LineSelector = %s", camera->LineSelector.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.LineSource = %s", camera->LineSource.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.OffsetX = %s", camera->OffsetX.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.OffsetY = %s", camera->OffsetY.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.PayloadSize = %s", camera->PayloadSize.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.PixelDynamicRangeMax = %s", camera->PixelDynamicRangeMax.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.PixelDynamicRangeMin = %s", camera->PixelDynamicRangeMin.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.PixelFormat = %s", camera->PixelFormat.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.PixelSize = %s", camera->PixelSize.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.ResultingFrameRateAbs = %s", camera->ResultingFrameRateAbs.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.ReverseX = %s", camera->ReverseX.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.ReverseY = %s", camera->ReverseY.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.SensorHeight = %s", camera->SensorHeight.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.SensorWidth = %s", camera->SensorWidth.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.TestImageSelector = %s", camera->TestImageSelector.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.TriggerActivation = %s", camera->TriggerActivation.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.TriggerDelay = %s", camera->TriggerDelay.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.TriggerMode = %s", camera->TriggerMode.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.TriggerSelector = %s", camera->TriggerSelector.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.TriggerSoftware = %s", camera->TriggerSoftware.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.TriggerSource = %s", camera->TriggerSource.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.UserOutputSelector = %s", camera->UserOutputSelector.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.UserOutputValue = %s", camera->UserOutputValue.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.Width = %s", camera->Width.ToStringOrDefault("<not readable>").c_str());
		wxLogMessage("camera.WidthMax = %s", camera->WidthMax.ToStringOrDefault("<not readable>").c_str());

		// Set parameter values
		// camera->Height.TrySetToMaximum();
		// camera->OffsetX.TrySetToMinimum();
		// camera->OffsetY.TrySetToMinimum();
		// camera->Width.TrySetToMaximum();
	}
	catch (const GenericException &e)
	{
		// Error handling.
		wxLogMessage("An exception occurred: %s", e.GetDescription());
	}
#else
	try
	{
		if (!camera->isOpened())
			camera->open(0);
		cameraConnected = true;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	

#endif
}


void MainFrame::OnTimer(wxTimerEvent &event)
{

	if (cameraConnected)
	{


#ifndef WEBCAM
		try
		{
			Pylon::CGrabResultPtr grabResult;
			camera->GrabOne(1000, grabResult);
						wxLogMessage("GrabOne");
			if (grabResult->GrabSucceeded())
			{	CPylonImage ConvertedGrabResult;
				bool rePaintFrame=false;
				int w = grabResult->GetWidth();
				int h = grabResult->GetHeight();
				EPixelType p = grabResult->GetPixelType();
				Output.CheckAndCreateOutputImage(0, grabResult);
				Output.CheckAndCreateOutputImage(1, grabResult);
				Output.CheckAndCreateOutputImage(2, grabResult);
				Output.CheckAndCreateOutputImage(3, grabResult);

				Output.CopyToOutputImage(0, grabResult);
				Output.SetGenericBitmap(0);
	
				HoughLines.ConvertGrabToMat(grabResult);
				HoughLines.CannyEdgeDetection();
				HoughLines.HoughLineDetection();
				HoughLines.HoughCircleDetection();

				Output.CopyToOutputImage(1, HoughLines.EdgeDetectedImage);
				Output.SetGenericBitmap(1);
				Output.CopyToOutputImage(2, HoughLines.HoughLines);
				Output.SetGenericBitmap(2);
				Output.CopyToOutputImage(3, HoughLines.HoughCircles);
				Output.SetGenericBitmap(3);

				if (Output.getRepaintFrame())
					gbSizer1->Layout();
			}
			else
				wxLogMessage("Grab failed!");
		}
		catch (const GenericException &e)
		{
			// Error handling.
			wxLogMessage("An exception occurred: %s", e.GetDescription());
		}

#else
		try
		{
			cv::Mat grabColorResult, grabResult;
			if (camera->read(grabColorResult))
			{	
				wxLogMessage("GrabOne");
				cv::cvtColor(grabColorResult, grabResult, cv::COLOR_BGR2GRAY);
				CPylonImage ConvertedGrabResult;

				Output.CheckAndCreateOutputImage(0, grabResult);
				Output.CheckAndCreateOutputImage(1, grabResult);
				Output.CheckAndCreateOutputImage(2, grabResult);
				Output.CheckAndCreateOutputImage(3, grabResult);

				Output.CopyToOutputImage(0, grabResult);
				Output.SetGenericBitmap(0);
	
				HoughLines.ConvertGrabToMat(grabResult);
				HoughLines.CannyEdgeDetection();
				HoughLines.HoughLineDetection();
				HoughLines.HoughCircleDetection();

				Output.CopyToOutputImage(1, HoughLines.EdgeDetectedImage);
				Output.SetGenericBitmap(1);
				Output.CopyToOutputImage(2, HoughLines.HoughLines);
				Output.SetGenericBitmap(2);
				Output.CopyToOutputImage(3, HoughLines.HoughCircles);
				Output.SetGenericBitmap(3);

				if (Output.getRepaintFrame())
					gbSizer1->Layout();
			}
			else
				wxLogMessage("Grab failed!");
		}
		catch (const GenericException &e)
		{
			// Error handling.
			wxLogMessage("An exception occurred: %s", e.GetDescription());
		}

#endif
	}
	this->Refresh();
	m_timer.Start(TIMERVALUE, true);
}
void MainFrame::OnDisconnect(wxCommandEvent &event)
{
	wxLogMessage("OnDisconnect");
	if (cameraConnected)
	{
#ifndef WEBCAM
		camera->Close();
#else
		camera->release();
#endif
		// ImageFormatConvertor.Uninitialize();
	}
	cameraConnected = false;
}
void MainFrame::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
}

MainFrame::~MainFrame()
{ // delete decompressor;
	wxLog::SetActiveTarget(nullptr);
	delete logger;
}
