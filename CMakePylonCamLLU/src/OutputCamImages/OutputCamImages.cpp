#include "OutputCamImages.h"

void OutputCamImages::Initialize(wxFrame* MainFrame)
{
    wxSize bitmapSize(100,100); //(512, 384);
	wxBitmap* bm = new wxBitmap(bitmapSize, 24);
    for (int i=0; i<MAX_OUTPUT_IMAGES; i++)
	    m_genBitmap[i] = new wxGenericStaticBitmap(MainFrame, wxID_ANY, *bm, wxDefaultPosition, wxDefaultSize, 0);

    for (int i = 0; i < MAX_OUTPUT_IMAGES; i++)
        m_bitmap[i] = nullptr;
}

void OutputCamImages::CheckAndCreateOutputImage(int ImgNr, Pylon::CGrabResultPtr ptrGrabResult)
{   rePaintFrame=false;
    if (ImgNr >= 0 && ImgNr < MAX_OUTPUT_IMAGES)
    {
            int w = ptrGrabResult->GetWidth();
            int h = ptrGrabResult->GetHeight();

 
            if (m_bitmap[ImgNr] == nullptr)
	        {	m_bitmap[ImgNr] = new wxBitmap(w/4, h/4, 24);
		        rePaintFrame = true;
	        }


			if ((m_bitmap[ImgNr]->GetWidth()*4 != w) || (m_bitmap[ImgNr]->GetHeight()*4 != h))
			{
			    delete m_bitmap[ImgNr];
				m_bitmap[ImgNr] = new wxBitmap(w/4, h/4, 24);
				rePaintFrame = true;
			}
    }
}



typedef wxNativePixelData PixelData;
void OutputCamImages::CopyToOutputImage(int ImgNr, Pylon::CGrabResultPtr ptrGrabResult)
{
    if (ImgNr >= 0 && ImgNr < MAX_OUTPUT_IMAGES)
        if (m_bitmap[ImgNr] != nullptr)
        {
            int w = ptrGrabResult->GetWidth();
            int h = ptrGrabResult->GetHeight();

            PixelData bmdata(*m_bitmap[ImgNr]);
            //wxLogMessage("Value of m_bitmap, value:%i", (bool)bmdata);
            if (!bmdata)
                return;

            // use raw bitmap access to write MONO8 data directly into the bitmap
            const uint8_t *pImageBuffer = (uint8_t *)ptrGrabResult->GetBuffer();
            PixelData::Iterator dst(bmdata);

            for (int y = 0; y < h; y += 4)
            {
                for (int x = 0; x < w; x += 4)
                {
                    dst.MoveTo(bmdata, x / 4, y / 4);
                    uint8_t grayValue = (uint8_t)pImageBuffer[x + y * w];
                    dst.Blue() = grayValue;
                    dst.Green() = grayValue;
                    dst.Red() = grayValue;
                }
            }
        }
}
void OutputCamImages::SetGenericBitmap(int ImgNr)
{
        if (ImgNr >= 0 && ImgNr < MAX_OUTPUT_IMAGES)
            if (rePaintFrame)
                m_genBitmap[ImgNr]->SetBitmap(*m_bitmap[ImgNr]);
}
wxBitmap* OutputCamImages::getBitmap(int ImgNr)
{    if (ImgNr >= 0 && ImgNr < MAX_OUTPUT_IMAGES)
        return m_bitmap[ImgNr];
    else
        return nullptr;
}
wxGenericStaticBitmap* OutputCamImages::getGenBitmap(int ImgNr)
{    if (ImgNr >= 0 && ImgNr < MAX_OUTPUT_IMAGES)
        return m_genBitmap[ImgNr];
    else
        return nullptr;
}
bool OutputCamImages::getRepaintFrame()
{    return rePaintFrame;
}
OutputCamImages::~OutputCamImages()
{   for (int i = 0; i < MAX_OUTPUT_IMAGES; i++)
    {  delete m_bitmap[i];
    }
}

