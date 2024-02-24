#include "Texture.h"
#include "System.h"


using namespace DirectX;

namespace Duat::Graphics {

	/*Texture& Texture::operator=(const Texture& rhs)
	{
		m_pGFX = rhs.m_pGFX;
		m_hresult = rhs.m_hresult;
		m_texture = rhs.m_texture;
		m_SRV = rhs.m_SRV;
		m_RTV = rhs.m_RTV;
		m_DSV = rhs.m_DSV;
		m_desc = rhs.m_desc;
		m_type = rhs.m_type;
		m_images.resize(rhs.m_images.size());
		for (int i = 0; i < m_images.size(); ++i)
		{
			m_images[i].Initialize(rhs.m_images[i].GetMetadata());
			std::memcpy(m_images[i].GetPixels(), rhs.m_images[i].GetPixels(), rhs.m_images[i].GetPixelsSize());
		}
		return *this;
	}*/

	/*/void Texture::SaveDepth(const std::filesystem::path& path) const
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
	}*/

	Texture::Type Texture::GetTextureType() const
	{
		return m_type;
	}

	D3D11_TEXTURE2D_DESC Texture::GetDesc() const
	{
		return m_desc;
	}

	UINT Texture::GetWidth() const
	{
		return m_desc.Width;
	}

	UINT Texture::GetHeight() const
	{
		return m_desc.Height;
	}

	UINT Texture::GetMipLevels() const
	{
		return m_desc.MipLevels;
	}

	UINT Texture::GetArraySize() const
	{
		return m_desc.ArraySize;
	}

	DXGI_FORMAT Texture::GetFormat() const
	{
		return m_desc.Format;
	}

	DXGI_FORMAT Texture::GetSRVFormat() const
	{
		return m_srvFormat;
	}

	DXGI_FORMAT Texture::GetDSVFormat() const
	{
		return m_dsvFormat;
	}

	DXGI_FORMAT Texture::GetRTVFormat() const
	{
		return m_rtvFormat;
	}

	UINT Texture::GetSampleCount() const
	{
		return m_desc.SampleDesc.Count;
	}

	UINT Texture::GetSampleQuality() const
	{
		return m_desc.SampleDesc.Quality;
	}

	Usage Texture::GetUsage() const
	{
		return Usage(m_desc.Usage);
	}

	UINT Texture::GetBindFlags() const
	{
		return m_desc.BindFlags;
	}

	UINT Texture::GetCPUAccessFlags() const
	{
		return m_desc.CPUAccessFlags;
	}

	UINT Texture::GetMiscFlags() const
	{
		return m_desc.MiscFlags;
	}

	ID3D11Texture2D* Texture::Get()
	{
		return m_texture.Get();
	}

	ID3D11Texture2D** Texture::GetAddressOf()
	{
		return m_texture.GetAddressOf();
	}

	ID3D11Texture2D** Texture::ReleaseAndGetAddressOf()
	{
		return m_texture.ReleaseAndGetAddressOf();
	}

	ID3D11ShaderResourceView* Texture::GetSRV()
	{
		return m_SRV.Get();
	}

	ID3D11ShaderResourceView** Texture::GetSRVAddressOf()
	{
		return m_SRV.GetAddressOf();
	}

	ID3D11ShaderResourceView** Texture::ReleaseSRVAndGetAddressOf()
	{
		return m_SRV.ReleaseAndGetAddressOf();
	}

	ID3D11DepthStencilView* Texture::GetDSV()
	{
		return m_DSV.Get();
	}

	ID3D11DepthStencilView** Texture::GetDSVAddressOf()
	{
		return m_DSV.GetAddressOf();
	}

	ID3D11DepthStencilView** Texture::ReleaseDSVAndGetAddressOf()
	{
		return m_DSV.ReleaseAndGetAddressOf();
	}

	ID3D11RenderTargetView* Texture::GetRTV()
	{
		return m_RTV.Get();
	}

	ID3D11RenderTargetView** Texture::GetRTVAddressOf()
	{
		return m_RTV.GetAddressOf();
	}

	ID3D11RenderTargetView** Texture::ReleaseRTVAndGetAddressOf()
	{
		return m_RTV.ReleaseAndGetAddressOf();
	}

	void Texture::SetDesc(D3D11_TEXTURE2D_DESC desc)
	{
		m_desc = desc;
	}

	void Texture::SetWidth(UINT width)
	{
		m_desc.Width = width;
	}

	void Texture::SetHeight(UINT height)
	{
		m_desc.Height = height;
	}

	void Texture::SetMipLevels(UINT mipLevels)
	{
		m_desc.MipLevels = mipLevels;
	}

	void Texture::SetArraySize(UINT arraySize)
	{
		m_desc.ArraySize = arraySize;
	}

	void Texture::SetFormat(DXGI_FORMAT format)
	{
		m_desc.Format = format;
	}

	void Texture::SetSRVFormat(DXGI_FORMAT format)
	{
		m_srvFormat = format;
	}

	void Texture::SetDSVFormat(DXGI_FORMAT format)
	{
		m_dsvFormat = format;
	}

	void Texture::SetRTVFormat(DXGI_FORMAT format)
	{
		m_rtvFormat = format;
	}
		
	void Texture::SetSample(UINT count, UINT quality)
	{
		m_desc.SampleDesc.Count = count;
		m_desc.SampleDesc.Quality = quality;
	}

	void Texture::SetUsage(Usage usage)
	{
		m_desc.Usage = D3D11_USAGE(usage);
	}

	void Texture::SetBindFlags(UINT bindFlags)
	{
		m_desc.BindFlags = bindFlags;
	}

	void Texture::SetCPUAccessFlags(UINT cpuFlags)
	{
		m_desc.CPUAccessFlags = cpuFlags;
	}

	void Texture::SetMiscFlags(UINT miscFlags)
	{
		m_desc.MiscFlags = miscFlags;
	}

}