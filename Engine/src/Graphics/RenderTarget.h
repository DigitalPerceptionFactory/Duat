#pragma once
#include "Texture2D.h"


namespace Duat::Graphics {
		
	struct System;
	struct Camera;
	struct RenderTarget {
		friend System;
		friend Camera;

		void Init(System& gfx, const std::filesystem::path& path);
		void Init(System* pGFX, const std::filesystem::path& path);
		void Init(System& gfx, ID3D11Texture2D* pTex2D);
		void Init(System* pGFX, ID3D11Texture2D* pTex2D);
		void Init(System& gfx, size_t width, size_t height, DXGI_FORMAT pixelFormat, DXGI_FORMAT depthFormat = DXGI_FORMAT_D24_UNORM_S8_UINT);
		void Init(System* pGFX, size_t width, size_t height, DXGI_FORMAT pixelFormat, DXGI_FORMAT depthFormat = DXGI_FORMAT_D24_UNORM_S8_UINT);
		void Init(const Texture2D& rt, const Texture2D& depth);

		UINT GetWidth() const;
		UINT GetHeight() const;
		Texture2D& GetTarget();
		Texture2D& GetDepth();
			
	private:
		Texture2D m_targetTexture;
		Texture2D m_depthTexture;
		std::vector<Camera*> m_cameras;
	};

}