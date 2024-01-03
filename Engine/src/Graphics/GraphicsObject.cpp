#include "GraphicsObject.h"


namespace Duat::Graphics {

	GraphicsObject::GraphicsObject()
	{
		ZeroMemory(&m_BS, sizeof(m_BS));
		ZeroMemory(&m_DSS, sizeof(m_DSS));
		ZeroMemory(&m_RS, sizeof(m_RS));
		Set(Preset::Default);
	}

	void GraphicsObject::Set(Preset preset, int index)
	{
		switch (preset)
		{
		case Preset::Default:
			Set(Preset::DefaultBS, index);
			Set(Preset::DefaultDSS, index);
			Set(Preset::DefaultRS, index);
			Set(Preset::DefaultVP, index);
			SetTopology(Topology::TriangleList);
			SetVS("Default");
			SetPS("Default");
			SetCamera("Default");
			break;
		case Preset::DefaultBS:
			SetBS_BlendEnabled(false);
			SetBS_Mask(ColorWriteMask::EnableAll);
			break;
		case Preset::DefaultDSS:
			SetDSS_DepthEnabled(true);
			SetDSS_DepthWriteMask(DepthWriteMask::All);
			SetDSS_DepthComparison(Comparison::LessEqual);
			SetDSS_StencilEnabled(false);
			break;
		case Preset::DefaultRS:
			SetRS_FrontCounterClockwise(false);
			SetRS_FillMode(Fill::Solid);
			SetRS_CullMode(Cull::Back);
			SetRS_MultisampleEnabled(true);
			SetRS_AntialiasedLineEnabled(false);
			SetRS_DepthClipEnabled(false);
			SetRS_ScissorEnabled(false);
			break;
		case Preset::DefaultVP:
			SetVP_Width(GetSystemMetrics(SM_CXSCREEN), index);
			SetVP_Height(GetSystemMetrics(SM_CYSCREEN), index);
			SetVP_TopLeftX(0, index);
			SetVP_TopLeftY(0, index);
			SetVP_MinDepth(0.0f, index);
			SetVP_MaxDepth(1.0f, index);
			break;
		case Preset::Transparent:
			SetBS_BlendEnabled(true);
			SetBS_SrcBlend(Blend::SrcAlpha);
			SetBS_DestBlend(Blend::InvSrcAlpha);
			SetBS_BlendOp(BlendOp::Add);
			SetBS_SrcAlphaBlend(Blend::One);
			SetBS_DestAlphaBlend(Blend::One);
			SetBS_AlphaBlendOp(BlendOp::Add);
			SetBS_Mask(ColorWriteMask::EnableAll);
			break;
		case Preset::Skybox:
			SetVS("Skybox");
			SetPS("Skybox");
			SetTopology(Topology::TriangleList);
			Set(Preset::DefaultRS);
			SetRS_CullMode(Cull::None);
			Set(Preset::DefaultVP, index);
			Set(Preset::Transparent);
			Set(Preset::DefaultDSS);
			//SetDSS_DepthComparison(Comparison::Less);
			
			SetSS_Comparison(Comparison::GreaterEqual);
			
			break;
		}

	}

	std::string GraphicsObject::GetPS() const
	{
		return m_PS;
	}

	std::string GraphicsObject::GetVS() const
	{
		return m_VS;
	}

	void GraphicsObject::SetPS(const std::string& ps)
	{
		m_PS = ps;
	}

	void GraphicsObject::SetVS(const std::string& vs)
	{
		m_VS = vs;
	}

	std::string GraphicsObject::GetCamera() const
	{
		return m_Camera;
	}

	void GraphicsObject::SetCamera(const std::string& cam)
	{
		m_Camera = cam;
	}

	std::string GraphicsObject::GetTexture(int textureIndex) const
	{
		return m_Textures.at(textureIndex);
	}

	std::vector<std::string> GraphicsObject::GetTextures() const
	{
		std::vector<std::string> out;
		std::vector<std::pair<int, std::string>> sortedOut;

		for (auto& tex : m_Textures) sortedOut.push_back(tex);

		std::sort(sortedOut.begin(), sortedOut.end(),
			[](const auto& a, const auto& b) {
				return a.first < b.first;
			});

		for (auto& o : sortedOut) out.push_back(o.second);

		return out;
	}

	void GraphicsObject::SetTexture(const std::string& name, int textureIndex)
	{
		m_Textures[textureIndex] = name;
	}

