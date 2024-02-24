#include "RenderTarget.h"
#include "System.h"


namespace Duat::Graphics {
/*
	void RenderTarget::Init(System& gfx, const std::filesystem::path& path)
	{
		Init(&gfx, path);
	}

	void RenderTarget::Init(System* pGFX, const std::filesystem::path& path)
	{
		m_targetTexture.Load(pGFX, path);
		m_targetTexture.SetBindFlags(D3D11_BIND_RENDER_TARGET);
		
		D3D11_TEXTURE2D_DESC depth_desc;
		ZeroMemory(&depth_desc, sizeof(depth_desc));
		depth_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_desc.Usage = D3D11_USAGE_DEFAULT;
		depth_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depth_desc.SampleDesc.Count = 1;
		depth_desc.SampleDesc.Quality = 0;
		depth_desc.MipLevels = 1;
		depth_desc.Width = m_targetTexture.GetWidth();
		depth_desc.Height = m_targetTexture.GetHeight();
		m_depthTexture.SetDesc(depth_desc);
		m_depthTexture.Update(pGFX);
	}

	void RenderTarget::Init(System& gfx, ID3D11Texture2D* pTex2D)
	{
		Init(&gfx, pTex2D);
	}

	void RenderTarget::Init(System* pGFX, ID3D11Texture2D* pTex2D)
	{
		D3D11_TEXTURE2D_DESC desc;
		pTex2D->GetDesc(&desc);
		m_targetTexture.SetDesc(desc);
		desc.BindFlags |= D3D11_BIND_RENDER_TARGET;
		m_targetTexture.Update(pGFX);
		
		D3D11_TEXTURE2D_DESC depth_desc;
		ZeroMemory(&depth_desc, sizeof(depth_desc));
		depth_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_desc.Usage = D3D11_USAGE_DEFAULT;
		depth_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depth_desc.SampleDesc.Count = m_targetTexture.GetSampleCount();
		depth_desc.SampleDesc.Quality = m_targetTexture.GetSampleQuality();
		depth_desc.MipLevels = 1;
		depth_desc.CPUAccessFlags = 0;
		depth_desc.MiscFlags = 0;
		depth_desc.ArraySize = 1;
		depth_desc.Width = m_targetTexture.GetWidth();
		depth_desc.Height = m_targetTexture.GetHeight();
		m_depthTexture.SetDesc(depth_desc);
		m_depthTexture.Update(pGFX);
	}

	void RenderTarget::Init(System& gfx, size_t width, size_t height, DXGI_FORMAT pixelFormat, DXGI_FORMAT depthFormat)
	{
		Init(&gfx, width, height, pixelFormat, depthFormat);
	}

	void RenderTarget::Init(System* pGFX, size_t width, size_t height, DXGI_FORMAT pixelFormat, DXGI_FORMAT depthFormat)
	{
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Format = pixelFormat;
		desc.Width = width;
		desc.Height = height;
		desc.ArraySize = 1;
		desc.BindFlags = D3D11_BIND_RENDER_TARGET;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.CPUAccessFlags = 0;
		desc.MipLevels = 1;
		desc.MiscFlags = 0;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		m_targetTexture.SetDesc(desc);
		m_targetTexture.Update(pGFX);

		ZeroMemory(&desc, sizeof(desc));
		desc.Format = depthFormat;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.MipLevels = 1;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.ArraySize = 1;
		desc.Width = m_targetTexture.GetWidth();
		desc.Height = m_targetTexture.GetHeight();
		m_depthTexture.Init(pGFX, desc, DXGI_FORMAT_R32_FLOAT, depthFormat);
	}

	void RenderTarget::Init(System& gfx, D3D11_TEXTURE2D_DESC targetDesc)
	{
		Init(&gfx, targetDesc);
	}

	void RenderTarget::Init(System* pGFX, D3D11_TEXTURE2D_DESC targetDesc)
	{
		targetDesc.BindFlags = D3D11_BIND_RENDER_TARGET;
		m_targetTexture.SetDesc(targetDesc);
		m_targetTexture.Update(pGFX);

		D3D11_TEXTURE2D_DESC depth_desc;
		ZeroMemory(&depth_desc, sizeof(depth_desc));
		depth_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_desc.Usage = D3D11_USAGE_DEFAULT;
		depth_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depth_desc.SampleDesc.Count = m_targetTexture.GetSampleCount();
		depth_desc.SampleDesc.Quality = m_targetTexture.GetSampleQuality();
		depth_desc.MipLevels = 1;
		depth_desc.CPUAccessFlags = 0;
		depth_desc.MiscFlags = 0;
		depth_desc.ArraySize = 1;
		depth_desc.Width = m_targetTexture.GetWidth();
		depth_desc.Height = m_targetTexture.GetHeight();
		m_depthTexture.SetDesc(depth_desc);
		m_depthTexture.Update(pGFX);
	}

	void RenderTarget::Init(const Texture2D& rt, const Texture2D& depth)
	{
		// m_targetTexture = rt;
		// m_depthTexture = depth;
	}

	void RenderTarget::SetTargetDesc(D3D11_TEXTURE2D_DESC desc)
	{
		m_targetTexture.SetDesc(desc);
	}

	void RenderTarget::SetTargetWidth(UINT width)
	{
		m_targetTexture.SetWidth(width);
	}

	void RenderTarget::SetTargetHeight(UINT height)
	{
		m_targetTexture.SetHeight(height);
	}

	void RenderTarget::SetTargetMipLevels(UINT mipLevels)
	{
		m_targetTexture.SetMipLevels(mipLevels);
	}

	void RenderTarget::SetTargetArraySize(UINT arraySize)
	{
		m_targetTexture.SetArraySize(arraySize);
	}

	void RenderTarget::SetTargetFormat(DXGI_FORMAT format)
	{
		m_targetTexture.SetFormat(format);
	}

	void RenderTarget::SetTargetSample(UINT count, UINT quality)
	{
		m_targetTexture.SetSample(count, quality);
	}

	void RenderTarget::SetTargetUsage(Usage usage)
	{
		m_targetTexture.SetUsage(usage);
	}

	void RenderTarget::SetTargetBindFlags(UINT bindFlags)
	{
		m_targetTexture.SetBindFlags(bindFlags);
	}

	void RenderTarget::SetTargetCPUAccessFlags(UINT cpuFlags)
	{
		m_targetTexture.SetCPUAccessFlags(cpuFlags);
	}

	void RenderTarget::SetTargetMiscFlags(UINT miscFlags)
	{
		m_targetTexture.SetMiscFlags(miscFlags);
	}

	void RenderTarget::SetDepthDesc(D3D11_TEXTURE2D_DESC desc)
	{
		m_depthTexture.SetDesc(desc);
	}

	void RenderTarget::SetDepthWidth(UINT width)
	{
		m_depthTexture.SetWidth(width);
	}

	void RenderTarget::SetDepthHeight(UINT height)
	{
		m_depthTexture.SetHeight(height);
	}

	void RenderTarget::SetDepthMipLevels(UINT mipLevels)
	{
		m_depthTexture.SetMipLevels(mipLevels);
	}

	void RenderTarget::SetDepthArraySize(UINT arraySize)
	{
		m_depthTexture.SetArraySize(arraySize);
	}

	void RenderTarget::SetDepthFormat(DXGI_FORMAT format)
	{
		m_depthTexture.SetFormat(format);
	}

	void RenderTarget::SetDepthSample(UINT count, UINT quality)
	{
		m_depthTexture.SetSample(count, quality);
	}

	void RenderTarget::SetDepthUsage(Usage usage)
	{
		m_depthTexture.SetUsage(usage);
	}

	void RenderTarget::SetDepthBindFlags(UINT bindFlags)
	{
		m_depthTexture.SetBindFlags(bindFlags);
	}

	void RenderTarget::SetDepthCPUAccessFlags(UINT cpuFlags)
	{
		m_depthTexture.SetCPUAccessFlags(cpuFlags);
	}

	void RenderTarget::SetDepthMiscFlags(UINT miscFlags)
	{
		m_depthTexture.SetMiscFlags(miscFlags);
	}

	UINT RenderTarget::GetWidth() const
	{
		return m_targetTexture.GetWidth();
	}

	UINT RenderTarget::GetHeight() const
	{
		return m_targetTexture.GetHeight();
	}

	Texture& RenderTarget::GetTarget()
	{
		return m_targetTexture;
	}

	Texture& RenderTarget::GetDepth()
	{
		return m_depthTexture;
	}
	*/
}