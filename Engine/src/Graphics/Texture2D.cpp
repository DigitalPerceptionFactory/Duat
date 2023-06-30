#include "Texture2D.h"
#include "System.h"


using namespace DirectX;

namespace Duat::Graphics
{

	Texture2D::~Texture2D()
	{
		m_image.Release();
	}

	Texture2D::Texture2D(System& gfx, const std::filesystem::path& path)
	{
		Init(gfx, path);
	}

	Texture2D::Texture2D(System* pGFX, const std::filesystem::path& path)
	{
		Init(pGFX, path);
	}

	Texture2D::Texture2D(System& gfx, ID3D11Texture2D* pTex2D)
	{
		Init(gfx, pTex2D);
	}

	Texture2D::Texture2D(System* pGFX, ID3D11Texture2D* pTex2D)
	{
		Init(pGFX, pTex2D);
	}

	void Texture2D::Init(System& gfx, const std::filesystem::path& path)
	{
		Init(&gfx, path);
	}

	void Texture2D::Init(System* pGFX, const std::filesystem::path& path)
	{
		if (pGFX == nullptr)
		{
			Utility::Result result;
			result << "You can't initialize Texture2D because System pointer you provided is a null pointer.";
			return;
		}
		m_pGFX = pGFX;

		if (path.extension() == "dds")
			m_hresult << LoadFromDDSFile(path.c_str(), DDS_FLAGS_NONE, nullptr, m_image);
		else if (path.extension() == "tga")
			m_hresult << LoadFromTGAFile(path.c_str(), nullptr, m_image);
		else if (path.extension() == "hdr")
			m_hresult << LoadFromHDRFile(path.c_str(), nullptr, m_image);
		else
			m_hresult << LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, nullptr, m_image);

		auto metadata = m_image.GetMetadata();
		m_desc.Width = (UINT)metadata.width;
		m_desc.Height = (UINT)metadata.height;
		m_desc.MipLevels = (UINT)metadata.mipLevels;
		m_desc.ArraySize = 1;
		m_desc.Format = metadata.format;
		m_desc.SampleDesc.Count = 1;
		m_desc.Usage = D3D11_USAGE_DEFAULT;
		m_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		m_desc.CPUAccessFlags = 0;
		m_desc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initialData;
		ZeroMemory(&initialData, sizeof(initialData));
		initialData.pSysMem = m_image.GetImage(0, 0, 0)->pixels;
		initialData.SysMemPitch = (UINT)m_image.GetImage(0, 0, 0)->rowPitch;
		initialData.SysMemSlicePitch = 0;

