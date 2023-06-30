#include "PixelShader.h"
#include "System.h"


namespace Duat::Graphics {

	void PixelShader::Compile(System& gfx, const std::filesystem::path& path, const std::string& psModel, const std::string& entryPoint)
	{
		Compile(&gfx, path, psModel, entryPoint);
	}

	void PixelShader::Load(System& gfx, const std::filesystem::path& path)
	{
		Load(&gfx, path);
	}

	void PixelShader::Compile(System* pGFX, const std::filesystem::path& path, const std::string& psModel, const std::string& entryPoint)
	{
		m_path = path;
		m_model = psModel;
		m_entryPoint = entryPoint;

		m_hresult << D3DCompileFromFile(path.c_str(), NULL,
			D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint.c_str(), psModel.c_str(),
			D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
			0, m_blob.GetAddressOf(), NULL);

		m_hresult << pGFX->m_Device->CreatePixelShader(m_blob.Get()->GetBufferPointer(),
			m_blob.Get()->GetBufferSize(), NULL, GetAddressOf());
	}

	void PixelShader::Load(System* pGFX, const std::filesystem::path& path)
	{
		m_path = path;

		m_hresult << D3DReadFileToBlob(path.c_str(), m_blob.GetAddressOf());

		m_hresult << pGFX->m_Device->CreatePixelShader(m_blob.Get()->GetBufferPointer(),
			m_blob.Get()->GetBufferSize(), NULL, GetAddressOf());
	}


}