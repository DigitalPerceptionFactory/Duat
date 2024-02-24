#pragma once
#include "Texture.h"


namespace Duat::Graphics {

	struct Texture2D : public Texture {
		Texture2D();

		void ClearDSV(System& gfx, bool clearDepth = true, float depthValue = 0.0f, bool clearStencil = true, float stencilValue = 0.0f) override;
		void ClearDSV(System* pGFX, bool clearDepth = true, float depthValue = 0.0f, bool clearStencil = true, float stencilValue = 0.0f) override;
		void ClearRTV(System& gfx, DirectX::XMFLOAT4 color = { 0,0,0,0 }) override;
		void ClearRTV(System* pGFX, DirectX::XMFLOAT4 color = { 0,0,0,0 }) override;

		void Load(System& gfx, const std::filesystem::path& path) override;
		void Load(System* pGFX, const std::filesystem::path& path) override;
		
		void Save(System& gfx, const std::filesystem::path& path) override;
		void Save(System* pGFX, const std::filesystem::path& path) override;

		void Update(System& gfx) override;
		void Update(System* pGFX) override;
	};

}