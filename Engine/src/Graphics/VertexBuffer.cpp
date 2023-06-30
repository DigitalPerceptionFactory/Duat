#include "VertexBuffer.h"
#include "System.h"


namespace Duat::Graphics {

	VertexBuffer::VertexBuffer(System& gfx, const Utility::HLSL::Layout& layout, Usage usage, Access cpuAccess)
	{
		Init(gfx, layout, usage, cpuAccess);
	}

	VertexBuffer::VertexBuffer(System* pGFX, const Utility::HLSL::Layout& layout, Usage usage, Access cpuAccess)
	{
		Init(pGFX, layout, usage, cpuAccess);
	}

	void VertexBuffer::Init(System& gfx, const Utility::HLSL::Layout& layout, Usage usage, Access cpuAccess)
	{
		Init(&gfx, layout, usage, cpuAccess);
	}

	void VertexBuffer::Init(System* pGFX, const Utility::HLSL::Layout& layout, Usage usage, Access cpuAccess)
	{
		Utility::HLSL::Buffer::Init(layout);

		m_stride = GetRoot()[1].GetOffset();

		if (usage == Usage::Dynamic) is_dynamic = true;
		else is_dynamic = false;

		Utility::HLSL::Buffer::Init(layout);
		ZeroMemory(&m_desc, sizeof(D3D11_BUFFER_DESC));
		m_desc.ByteWidth = (UINT)GetBufferSize();
		m_desc.Usage = D3D11_USAGE(usage);
		m_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		m_desc.CPUAccessFlags = (UINT)cpuAccess;

		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(subData));
		subData.pSysMem = GetBuffer();

		m_hresult << pGFX->m_Device->CreateBuffer(&m_desc, &subData, ReleaseAndGetAddressOf());
	}

	void VertexBuffer::TestInit(System* pGFX, void* pBuffer, size_t bufferSize)
	{
		m_stride = sizeof(Geometry::Vertex);
		ZeroMemory(&m_desc, sizeof(D3D11_BUFFER_DESC));
		m_desc.ByteWidth = (UINT)(bufferSize * sizeof(Geometry::Vertex));
		m_desc.Usage = D3D11_USAGE_DEFAULT;
		m_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		m_desc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(subData));
		subData.pSysMem = pBuffer;

		m_hresult << pGFX->m_Device->CreateBuffer(&m_desc, &subData, ReleaseAndGetAddressOf());
	}

	const UINT& VertexBuffer::GetStride() const
	{
		return m_stride;
	}

	ID3D11Buffer* VertexBuffer::Get()
	{
		return m_pVertexBuffer.Get();
	}

	ID3D11Buffer** VertexBuffer::GetAddressOf()
	{
		return m_pVertexBuffer.GetAddressOf();
	}

	ID3D11Buffer** VertexBuffer::ReleaseAndGetAddressOf()
	{
		return m_pVertexBuffer.ReleaseAndGetAddressOf();
	}

}