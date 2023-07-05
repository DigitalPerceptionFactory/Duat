#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <Utility/DirectX.h>


namespace Duat::Graphics {

	struct System;
	struct BlendState : public Microsoft::WRL::ComPtr<ID3D11BlendState> {
		HRESULT Init(System& gfx,
			bool blendEnable = true, Blend srcBlend = Blend::SrcAlpha, Blend destBlend = Blend::InvSrcAlpha,
			BlendOp blendOp = BlendOp::Add,
			Blend srcBlendAlpha = Blend::One, Blend destBlendAlpha = Blend::One,
			BlendOp blendOpAlpha = BlendOp::Add,
			ColorWriteMask mask = ColorWriteMask::EnableAll);
		HRESULT Init(System* pGFX,
			bool blendEnable = true, Blend srcBlend = Blend::SrcAlpha, Blend destBlend = Blend::InvSrcAlpha,
			BlendOp blendOp = BlendOp::Add,
			Blend srcBlendAlpha = Blend::One, Blend destBlendAlpha = Blend::One,
			BlendOp blendOpAlpha = BlendOp::Add,
			ColorWriteMask mask = ColorWriteMask::EnableAll);
		HRESULT Update();

		bool IsBlendEnabled();
		Blend GetSrcBlend();
		Blend GetDestBlend();
		BlendOp GetBlendOp();
		Blend GetSrcAlphaBlend();
		Blend GetDestAlphaBlend();
		BlendOp GetAlphaOp();
		ColorWriteMask GetMask();

		void SetBlendEnabled(bool flag);
		void SetSrcBlend(Blend blend);
		void SetDestBlend(Blend blend);
		void SetBlendOp(BlendOp blendOp);
		void SetSrcAlphaBlend(Blend blend);
		void SetDestAlphaBlend(Blend blend);
		void SetAlphaOp(BlendOp blendOp);
		void SetMask(ColorWriteMask mask);

	private:
		System* m_pGFX;
		D3D11_RENDER_TARGET_BLEND_DESC m_desc;
	};

}