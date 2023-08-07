#pragma once
#include <dxgi.h>
#include <wincodec.h>
#include <string>


namespace Duat {

    struct PixelFormatInfo
    {
        UINT bitsPerPixel;
        UINT channelCount;
        UINT redMask;
        UINT greenMask;
        UINT blueMask;
        UINT alphaMask;
        BOOL isAlphaPremultiplied;
        BOOL isNumericRepresentation;
        std::string name;
    };

    PixelFormatInfo GetPixelFormatInfo(IWICImagingFactory* pFactory, DXGI_FORMAT format);

}