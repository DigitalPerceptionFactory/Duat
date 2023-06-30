#pragma once
#include <vector>
#include "Shader.h"


namespace Duat::Graphics {
	
	struct VertexShader : public Shader, public Microsoft::WRL::ComPtr<ID3D11VertexShader> {
		void Compile(System& gfx, const std::filesystem::path& path, const std::string& vsModel = "vs_5_0",
			const std::string& entryPoint = "main");
		void Load(System& gfx, const std::filesystem::path& path);
		void Compile(System* pGFX, const std::filesystem::path& path, const std::string& vsModel = "vs_5_0",
			const std::string& entryPoint = "main");
		void Load(System* pGFX, const std::filesystem::path& path);
	private:
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	};

}