	Topology GraphicsObject::GetTopology() const
	{
		return m_TP;
	}

	void GraphicsObject::SetTopology(Topology tp)
	{
		m_TP = tp;
	}

	std::string GraphicsObject::GetBS() const
	{
		return Serialize(m_BS);
	}

	D3D11_RENDER_TARGET_BLEND_DESC GraphicsObject::GetBS_DESC() const
	{
		return m_BS;
	}

	bool GraphicsObject::GetBS_IsBlendEnabled() const
	{
		return m_BS.BlendEnable;
	}

	Blend GraphicsObject::GetBS_SrcBlend() const
	{
		return Blend(m_BS.SrcBlend);
	}

	Blend GraphicsObject::GetBS_DestBlend() const
	{
		return Blend(m_BS.DestBlend);
	}

	BlendOp GraphicsObject::GetBS_BlendOp() const
	{
		return BlendOp(m_BS.BlendOp);
	}

	Blend GraphicsObject::GetBS_SrcAlphaBlend() const
	{
		return Blend(m_BS.SrcBlendAlpha);
	}

	Blend GraphicsObject::GetBS_DestAlphaBlend() const
	{
		return Blend(m_BS.DestBlendAlpha);
	}

	BlendOp GraphicsObject::GetBS_AlphaOp() const
	{
		return BlendOp(m_BS.BlendOpAlpha);
	}

	ColorWriteMask GraphicsObject::GetBS_Mask() const
	{
		return ColorWriteMask(m_BS.RenderTargetWriteMask);
	}

	void GraphicsObject::SetBS_BlendEnabled(bool flag)
	{
		m_BS.BlendEnable = flag;
	}

	void GraphicsObject::SetBS_SrcBlend(Blend blend)
	{
		m_BS.SrcBlend = D3D11_BLEND(blend);
	}

	void GraphicsObject::SetBS_DestBlend(Blend blend)
	{
		m_BS.DestBlend = D3D11_BLEND(blend);
	}

	void GraphicsObject::SetBS_BlendOp(BlendOp blendOp)
	{
		m_BS.BlendOp = D3D11_BLEND_OP(blendOp);
	}

	void GraphicsObject::SetBS_SrcAlphaBlend(Blend blend)
	{
		m_BS.SrcBlendAlpha = D3D11_BLEND(blend);
	}

	void GraphicsObject::SetBS_DestAlphaBlend(Blend blend)
	{
		m_BS.DestBlendAlpha = D3D11_BLEND(blend);
	}

	void GraphicsObject::SetBS_AlphaBlendOp(BlendOp blendOp)
	{
		m_BS.BlendOpAlpha = D3D11_BLEND_OP(blendOp);
	}

	void GraphicsObject::SetBS_Mask(ColorWriteMask mask)
	{
		m_BS.RenderTargetWriteMask = (UINT8)mask;
	}

	std::string GraphicsObject::GetDSS() const
	{
		return Serialize(m_DSS);
	}

	D3D11_DEPTH_STENCIL_DESC GraphicsObject::GetDSS_DESC() const
	{
		return m_DSS;
	}

	bool GraphicsObject::GetDSS_IsDepthEnabled() const
	{
		return m_DSS.DepthEnable;
	}

	DepthWriteMask GraphicsObject::GetDSS_DepthWriteMask() const
	{
		return DepthWriteMask(m_DSS.DepthWriteMask);
	}

	Comparison GraphicsObject::GetDSS_DepthComparison() const
	{
		return Comparison(m_DSS.DepthFunc);
	}

	bool GraphicsObject::GetDSS_IsStencilEnabled() const
	{
		return m_DSS.StencilEnable;
	}

	StencilOp GraphicsObject::GetDSS_FrontFail() const
	{
		return StencilOp(m_DSS.FrontFace.StencilFailOp);
	}

	StencilOp GraphicsObject::GetDSS_FrontDepthFail() const
	{
		return StencilOp(m_DSS.FrontFace.StencilDepthFailOp);
	}

	StencilOp GraphicsObject::GetDSS_FrontPass() const
	{
		return StencilOp(m_DSS.FrontFace.StencilPassOp);
	}

	Comparison GraphicsObject::GetDSS_FrontComparison() const
	{
		return Comparison(m_DSS.FrontFace.StencilFunc);
	}

	StencilOp GraphicsObject::GetDSS_BackFail() const
	{
		return StencilOp(m_DSS.BackFace.StencilFailOp);
	}

