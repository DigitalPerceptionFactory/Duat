#include "StructuredBuffer.h"
#include "System.h"


using namespace Duat::Utility;

namespace Duat::Graphics {

	StructuredBuffer::StructuredBuffer(System& gfx, const Utility::HLSL::Layout& layout, bool isDynamic)
	{
		Init(gfx, layout, isDynamic);
	}

	StructuredBuffer::StructuredBuffer(System* pGFX, const Utility::HLSL::Layout& layout, bool isDynamic)
	{
		Init(pGFX, layout, isDynamic);
	}

	void StructuredBuffer::Init(System& gfx, const Utility::HLSL::Layout& layout, bool isDynamic)
	{
		Init(&gfx, layout, isDynamic);
	}

	void StructuredBuffer::Init(System* pGFX, const Utility::HLSL::Layout& layout, bool isDynamic)
	{
		m_pGFX = pGFX;
		HLSL::Buffer::Init(layout);
		m_isDynamic = HLSL::Buffer::IsDynamic() || isDynamic;

		if (HLSL::Buffer::GetRootType() != HLSL::Type::Array) {
			Result result;
			result << "StructuredBuffer layout must have root of Array type.";
			return;
		}

		ZeroMemory(&m_bufferDesc, sizeof(D3D11_BUFFER_DESC));
		m_bufferDesc.ByteWidth = (UINT)GetBufferSize();
		m_bufferDesc.StructureByteStride = HLSL::Buffer::GetArrayStride();
		m_bufferDesc.Usage = m_isDynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
		m_bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		m_bufferDesc.CPUAccessFlags = m_isDynamic ? D3D11_CPU_ACCESS_WRITE : 0;
		m_bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
		subData.pSysMem = GetBuffer();

		m_hresult << pGFX->m_Device->CreateBuffer(&m_bufferDesc, &subData, ReleaseAndGetAddressOf());

		ZeroMemory(&m_srvDesc, sizeof(m_srvDesc));
		m_srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		m_srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		m_srvDesc.BufferEx.FirstElement = 0;
		m_srvDesc.BufferEx.NumElements = GetRootElementCount();

		m_hresult << pGFX->m_Device->CreateShaderResourceView(m_pBuffer.Get(), &m_srvDesc, m_SRV.GetAddressOf());
	}

	void StructuredBuffer::Update()
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

	bool StructuredBuffer::IsDynamic()
	{
		return m_isDynamic;
	}
		
	ID3D11Buffer* StructuredBuffer::Get()
	{
		return m_pBuffer.Get();
	}

	ID3D11Buffer** StructuredBuffer::GetAddressOf()
	{
		return m_pBuffer.GetAddressOf();
	}

	ID3D11Buffer** StructuredBuffer::ReleaseAndGetAddressOf()
	{
		return m_pBuffer.ReleaseAndGetAddressOf();
	}

	ID3D11ShaderResourceView* StructuredBuffer::GetSRV()
	{
		return m_SRV.Get();
	}

	ID3D11ShaderResourceView** StructuredBuffer::GetSRVAddressOf()
	{
		return m_SRV.GetAddressOf();
	}

	ID3D11ShaderResourceView** StructuredBuffer::ReleaseSRVAndGetAddressOf()
	{
		return m_SRV.ReleaseAndGetAddressOf();
	}

}