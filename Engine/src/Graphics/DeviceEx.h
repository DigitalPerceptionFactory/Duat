#pragma once
#include <vector>
#include <algorithm>
#include <d3d11.h>
#include <dxgi1_3.h>
#include <dxgi.h>
#include <d3d11_2.h>
#include <d2d1.h>
#include <dcomp.h>
#include <dwrite.h>
#include <wincodec.h>
#include <wrl.h>
#include <Utility/ErrorHandling.h>


namespace Duat::Graphics {

	struct DeviceEx : public Microsoft::WRL::ComPtr<ID3D11Device>
	{
		IDXGIAdapter* GetAdapter(UINT index = 0);
		void Init();
		IDXGIDevice* AsDXGI();
		IDXGIFactory2* DXGI();
		ID2D1Factory* D2D1();
		IDWriteFactory* DWrite();
		IWICImagingFactory* WIC();
	private:
		Utility::HResult m_hresult;
		Microsoft::WRL::ComPtr<IDXGIFactory2>         m_pDXGIFactory;
		Microsoft::WRL::ComPtr<ID2D1Factory>          m_pD2D1Factory;
		Microsoft::WRL::ComPtr<IDWriteFactory>        m_pDWriteFactory;
		Microsoft::WRL::ComPtr<IWICImagingFactory>    m_pWICFactory;
		Microsoft::WRL::ComPtr<IWICFormatConverter>   m_pWICFormatConverter;

		std::vector<Microsoft::WRL::ComPtr<IDXGIAdapter>> m_adapters;
	};

}