	StencilOp GraphicsObject::GetDSS_BackDepthFail() const
	{
		return StencilOp(m_DSS.BackFace.StencilDepthFailOp);
	}

	StencilOp GraphicsObject::GetDSS_BackPass() const
	{
		return StencilOp(m_DSS.BackFace.StencilPassOp);
	}

	Comparison GraphicsObject::GetDSS_BackComparison() const
	{
		return Comparison(m_DSS.BackFace.StencilFunc);
	}

	UINT8 GraphicsObject::GetDSS_WriteMask() const
	{
		return m_DSS.StencilWriteMask;
	}

	UINT8 GraphicsObject::GetDSS_ReadMask() const
	{
		return m_DSS.StencilReadMask;
	}

	void GraphicsObject::SetDSS_DepthEnabled(bool flag)
	{
		m_DSS.DepthEnable = flag;
	}

	void GraphicsObject::SetDSS_DepthWriteMask(DepthWriteMask mask)
	{
		m_DSS.DepthWriteMask = D3D11_DEPTH_WRITE_MASK(mask);
	}

	void GraphicsObject::SetDSS_DepthComparison(Comparison comp)
	{
		m_DSS.DepthFunc = D3D11_COMPARISON_FUNC(comp);
	}

	void GraphicsObject::SetDSS_StencilEnabled(bool flag)
	{
		m_DSS.StencilEnable = flag;
	}

	void GraphicsObject::SetDSS_FrontFail(StencilOp op)
	{
		m_DSS.FrontFace.StencilFailOp = D3D11_STENCIL_OP(op);
	}

	void GraphicsObject::SetDSS_FrontDepthFail(StencilOp op)
	{
		m_DSS.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP(op);
	}

	void GraphicsObject::SetDSS_FrontPass(StencilOp op)
	{
		m_DSS.FrontFace.StencilPassOp = D3D11_STENCIL_OP(op);
	}

	void GraphicsObject::SetDSS_FrontComparison(Comparison comp)
	{
		m_DSS.FrontFace.StencilFunc = D3D11_COMPARISON_FUNC(comp);
	}

	void GraphicsObject::SetDSS_BackFail(StencilOp op)
	{
		m_DSS.BackFace.StencilFailOp = D3D11_STENCIL_OP(op);
	}

	void GraphicsObject::SetDSS_BackDepthFail(StencilOp op)
	{
		m_DSS.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP(op);
	}

	void GraphicsObject::SetDSS_BackPass(StencilOp op)
	{
		m_DSS.BackFace.StencilPassOp = D3D11_STENCIL_OP(op);
	}

	void GraphicsObject::SetDSS_BackComparison(Comparison comp)
	{
		m_DSS.BackFace.StencilFunc = D3D11_COMPARISON_FUNC(comp);
	}

	void GraphicsObject::SetDSS_StencilWriteMask(UINT8 mask)
	{
		m_DSS.StencilWriteMask = mask;
	}

	void GraphicsObject::SetDSS_StencilReadMask(UINT8 mask)
	{
		m_DSS.StencilReadMask = mask;
	}

	std::string GraphicsObject::GetRS() const
	{
		std::string out = Serialize(m_RS);

		for (auto& vp : GetVP_DESC())
			out += Serialize(vp);

		return out;
	}

	D3D11_RASTERIZER_DESC GraphicsObject::GetRS_DESC() const
	{
		return m_RS;
	}

	bool GraphicsObject::GetRS_IsAntialiasedLineEnabled() const
	{
		return m_RS.AntialiasedLineEnable;
	}

	bool GraphicsObject::GetRS_IsMultisampleEnabled() const
	{
		return m_RS.MultisampleEnable;
	}

	bool GraphicsObject::GetRS_IsScissorEnabled() const
	{
		return m_RS.ScissorEnable;
	}

	bool GraphicsObject::GetRS_IsDepthClipEnabled() const
	{
		return m_RS.DepthClipEnable;
	}

	int GraphicsObject::GetRS_DepthBias() const
	{
		return m_RS.DepthBias;
	}

	float GraphicsObject::GetRS_SlopeScaledDepthBias() const
	{
		return m_RS.SlopeScaledDepthBias;
	}

	Fill GraphicsObject::GetRS_FillMode() const
	{
		return Fill(m_RS.FillMode);
	}

	Cull GraphicsObject::GetRS_CullMode() const
	{
		return Cull(m_RS.CullMode);
	}

