#pragma once
#include <string>
#include <filesystem>
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <Utility/ErrorHandling.h>


namespace Duat::Graphics {

	enum class ShaderType {
		Null,VS,PS,CS
	};


	struct System;
	struct Shader
	{
		virtual void Compile(System* pGFX, const std::filesystem::path& path, const std::string& model,
			const std::string& entryPoint) = 0;
		virtual void Load(System* pGFX, const std::filesystem::path& path) = 0;
		ShaderType GetShaderType() { return m_type; }
	protected:
		Utility::Result m_result;
		Utility::HResult m_hresult;

		ShaderType m_type = ShaderType::Null;
		std::filesystem::path m_path;
		std::string m_model;
		std::string m_entryPoint;
		Microsoft::WRL::ComPtr<ID3DBlob> m_blob;
	};

}