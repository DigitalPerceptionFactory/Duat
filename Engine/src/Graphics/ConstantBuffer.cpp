#include "ConstantBuffer.h"
#include "System.h"


namespace Duat::Graphics {

	ConstantBuffer::ConstantBuffer(System& gfx, const Utility::HLSL::Layout& layout, Usage usage, Access cpuAccess)
	{
		Init(gfx, layout, usage, cpuAccess);
	}

	ConstantBuffer::ConstantBuffer(System* pGFX, const Utility::HLSL::Layout& layout, Usage usage, Access cpuAccess)
	{
		Init(pGFX, layout, usage, cpuAccess);
	}

	void ConstantBuffer::Init(System& gfx, const Utility::HLSL::Layout& layout, Usage usage, Access cpuAccess)
	{
		Init(&gfx, layout, usage, cpuAccess);
	}

	void ConstantBuffer::Init(System* pGFX, const Utility::HLSL::Layout& layout, Usage usage, Access cpuAccess)
	{
		Utility::HLSL::Buffer::Init(layout);

		if (usage == Usage::Dynamic) is_dynamic = true;
		else is_dynamic = false;

		ZeroMemory(&m_desc, sizeof(D3D11_BUFFER_DESC));
		m_desc.ByteWidth = (UINT)GetBufferSize();
		m_desc.Usage = D3D11_USAGE(usage);
		m_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		m_desc.CPUAccessFlags = (UINT)cpuAccess;

		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
		subData.pSysMem = GetBuffer();

		m_hresult << pGFX->m_Device->CreateBuffer(&m_desc, &subData, ReleaseAndGetAddressOf());
	}

	ID3D11Buffer* ConstantBuffer::Get()
	{
		return m_pConstantBuffer.Get();
	}

	ID3D11Buffer** ConstantBuffer::GetAddressOf()
	{
		return m_pConstantBuffer.GetAddressOf();
	}

	ID3D11Buffer** ConstantBuffer::ReleaseAndGetAddressOf()
	{
		return m_pConstantBuffer.ReleaseAndGetAddressOf();
	}

	bool ConstantBuffer::IsDynamic() const
	{
		return is_dynamic;
	}

}