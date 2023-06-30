#include "DeviceEx.h"

namespace Duat::Graphics
{
	IDXGIAdapter* DeviceEx::GetAdapter(UINT index)
	{
		return m_adapters[index].Get();
	}

	void DeviceEx::Init()
	{
		m_hresult << CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(m_pWICFactory.GetAddressOf())
		);
		m_hresult << m_pWICFactory->CreateFormatConverter(m_pWICFormatConverter.GetAddressOf());

		m_hresult << D2D1CreateFactory(
			D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_MULTI_THREADED,
			m_pD2D1Factory.GetAddressOf()
		);

		m_hresult << DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory), (IUnknown**)m_pDWriteFactory.GetAddressOf());

		m_hresult << CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, __uuidof(m_pDXGIFactory), (void**)m_pDXGIFactory.GetAddressOf());

		int availableAdapters = 0;
		Microsoft::WRL::ComPtr<IDXGIAdapter> temp_adapter;
		while (SUCCEEDED(m_pDXGIFactory->EnumAdapters(availableAdapters, temp_adapter.GetAddressOf())))
		{
			m_adapters.push_back(temp_adapter);
			temp_adapter.Reset();
			++availableAdapters;
		}

		if (m_adapters.size() < 1)
		{
			Utility::Result result;
			result << "No adapter found.";
		}
		else if (m_adapters.size() > 1)
		{
			std::sort(m_adapters.begin(), m_adapters.end(), [](
				Microsoft::WRL::ComPtr<IDXGIAdapter> a,
				Microsoft::WRL::ComPtr<IDXGIAdapter> b)
				{
					DXGI_ADAPTER_DESC aDesc, bDesc;
					a->GetDesc(&aDesc);
					b->GetDesc(&bDesc);

					if (aDesc.DedicatedVideoMemory > bDesc.DedicatedVideoMemory) return true;
					else return false;
				}
			);
		}
	}

	IDXGIDevice* DeviceEx::AsDXGI()
	{
		static Microsoft::WRL::ComPtr<IDXGIDevice> pDevice;
		static HRESULT whatever = As(&pDevice);
		return pDevice.Get();
	}

	IDXGIFactory2* DeviceEx::DXGI()
	{
		return m_pDXGIFactory.Get();
	}

	ID2D1Factory* DeviceEx::D2D1()
	{
		return m_pD2D1Factory.Get();
	}

	IDWriteFactory* DeviceEx::DWrite()
	{
		return m_pDWriteFactory.Get();
	}

	IWICImagingFactory* DeviceEx::WIC()
	{
		return m_pWICFactory.Get();
	}



}
