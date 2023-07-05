#pragma once
#include "SwapChain.h"
#include "RenderTarget.h"


namespace Duat::Graphics {

	struct ContextEx : public Microsoft::WRL::ComPtr<ID3D11DeviceContext>
	{
		void Init(HWND handle);
		void Present();
		void ClearRT(RenderTarget& rt);
		void ClearRT(RenderTarget& rt, DirectX::XMFLOAT4& color);
		void SetClearColor(float r, float g, float b, float a);
		void SetClearColor(DirectX::XMFLOAT4& color);

		ID3D11Texture2D* GetBackBuffer();
		IDXGISwapChain1* GetSwapChain();
		IDXGISwapChain1** GetSwapChainAddressOf();
		const DXGI_SWAP_CHAIN_DESC1& GetSwapChainDesc() const;
	private:
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_swapChainRTV;
		SwapChain m_swapChain;
		float m_clearColor[4];
	};

}