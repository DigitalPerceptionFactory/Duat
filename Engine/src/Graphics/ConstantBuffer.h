#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <Utility/ErrorHandling.h>
#include <Utility/DirectX.h>


namespace Duat::Graphics {

	struct System;
	struct ConstantBuffer : public Utility::HLSL::Buffer {
		ConstantBuffer(System& gfx, const Utility::HLSL::Layout& layout,
			Usage usage = Usage::Default, Access cpuAccess = Access::None);
		ConstantBuffer(System* pGFX, const Utility::HLSL::Layout& layout,
			Usage usage = Usage::Default, Access cpuAccess = Access::None);
		void Init(System& gfx, const Utility::HLSL::Layout& layout,
			Usage usage = Usage::Default, Access cpuAccess = Access::None);
		void Init(System* pGFX, const Utility::HLSL::Layout& layout,
			Usage usage = Usage::Default, Access cpuAccess = Access::None);
	
		ID3D11Buffer* Get();
		ID3D11Buffer** GetAddressOf();
		ID3D11Buffer** ReleaseAndGetAddressOf();

		bool IsDynamic() const;
	private:
		Utility::HResult m_hresult;
		bool is_dynamic;
		D3D11_BUFFER_DESC m_desc;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_pConstantBuffer;
	};

}