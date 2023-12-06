#include <wx/generic/statbmpg.h>
#include <wx/rawbmp.h>
#include <wx/wx.h>
// Include files to use the pylon API.
#include <pylon/PylonIncludes.h>
#ifdef PYLON_WIN_BUILD
#    include <pylon/PylonGUI.h>
#endif



class OutputCamImages
{
    public:
        void Initialize(wxFrame* MainFrame);
        void CheckAndCreateOutputImage(int ImgNr, Pylon::CGrabResultPtr ptrGrabResult);
        //void CheckAndCreateOutputImage(int ImgNr, cv::InputArray CalculatedResult);
        
        void CopyToOutputImage(int ImgNr, Pylon::CGrabResultPtr ptrGrabResult);
        //void CopyToOutputImage(int ImgNr, cv::InputArray CalculatedResult);

        void SetGenericBitmap(int ImgNr);
        bool getRepaintFrame();
        wxBitmap* getBitmap(int ImgNr);
        wxGenericStaticBitmap* getGenBitmap(int ImgNr);
        
        ~OutputCamImages();
        const int MAX_OUTPUT_IMAGES=8;

    private:
    	wxBitmap *m_bitmap[8];
        wxGenericStaticBitmap *m_genBitmap[8];
        bool rePaintFrame;
};