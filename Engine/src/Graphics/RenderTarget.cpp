#include "RenderTarget.h"
#include "System.h"


namespace Duat::Graphics {
	
	void RenderTarget::Init(System& gfx, const std::filesystem::path& path)
	{
		Init(&gfx, path);
	}

	void RenderTarget::Init(System* pGFX, const std::filesystem::path& path)
	{
		m_targetTexture.Init(pGFX, path);
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
		m_depthTexture.Init(pGFX, depth_desc);
	}

	void RenderTarget::Init(System& gfx, ID3D11Texture2D* pTex2D)
	{
		Init(&gfx, pTex2D);
	}

	void RenderTarget::Init(System* pGFX, ID3D11Texture2D* pTex2D)
	{
		m_targetTexture.Init(pGFX, pTex2D);
		
		D3D11_TEXTURE2D_DESC depth_desc;
		ZeroMemory(&depth_desc, sizeof(depth_desc));
		depth_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_desc.Usage = D3D11_USAGE_DEFAULT;
		depth_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depth_desc.SampleDesc.Count = m_targetTexture.GetSampleCount();
		depth_desc.SampleDesc.Quality = 0;
		depth_desc.MipLevels = 1;
		depth_desc.CPUAccessFlags = 0;
		depth_desc.MiscFlags = 0;
		depth_desc.ArraySize = 1;
		depth_desc.Width = m_targetTexture.GetWidth();
		depth_desc.Height = m_targetTexture.GetHeight();
		m_depthTexture.Init(pGFX, depth_desc);
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
		m_targetTexture.Init(pGFX, desc);

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

	void RenderTarget::Init(const Texture2D& rt, const Texture2D& depth)
	{
		m_targetTexture = rt;
		m_depthTexture = depth;
	}

	UINT RenderTarget::GetWidth() const
	{
		return m_targetTexture.GetWidth();
	}

	UINT RenderTarget::GetHeight() const
	{
		return m_targetTexture.GetHeight();
	}

	Texture2D& RenderTarget::GetTarget()
	{
		return m_targetTexture;
	}

	Texture2D& RenderTarget::GetDepth()
	{
		return m_depthTexture;
	}

}