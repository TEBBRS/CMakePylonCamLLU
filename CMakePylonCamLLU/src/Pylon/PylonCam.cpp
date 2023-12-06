#include "PylonCam.h"


Camera::Camera()
{
    try
    {
        // Before using any pylon methods, the pylon runtime must be initialized.
        Pylon::PylonInitialize();
        // Create an instant camera object with the first found camera device.
        camera = new Pylon::CBaslerUniversalInstantCamera(Pylon::CTlFactory::GetInstance().CreateFirstDevice());

        // Print the model name of the camera.
        //wxLogMessage("Using device %s", camera->GetDeviceInfo().GetModelName());
        cameraFoundAndInitialised = true;
    }
    catch (const Pylon::GenericException& e)
    {
        // Error handling.
        //wxLogMessage ("An exception occurred: %s", e.GetDescription());
        cameraFoundAndInitialised = false;
    }
	cameraConnected = false;
}
void Camera::Open()
{
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
			camera->GrabOne(1000, grabResult);

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
		
	}
	catch (const Pylon::GenericException& e)
	{
		// Error handling.
		//wxLogMessage("An exception occurred: %s", e.GetDescription());
	}

}
Pylon::CGrabResultPtr Camera::GrabOne()
{
	try
	{

		camera->GrabOne(1000, grabResult);
		return grabResult;
	}
	catch (const Pylon::GenericException& e)
	{
		// Error handling.
		//wxLogMessage("An exception occurred: %s", e.GetDescription());
		return empty;
	}

}
void Camera::Disconnect()
{
	if (cameraConnected)
	{
		camera->Close();
		cameraConnected = false;
	}
	

}
bool Camera::Connected()
{
	return cameraConnected;
}
Camera::~Camera()
{
    // When exited release all resources
    Pylon::PylonTerminate();
}