		m_hresult << pGFX->m_Device->CreateTexture2D(&m_desc, &initialData, ReleaseAndGetAddressOf());
		InitViews();
	}

	void Texture2D::Init(System& gfx, ID3D11Texture2D* pTex2D)
	{
		Init(&gfx, pTex2D);
	}

	void Texture2D::Init(System* pGFX, ID3D11Texture2D* pTex2D)
	{
		if (pGFX == nullptr)
		{
			Utility::Result result;
			result << "You can't initialize Texture2D because System pointer you provided is a null pointer.";
			return;
		}
		if (pTex2D == nullptr)
		{
			Utility::Result result;
			result << "You can't initialize Texture2D because pTex2D you provided is a null pointer.";
			return;
		}

		m_pGFX = pGFX;
		m_texture = pTex2D;
		pTex2D->GetDesc(&m_desc);
		//m_hresult << pGFX->m_Device->CreateTexture2D(&m_desc, nullptr, ReleaseAndGetAddressOf());
		InitViews();
	}

	void Texture2D::Init(System& gfx, D3D11_TEXTURE2D_DESC desc)
	{
		Init(&gfx, desc);
	}

	void Texture2D::Init(System* pGFX, D3D11_TEXTURE2D_DESC desc)
	{
		if (pGFX == nullptr)
		{
			Utility::Result result;
			result << "You can't initialize Texture2D because System pointer you provided is a null pointer.";
			return;
		}

		m_pGFX = pGFX;
		m_desc = desc;
		m_hresult << pGFX->m_Device->CreateTexture2D(&m_desc, nullptr, ReleaseAndGetAddressOf());
		InitViews();
	}

	Texture2D& Texture2D::operator=(const Texture2D& rhs)
	{
		m_hresult = rhs.m_hresult;
		m_texture = rhs.m_texture;
		m_SRV = rhs.m_SRV;
		m_RTV = rhs.m_RTV;
		m_DSV = rhs.m_DSV;
		m_desc = rhs.m_desc;
		m_image.Initialize(rhs.m_image.GetMetadata());
		std::memcpy(m_image.GetPixels(), rhs.m_image.GetPixels(), rhs.m_image.GetPixelsSize());
		return *this;
	}

	D3D11_TEXTURE2D_DESC Texture2D::GetDesc()
	{
		return m_desc;
	}

	UINT Texture2D::GetWidth()
	{
		return m_desc.Width;
	}

	UINT Texture2D::GetHeight()
	{
		return m_desc.Height;
	}

	UINT Texture2D::GetMipLevels()
	{
		return m_desc.MipLevels;
	}

	UINT Texture2D::GetArraySize()
	{
		return m_desc.ArraySize;
	}

	DXGI_FORMAT Texture2D::GetFormat()
	{
		return m_desc.Format;
	}

	UINT Texture2D::GetSampleCount()
	{
		return m_desc.SampleDesc.Count;
	}

	Usage Texture2D::GetUsage()
	{
		return Usage(m_desc.Usage);
	}

	UINT Texture2D::GetBindFlags()
	{
		return m_desc.BindFlags;
	}

	UINT Texture2D::GetCPUAccessFlags()
	{
		return m_desc.CPUAccessFlags;
	}

	UINT Texture2D::GetMiscFlags()
	{
		return m_desc.MiscFlags;
	}

	ID3D11Texture2D* Texture2D::Get()
	{
		return m_texture.Get();
	}

	ID3D11Texture2D** Texture2D::GetAddressOf()
	{
		return m_texture.GetAddressOf();
	}

	ID3D11Texture2D** Texture2D::ReleaseAndGetAddressOf()
	{
		return m_texture.ReleaseAndGetAddressOf();
	}

	ID3D11ShaderResourceView* Texture2D::GetSRV()
	{
		return m_SRV.Get();
	}

	ID3D11ShaderResourceView** Texture2D::GetSRVAddressOf()
	{
		return m_SRV.GetAddressOf();
	}

	ID3D11RenderTargetView* Texture2D::GetRTV()
	{
		return m_RTV.Get();
	}

	ID3D11RenderTargetView** Texture2D::GetRTVAddressOf()
	{
		return m_RTV.GetAddressOf();
	}

	ID3D11DepthStencilView* Texture2D::GetDSV()
	{
		return m_DSV.Get();
	}

	ID3D11DepthStencilView** Texture2D::GetDSVAddressOf()
	{
		return m_DSV.GetAddressOf();
	}

	void Texture2D::SetDesc(D3D11_TEXTURE2D_DESC desc)
	{
		m_desc = desc;
		UpdateTexture();
	}

	void Texture2D::SetWidth(UINT width)
	{
		m_desc.Width = width;
		UpdateTexture();
	}

	void Texture2D::SetHeight(UINT height)
	{
		m_desc.Height = height;
		UpdateTexture();
	}

	void Texture2D::SetMipLevels(UINT mipLevels)
	{
		m_desc.MipLevels = mipLevels;
		UpdateTexture();
	}

	void Texture2D::SetArraySize(UINT arraySize)
	{
		m_desc.ArraySize = arraySize;
		UpdateTexture();
	}

	void Texture2D::SetFormat(DXGI_FORMAT format)
	{
		m_desc.Format = format;
		UpdateTexture();
	}

	void Texture2D::SetSampleCount(UINT sampleCount)
	{
		m_desc.SampleDesc.Count = sampleCount;
		UpdateTexture();
	}

	void Texture2D::SetUsage(Usage usage)
	{
		m_desc.Usage = D3D11_USAGE(usage);
		UpdateTexture();
	}

	void Texture2D::SetBindFlags(UINT bindFlags)
	{
		m_desc.BindFlags = bindFlags;
		UpdateTexture();
	}

	void Texture2D::SetCPUAccessFlags(UINT cpuFlags)
	{
		m_desc.CPUAccessFlags = cpuFlags;
		UpdateTexture();
	}

	void Texture2D::SetMiscFlags(UINT miscFlags)
	{
		m_desc.MiscFlags = miscFlags;
		UpdateTexture();
	}

	void Texture2D::InitViews()
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
			srv_desc.Format = m_desc.Format;
			srv_desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srv_desc.Texture2D.MipLevels = m_desc.MipLevels;
			srv_desc.Texture2D.MostDetailedMip = 0;
			m_hresult << m_pGFX->m_Device->CreateShaderResourceView(Get(), &srv_desc, m_SRV.ReleaseAndGetAddressOf());
		}
		if (m_desc.BindFlags & D3D11_BIND_DEPTH_STENCIL)
		{
			D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc;
			ZeroMemory(&dsv_desc, sizeof(dsv_desc));
			dsv_desc.Format = m_desc.Format;
			dsv_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			dsv_desc.Texture2D.MipSlice = 0;
			m_hresult << m_pGFX->m_Device->CreateDepthStencilView(Get(), &dsv_desc, m_DSV.ReleaseAndGetAddressOf());
		}
		if (m_desc.BindFlags & D3D11_BIND_RENDER_TARGET)
		{
			D3D11_RENDER_TARGET_VIEW_DESC rtv_desc;
			ZeroMemory(&rtv_desc, sizeof(rtv_desc));
			rtv_desc.Format = m_desc.Format;
			rtv_desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			rtv_desc.Texture2D.MipSlice = 0;
			m_hresult << m_pGFX->m_Device->CreateRenderTargetView(Get(), &rtv_desc, m_RTV.ReleaseAndGetAddressOf());
		}
	}

	void Texture2D::UpdateTexture()
	{
		if (m_pGFX == nullptr)
		{
			Utility::Result result;
			result << "For some reason m_pGFX is a nullptr.";
			return;
		}
		Microsoft::WRL::ComPtr<ID3D11Texture2D> newTexture;
		m_hresult << m_pGFX->m_Device->CreateTexture2D(&m_desc, nullptr, newTexture.GetAddressOf());
		m_pGFX->m_Context->CopyResource(newTexture.Get(), Get());
		m_texture = newTexture;
		InitViews();
	}

}