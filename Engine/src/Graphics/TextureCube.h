#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <filesystem>
#include <DirectXTex/DirectXTex.h>
#include <Utility/ErrorHandling.h>
#include <Utility/DirectX.h>


namespace Duat::Graphics {

	struct System;
	struct TextureCube {
		TextureCube() = default;
		~TextureCube();
		TextureCube(System& gfx, const std::filesystem::path& path);
		TextureCube(System* pGFX, const std::filesystem::path& path);
		void Init(System& gfx, const std::filesystem::path& path);
		void Init(System* pGFX, const std::filesystem::path& path);
		void Init(System& gfx, D3D11_TEXTURE2D_DESC desc, DXGI_FORMAT srvFormat = DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT dsvFormat = DXGI_FORMAT_UNKNOWN, DXGI_FORMAT rtvFormat = DXGI_FORMAT_UNKNOWN);
		void Init(System* pGFX, D3D11_TEXTURE2D_DESC desc, DXGI_FORMAT srvFormat = DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT dsvFormat = DXGI_FORMAT_UNKNOWN, DXGI_FORMAT rtvFormat = DXGI_FORMAT_UNKNOWN);

		TextureCube& operator=(const TextureCube& rhs);

		void Save(const std::filesystem::path& path) const;
		void SaveDepth(const std::filesystem::path& path) const;

		D3D11_TEXTURE2D_DESC GetDesc() const;
		UINT GetWidth() const;
		UINT GetHeight() const;
		UINT GetMipLevels() const;
		UINT GetArraySize() const;
		DXGI_FORMAT GetFormat() const;
		UINT GetSampleCount() const;
		UINT GetSampleQuality() const;
		Usage GetUsage() const;
		UINT GetBindFlags() const;
		UINT GetCPUAccessFlags() const;
		UINT GetMiscFlags() const;
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
		void SetSample(UINT count, UINT quality);
		void SetUsage(Usage usage);
		void SetBindFlags(UINT bindFlags);
		void SetCPUAccessFlags(UINT cpuFlags);
		void SetMiscFlags(UINT miscFlags);
	private:
		void InitViews();
		void UpdateTexture();

		System* m_pGFX;
		mutable Utility::HResult m_hresult;
		std::vector<DirectX::ScratchImage> m_images;
		D3D11_TEXTURE2D_DESC m_desc;
		DXGI_FORMAT m_srvFormat = DXGI_FORMAT_UNKNOWN;
		DXGI_FORMAT m_dsvFormat = DXGI_FORMAT_UNKNOWN;
		DXGI_FORMAT m_rtvFormat = DXGI_FORMAT_UNKNOWN;
		mutable Microsoft::WRL::ComPtr<ID3D11Texture2D> m_texture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_SRV;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RTV;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DSV;
	};

}