#include "SwapChain.h"

namespace Duat::Graphics {

	void SwapChain::Init(HWND handle, DXGI_FORMAT format)
	{
		m_vSync = false;
		RECT rect;
		GetClientRect(handle, &rect);

		ZeroMemory(&m_desc, sizeof(DXGI_SWAP_CHAIN_DESC1));
		m_desc.Width = (UINT)(rect.right - rect.left);
		m_desc.Height = (UINT)(rect.bottom - rect.top);
		m_desc.Format = format;
		m_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		m_desc.BufferCount = 2;
		m_desc.SampleDesc.Count = 1;
		m_desc.SampleDesc.Quality = 0;
		m_desc.Scaling = DXGI_SCALING_STRETCH;
		m_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
		m_desc.AlphaMode = DXGI_ALPHA_MODE_PREMULTIPLIED;
	}

	void SwapChain::Present()
	{
		Get()->Present(m_vSync ? 1 : 0, 0);
	}

	const DXGI_SWAP_CHAIN_DESC1& SwapChain::GetDesc() const
	{
		return m_desc;
	}
		
	ID3D11Texture2D* SwapChain::GetBackBuffer()
	{
		ID3D11Texture2D* pBackBuffer = nullptr;
		m_hresult << Get()->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)(&pBackBuffer));
		return pBackBuffer;
	}
	
	void SwapChain::SetVSync(bool flag)
	{
		m_vSync = flag;
	}

	void SwapChain::SetRect(UINT width, UINT height)
	{
		if (width > 0) m_desc.Width = width;
		if (height > 0) m_desc.Height = height;
	}
		
	void SwapChain::SetFormat(DXGI_FORMAT format)
	{
		m_desc.Format = format;
	}
		
	void SwapChain::SetUsage(DXGIUsage usage)
	{
		m_desc.BufferUsage = DXGI_USAGE(usage);
	}

	void SwapChain::SetEffect(SwapEffect effect)
	{
		m_desc.SwapEffect = DXGI_SWAP_EFFECT(effect);
	}

	void SwapChain::SetScaling(Scaling scaling)
	{
		m_desc.Scaling = DXGI_SCALING(scaling);
	}

	void SwapChain::SetFlags(UINT flags)
	{
		m_desc.Flags = flags;
	}
		
	void SwapChain::SetBufferCount(UINT count)
	{
		m_desc.BufferCount = count;
	}

	void SwapChain::SetSampleCount(UINT count)
	{
		m_desc.SampleDesc.Count = count;
	}

	void SwapChain::SetSampleQuality(UINT quality)
	{
		m_desc.SampleDesc.Quality = quality;
	}

}