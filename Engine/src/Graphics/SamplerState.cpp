#include "SamplerState.h"
#include "System.h"


namespace Duat::Graphics {
	
	HRESULT SamplerState::Init(System& gfx, Address u, Address v, Comparison comp, TextureFiltering filter, UINT maxAnisotropy, FLOAT minLOD, FLOAT maxLOD, FLOAT offsetLOD, DirectX::XMFLOAT4 borderColor)
	{
		return Init(&gfx, u, v, comp, filter, maxAnisotropy, minLOD, maxLOD, offsetLOD, borderColor);
	}

	HRESULT SamplerState::Init(System& gfx, Address u, Address v, Address w, Comparison comp, TextureFiltering filter, UINT maxAnisotropy, FLOAT minLOD, FLOAT maxLOD, FLOAT offsetLOD, DirectX::XMFLOAT4 borderColor)
	{
		return Init(&gfx, u, v, w, comp, filter, maxAnisotropy, minLOD, maxLOD, offsetLOD, borderColor);
	}

	HRESULT SamplerState::Init(System* pGFX, Address u, Address v, Comparison comp, TextureFiltering filter, UINT maxAnisotropy, FLOAT minLOD, FLOAT maxLOD, FLOAT offsetLOD, DirectX::XMFLOAT4 borderColor)
	{
		m_pGFX = pGFX;
		desc.Filter = filter.GetFilter();
		desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE(u);
		desc.AddressV = D3D11_TEXTURE_ADDRESS_MODE(v);
		desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE(Address::Wrap);
		desc.MipLODBias = offsetLOD;
		desc.MinLOD = minLOD;
		desc.MaxLOD = maxLOD;
		desc.MaxAnisotropy = maxAnisotropy;
		desc.BorderColor[0] = borderColor.x;
		desc.BorderColor[1] = borderColor.y;
		desc.BorderColor[2] = borderColor.z;
		desc.BorderColor[3] = borderColor.w;

		return m_pGFX->m_Device->CreateSamplerState(&desc, ReleaseAndGetAddressOf());
	}

	HRESULT SamplerState::Init(System* pGFX, Address u, Address v, Address w, Comparison comp, TextureFiltering filter, UINT maxAnisotropy, FLOAT minLOD, FLOAT maxLOD, FLOAT offsetLOD, DirectX::XMFLOAT4 borderColor)
	{
		m_pGFX = pGFX;
		desc.Filter = filter.GetFilter();
		desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE(u);
		desc.AddressV = D3D11_TEXTURE_ADDRESS_MODE(v);
		desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE(w);
		desc.MipLODBias = offsetLOD;
		desc.MinLOD = minLOD;
		desc.MaxLOD = maxLOD;
		desc.MaxAnisotropy = maxAnisotropy;
		desc.BorderColor[0] = borderColor.x;
		desc.BorderColor[1] = borderColor.y;
		desc.BorderColor[2] = borderColor.z;
		desc.BorderColor[3] = borderColor.w;

		return m_pGFX->m_Device->CreateSamplerState(&desc, ReleaseAndGetAddressOf());
	}

	HRESULT SamplerState::Update()
	{
		return m_pGFX->m_Device->CreateSamplerState(&desc, ReleaseAndGetAddressOf());
	}

	Address SamplerState::GetAddressU()
	{
		return Address(desc.AddressU);
	}

	Address SamplerState::GetAddressV()
	{
		return Address(desc.AddressV);
	}

	Address SamplerState::GetAddressW()
	{
		return Address(desc.AddressW);
	}

	Comparison SamplerState::GetComparison()
	{
		return Comparison(desc.ComparisonFunc);
	}

	FLOAT SamplerState::GetOffsetLOD()
	{
		return desc.MipLODBias;
	}

	FLOAT SamplerState::GetMinLOD()
	{
		return desc.MinLOD;
	}

	FLOAT SamplerState::GetMaxLOD()
	{
		return desc.MaxLOD;
	}

	D3D11_FILTER SamplerState::GetFilter()
	{
		return desc.Filter;
	}

	UINT SamplerState::GetMaxAnisotropy()
	{
		return desc.MaxAnisotropy;
	}

	DirectX::XMFLOAT4 SamplerState::GetBorderColor()
	{
		return {
			desc.BorderColor[0],
			desc.BorderColor[1],
			desc.BorderColor[2],
			desc.BorderColor[3]
		};
	}

	void SamplerState::SetAddressU(Address u)
	{
		desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE(u);
	}

	void SamplerState::SetAddressV(Address v)
	{
		desc.AddressV = D3D11_TEXTURE_ADDRESS_MODE(v);
	}

	void SamplerState::SetAddressW(Address w)
	{
		desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE(w);
	}

	void SamplerState::SetComparison(Comparison comp)
	{
		desc.ComparisonFunc = D3D11_COMPARISON_FUNC(comp);
	}

	void SamplerState::SetOffsetLOD(FLOAT offsetLOD)
	{
		desc.MipLODBias = offsetLOD;
	}

	void SamplerState::SetMinLOD(FLOAT minLOD)
	{
		desc.MinLOD = minLOD;
	}

	void SamplerState::SetMaxLOD(FLOAT maxLOD)
	{
		desc.MaxLOD = maxLOD;
	}

	void SamplerState::SetFilter(D3D11_FILTER filter)
	{
		desc.Filter = filter;
	}

	void SamplerState::SetFilter(TextureFiltering filter)
	{
		desc.Filter = filter.GetFilter();
	}

	void SamplerState::SetMaxAnisotropy(UINT maxAnisotropy)
	{
		desc.MaxAnisotropy = maxAnisotropy;
	}

	void SamplerState::SetBorderColor(DirectX::XMFLOAT4 borderColor)
	{
		desc.BorderColor[0] = borderColor.x;
		desc.BorderColor[1] = borderColor.y;
		desc.BorderColor[2] = borderColor.z;
		desc.BorderColor[3] = borderColor.w;
	}

}