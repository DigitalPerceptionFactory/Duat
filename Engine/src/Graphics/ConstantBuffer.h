#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <Utility/ErrorHandling.h>
#include <Utility/DirectX.h>


namespace Duat::Graphics {

	struct System;
	struct ConstantBuffer : public Utility::HLSL::Buffer {
		ConstantBuffer() = default;
		ConstantBuffer(System& gfx, const Utility::HLSL::Layout& layout, bool isDynamic = false);
		ConstantBuffer(System* pGFX, const Utility::HLSL::Layout& layout, bool isDynamic = false);
		void Init(System& gfx, const Utility::HLSL::Layout& layout, bool isDynamic = false);
		void Init(System* pGFX, const Utility::HLSL::Layout& layout, bool isDynamic = false);
	
		void Update();

		bool IsDynamic();
		ID3D11Buffer* Get();
		ID3D11Buffer** GetAddressOf();
		ID3D11Buffer** ReleaseAndGetAddressOf();

	private:
		System* m_pGFX;
		Utility::HResult m_hresult;
		bool m_isDynamic;
		D3D11_BUFFER_DESC m_desc;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_pBuffer;
	};

}