#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <Utility/ErrorHandling.h>
#include <Utility/DirectX.h>


namespace Duat::Graphics {

	struct System;
	struct StructuredBuffer : public Utility::HLSL::Buffer {
		StructuredBuffer() = default;
		StructuredBuffer(System& gfx, const Utility::HLSL::Layout& layout, bool isDynamic = false);
		StructuredBuffer(System* pGFX, const Utility::HLSL::Layout& layout, bool isDynamic = false);
		void Init(System& gfx, const Utility::HLSL::Layout& layout, bool isDynamic = false);
		void Init(System* pGFX, const Utility::HLSL::Layout& layout, bool isDynamic = false);
	
		void Update();

		bool IsDynamic();
		ID3D11Buffer* Get();
		ID3D11Buffer** GetAddressOf();
		ID3D11Buffer** ReleaseAndGetAddressOf();
		ID3D11ShaderResourceView* GetSRV();
		ID3D11ShaderResourceView** GetSRVAddressOf();
		ID3D11ShaderResourceView** ReleaseSRVAndGetAddressOf();

	private:
		System* m_pGFX;
		Utility::HResult m_hresult;
		bool m_isDynamic;
		D3D11_BUFFER_DESC m_bufferDesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC m_srvDesc;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_pBuffer;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_SRV;
	};

}