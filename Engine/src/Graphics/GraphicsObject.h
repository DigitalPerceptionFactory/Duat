#pragma once
#include <unordered_map>
#include <string>
#include <algorithm>
#include <Geometry/Mesh.h>
#include <Utility/DirectX/EnumWrappers.h>
#include <Utility/Classes/Serialization.h>


namespace Duat::Graphics {

	enum class Preset {
		Default, DefaultBS, DefaultDSS, DefaultRS, DefaultVP,
		Transparent, Skybox
	};

	struct GraphicsObject {
		GraphicsObject();
		GraphicsObject(Preset preset, int index = 0);

		void Set(Preset preset, int index = 0);

		// Shader getters
		std::string GetPS() const;
		std::string GetVS() const;
		// Shader setters
		void SetPS(const std::string& ps);
		void SetVS(const std::string& vs);

		// Camera getters
		std::string GetCamera() const;
		// Camera setters
		void SetCamera(const std::string& cam);

		// Texture getters
		std::string GetTexture(int textureIndex = 0) const;
		std::vector<std::string> GetTextures() const;
		// Texture setters
		void SetTexture(const std::string&  name, int textureIndex = 0);

		// Topology getters
		Topology GetTopology() const;
		// Topology setters
		void SetTopology(Topology tp);

		// Blend State getters
		std::string GetBS() const;
		D3D11_RENDER_TARGET_BLEND_DESC GetBS_DESC() const;
		bool GetBS_IsBlendEnabled() const;
		Blend GetBS_SrcBlend() const;
		Blend GetBS_DestBlend() const;
		BlendOp GetBS_BlendOp() const;
		Blend GetBS_SrcAlphaBlend() const;
		Blend GetBS_DestAlphaBlend() const;
		BlendOp GetBS_AlphaOp() const;
		ColorWriteMask GetBS_Mask() const;
		// Blend State setters
		void SetBS_BlendEnabled(bool flag);
		void SetBS_SrcBlend(Blend blend);
		void SetBS_DestBlend(Blend blend);
		void SetBS_BlendOp(BlendOp blendOp);
		void SetBS_SrcAlphaBlend(Blend blend);
		void SetBS_DestAlphaBlend(Blend blend);
		void SetBS_AlphaBlendOp(BlendOp blendOp);
		void SetBS_Mask(ColorWriteMask mask);

		// Depth Stencil State getters
		std::string GetDSS() const;
		D3D11_DEPTH_STENCIL_DESC GetDSS_DESC() const;
		bool GetDSS_IsDepthEnabled() const;
		DepthWriteMask GetDSS_DepthWriteMask() const;
		Comparison GetDSS_DepthComparison() const;
		bool GetDSS_IsStencilEnabled() const;
		StencilOp GetDSS_FrontFail() const;
		StencilOp GetDSS_FrontDepthFail() const;
		StencilOp GetDSS_FrontPass() const;
		Comparison GetDSS_FrontComparison() const;
		StencilOp GetDSS_BackFail() const;
		StencilOp GetDSS_BackDepthFail() const;
		StencilOp GetDSS_BackPass() const;
		Comparison GetDSS_BackComparison() const;
		UINT8 GetDSS_WriteMask() const;
		UINT8 GetDSS_ReadMask() const;
		// Depth Stencil State setters
		void SetDSS_DepthEnabled(bool flag);
		void SetDSS_DepthWriteMask(DepthWriteMask mask);
		void SetDSS_DepthComparison(Comparison comp);
		void SetDSS_StencilEnabled(bool flag);
		void SetDSS_FrontFail(StencilOp op);
		void SetDSS_FrontDepthFail(StencilOp op);
		void SetDSS_FrontPass(StencilOp op);
		void SetDSS_FrontComparison(Comparison comp);
		void SetDSS_BackFail(StencilOp op);
		void SetDSS_BackDepthFail(StencilOp op);
		void SetDSS_BackPass(StencilOp op);
		void SetDSS_BackComparison(Comparison comp);
		void SetDSS_StencilWriteMask(UINT8 mask);
		void SetDSS_StencilReadMask(UINT8 mask);
				
