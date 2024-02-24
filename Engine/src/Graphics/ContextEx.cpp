#include "ContextEx.h"


namespace Duat::Graphics {

	void ContextEx::Init(HWND handle, DXGI_FORMAT format)
	{
		m_swapChain.Init(handle, format);
	}

	void ContextEx::Present()
	{
		m_swapChain.Present();
	}

	/*void ContextEx::ClearRT(RenderTarget& rt)
	{
		(*this)->ClearRenderTargetView(rt.GetTarget().GetRTV(), m_clearColor);
		(*this)->ClearDepthStencilView(rt.GetDepth().GetDSV(), 
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	void ContextEx::ClearRT(RenderTarget& rt, DirectX::XMFLOAT4& color, float depthValue, unsigned int stencilValue)
	{
		float clearColor[4];
		std::memcpy(clearColor, &color, sizeof(float) * 4);
		(*this)->ClearRenderTargetView(rt.GetTarget().GetRTV(), clearColor);
		(*this)->ClearDepthStencilView(rt.GetDepth().GetDSV(),
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depthValue, stencilValue);
	}

	void ContextEx::ClearRT(RenderTarget& rt, float depthValue, unsigned int stencilValue)
	{
		(*this)->ClearRenderTargetView(rt.GetTarget().GetRTV(), m_clearColor);
		(*this)->ClearDepthStencilView(rt.GetDepth().GetDSV(),
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depthValue, stencilValue);
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
	}*/
		
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