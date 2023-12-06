#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <Utility/DirectX.h>


namespace Duat::Graphics {

	struct System;
	struct SamplerState : public Microsoft::WRL::ComPtr<ID3D11SamplerState> {
		HRESULT Init(System& gfx,
			Address u = Address::Wrap, Address v = Address::Wrap, Comparison comp = Comparison::LessEqual,
			TextureFiltering filter = Filter::Linear, UINT maxAnisotropy = 16,
			FLOAT minLOD = 0, FLOAT maxLOD = D3D11_FLOAT32_MAX, FLOAT offsetLOD = 0,
			DirectX::XMFLOAT4 borderColor = { 1,0,0,1 });
		HRESULT Init(System& gfx,
			Address u, Address v, Address w, Comparison comp = Comparison::LessEqual,
			TextureFiltering filter = Filter::Linear, UINT maxAnisotropy = 16,
			FLOAT minLOD = 0, FLOAT maxLOD = D3D11_FLOAT32_MAX, FLOAT offsetLOD = 0,
			DirectX::XMFLOAT4 borderColor = { 1,0,0,1 });

		HRESULT Init(System* pGFX,
			Address u = Address::Wrap, Address v = Address::Wrap, Comparison comp = Comparison::LessEqual,
			TextureFiltering filter = Filter::Linear, UINT maxAnisotropy = 16,
			FLOAT minLOD = 0, FLOAT maxLOD = D3D11_FLOAT32_MAX, FLOAT offsetLOD = 0,
			DirectX::XMFLOAT4 borderColor = { 1,0,0,1 });
		HRESULT Init(System* pGFX,
			Address u, Address v, Address w, Comparison comp = Comparison::LessEqual,
			TextureFiltering filter = Filter::Linear, UINT maxAnisotropy = 16,
			FLOAT minLOD = 0, FLOAT maxLOD = D3D11_FLOAT32_MAX, FLOAT offsetLOD = 0,
			DirectX::XMFLOAT4 borderColor = { 1,0,0,1 });
		HRESULT Update();

		Address GetAddressU();
		Address GetAddressV();
		Address GetAddressW();
		Comparison GetComparison();
		FLOAT GetOffsetLOD();
		FLOAT GetMinLOD();
		FLOAT GetMaxLOD();
		D3D11_FILTER GetFilter();
		UINT GetMaxAnisotropy();
		DirectX::XMFLOAT4 GetBorderColor();

		void SetAddressU(Address u);
		void SetAddressV(Address v);
		void SetAddressW(Address w);
		void SetComparison(Comparison comp);
		void SetOffsetLOD(FLOAT offsetLOD);
		void SetMinLOD(FLOAT minLOD);
		void SetMaxLOD(FLOAT maxLOD);
		void SetFilter(D3D11_FILTER filter);
		void SetFilter(TextureFiltering filter);
		void SetMaxAnisotropy(UINT maxAnisotropy);
		void SetBorderColor(DirectX::XMFLOAT4 borderColor);

	private:
		System* m_pGFX;
		D3D11_SAMPLER_DESC desc;
	};

}