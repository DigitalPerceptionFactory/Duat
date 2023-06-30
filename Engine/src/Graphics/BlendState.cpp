#include "BlendState.h"
#include "System.h"


namespace Duat::Graphics {
	
	HRESULT BlendState::Init(System& gfx, bool blendEnable, Blend srcBlend, Blend destBlend, BlendOp blendOp, Blend srcBlendAlpha, Blend destBlendAlpha, BlendOp blendOpAlpha, ColorWriteMask mask)
	{
		return Init(&gfx, blendEnable, srcBlend, destBlend, blendOp, srcBlendAlpha, destBlendAlpha, blendOpAlpha, mask);
	}

	HRESULT BlendState::Init(System* pGFX, bool blendEnable, Blend srcBlend, Blend destBlend, BlendOp blendOp, Blend srcBlendAlpha, Blend destBlendAlpha, BlendOp blendOpAlpha, ColorWriteMask mask)
	{
		m_pGFX = pGFX;
		m_desc.BlendEnable = blendEnable;
		m_desc.SrcBlend = D3D11_BLEND(srcBlend);
		m_desc.DestBlend = D3D11_BLEND(destBlend);
		m_desc.BlendOp = D3D11_BLEND_OP(blendOp);
		m_desc.SrcBlendAlpha = D3D11_BLEND(srcBlendAlpha);
		m_desc.DestBlendAlpha = D3D11_BLEND(destBlendAlpha);
		m_desc.BlendOpAlpha = D3D11_BLEND_OP(blendOpAlpha);
		m_desc.RenderTargetWriteMask = (UINT8)mask;

		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
		blendDesc.RenderTarget[0] = m_desc;

		return m_pGFX->m_Device->CreateBlendState(&blendDesc, ReleaseAndGetAddressOf());
	}

	HRESULT BlendState::Update()
	{
		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
		blendDesc.RenderTarget[0] = m_desc;

		return m_pGFX->m_Device->CreateBlendState(&blendDesc, ReleaseAndGetAddressOf());
	}

	bool BlendState::IsBlendEnabled()
	{
		return m_desc.BlendEnable;
	}

	Blend BlendState::GetSrcBlend()
	{
		return Blend(m_desc.SrcBlend);
	}

	Blend BlendState::GetDestBlend()
	{
		return Blend(m_desc.DestBlend);
	}

	BlendOp BlendState::GetBlendOp()
	{
		return BlendOp(m_desc.BlendOp);
	}

	Blend BlendState::GetSrcAlphaBlend()
	{
		return Blend(m_desc.SrcBlendAlpha);
	}

	Blend BlendState::GetDestAlphaBlend()
	{
		return Blend(m_desc.DestBlendAlpha);
	}

	BlendOp BlendState::GetAlphaOp()
	{
		return BlendOp(m_desc.BlendOpAlpha);
	}

	ColorWriteMask BlendState::GetMask()
	{
		return ColorWriteMask(m_desc.RenderTargetWriteMask);
	}

	void BlendState::SetBlendEnabled(bool flag)
	{
		m_desc.BlendEnable = flag;
	}

	void BlendState::SetSrcBlend(Blend blend)
	{
		m_desc.SrcBlend = D3D11_BLEND(blend);
	}

	void BlendState::SetDestBlend(Blend blend)
	{
		m_desc.DestBlend = D3D11_BLEND(blend);
	}

	void BlendState::SetBlendOp(BlendOp blendOp)
	{
		m_desc.BlendOp = D3D11_BLEND_OP(blendOp);
	}

	void BlendState::SetSrcAlphaBlend(Blend blend)
	{
		m_desc.SrcBlendAlpha = D3D11_BLEND(blend);
	}

	void BlendState::SetDestAlphaBlend(Blend blend)
	{
		m_desc.DestBlendAlpha = D3D11_BLEND(blend);
	}

	void BlendState::SetAlphaOp(BlendOp blendOp)
	{
		m_desc.BlendOpAlpha = D3D11_BLEND_OP(blendOp);
	}

	void BlendState::SetMask(ColorWriteMask mask)
	{
		m_desc.RenderTargetWriteMask = (UINT8)mask;
	}
	
}