#include "TextureCube.h"
#include "System.h"


using namespace DirectX;

namespace Duat::Graphics
{

	TextureCube::~TextureCube()
	{
		for(auto& img : m_images)
			img.Release();
	}

	TextureCube::TextureCube(System& gfx, const std::filesystem::path& path)
	{
		Init(gfx, path);
	}

	TextureCube::TextureCube(System* pGFX, const std::filesystem::path& path)
	{
		Init(pGFX, path);
	}

	void TextureCube::Init(System& gfx, const std::filesystem::path& path)
	{
		Init(&gfx, path);
	}

	void TextureCube::Init(System* pGFX, const std::filesystem::path& path)
	{
		m_images.resize(6);

		if (pGFX == nullptr)
		{
			Utility::Result result;
			result << "You can't initialize TextureCube because System pointer you provided is a null pointer.";
			return;
		}
		m_pGFX = pGFX;

		std::filesystem::path pathCopy = path;
		for(int i = 0; i < 6; ++i)
		{
			pathCopy.replace_filename(path.filename().string() + std::to_string(i));
			if (path.extension() == "dds")
				m_hresult << LoadFromDDSFile(pathCopy.c_str(), DDS_FLAGS_NONE, nullptr, m_images[i]);
			else if (path.extension() == "tga")
				m_hresult << LoadFromTGAFile(pathCopy.c_str(), nullptr, m_images[i]);
			else if (path.extension() == "hdr")
				m_hresult << LoadFromHDRFile(pathCopy.c_str(), nullptr, m_images[i]);
			else
				m_hresult << LoadFromWICFile(pathCopy.c_str(), WIC_FLAGS_NONE, nullptr, m_images[i]);
		}

		auto metadata = m_images[0].GetMetadata();
		m_desc.Width = (UINT)metadata.width;
		m_desc.Height = (UINT)metadata.height;
		m_desc.MipLevels = (UINT)metadata.mipLevels;
		m_desc.ArraySize = 6;
		m_desc.Format = metadata.format;
		m_desc.SampleDesc.Count = 1;
		m_desc.Usage = D3D11_USAGE_DEFAULT;
		m_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		m_desc.CPUAccessFlags = 0;
		m_desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

		D3D11_SUBRESOURCE_DATA initialData[6];
		for(int i = 0; i < 6; ++i)
		{
			ZeroMemory(&initialData, sizeof(initialData));
			initialData[i].pSysMem = m_images[i].GetImage(0, 0, 0)->pixels;
			initialData[i].SysMemPitch = (UINT)m_images[i].GetImage(0, 0, 0)->rowPitch;
			initialData[i].SysMemSlicePitch = 0;
		}

		m_hresult << pGFX->m_Device->CreateTexture2D(&m_desc, initialData, ReleaseAndGetAddressOf());
		InitViews();
	}

	void TextureCube::Init(System& gfx, D3D11_TEXTURE2D_DESC desc, DXGI_FORMAT srvFormat, DXGI_FORMAT dsvFormat, DXGI_FORMAT rtvFormat)
	{
		Init(&gfx, desc, srvFormat, dsvFormat, rtvFormat);
	}

	void TextureCube::Init(System* pGFX, D3D11_TEXTURE2D_DESC desc, DXGI_FORMAT srvFormat, DXGI_FORMAT dsvFormat, DXGI_FORMAT rtvFormat)
	{
		if (pGFX == nullptr)
		{
			Utility::Result result;
			result << "You can't initialize Texture2D because System pointer you provided is a null pointer.";
			return;
		}

		m_pGFX = pGFX;
		m_desc = desc;
		m_srvFormat = srvFormat;
		m_rtvFormat = rtvFormat;
		m_dsvFormat = dsvFormat;
		m_hresult << pGFX->m_Device->CreateTexture2D(&m_desc, nullptr, ReleaseAndGetAddressOf());
		InitViews();
	}

	TextureCube& TextureCube::operator=(const TextureCube& rhs)
	{
		m_pGFX = rhs.m_pGFX;
		m_hresult = rhs.m_hresult;
		m_texture = rhs.m_texture;
		m_SRV = rhs.m_SRV;
		m_RTV = rhs.m_RTV;
		m_DSV = rhs.m_DSV;
		m_desc = rhs.m_desc;
		for(int i = 0; i < 6; ++i)
		{
			m_images[i].Initialize(rhs.m_images[i].GetMetadata());
			std::memcpy(m_images[i].GetPixels(), rhs.m_images[i].GetPixels(), rhs.m_images[i].GetPixelsSize());
		}
		return *this;
	}

	void TextureCube::Save(const std::filesystem::path& path) const
	{
		ScratchImage img;
		m_hresult << CaptureTexture(m_pGFX->m_Device.Get(), m_pGFX->m_Context.Get(), m_texture.Get(), img);
		m_hresult << SaveToWICFile(img.GetImages(), img.GetImageCount(), DirectX::WIC_FLAGS_NONE,
			GetWICCodec(WIC_CODEC_PNG), path.wstring().c_str());
	}