	bool GraphicsObject::GetRS_IsFrontCounterClockwise() const
	{
		return m_RS.FrontCounterClockwise;
	}

	void GraphicsObject::SetRS_AntialiasedLineEnabled(bool flag)
	{
		m_RS.AntialiasedLineEnable = flag;
	}

	void GraphicsObject::SetRS_MultisampleEnabled(bool flag)
	{
		m_RS.MultisampleEnable = flag;
	}

	void GraphicsObject::SetRS_ScissorEnabled(bool flag)
	{
		m_RS.ScissorEnable = flag;
	}

	void GraphicsObject::SetRS_DepthClipEnabled(bool flag)
	{
		m_RS.DepthClipEnable = flag;
	}

	void GraphicsObject::SetRS_DepthBias(int bias)
	{
		m_RS.DepthBias = bias;
	}

	void GraphicsObject::SetRS_SlopeScaledDepthBias(float bias)
	{
		m_RS.SlopeScaledDepthBias = bias;
	}

	void GraphicsObject::SetRS_FillMode(Fill fillMode)
	{
		m_RS.FillMode = D3D11_FILL_MODE(fillMode);
	}

	void GraphicsObject::SetRS_CullMode(Cull cullMode)
	{
		m_RS.CullMode = D3D11_CULL_MODE(cullMode);
	}

	void GraphicsObject::SetRS_FrontCounterClockwise(bool flag)
	{
		m_RS.FrontCounterClockwise = flag;
	}

	std::vector<D3D11_VIEWPORT> GraphicsObject::GetVP_DESC() const
	{
		std::vector<D3D11_VIEWPORT> out;
		
		std::vector<std::pair<int,D3D11_VIEWPORT>> sortedOut;
		for (auto& vp : m_VP)
		{
			if (vp.second.Width != 0 && vp.second.Height != 0)
				sortedOut.push_back(vp);
		}

		std::sort(sortedOut.begin(), sortedOut.end(),
			[](const auto& a, const auto& b) {
				return a.first < b.first;
			});

		for (auto& o : sortedOut)
			out.push_back(o.second);

		return out;
	}

	float GraphicsObject::GetVP_Width(int viewportIndex) const
	{
		return m_VP.at(viewportIndex).Width;
	}

	float GraphicsObject::GetVP_Height(int viewportIndex) const
	{
		return m_VP.at(viewportIndex).Height;
	}

	float GraphicsObject::GetVP_TopLeftX(int viewportIndex) const
	{
		return m_VP.at(viewportIndex).TopLeftX;
	}

	float GraphicsObject::GetVP_TopLeftY(int viewportIndex) const
	{
		return m_VP.at(viewportIndex).TopLeftY;
	}

	float GraphicsObject::GetVP_MinDepth(int viewportIndex) const
	{
		return m_VP.at(viewportIndex).MinDepth;
	}

	float GraphicsObject::GetVP_MaxDepth(int viewportIndex) const
	{
		return m_VP.at(viewportIndex).MaxDepth;
	}

	void GraphicsObject::SetVP_Width(float width, int viewportIndex)
	{
		m_VP[viewportIndex].Width = width;
	}

	void GraphicsObject::SetVP_Height(float height, int viewportIndex)
	{
		m_VP[viewportIndex].Height = height;
	}

	void GraphicsObject::SetVP_TopLeftX(float topLeftX, int viewportIndex)
	{
		m_VP[viewportIndex].TopLeftX = topLeftX;
	}

	void GraphicsObject::SetVP_TopLeftY(float topLeftY, int viewportIndex)
	{
		m_VP[viewportIndex].TopLeftY = topLeftY;
	}

	void GraphicsObject::SetVP_MinDepth(float minDepth, int viewportIndex)
	{
		m_VP[viewportIndex].MinDepth = minDepth;
	}

	void GraphicsObject::SetVP_MaxDepth(float maxDepth, int viewportIndex)
	{
		m_VP[viewportIndex].MaxDepth = maxDepth;
	}

	std::vector<D3D11_SAMPLER_DESC> GraphicsObject::GetSS_DESC() const
	{
		std::vector<D3D11_SAMPLER_DESC> out;
		std::vector<std::pair<int, D3D11_SAMPLER_DESC>> sortedOut;

		for (auto& ss : m_SS) sortedOut.push_back(ss);

		std::sort(sortedOut.begin(), sortedOut.end(),
			[](const auto& a, const auto& b) {
				return a.first < b.first;
			});

		for (auto& o : sortedOut) out.push_back(o.second);

		return out;
	}

