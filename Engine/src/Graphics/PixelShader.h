#pragma once
#include "Shader.h"


namespace Duat::Graphics {

	struct PixelShader : public Shader, public Microsoft::WRL::ComPtr<ID3D11PixelShader> {
		void Compile(System& gfx, const std::filesystem::path& path, const std::string& psModel = "ps_5_0",
			const std::string& entryPoint = "main");
		void Load(System& gfx, const std::filesystem::path& path);
		void Compile(System* pGFX, const std::filesystem::path& path, const std::string& psModel = "ps_5_0",
			const std::string& entryPoint = "main");
		void Load(System* pGFX, const std::filesystem::path& path);
	};

}