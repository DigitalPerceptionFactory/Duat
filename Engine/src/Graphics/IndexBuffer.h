#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <Utility/ErrorHandling.h>
#include <Utility/DirectX.h>


namespace Duat::Graphics {

	struct System;
	struct IndexBuffer : public Utility::HLSL::Buffer {
		IndexBuffer() = default;
		IndexBuffer(System& gfx, const Utility::HLSL::Layout& layout,
			Usage usage = Usage::Default, Access cpuAccess = Access::None);
		IndexBuffer(System* pGFX, const Utility::HLSL::Layout& layout,
			Usage usage = Usage::Default, Access cpuAccess = Access::None);
		void Init(System& gfx, const Utility::HLSL::Layout& layout,
			Usage usage = Usage::Default, Access cpuAccess = Access::None);
		void Init(System* pGFX, const Utility::HLSL::Layout& layout,
			Usage usage = Usage::Default, Access cpuAccess = Access::None);

		void TestInit(System* pGFX, void* pBuffer, size_t bufferSize);

		size_t GetIndexCount();
		ID3D11Buffer* Get();
		ID3D11Buffer** GetAddressOf();
		ID3D11Buffer** ReleaseAndGetAddressOf();

		bool IsDynamic() const;
	private:
		Utility::HResult m_hresult;
		bool is_dynamic;
		size_t m_indexCount;
		D3D11_BUFFER_DESC m_desc;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer;
	};

}