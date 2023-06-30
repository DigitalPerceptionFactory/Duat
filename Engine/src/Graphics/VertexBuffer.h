#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <Utility/ErrorHandling.h>
#include <Utility/DirectX.h>


namespace Duat::Graphics {

	struct System;
	struct VertexBuffer : public Utility::HLSL::Buffer {
		VertexBuffer() = default;
		VertexBuffer(System&  gfx, const Utility::HLSL::Layout& layout,
			Usage usage = Usage::Default, Access cpuAccess = Access::None);
		VertexBuffer(System*  pGFX, const Utility::HLSL::Layout& layout,
			Usage usage = Usage::Default, Access cpuAccess = Access::None);
		void Init(System& gfx, const Utility::HLSL::Layout& layout,
			Usage usage = Usage::Default, Access cpuAccess = Access::None);
		void Init(System* pGFX, const Utility::HLSL::Layout& layout,
			Usage usage = Usage::Default, Access cpuAccess = Access::None);
		
		void TestInit(System* pGFX, void* pBuffer, size_t bufferSize);

		const UINT& GetStride() const;
		ID3D11Buffer* Get();
		ID3D11Buffer** GetAddressOf();
		ID3D11Buffer** ReleaseAndGetAddressOf();
	private:
		Utility::HResult m_hresult;
		bool is_dynamic;
		UINT m_stride;
		D3D11_BUFFER_DESC m_desc;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_pVertexBuffer;
	};

}