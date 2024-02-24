#pragma once
#include "Texture2D.h"


namespace Duat::Graphics {
		
	struct System;
	struct Camera;
	struct RenderTarget {
		friend System;
		friend Camera;

		/*void Init(System& gfx, const std::filesystem::path& path);
		void Init(System* pGFX, const std::filesystem::path& path);
		void Init(System& gfx, ID3D11Texture2D* pTex2D);
		void Init(System* pGFX, ID3D11Texture2D* pTex2D);
		//  void Init(System& gfx, size_t width, size_t height, DXGI_FORMAT pixelFormat, DXGI_FORMAT depthFormat = DXGI_FORMAT_D24_UNORM_S8_UINT);
		//  void Init(System* pGFX, size_t width, size_t height, DXGI_FORMAT pixelFormat, DXGI_FORMAT depthFormat = DXGI_FORMAT_D24_UNORM_S8_UINT);
		void Init(System& gfx, D3D11_TEXTURE2D_DESC targetDesc);
		void Init(System* pGFX, D3D11_TEXTURE2D_DESC targetDesc);
		void Init(const Texture2D& rt, const Texture2D& depth);

		void SetTargetDesc(D3D11_TEXTURE2D_DESC desc);
		void SetTargetWidth(UINT width);
		void SetTargetHeight(UINT height);
		void SetTargetMipLevels(UINT mipLevels);
		void SetTargetArraySize(UINT arraySize);
		void SetTargetFormat(DXGI_FORMAT format);
		void SetTargetSample(UINT count, UINT quality);
		void SetTargetUsage(Usage usage);
		void SetTargetBindFlags(UINT bindFlags);
		void SetTargetCPUAccessFlags(UINT cpuFlags);
		void SetTargetMiscFlags(UINT miscFlags);

		void SetDepthDesc(D3D11_TEXTURE2D_DESC desc);
		void SetDepthWidth(UINT width);
		void SetDepthHeight(UINT height);
		void SetDepthMipLevels(UINT mipLevels);
		void SetDepthArraySize(UINT arraySize);
		void SetDepthFormat(DXGI_FORMAT format);
		void SetDepthSample(UINT count, UINT quality);
		void SetDepthUsage(Usage usage);
		void SetDepthBindFlags(UINT bindFlags);
		void SetDepthCPUAccessFlags(UINT cpuFlags);
		void SetDepthMiscFlags(UINT miscFlags);

		UINT GetWidth() const;
		UINT GetHeight() const;
		Texture& GetTarget();
		Texture& GetDepth();
			
	private:*/
		Texture2D m_targetTexture;
		Texture2D m_depthTexture;
		std::vector<Camera*> m_cameras;
	};

}