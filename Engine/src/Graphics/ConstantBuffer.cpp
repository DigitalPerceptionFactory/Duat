#include "ConstantBuffer.h"
#include "System.h"


using namespace Duat::Utility;

namespace Duat::Graphics {

	ConstantBuffer::ConstantBuffer(System& gfx, const Utility::HLSL::Layout& layout, bool isDynamic)
	{
		Init(gfx, layout, isDynamic);
	}

	ConstantBuffer::ConstantBuffer(System* pGFX, const Utility::HLSL::Layout& layout, bool isDynamic)
	{
		Init(pGFX, layout, isDynamic);
	}

	void ConstantBuffer::Init(System& gfx, const Utility::HLSL::Layout& layout, bool isDynamic)
	{
		Init(&gfx, layout, isDynamic);
	}

	void ConstantBuffer::Init(System* pGFX, const Utility::HLSL::Layout& layout, bool isDynamic)
	{
		m_pGFX = pGFX;
		HLSL::Buffer::Init(layout);
		m_isDynamic = HLSL::Buffer::IsDynamic() || isDynamic;

		ZeroMemory(&m_desc, sizeof(D3D11_BUFFER_DESC));
		m_desc.ByteWidth = (UINT)GetBufferSize();
		m_desc.Usage = m_isDynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
		m_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		m_desc.CPUAccessFlags = m_isDynamic ? D3D11_CPU_ACCESS_WRITE : 0;

		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
		subData.pSysMem = GetBuffer();

		m_hresult << pGFX->m_Device->CreateBuffer(&m_desc, &subData, ReleaseAndGetAddressOf());
	}

	void ConstantBuffer::Update()
	{
		if (m_isDynamic)
		{
			HLSL::Buffer::Update();
			D3D11_MAPPED_SUBRESOURCE mapped;
			m_hresult << m_pGFX->m_Context->Map(Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
			std::memcpy(mapped.pData, GetBuffer(), GetBufferSize());
			m_pGFX->m_Context->Unmap(Get(), 0);
		}
	}

	bool ConstantBuffer::IsDynamic()
	{
		return m_isDynamic;
	}
		
	ID3D11Buffer* ConstantBuffer::Get()
	{
		return m_pBuffer.Get();
	}

	ID3D11Buffer** ConstantBuffer::GetAddressOf()
	{
		return m_pBuffer.GetAddressOf();
	}

	ID3D11Buffer** ConstantBuffer::ReleaseAndGetAddressOf()
	{
		return m_pBuffer.ReleaseAndGetAddressOf();
	}

}