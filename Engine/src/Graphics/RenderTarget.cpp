#include "RenderTarget.h"
#include "System.h"


namespace Duat::Graphics {

	void RenderTarget::Init(System& gfx, const std::filesystem::path& path)
	{
		Init(&gfx, path);
	}

	void RenderTarget::Init(System* pGFX, const std::filesystem::path& path)
	{
		m_texture.Init(pGFX, path);
		m_texture.SetBindFlags(D3D11_BIND_RENDER_TARGET);
		
		D3D11_TEXTURE2D_DESC depth_desc;
		ZeroMemory(&depth_desc, sizeof(depth_desc));
		depth_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_desc.Usage = D3D11_USAGE_DEFAULT;
		depth_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depth_desc.SampleDesc.Count = 1;
		depth_desc.SampleDesc.Quality = 0;
		depth_desc.MipLevels = 1;
		depth_desc.Width = m_texture.GetWidth();
		depth_desc.Height = m_texture.GetHeight();
		m_depthTexture.Init(pGFX, depth_desc);
	}

	void RenderTarget::Init(System& gfx, ID3D11Texture2D* pTex2D)
	{
		Init(&gfx, pTex2D);
	}

	void RenderTarget::Init(System* pGFX, ID3D11Texture2D* pTex2D)
	{
		m_texture.Init(pGFX, pTex2D);
		//m_texture.SetBindFlags(D3D11_BIND_RENDER_TARGET);

		D3D11_TEXTURE2D_DESC depth_desc;
		ZeroMemory(&depth_desc, sizeof(depth_desc));
		depth_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_desc.Usage = D3D11_USAGE_DEFAULT;
		depth_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depth_desc.SampleDesc.Count = 1;
		depth_desc.SampleDesc.Quality = 0;
		depth_desc.MipLevels = 1;
		depth_desc.CPUAccessFlags = 0;
		depth_desc.MiscFlags = 0;
		depth_desc.ArraySize = 1;
		depth_desc.Width = m_texture.GetWidth();
		depth_desc.Height = m_texture.GetHeight();
		m_depthTexture.Init(pGFX, depth_desc);
	}

	UINT RenderTarget::GetWidth()
	{
		return m_texture.GetWidth();
	}

	UINT RenderTarget::GetHeight()
	{
		return m_texture.GetHeight();
	}

	ID3D11Texture2D* RenderTarget::GetTexture()
	{
		return m_texture.Get();
	}

	ID3D11Texture2D** RenderTarget::GetTextureAddressOf()
	{
		return m_texture.GetAddressOf();
	}

	ID3D11Texture2D* RenderTarget::GetDepthTexture()
	{
		return m_depthTexture.Get();
	}

	ID3D11Texture2D** RenderTarget::GetDepthTextureAddressOf()
	{
		return m_depthTexture.GetAddressOf();
	}

	ID3D11ShaderResourceView* RenderTarget::GetSRV()
	{
		return m_texture.GetSRV();
	}

	ID3D11ShaderResourceView** RenderTarget::GetSRVAddressOf()
	{
		return m_texture.GetSRVAddressOf();
	}

	ID3D11RenderTargetView* RenderTarget::GetRTV()
	{
		return m_texture.GetRTV();
	}

	ID3D11RenderTargetView** RenderTarget::GetRTVAddressOf()
	{
		return m_texture.GetRTVAddressOf();
	}

	ID3D11DepthStencilView* RenderTarget::GetDSV()
	{
		return m_depthTexture.GetDSV();
	}

	ID3D11DepthStencilView** RenderTarget::GetDSVAddressOf()
	{
		return m_depthTexture.GetDSVAddressOf();
	}
}