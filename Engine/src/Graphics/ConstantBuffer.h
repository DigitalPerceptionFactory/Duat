#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <Utility/ErrorHandling.h>
#include <Utility/DirectX.h>


namespace Duat::Graphics {

	struct System;
	struct ConstantBuffer : public Utility::HLSL::Buffer {
		ConstantBuffer() = default;
		ConstantBuffer(System& gfx, const Utility::HLSL::Layout& layout);
		ConstantBuffer(System* pGFX, const Utility::HLSL::Layout& layout);
		void Init(System& gfx, const Utility::HLSL::Layout& layout);
		void Init(System* pGFX, const Utility::HLSL::Layout& layout);
	
		void Update();

		ID3D11Buffer* Get();
		ID3D11Buffer** GetAddressOf();
		ID3D11Buffer** ReleaseAndGetAddressOf();

	private:
		System* m_pGFX;
		Utility::HResult m_hresult;
		D3D11_BUFFER_DESC m_desc;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_pConstantBuffer;
	};

}