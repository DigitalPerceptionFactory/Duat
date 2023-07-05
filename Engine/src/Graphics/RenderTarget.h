#pragma once
#include "Texture2D.h"


namespace Duat::Graphics {
		
	struct System;
	struct RenderTarget {
		void Init(System& gfx, const std::filesystem::path& path);
		void Init(System* pGFX, const std::filesystem::path& path);
		void Init(System& gfx, ID3D11Texture2D* pTex2D);
		void Init(System* pGFX, ID3D11Texture2D* pTex2D);

		UINT GetWidth();
		UINT GetHeight();
		ID3D11Texture2D* GetTexture();
		ID3D11Texture2D** GetTextureAddressOf();
		ID3D11Texture2D* GetDepthTexture();
		ID3D11Texture2D** GetDepthTextureAddressOf();
		ID3D11ShaderResourceView* GetSRV();
		ID3D11ShaderResourceView** GetSRVAddressOf();
		ID3D11RenderTargetView*  GetRTV();
		ID3D11RenderTargetView** GetRTVAddressOf();
		ID3D11DepthStencilView*  GetDSV();
		ID3D11DepthStencilView** GetDSVAddressOf();
	private:
		Texture2D m_texture;
		Texture2D m_depthTexture;
	};

}