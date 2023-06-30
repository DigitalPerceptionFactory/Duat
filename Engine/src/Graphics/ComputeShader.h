#pragma once
#include "Shader.h"


namespace Duat::Graphics {

	struct ComputeShader : public Shader, public Microsoft::WRL::ComPtr<ID3D11ComputeShader> {
		void Compile(System& gfx, const std::filesystem::path& path, const std::string& csModel = "cs_5_0",
			const std::string& entryPoint = "main");
		void Load(System& gfx, const std::filesystem::path& path);
		void Compile(System* pGFX, const std::filesystem::path& path, const std::string& csModel = "cs_5_0",
			const std::string& entryPoint = "main");
		void Load(System* pGFX, const std::filesystem::path& path);
	};

}