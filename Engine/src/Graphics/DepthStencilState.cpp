#include "DepthStencilState.h"
#include "System.h"


namespace Duat::Graphics {

	HRESULT DepthStencilState::Init(System& gfx, D3D11_DEPTH_STENCIL_DESC desc)
	{
		return Init(&gfx, desc);
	}

	HRESULT DepthStencilState::Init(System* pGFX, D3D11_DEPTH_STENCIL_DESC desc)
	{
		m_pGFX = pGFX;
		m_desc = desc;
		Stencil::Set(desc);

		return m_pGFX->m_Device->CreateDepthStencilState(&m_desc, ReleaseAndGetAddressOf());
	}

	HRESULT DepthStencilState::Init(System& gfx, bool depthEnabled, DepthWriteMask depthWriteMask, Comparison comp, bool stencilEnabled, Stencil stencil)
	{
		return Init(&gfx, depthEnabled, depthWriteMask, comp, stencilEnabled, stencil);
	}

	HRESULT DepthStencilState::Init(System* pGFX, bool depthEnabled, DepthWriteMask depthWriteMask, Comparison comp, bool stencilEnabled, Stencil stencil)
	{
		m_pGFX = pGFX;
		m_desc.DepthEnable = depthEnabled;
		m_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK(depthWriteMask);
		m_desc.DepthFunc = D3D11_COMPARISON_FUNC(comp);
		SetFrontFail( stencil.GetFrontFail() );
		SetFrontDepthFail(stencil.GetFrontDepthFail());
		SetFrontPass(stencil.GetFrontPass());
		SetFrontComparison(stencil.GetFrontComparison());
		SetBackFail(stencil.GetBackFail());
		SetBackDepthFail(stencil.GetBackDepthFail());
		SetBackPass(stencil.GetBackPass());
		SetBackComparison(stencil.GetBackComparison());
		SetWriteMask(stencil.GetWriteMask());
		SetReadMask(stencil.GetReadMask());
		
		return m_pGFX->m_Device->CreateDepthStencilState(&m_desc, ReleaseAndGetAddressOf());
	}

	HRESULT DepthStencilState::Update()
	{
		return m_pGFX->m_Device->CreateDepthStencilState(&m_desc, ReleaseAndGetAddressOf());
	}

	bool DepthStencilState::GetDepthEnabled()
	{
		return m_desc.DepthEnable;
	}

	DepthWriteMask DepthStencilState::GetDepthWriteMask(DepthWriteMask mask)
	{
		return DepthWriteMask(m_desc.DepthWriteMask);
	}

	Comparison DepthStencilState::GetDepthComparison(Comparison comp)
	{
		return Comparison(m_desc.DepthFunc);
	}

	bool DepthStencilState::GetStencilEnabled(bool flag)
	{
		return m_desc.StencilEnable;
	}

	void DepthStencilState::SetDepthEnabled(bool flag)
	{
		m_desc.DepthEnable = flag;
	}

	void DepthStencilState::SetDepthWriteMask(DepthWriteMask mask)
	{
		m_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK(mask);
	}

	void DepthStencilState::SetDepthComparison(Comparison comp)
	{
		m_desc.DepthFunc = D3D11_COMPARISON_FUNC(comp);
	}

	void DepthStencilState::SetStencilEnabled(bool flag)
	{
		m_desc.StencilEnable = flag;
	}

	void DepthStencilState::SetFrontFail(StencilOp op)
	{
		Stencil::SetFrontFail(op);
		m_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP(op);
	}

	void DepthStencilState::SetFrontDepthFail(StencilOp op)
	{
		Stencil::SetFrontDepthFail(op);
		m_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP(op);
	}

	void DepthStencilState::SetFrontPass(StencilOp op)
	{
		Stencil::SetFrontPass(op);
		m_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP(op);
	}

	void DepthStencilState::SetFrontComparison(Comparison comp)
	{
		Stencil::SetFrontComparison(comp);
		m_desc.FrontFace.StencilFunc = D3D11_COMPARISON_FUNC(comp);
	}

	void DepthStencilState::SetBackFail(StencilOp op)
	{
		Stencil::SetBackFail(op);
		m_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP(op);
	}

	void DepthStencilState::SetBackDepthFail(StencilOp op)
	{
		Stencil::SetBackDepthFail(op);
		m_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP(op);
	}

	void DepthStencilState::SetBackPass(StencilOp op)
	{
		Stencil::SetBackPass(op);
		m_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP(op);
	}

	void DepthStencilState::SetBackComparison(Comparison comp)
	{
		Stencil::SetBackComparison(comp);
		m_desc.BackFace.StencilFunc = D3D11_COMPARISON_FUNC(comp);
	}

	void DepthStencilState::SetWriteMask(UINT8 mask)
	{
		Stencil::SetWriteMask(mask);
		m_desc.StencilWriteMask = mask;
	}

	void DepthStencilState::SetReadMask(UINT8 mask)
	{
		Stencil::SetReadMask(mask);
		m_desc.StencilReadMask = mask;
	}

}