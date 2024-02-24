#include "Texture2D.h"
#include "System.h"


using namespace DirectX;

namespace Duat::Graphics {

	Texture2D::Texture2D()
	{
		m_type = Type::Tex2D;
		m_desc.ArraySize = 1;
		m_desc.SampleDesc.Count = 1;
		m_desc.MipLevels = 1;
		m_desc.Usage = D3D11_USAGE_DEFAULT;
	}

	void Texture2D::ClearDSV(System& gfx, bool clearDepth, float depthValue, bool clearStencil, float stencilValue)
	{
		ClearDSV(&gfx, clearDepth, depthValue, clearStencil, stencilValue);
	}

	void Texture2D::ClearDSV(System* pGFX, bool clearDepth, float depthValue, bool clearStencil, float stencilValue)
	{
		UINT clearFlags = 0;
		if (clearDepth) clearFlags |= D3D11_CLEAR_DEPTH;
		if (clearStencil) clearFlags |= D3D11_CLEAR_STENCIL;

		pGFX->m_Context->ClearDepthStencilView(m_DSV.Get(),clearFlags, depthValue, stencilValue);
	}

	void Texture2D::ClearRTV(System& gfx, DirectX::XMFLOAT4 color)
	{
		ClearRTV(&gfx, color);
	}

	void Texture2D::ClearRTV(System* pGFX, DirectX::XMFLOAT4 color)
	{
		pGFX->m_Context->ClearRenderTargetView(m_RTV.Get(), (FLOAT*)(&color));
	}

	void Texture2D::Load(System& gfx, const std::filesystem::path& path)
	{
		Load(&gfx, path);
	}

	void Texture2D::Load(System* pGFX, const std::filesystem::path& path)
	{
		ScratchImage img;

		if (path.extension() == "dds")
			m_hresult << LoadFromDDSFile(path.c_str(), DDS_FLAGS_NONE, nullptr, img);
		else if (path.extension() == "tga")
			m_hresult << LoadFromTGAFile(path.c_str(), nullptr, img);
		else if (path.extension() == "hdr")
			m_hresult << LoadFromHDRFile(path.c_str(), nullptr, img);
		else
			m_hresult << LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, nullptr, img);
				
		auto metadata = img.GetMetadata();
		m_desc.Width = (UINT)metadata.width;
		m_desc.Height = (UINT)metadata.height;
		m_desc.Format = metadata.format;
		m_desc.MipLevels = (UINT)metadata.mipLevels;
		m_desc.ArraySize = 1;
		m_desc.SampleDesc.Count = 1;
		m_desc.Usage = D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA initialData;
		ZeroMemory(&initialData, sizeof(initialData));
		initialData.pSysMem = img.GetImage(0, 0, 0)->pixels;
		initialData.SysMemPitch = (UINT)img.GetImage(0, 0, 0)->rowPitch;
		initialData.SysMemSlicePitch = 0;

		m_hresult << pGFX->m_Device->CreateTexture2D(&m_desc, &initialData, ReleaseAndGetAddressOf());
	}

	void Texture2D::Save(System& gfx, const std::filesystem::path& path)
	{
		Save(&gfx, path);
	}

	void Texture2D::Save(System* pGFX, const std::filesystem::path& path)
	{
		ScratchImage img;
		m_hresult << CaptureTexture(pGFX->m_Device.Get(), pGFX->m_Context.Get(), Get(), img);
		m_hresult << SaveToWICFile(img.GetImages(), img.GetImageCount(), DirectX::WIC_FLAGS_NONE,
			GetWICCodec(WIC_CODEC_PNG), path.wstring().c_str());
	}
		
	void Texture2D::Update(System& gfx)
	{
		Update(&gfx);
	}

	void Texture2D::Update(System* pGFX)
	{
		UINT maxSupportedQuality;
		m_hresult << pGFX->m_Device->CheckMultisampleQualityLevels(
			GetFormat(),
			m_desc.SampleDesc.Count,
			&maxSupportedQuality
		);
		if (maxSupportedQuality == 0)
		{
			m_result << "This MSAA is not supported by hardware. (Count=" + std::to_string(m_desc.SampleDesc.Count) +
				", Quality=" + std::to_string(m_desc.SampleDesc.Quality) + ")";
		}
		else if (m_desc.SampleDesc.Quality >= maxSupportedQuality)	
			m_desc.SampleDesc.Quality = maxSupportedQuality - 1;

		if (m_texture != nullptr)
		{
			ScratchImage img;
			m_hresult << CaptureTexture(pGFX->m_Device.Get(), pGFX->m_Context.Get(), Get(), img);

			size_t oldSize = img.GetImage(0, 0, 0)->width * img.GetImage(0, 0, 0)->height * BitsPerPixel(img.GetMetadata().format);
			size_t newSize = m_desc.Width * m_desc.Height * BitsPerPixel(m_desc.Format);

			if(newSize >= oldSize)
			{
				D3D11_SUBRESOURCE_DATA initialData;
				ZeroMemory(&initialData, sizeof(initialData));
				initialData.pSysMem = img.GetImage(0, 0, 0)->pixels;
				initialData.SysMemPitch = img.GetImage(0, 0, 0)->rowPitch;
				initialData.SysMemSlicePitch = 0;
				m_hresult << pGFX->m_Device->CreateTexture2D(&m_desc, &initialData, ReleaseAndGetAddressOf());
			}
			else m_hresult << pGFX->m_Device->CreateTexture2D(&m_desc, nullptr, ReleaseAndGetAddressOf());
		}
		else m_hresult << pGFX->m_Device->CreateTexture2D(&m_desc, nullptr, ReleaseAndGetAddressOf());

		if (m_desc.BindFlags & D3D11_BIND_SHADER_RESOURCE && m_srvFormat != DXGI_FORMAT_UNKNOWN)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
			ZeroMemory(&srvDesc, sizeof(srvDesc));
			srvDesc.Format = m_srvFormat;
			srvDesc.ViewDimension = GetSampleCount() > 1 ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MipLevels = m_desc.MipLevels;
			m_hresult << pGFX->m_Device->CreateShaderResourceView(Get(), &srvDesc, m_SRV.ReleaseAndGetAddressOf());
		}
		if (m_desc.BindFlags & D3D11_BIND_DEPTH_STENCIL && m_dsvFormat != DXGI_FORMAT_UNKNOWN)
		{
			D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
			ZeroMemory(&dsvDesc, sizeof(dsvDesc));
			dsvDesc.Format = m_dsvFormat;
			dsvDesc.ViewDimension = GetSampleCount() > 1 ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
			dsvDesc.Texture2D.MipSlice = 0;
			m_hresult << pGFX->m_Device->CreateDepthStencilView(Get(), &dsvDesc, m_DSV.ReleaseAndGetAddressOf());
		}
		if (m_desc.BindFlags & D3D11_BIND_RENDER_TARGET && m_rtvFormat != DXGI_FORMAT_UNKNOWN)
		{
			D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
			ZeroMemory(&rtvDesc, sizeof(rtvDesc));
			rtvDesc.ViewDimension = GetSampleCount() > 1 ? D3D11_RTV_DIMENSION_TEXTURE2DMS : D3D11_RTV_DIMENSION_TEXTURE2D;
			rtvDesc.Texture2D.MipSlice = 0;
			m_hresult << pGFX->m_Device->CreateRenderTargetView(Get(), &rtvDesc, m_RTV.ReleaseAndGetAddressOf());
		}
	}

}