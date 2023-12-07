#include "ItCGrabResulPtr.h"
ItCGrabResultPtr::ItCGrabResultPtr(Pylon::CGrabResultPtr ptr)
{
	grabResult = ptr;
}
ItCGrabResultPtr::Iterator ItCGrabResultPtr::begin()
{
	uint8_t* pImageBuffer = (uint8_t*)grabResult->GetBuffer();
	return Iterator(&pImageBuffer[0]);
}
ItCGrabResultPtr::Iterator ItCGrabResultPtr::end()
{
	uint8_t* pImageBuffer = (uint8_t*)grabResult->GetBuffer();
	return Iterator(&pImageBuffer[grabResult->GetWidth()*grabResult->GetHeight()]);
}
