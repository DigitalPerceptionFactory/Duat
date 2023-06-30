#include "ContextEx.h"


namespace Duat::Graphics {

	void ContextEx::Init(HWND handle)
	{
		m_swapChain.Init(handle);
	}

	void ContextEx::Present()
	{
		m_swapChain.Present();
	}

	void ContextEx::ClearRTV(RenderTarget& rt)
	{
		(*this)->ClearRenderTargetView(rt.GetRTV(), m_clearColor);
	}

	void ContextEx::ClearRTV(RenderTarget& rt, DirectX::XMFLOAT4& color)
	{
		float clearColor[4];
		std::memcpy(clearColor, &color, sizeof(float) * 4);
		(*this)->ClearRenderTargetView(rt.GetRTV(), clearColor);
	}

	void ContextEx::SetClearColor(float r, float g, float b, float a)
	{
		m_clearColor[0] = r * a;
		m_clearColor[1] = g * a;
		m_clearColor[2] = b * a;
		m_clearColor[3] = a;
	}

	void ContextEx::SetClearColor(DirectX::XMFLOAT4& color)
	{
		std::memcpy(m_clearColor, &color, sizeof(float) * 4);
		m_clearColor[0] *= color.w;
		m_clearColor[1] *= color.w;
		m_clearColor[2] *= color.w;
	}
		
	ID3D11Texture2D* ContextEx::GetBackBuffer()
	{
		return m_swapChain.GetBackBuffer();
	}

	IDXGISwapChain1* ContextEx::GetSwapChain()
	{
		return m_swapChain.Get();
	}

	IDXGISwapChain1** ContextEx::GetSwapChainAddressOf()
	{
		return m_swapChain.GetAddressOf();
	}

	const DXGI_SWAP_CHAIN_DESC1& ContextEx::GetSwapChainDesc() const
	{
		return m_swapChain.GetDesc();
	}

}