	void TextureCube::SaveDepth(const std::filesystem::path& path) const
	{
		D3D11_TEXTURE2D_DESC desc;
		m_texture.Get()->GetDesc(&desc);
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		desc.Usage = D3D11_USAGE_STAGING;
		desc.BindFlags = 0;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> tempTex2D;
		D3D11_MAPPED_SUBRESOURCE msr = {};

		m_hresult << m_pGFX->m_Device->CreateTexture2D(&desc, nullptr, tempTex2D.GetAddressOf());
		m_pGFX->m_Context->CopyResource(tempTex2D.Get(), m_texture.Get());
		m_hresult << m_pGFX->m_Context->Map(tempTex2D.Get(), 0, D3D11_MAP_READ, 0, &msr);

		ScratchImage img;
		m_hresult << img.Initialize2D(DXGI_FORMAT_R32G32B32A32_FLOAT, GetWidth(), GetHeight(), 1, 1);

		auto pData = static_cast<float*>(msr.pData);
		auto pPixels = reinterpret_cast<float*>(img.GetPixels());
		for (int y = 0; y < GetHeight(); ++y)
			for (int x = 0; x < GetWidth(); ++x)
			{
				size_t index = size_t(y * GetWidth() + x);
				if (pData[index] != 1.0f)
				{
					pPixels[index * 4] = pData[index];
					pPixels[index * 4 + 1] = pData[index];
					pPixels[index * 4 + 2] = pData[index];
					pPixels[index * 4 + 3] = 1.0f;
				}
				else {
					pPixels[index * 4] = 0;
					pPixels[index * 4 + 1] = 0;
					pPixels[index * 4 + 2] = 0;
					pPixels[index * 4 + 3] = 1.0f;
				}

			}

		m_pGFX->m_Context->Unmap(tempTex2D.Get(), 0);

		m_hresult << SaveToWICFile(img.GetImages(), img.GetImageCount(), DirectX::WIC_FLAGS_NONE,
			GetWICCodec(WIC_CODEC_PNG), path.wstring().c_str());
	}

	D3D11_TEXTURE2D_DESC TextureCube::GetDesc() const
	{
		return m_desc;
	}

	UINT TextureCube::GetWidth() const
	{
		return m_desc.Width;
	}

	UINT TextureCube::GetHeight() const
	{
		return m_desc.Height;
	}

	UINT TextureCube::GetMipLevels() const
	{
		return m_desc.MipLevels;
	}

	UINT TextureCube::GetArraySize() const
	{
		return m_desc.ArraySize;
	}

	DXGI_FORMAT TextureCube::GetFormat() const
	{
		return m_desc.Format;
	}

	UINT TextureCube::GetSampleCount() const
	{
		return m_desc.SampleDesc.Count;
	}

	UINT TextureCube::GetSampleQuality() const
	{
		return m_desc.SampleDesc.Quality;
	}

	Usage TextureCube::GetUsage() const
	{
		return Usage(m_desc.Usage);
	}

	UINT TextureCube::GetBindFlags() const
	{
		return m_desc.BindFlags;
	}

	UINT TextureCube::GetCPUAccessFlags() const
	{
		return m_desc.CPUAccessFlags;
	}

	UINT TextureCube::GetMiscFlags() const
	{
		return m_desc.MiscFlags;
	}

	ID3D11Texture2D* TextureCube::Get()
	{
		return m_texture.Get();
	}

	ID3D11Texture2D** TextureCube::GetAddressOf()
	{
		return m_texture.GetAddressOf();
	}

	ID3D11Texture2D** TextureCube::ReleaseAndGetAddressOf()
	{
		return m_texture.ReleaseAndGetAddressOf();
	}

	ID3D11ShaderResourceView* TextureCube::GetSRV()
	{
		return m_SRV.Get();
	}

	ID3D11ShaderResourceView** TextureCube::GetSRVAddressOf()
	{
		return m_SRV.GetAddressOf();
	}

	ID3D11RenderTargetView* TextureCube::GetRTV()
	{
		return m_RTV.Get();
	}

	ID3D11RenderTargetView** TextureCube::GetRTVAddressOf()
	{
		return m_RTV.GetAddressOf();
	}

	ID3D11DepthStencilView* TextureCube::GetDSV()
	{
		return m_DSV.Get();
	}

	ID3D11DepthStencilView** TextureCube::GetDSVAddressOf()
	{
		return m_DSV.GetAddressOf();
	}

	void TextureCube::SetDesc(D3D11_TEXTURE2D_DESC desc)
	{
		m_desc = desc;
		UpdateTexture();
	}

