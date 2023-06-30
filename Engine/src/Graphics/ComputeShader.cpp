#include "ComputeShader.h"
#include "System.h"


namespace Duat::Graphics {

	void ComputeShader::Compile(System& gfx, const std::filesystem::path& path, const std::string& csModel, const std::string& entryPoint)
	{
		Compile(&gfx, path, csModel, entryPoint);
	}

	void ComputeShader::Load(System& gfx, const std::filesystem::path& path)
	{
		Load(&gfx, path);
	}

	void ComputeShader::Compile(System* pGFX, const std::filesystem::path& path, const std::string& csModel, const std::string& entryPoint)
	{
		m_path = path;
		m_model = csModel;
		m_entryPoint = entryPoint;

		m_hresult << D3DCompileFromFile(path.c_str(), NULL, NULL, entryPoint.c_str(), csModel.c_str(),
			D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
			0, m_blob.GetAddressOf(), NULL);

		m_hresult << pGFX->m_Device->CreateComputeShader(m_blob.Get()->GetBufferPointer(),
			m_blob.Get()->GetBufferSize(), NULL, GetAddressOf());
	}

	void ComputeShader::Load(System* pGFX, const std::filesystem::path& path)
	{
		m_path = path;

		m_hresult << D3DReadFileToBlob(path.c_str(), m_blob.GetAddressOf());

		m_hresult << pGFX->m_Device->CreateComputeShader(m_blob.Get()->GetBufferPointer(),
			m_blob.Get()->GetBufferSize(), NULL, GetAddressOf());
	}

}