#include "VertexShader.h"
#include "System.h"


namespace Duat::Graphics {
		
	void VertexShader::Compile(System& gfx, const std::filesystem::path& path, const std::string& vsModel, const std::string& entryPoint)
	{
		Compile(&gfx, path, vsModel, entryPoint);
	}

	void VertexShader::Load(System& gfx, const std::filesystem::path& path)
	{
		Load(&gfx, path);
	}

	void VertexShader::Compile(System* pGFX, const std::filesystem::path& path, const std::string& vsModel, const std::string& entryPoint)
	{
		m_path = path;
		m_model = vsModel;
		m_entryPoint = entryPoint;

		m_hresult << D3DCompileFromFile(path.c_str(), NULL,
			D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint.c_str(), vsModel.c_str(),
			D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
			0, m_blob.GetAddressOf(), NULL);
		
		m_hresult << pGFX->m_Device->CreateVertexShader(m_blob.Get()->GetBufferPointer(),
			m_blob.Get()->GetBufferSize(), NULL, GetAddressOf());

		ID3D11ShaderReflection* vsReflection;
		m_hresult << D3DReflect(m_blob->GetBufferPointer(), m_blob->GetBufferSize(),
			IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&vsReflection));
		D3D11_SHADER_DESC vsDesc;
		m_hresult << vsReflection->GetDesc(&vsDesc);

		std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDescs;
		for (UINT i = 0; i < vsDesc.InputParameters; ++i)
		{
			D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
			vsReflection->GetInputParameterDesc(i, &paramDesc);

			D3D11_INPUT_ELEMENT_DESC inputDesc;
			inputDesc.SemanticName = paramDesc.SemanticName;
			inputDesc.SemanticIndex = paramDesc.SemanticIndex;
			inputDesc.InputSlot = paramDesc.Register;
			inputDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			inputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			inputDesc.InstanceDataStepRate = 0;

			if (paramDesc.Mask == 1)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
					inputDesc.Format = DXGI_FORMAT_R32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
					inputDesc.Format = DXGI_FORMAT_R32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
					inputDesc.Format = DXGI_FORMAT_R32_FLOAT;
			}
			else if (paramDesc.Mask <= 3)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
					inputDesc.Format = DXGI_FORMAT_R32G32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
					inputDesc.Format = DXGI_FORMAT_R32G32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
					inputDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
			}
			else if (paramDesc.Mask <= 7)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
					inputDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
					inputDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
					inputDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			}
			else if (paramDesc.Mask <= 15)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
					inputDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
					inputDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
					inputDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			}

			inputElementDescs.push_back(inputDesc);
		}

		m_hresult << pGFX->m_Device->CreateInputLayout(inputElementDescs.data(), (UINT)inputElementDescs.size(),
			m_blob.Get()->GetBufferPointer(), m_blob.Get()->GetBufferSize(), m_inputLayout.GetAddressOf());
	}

	void VertexShader::Load(System* pGFX, const std::filesystem::path& path)
	{
		m_path = path;
		m_hresult << D3DReadFileToBlob(path.c_str(), m_blob.GetAddressOf());

		m_hresult << pGFX->m_Device->CreateVertexShader(m_blob.Get()->GetBufferPointer(),
			m_blob.Get()->GetBufferSize(), NULL, GetAddressOf());
		
		ID3D11ShaderReflection* vsReflection;
		m_hresult << D3DReflect(m_blob->GetBufferPointer(), m_blob->GetBufferSize(),
			IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&vsReflection));
		D3D11_SHADER_DESC vsDesc;
		m_hresult << vsReflection->GetDesc(&vsDesc);

		std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDescs;
		for (UINT i = 0; i < vsDesc.InputParameters; ++i)
		{
			D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
			vsReflection->GetInputParameterDesc(i, &paramDesc);

			D3D11_INPUT_ELEMENT_DESC inputDesc;
			inputDesc.SemanticName = paramDesc.SemanticName;
			inputDesc.SemanticIndex = paramDesc.SemanticIndex;
			inputDesc.InputSlot = paramDesc.Register;
			inputDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			inputDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			inputDesc.InstanceDataStepRate = 0;

			if (paramDesc.Mask == 1)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
					inputDesc.Format = DXGI_FORMAT_R32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
					inputDesc.Format = DXGI_FORMAT_R32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
					inputDesc.Format = DXGI_FORMAT_R32_FLOAT;
			}
			else if (paramDesc.Mask <= 3)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
					inputDesc.Format = DXGI_FORMAT_R32G32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
					inputDesc.Format = DXGI_FORMAT_R32G32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
					inputDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
			}
			else if (paramDesc.Mask <= 7)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
					inputDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
					inputDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
					inputDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			}
			else if (paramDesc.Mask <= 15)
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
					inputDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
					inputDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
					inputDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			}

			inputElementDescs.push_back(inputDesc);
		}

		m_hresult << pGFX->m_Device->CreateInputLayout(inputElementDescs.data(), (UINT)inputElementDescs.size(),
			m_blob.Get()->GetBufferPointer(), m_blob.Get()->GetBufferSize(), m_inputLayout.GetAddressOf());
	}
		
}