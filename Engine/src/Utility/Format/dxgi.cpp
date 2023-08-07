#include "dxgi.h"
#include "String.h"
#include "../ErrorHandling.h"


namespace Duat {

	PixelFormatInfo GetPixelFormatInfo(IWICImagingFactory* pFactory, DXGI_FORMAT format)
	{
		Utility::Result result;
		result << "Function not implemented yet.";

		Utility::HResult hr;
		PixelFormatInfo out;
		return out;
		//IWICPixelFormatInfo* pFormatInfo;
		//IWICComponentInfo* pComponentInfo;
		//hr << pFactory->CreateComponentInfo(format, &pComponentInfo);
		//pComponentInfo->QueryInterface(&pPixelFormatInfo);
	}

}