	Address GraphicsObject::GetSS_AddressU(int samplerIndex) const
	{
		return Address(m_SS.at(samplerIndex).AddressU);
	}

	Address GraphicsObject::GetSS_AddressV(int samplerIndex) const
	{
		return Address(m_SS.at(samplerIndex).AddressV);
	}

	Address GraphicsObject::GetSS_AddressW(int samplerIndex) const
	{
		return Address(m_SS.at(samplerIndex).AddressW);
	}

	Comparison GraphicsObject::GetSS_Comparison(int samplerIndex) const
	{
		return Comparison(m_SS.at(samplerIndex).ComparisonFunc);
	}

	FLOAT GraphicsObject::GetSS_MipLODBias(int samplerIndex) const
	{
		return m_SS.at(samplerIndex).MipLODBias;
	}

	FLOAT GraphicsObject::GetSS_MinLOD(int samplerIndex) const
	{
		return m_SS.at(samplerIndex).MinLOD;
	}

	FLOAT GraphicsObject::GetSS_MaxLOD(int samplerIndex) const
	{
		return m_SS.at(samplerIndex).MaxLOD;
	}

	D3D11_FILTER GraphicsObject::GetSS_Filter(int samplerIndex) const
	{
		return D3D11_FILTER(m_SS.at(samplerIndex).Filter);
	}
		
	UINT GraphicsObject::GetSS_MaxAnisotropy(int samplerIndex) const
	{
		return m_SS.at(samplerIndex).MaxAnisotropy;
	}

	DirectX::XMFLOAT4 GraphicsObject::GetSS_BorderColor(int samplerIndex) const
	{
		DirectX::XMFLOAT4 out;
		out.x = m_SS.at(samplerIndex).BorderColor[0];
		out.y = m_SS.at(samplerIndex).BorderColor[1];
		out.z = m_SS.at(samplerIndex).BorderColor[2];
		out.w = m_SS.at(samplerIndex).BorderColor[3];
		return out;
	}

	void GraphicsObject::SetSS_AddressU(Address u, int samplerIndex)
	{
		m_SS[samplerIndex].AddressU = D3D11_TEXTURE_ADDRESS_MODE(u);
	}

	void GraphicsObject::SetSS_AddressV(Address v, int samplerIndex)
	{
		m_SS[samplerIndex].AddressV = D3D11_TEXTURE_ADDRESS_MODE(v);
	}

	void GraphicsObject::SetSS_AddressW(Address w, int samplerIndex)
	{
		m_SS[samplerIndex].AddressW = D3D11_TEXTURE_ADDRESS_MODE(w);
	}

	void GraphicsObject::SetSS_Comparison(Comparison comp, int samplerIndex)
	{
		m_SS[samplerIndex].ComparisonFunc = D3D11_COMPARISON_FUNC(comp);
	}

	void GraphicsObject::SetSS_MipLODBias(FLOAT bias, int samplerIndex)
	{
		m_SS[samplerIndex].MipLODBias = bias;
	}

	void GraphicsObject::SetSS_MinLOD(FLOAT minLOD, int samplerIndex)
	{
		m_SS[samplerIndex].MinLOD = minLOD;
	}

	void GraphicsObject::SetSS_MaxLOD(FLOAT maxLOD, int samplerIndex)
	{
		m_SS[samplerIndex].MaxLOD = maxLOD;
	}

	void GraphicsObject::SetSS_Filter(D3D11_FILTER filter, int samplerIndex)
	{
		m_SS[samplerIndex].Filter = filter;
	}

	void GraphicsObject::SetSS_Filter(TextureFiltering filter, int samplerIndex)
	{
		m_SS[samplerIndex].Filter = filter.GetFilter();
	}

	void GraphicsObject::SetSS_MaxAnisotropy(UINT maxAnisotropy, int samplerIndex)
	{
		m_SS[samplerIndex].MaxAnisotropy = maxAnisotropy;
	}

	void GraphicsObject::SetSS_BorderColor(DirectX::XMFLOAT4 borderColor, int samplerIndex)
	{
		m_SS[samplerIndex].BorderColor[0] = borderColor.x;
		m_SS[samplerIndex].BorderColor[1] = borderColor.y;
		m_SS[samplerIndex].BorderColor[2] = borderColor.z;
		m_SS[samplerIndex].BorderColor[3] = borderColor.w;
	}

}