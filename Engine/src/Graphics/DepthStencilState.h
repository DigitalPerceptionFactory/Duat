#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <Utility/DirectX.h>


namespace Duat::Graphics {

	struct System;
	struct DepthStencilState : Microsoft::WRL::ComPtr<ID3D11DepthStencilState>, public Stencil {
		HRESULT Init(System& gfx,
			bool depthEnabled = true, DepthWriteMask depthWriteMask = DepthWriteMask::All, Comparison comp = Comparison::LessEqual,
			bool stencilEnabled = false, Stencil stencil = Stencil());
		HRESULT Init(System* pGFX,
			bool depthEnabled = true, DepthWriteMask depthWriteMask = DepthWriteMask::All, Comparison comp = Comparison::LessEqual,
			bool stencilEnabled = false, Stencil stencil = Stencil());
		HRESULT Update();

		bool GetDepthEnabled();
		DepthWriteMask GetDepthWriteMask(DepthWriteMask mask);
		Comparison GetDepthComparison(Comparison comp);
		bool GetStencilEnabled(bool flag);

		void SetDepthEnabled(bool flag);
		void SetDepthWriteMask(DepthWriteMask mask);
		void SetDepthComparison(Comparison comp);
		void SetStencilEnabled(bool flag);
		void SetFrontFail(StencilOp op);
		void SetFrontDepthFail(StencilOp op);
		void SetFrontPass(StencilOp op);
		void SetFrontComparison(Comparison comp);
		void SetBackFail(StencilOp op);
		void SetBackDepthFail(StencilOp op);
		void SetBackPass(StencilOp op);
		void SetBackComparison(Comparison comp);
		void SetWriteMask(UINT8 mask);
		void SetReadMask(UINT8 mask);

	private:
		System* m_pGFX;
		D3D11_DEPTH_STENCIL_DESC m_desc;
	};

}