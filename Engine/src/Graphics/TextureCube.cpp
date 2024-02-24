#include "TextureCube.h"
#include "System.h"


using namespace DirectX;

namespace Duat::Graphics {

	TextureCube::TextureCube()
	{
		m_type = Type::Cube;
		m_desc.Width = m_desc.Height = 4096;
		m_desc.Usage = D3D11_USAGE_DEFAULT;
		m_desc.ArraySize = 6;
		m_desc.SampleDesc.Count = 1;
		m_desc.MipLevels = 1;
		m_desc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
		m_desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
	}

	TextureCube::TextureCube(size_t cubeFaceWidth)
	{
		m_type = Type::Cube;
		m_desc.Width = m_desc.Height = cubeFaceWidth;
		m_desc.Usage = D3D11_USAGE_DEFAULT;
		m_desc.ArraySize = 6;
		m_desc.SampleDesc.Count = 1;
		m_desc.MipLevels = 1;
		m_desc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
		m_desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
	}

	void TextureCube::ClearDSV(System& gfx, bool clearDepth, float depthValue, bool clearStencil, float stencilValue)
	{
		ClearDSV(&gfx, clearDepth, depthValue, clearStencil, stencilValue);
	}

	void TextureCube::ClearDSV(System* pGFX, bool clearDepth, float depthValue, bool clearStencil, float stencilValue)
	{
		UINT clearFlags = 0;
		if (clearDepth) clearFlags |= D3D11_CLEAR_DEPTH;
		if (clearStencil) clearFlags |= D3D11_CLEAR_STENCIL;

		for (int i = 0; i < 6; ++i)
			pGFX->m_Context->ClearDepthStencilView(m_faceDSV[i].Get(), clearFlags, depthValue, stencilValue);

		// for (int i = 0; i < 6; ++i)
		// 	m_faces[i].ClearDSV(pGFX, clearDepth, depthValue, clearStencil, stencilValue);
	}

	void TextureCube::ClearRTV(System& gfx, DirectX::XMFLOAT4 color)
	{
		ClearRTV(&gfx, color);
	}

	void TextureCube::ClearRTV(System* pGFX, DirectX::XMFLOAT4 color)
	{
		for (int i = 0; i < 6; ++i)
			pGFX->m_Context->ClearRenderTargetView(m_faceRTV[i].Get(), (FLOAT*)(&color));

		// for (int i = 0; i < 6; ++i)
		// 	m_faces[i].ClearRTV(pGFX, color);
	}

	void TextureCube::Load(System& gfx, const std::filesystem::path& path)
	{
		Load(&gfx, path);
	}

	void TextureCube::Load(System* pGFX, const std::filesystem::path& path)
	{
		//m_result << "not implemented yet remember to fix.";
		std::string justPath = path.string().substr(0,
			path.string().length() - path.filename().string().length());
		std::string justName = path.filename().string().substr(0,
			path.filename().string().length() - path.extension().string().length() - 1);
				
		ScratchImage images[6];
		for (int i = 0; i < 6; ++i)
		{
			std::filesystem::path loadPath = justPath + justName + std::to_string(i) + path.extension().string();
			if (path.extension() == "dds")
				m_hresult << LoadFromDDSFile(loadPath.c_str(), DDS_FLAGS_NONE, nullptr, images[i]);
			else if (path.extension() == "tga")
				m_hresult << LoadFromTGAFile(loadPath.c_str(), nullptr, images[i]);
			else if (path.extension() == "hdr")
				m_hresult << LoadFromHDRFile(loadPath.c_str(), nullptr, images[i]);
			else
				m_hresult << LoadFromWICFile(loadPath.c_str(), WIC_FLAGS_NONE, nullptr, images[i]);
		}

		D3D11_SUBRESOURCE_DATA initialData[6];
		ZeroMemory(&initialData, sizeof(D3D11_SUBRESOURCE_DATA) * 6);
		for (int i = 0; i < 6; ++i)
		{
			initialData[i].pSysMem = images[i].GetImage(0, 0, 0)->pixels;
			initialData[i].SysMemPitch = (UINT)images[i].GetImage(0, 0, 0)->rowPitch;
			initialData[i].SysMemSlicePitch = 0;
		}
		//m_faces[i].Load(pGFX, justPath + justName + std::to_string(i) + path.extension().string());

		auto metadata = images[0].GetMetadata();
		m_desc.Width = (UINT)metadata.width;
		m_desc.Height = (UINT)metadata.height;
		m_desc.Format = metadata.format;
		m_srvFormat = m_desc.Format;

		m_hresult << pGFX->m_Device->CreateTexture2D(&m_desc, initialData, ReleaseAndGetAddressOf());

		//SyncDesc();
		SetSRVFormat(m_desc.Format);
		Update(pGFX);
	}

	void TextureCube::Save(System& gfx, const std::filesystem::path& path)
	{
		Save(&gfx, path);
	}

	void TextureCube::Save(System* pGFX, const std::filesystem::path& path)
	{
		m_result << "Not implemented yet, requires capturing texture slices.";
		std::string dir = path.string().substr(0, path.string().length() - path.filename().string().length());
		std::string name = path.filename().string().substr(0, path.filename().string().length() - path.extension().string().length());
		// for (int i = 0; i < 6; ++i)
		// 	m_faces[i].Save(pGFX, dir + name + std::to_string(i) + path.extension().string());
	}

	void TextureCube::Update(System& gfx)
	{
		Update(&gfx);
	}

