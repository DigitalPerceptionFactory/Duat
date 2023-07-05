#include "IndexBuffer.h"
#include "System.h"


namespace Duat::Graphics {

	IndexBuffer::IndexBuffer(System& gfx, const Utility::HLSL::Layout& layout, Usage usage, Access cpuAccess)
	{
		Init(gfx, layout, usage, cpuAccess);
	}

	IndexBuffer::IndexBuffer(System* pGFX, const Utility::HLSL::Layout& layout, Usage usage, Access cpuAccess)
	{
		Init(pGFX, layout, usage, cpuAccess);
	}

	void IndexBuffer::Init(System& gfx, const Utility::HLSL::Layout& layout, Usage usage, Access cpuAccess)
	{
		Init(&gfx, layout, usage, cpuAccess);
	}

	void IndexBuffer::Init(System* pGFX, const Utility::HLSL::Layout& layout, Usage usage, Access cpuAccess)
	{
		Utility::HLSL::Buffer::Init(layout);

		if (usage == Usage::Dynamic) is_dynamic = true;
		else is_dynamic = false;

		ZeroMemory(&m_desc, sizeof(D3D11_BUFFER_DESC));
		m_desc.ByteWidth = (UINT)GetBufferSize();
		m_desc.Usage = D3D11_USAGE(usage);
		m_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		m_desc.CPUAccessFlags = (UINT)cpuAccess;

		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
		subData.pSysMem = GetBuffer();

		m_indexCount = std::get<Utility::HLSL::Struct>(GetRoot().GetValue()).elements.size();;
		m_hresult << pGFX->m_Device->CreateBuffer(&m_desc, &subData, ReleaseAndGetAddressOf());
	}

	void IndexBuffer::TestInit(System* pGFX, void* pBuffer, size_t bufferSize)
	{
		ZeroMemory(&m_desc, sizeof(D3D11_BUFFER_DESC));
		m_desc.ByteWidth = (UINT)(bufferSize * sizeof(unsigned int));
		m_desc.Usage = D3D11_USAGE_DEFAULT;
		m_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		m_desc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
		subData.pSysMem = pBuffer;

		m_indexCount = bufferSize;
		m_hresult << pGFX->m_Device->CreateBuffer(&m_desc, &subData, ReleaseAndGetAddressOf());
	}

	size_t IndexBuffer::GetIndexCount()
	{
		return m_indexCount;
		//return std::get<Utility::HLSL::Struct>(GetRoot().GetValue()).elements.size();
	}

	ID3D11Buffer* IndexBuffer::Get()
	{
		return m_pIndexBuffer.Get();
	}

	ID3D11Buffer** IndexBuffer::GetAddressOf()
	{
		return m_pIndexBuffer.GetAddressOf();
	}

	ID3D11Buffer** IndexBuffer::ReleaseAndGetAddressOf()
	{
		return m_pIndexBuffer.ReleaseAndGetAddressOf();
	}

	bool IndexBuffer::IsDynamic() const
	{
		return is_dynamic;
	}

}