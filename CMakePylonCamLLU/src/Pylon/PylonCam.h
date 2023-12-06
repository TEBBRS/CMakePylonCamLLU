// Include files to use the pylon API.
#include <pylon/PylonIncludes.h>
#include <pylon/BaslerUniversalInstantCamera.h>
#ifdef PYLON_WIN_BUILD
	#include <pylon/PylonGUI.h>
#endif

#include <wx/log.h>
class Camera
{
	public:
		Camera();
		void Open();
		void Disconnect();
		Pylon::CGrabResultPtr GrabOne();
		bool Connected();
		~Camera();
	private:
		Pylon::CBaslerUniversalInstantCamera* camera;
		Pylon::CGrabResultPtr grabResult;
		Pylon::CGrabResultPtr empty;
		bool cameraFoundAndInitialised;
		bool cameraConnected;
};