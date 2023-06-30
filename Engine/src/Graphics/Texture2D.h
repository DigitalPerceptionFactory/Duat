#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <filesystem>
#include <DirectXTex/DirectXTex.h>
#include <Utility/ErrorHandling.h>
#include <Utility/DirectX.h>


namespace Duat::Graphics {

	struct System;
	struct Texture2D {
		Texture2D() = default;
		~Texture2D();
		Texture2D(System& gfx, const std::filesystem::path& path);
		Texture2D(System* pGFX, const std::filesystem::path& path);
		Texture2D(System& gfx, ID3D11Texture2D* pTex2D);
		Texture2D(System* pGFX, ID3D11Texture2D* pTex2D);
		void Init(System& gfx, const std::filesystem::path& path);
		void Init(System* pGFX, const std::filesystem::path& path);
		void Init(System& gfx, ID3D11Texture2D* pTex2D);
		void Init(System* pGFX, ID3D11Texture2D* pTex2D);
		void Init(System& gfx, D3D11_TEXTURE2D_DESC desc);
		void Init(System* pGFX, D3D11_TEXTURE2D_DESC desc);

		Texture2D& operator=(const Texture2D& rhs);

		D3D11_TEXTURE2D_DESC GetDesc();
		UINT GetWidth();
		UINT GetHeight();
		UINT GetMipLevels();
		UINT GetArraySize();
		DXGI_FORMAT GetFormat();
		UINT GetSampleCount();
		Usage GetUsage();
		UINT GetBindFlags();
		UINT GetCPUAccessFlags();
		UINT GetMiscFlags();
		ID3D11Texture2D* Get();
		ID3D11Texture2D** GetAddressOf();
		ID3D11Texture2D** ReleaseAndGetAddressOf();
		ID3D11ShaderResourceView* GetSRV();
		ID3D11ShaderResourceView** GetSRVAddressOf();
		ID3D11RenderTargetView* GetRTV();
		ID3D11RenderTargetView** GetRTVAddressOf();
		ID3D11DepthStencilView* GetDSV();
		ID3D11DepthStencilView** GetDSVAddressOf();

		void SetDesc(D3D11_TEXTURE2D_DESC desc);
		void SetWidth(UINT width);
		void SetHeight(UINT height);
		void SetMipLevels(UINT mipLevels);
		void SetArraySize(UINT arraySize);
		void SetFormat(DXGI_FORMAT format);
		void SetSampleCount(UINT sampleCount);
		void SetUsage(Usage usage);
		void SetBindFlags(UINT bindFlags);
		void SetCPUAccessFlags(UINT cpuFlags);
		void SetMiscFlags(UINT miscFlags);
	private:
		void InitViews();
		void UpdateTexture();

		System* m_pGFX;
		Utility::HResult m_hresult;
		DirectX::ScratchImage m_image;
		D3D11_TEXTURE2D_DESC m_desc;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_texture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_SRV;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RTV;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DSV;
	};

}