#pragma once
#include <wrl.h>
#include <dxgi.h>
#include <d3d11.h>
#include <dcomp.h>
#include <Utility/ErrorHandling.h>
#include <Utility/DirectX.h>


namespace Duat::Graphics {

	struct SwapChain : public Microsoft::WRL::ComPtr<IDXGISwapChain1>
	{
		void Init(HWND handle, DXGI_FORMAT format = DXGI_FORMAT_R16G16B16A16_FLOAT);
		void Present();

		const DXGI_SWAP_CHAIN_DESC1& GetDesc() const;

		ID3D11Texture2D* GetBackBuffer();

		void SetVSync(bool flag);
		void SetRect(UINT width, UINT height);
		void SetFormat(DXGI_FORMAT format);
		void SetUsage(DXGIUsage usage);
		void SetEffect(SwapEffect effect);
		void SetScaling(Scaling scaling);
		void SetFlags(UINT flags);
		void SetBufferCount(UINT count);
		void SetSampleCount(UINT count);
		void SetSampleQuality(UINT quality);
	private:
		bool m_vSync;
		Utility::HResult m_hresult;
		DXGI_SWAP_CHAIN_DESC1 m_desc;
	};

}