		// Rasterizer State getters
		std::string GetRS() const;
		D3D11_RASTERIZER_DESC GetRS_DESC() const;
		bool GetRS_IsAntialiasedLineEnabled() const;
		bool GetRS_IsMultisampleEnabled() const;
		bool GetRS_IsScissorEnabled() const;
		bool GetRS_IsDepthClipEnabled() const;
		int GetRS_DepthBias() const;
		float GetRS_SlopeScaledDepthBias() const;
		Fill GetRS_FillMode() const;
		Cull GetRS_CullMode() const;
		bool GetRS_IsFrontCounterClockwise() const;
		// Rasterizer State setters
		void SetRS_AntialiasedLineEnabled(bool flag);
		void SetRS_MultisampleEnabled(bool flag);
		void SetRS_ScissorEnabled(bool flag);
		void SetRS_DepthClipEnabled(bool flag);
		void SetRS_DepthBias(int bias);
		void SetRS_SlopeScaledDepthBias(float bias);
		void SetRS_FillMode(Fill fillMode);
		void SetRS_CullMode(Cull cullMode);
		void SetRS_FrontCounterClockwise(bool flag);

		// Viewport getters
		std::vector< D3D11_VIEWPORT> GetVP_DESC() const;
		float GetVP_Width(int viewportIndex = 0) const;
		float GetVP_Height(int viewportIndex = 0) const;
		float GetVP_TopLeftX(int viewportIndex = 0) const;
		float GetVP_TopLeftY(int viewportIndex = 0) const;
		float GetVP_MinDepth(int viewportIndex = 0) const;
		float GetVP_MaxDepth(int viewportIndex = 0) const;
		// Viewport setters
		void SetVP_Width(float width, int viewportIndex = 0);
		void SetVP_Height(float height, int viewportIndex = 0);
		void SetVP_TopLeftX(float topLeftX, int viewportIndex = 0);
		void SetVP_TopLeftY(float topLeftY, int viewportIndex = 0);
		void SetVP_MinDepth(float minDepth, int viewportIndex = 0);
		void SetVP_MaxDepth(float maxDepth, int viewportIndex = 0);

		// Sampler State getters
		std::vector<D3D11_SAMPLER_DESC> GetSS_DESC() const;
		Address GetSS_AddressU(int samplerIndex = 0) const;
		Address GetSS_AddressV(int samplerIndex = 0) const;
		Address GetSS_AddressW(int samplerIndex = 0) const;
		Comparison GetSS_Comparison(int samplerIndex = 0) const;
		FLOAT GetSS_MipLODBias(int samplerIndex = 0) const;
		FLOAT GetSS_MinLOD(int samplerIndex = 0) const;
		FLOAT GetSS_MaxLOD(int samplerIndex = 0) const;
		D3D11_FILTER GetSS_Filter(int samplerIndex = 0) const;
		//TextureFiltering GetSS_TextureFiltering(int samplerIndex = 0) const;
		UINT GetSS_MaxAnisotropy(int samplerIndex = 0) const;
		DirectX::XMFLOAT4 GetSS_BorderColor(int samplerIndex  = 0) const;
		// Sampler State setters
		void SetSS_AddressU(Address u, int samplerIndex = 0);
		void SetSS_AddressV(Address v, int samplerIndex = 0);
		void SetSS_AddressW(Address w, int samplerIndex = 0);
		void SetSS_Comparison(Comparison comp, int samplerIndex = 0);
		void SetSS_MipLODBias(FLOAT bias, int samplerIndex = 0);
		void SetSS_MinLOD(FLOAT minLOD, int samplerIndex = 0);
		void SetSS_MaxLOD(FLOAT maxLOD, int samplerIndex = 0);
		void SetSS_Filter(D3D11_FILTER filter, int samplerIndex = 0);
		void SetSS_Filter(TextureFiltering filter, int samplerIndex = 0);
		void SetSS_MaxAnisotropy(UINT maxAnisotropy, int samplerIndex = 0);
		void SetSS_BorderColor(DirectX::XMFLOAT4 borderColor, int samplerIndex = 0);

	private:
		std::string m_PS;
		std::string m_VS;
		std::string m_Camera;
		std::unordered_map<int, std::string> m_Textures;
		Topology m_TP;
		D3D11_RENDER_TARGET_BLEND_DESC m_BS;
		D3D11_DEPTH_STENCIL_DESC m_DSS; 
		D3D11_RASTERIZER_DESC m_RS;
		std::unordered_map<int, D3D11_VIEWPORT> m_VP;
		std::unordered_map<int, D3D11_SAMPLER_DESC> m_SS;
	};

}