	void TextureCube::Update(System* pGFX)
	{
		// ScratchImage images[6];
		// D3D11_SUBRESOURCE_DATA initialData[6];
		// ZeroMemory(&initialData, sizeof(D3D11_SUBRESOURCE_DATA) * 6);

		for (int i = 0; i < 6; ++i)
		{
			//  m_faces[i].SetDesc(m_desc);
			//  m_faces[i].SetMiscFlags(0);
			//  m_faces[i].SetArraySize(1);
			//  m_faces[i].SetSRVFormat(m_srvFormat);
			//  m_faces[i].SetDSVFormat(m_dsvFormat);
			//  m_faces[i].SetRTVFormat(m_rtvFormat);
			//  m_faces[i].Update(pGFX);

			//  m_hresult << CaptureTexture(pGFX->m_Device.Get(), pGFX->m_Context.Get(), m_faces[i].Get(), images[i]);
			//  initialData[i].pSysMem = images[i].GetImage(0, 0, 0)->pixels;
			//  initialData[i].SysMemPitch = (UINT)images[i].GetImage(0, 0, 0)->rowPitch;
			//  initialData[i].SysMemSlicePitch = 0;

			//  pGFX->m_Context->UpdateSubresource(Get(), D3D11CalcSubresource(0, i, 1), nullptr,
			//  	img.GetImage(0, 0, 0)->pixels, img.GetImage(0, 0, 0)->rowPitch, 0);
		}

		if(!Get())
			m_hresult << pGFX->m_Device->CreateTexture2D(&m_desc, nullptr, ReleaseAndGetAddressOf());

		if (m_desc.BindFlags & D3D11_BIND_SHADER_RESOURCE && m_srvFormat != DXGI_FORMAT_UNKNOWN)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
			ZeroMemory(&srvDesc, sizeof(srvDesc));
			srvDesc.Format = m_srvFormat;
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
			srvDesc.TextureCube.MipLevels = -1;
			m_hresult << pGFX->m_Device->CreateShaderResourceView(Get(), &srvDesc, m_SRV.ReleaseAndGetAddressOf());

			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
			srvDesc.Texture2DArray.ArraySize = 1;
			srvDesc.Texture2DArray.MipLevels = -1;
			for (int i = 0; i < 6; ++i)
			{
				srvDesc.Texture2DArray.FirstArraySlice = i;
				m_hresult << pGFX->m_Device->CreateShaderResourceView(Get(), &srvDesc, m_faceSRV[i].ReleaseAndGetAddressOf());
			}

		}
		if (m_desc.BindFlags & D3D11_BIND_DEPTH_STENCIL && m_dsvFormat != DXGI_FORMAT_UNKNOWN)
		{
			D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
			ZeroMemory(&dsvDesc, sizeof(dsvDesc));
			dsvDesc.Format = m_dsvFormat;
			dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
			dsvDesc.Texture2DArray.ArraySize = 1;
			
			for (int i = 0; i < 6; ++i)
			{
				dsvDesc.Texture2DArray.FirstArraySlice = i;
				m_hresult << pGFX->m_Device->CreateDepthStencilView(Get(), &dsvDesc, m_faceDSV[i].ReleaseAndGetAddressOf());
			}

			// Cube Texture does not support DSV yet.
		}
		if (m_desc.BindFlags & D3D11_BIND_RENDER_TARGET && m_rtvFormat != DXGI_FORMAT_UNKNOWN)
		{
			// Cube Texture does not support RTV yet.
		}
	}

	ID3D11ShaderResourceView* TextureCube::GetSRV(size_t index)
	{
		return m_faceSRV[std::clamp<size_t>(index, 0, 5)].Get();
	}

	ID3D11ShaderResourceView** TextureCube::GetSRVAddressOf(size_t index)
	{
		return m_faceSRV[std::clamp<size_t>(index, 0, 5)].GetAddressOf();
	}

	ID3D11ShaderResourceView** TextureCube::ReleaseSRVAndGetAddressOf(size_t index)
	{
		return m_faceSRV[std::clamp<size_t>(index, 0, 5)].ReleaseAndGetAddressOf();
	}

	ID3D11DepthStencilView* TextureCube::GetDSV(size_t index)
	{
		return m_faceDSV[std::clamp<size_t>(index, 0, 5)].Get();
	}

	ID3D11DepthStencilView** TextureCube::GetDSVAddressOf(size_t index)
	{
		return m_faceDSV[std::clamp<size_t>(index, 0, 5)].GetAddressOf();
	}

	ID3D11DepthStencilView** TextureCube::ReleaseDSVAndGetAddressOf(size_t index)
	{
		return m_faceDSV[std::clamp<size_t>(index, 0, 5)].ReleaseAndGetAddressOf();
	}

	ID3D11RenderTargetView* TextureCube::GetRTV(size_t index)
	{
		return m_faceRTV[std::clamp<size_t>(index, 0, 5)].Get();
	}

	ID3D11RenderTargetView** TextureCube::GetRTVAddressOf(size_t index)
	{
		return m_faceRTV[std::clamp<size_t>(index, 0, 5)].GetAddressOf();
	}

	ID3D11RenderTargetView** TextureCube::ReleaseRTVAndGetAddressOf(size_t index)
	{
		return m_faceRTV[std::clamp<size_t>(index, 0, 5)].ReleaseAndGetAddressOf();
	}

	//  Texture2D& TextureCube::GetFace(size_t index)
	//  {
	//  	if (index > 5) m_result << std::to_string(index) + " is not valid index.";
	//  	return m_faces[std::clamp<size_t>(index, 0, 5)];
	//  }

	//  void TextureCube::SyncDesc()
	//  {
	//  	m_desc = m_faces[0].GetDesc();
	//  	m_desc.Usage = D3D11_USAGE_DEFAULT;
	//  	m_desc.ArraySize = 6;
	//  	m_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	//  	m_desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
	//  }
}