	void TextureCube::SetWidth(UINT width)
	{
		m_desc.Width = width;
		UpdateTexture();
	}

	void TextureCube::SetHeight(UINT height)
	{
		m_desc.Height = height;
		UpdateTexture();
	}

	void TextureCube::SetMipLevels(UINT mipLevels)
	{
		m_desc.MipLevels = mipLevels;
		UpdateTexture();
	}

	void TextureCube::SetArraySize(UINT arraySize)
	{
		m_desc.ArraySize = arraySize;
		UpdateTexture();
	}

	void TextureCube::SetFormat(DXGI_FORMAT format)
	{
		m_desc.Format = format;
		UpdateTexture();
	}

	void TextureCube::SetSample(UINT count, UINT quality)
	{
		UINT maxSupportedQuality;
		m_hresult << m_pGFX->m_Device->CheckMultisampleQualityLevels(
			GetFormat(),
			count,
			&maxSupportedQuality
		);
		if (maxSupportedQuality == 0) return;

		if (quality >= maxSupportedQuality)	m_desc.SampleDesc.Quality = maxSupportedQuality - 1;
		m_desc.SampleDesc.Count = count;
		UpdateTexture();
	}

	void TextureCube::SetUsage(Usage usage)
	{
		m_desc.Usage = D3D11_USAGE(usage);
		UpdateTexture();
	}

	void TextureCube::SetBindFlags(UINT bindFlags)
	{
		m_desc.BindFlags = bindFlags;
		UpdateTexture();
	}

	void TextureCube::SetCPUAccessFlags(UINT cpuFlags)
	{
		m_desc.CPUAccessFlags = cpuFlags;
		UpdateTexture();
	}

	void TextureCube::SetMiscFlags(UINT miscFlags)
	{
		m_desc.MiscFlags = miscFlags;
		UpdateTexture();
	}

	void TextureCube::InitViews()
	{
		if (m_pGFX == nullptr)
		{
			Utility::Result result;
			result << "For some reason m_pGFX is a nullptr.";
			return;
		}
		if (m_desc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc;
			ZeroMemory(&srv_desc, sizeof(srv_desc));
			srv_desc.Format = m_srvFormat == DXGI_FORMAT_UNKNOWN ? m_desc.Format : m_srvFormat;
			srv_desc.ViewDimension = GetSampleCount() > 1 ? D3D11_SRV_DIMENSION_TEXTURE2DMS : D3D11_SRV_DIMENSION_TEXTURE2D;
			srv_desc.Texture2D.MipLevels = m_desc.MipLevels;
			srv_desc.Texture2D.MostDetailedMip = 0;
			m_hresult << m_pGFX->m_Device->CreateShaderResourceView(Get(), &srv_desc, m_SRV.ReleaseAndGetAddressOf());
		}
		if (m_desc.BindFlags & D3D11_BIND_DEPTH_STENCIL)
		{
			D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc;
			ZeroMemory(&dsv_desc, sizeof(dsv_desc));
			dsv_desc.Format = m_dsvFormat == DXGI_FORMAT_UNKNOWN ? m_desc.Format : m_dsvFormat;
			dsv_desc.ViewDimension = GetSampleCount() > 1 ? D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
			dsv_desc.Texture2D.MipSlice = 0;
			m_hresult << m_pGFX->m_Device->CreateDepthStencilView(Get(), &dsv_desc, m_DSV.ReleaseAndGetAddressOf());
		}
		if (m_desc.BindFlags & D3D11_BIND_RENDER_TARGET)
		{
			D3D11_RENDER_TARGET_VIEW_DESC rtv_desc;
			ZeroMemory(&rtv_desc, sizeof(rtv_desc));
			rtv_desc.Format = m_rtvFormat == DXGI_FORMAT_UNKNOWN ? m_desc.Format : m_rtvFormat;
			rtv_desc.ViewDimension = GetSampleCount() > 1 ? D3D11_RTV_DIMENSION_TEXTURE2DMS : D3D11_RTV_DIMENSION_TEXTURE2D;
			rtv_desc.Texture2D.MipSlice = 0;
			m_hresult << m_pGFX->m_Device->CreateRenderTargetView(Get(), &rtv_desc, m_RTV.ReleaseAndGetAddressOf());
		}
	}

	void TextureCube::UpdateTexture()
	{
		if (m_pGFX == nullptr)
		{
			Utility::Result result;
			result << "For some reason m_pGFX is a nullptr.";
			return;
		}
		Microsoft::WRL::ComPtr<ID3D11Texture2D> newTexture;
		m_hresult << m_pGFX->m_Device->CreateTexture2D(&m_desc, nullptr, newTexture.GetAddressOf());
		//m_pGFX->m_Context->CopyResource(newTexture.Get(), Get());
		m_texture = newTexture;
		InitViews();
	}

}