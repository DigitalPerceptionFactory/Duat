#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <filesystem>
#include <DirectXTex/DirectXTex.h>
#include <Utility/ErrorHandling.h>
#include <Utility/DirectX.h>


namespace Duat::Graphics {

	enum class TexType {
		Tex2D, Array2D, Cube
	};

	struct System;
	struct Texture {
		Texture() = default;
		~Texture();
		Texture(System& gfx, const std::filesystem::path& path, TexType type = TexType::Tex2D);
		Texture(System* pGFX, const std::filesystem::path& path, TexType type = TexType::Tex2D);
		Texture(System& gfx, ID3D11Texture2D* pTex2D, TexType type = TexType::Tex2D);
		Texture(System* pGFX, ID3D11Texture2D* pTex2D, TexType type = TexType::Tex2D);
		void Init(System& gfx, const std::filesystem::path& path, TexType type = TexType::Tex2D);
		void Init(System* pGFX, const std::filesystem::path& path, TexType type = TexType::Tex2D);
		void Init(System& gfx, ID3D11Texture2D* pTex2D, TexType type = TexType::Tex2D);
		void Init(System* pGFX, ID3D11Texture2D* pTex2D, TexType type = TexType::Tex2D);
		void Init(System& gfx, D3D11_TEXTURE2D_DESC desc, DXGI_FORMAT srvFormat = DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT dsvFormat = DXGI_FORMAT_UNKNOWN, DXGI_FORMAT rtvFormat = DXGI_FORMAT_UNKNOWN,
			TexType type = TexType::Tex2D);
		void Init(System* pGFX, D3D11_TEXTURE2D_DESC desc, DXGI_FORMAT srvFormat = DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT dsvFormat = DXGI_FORMAT_UNKNOWN, DXGI_FORMAT rtvFormat = DXGI_FORMAT_UNKNOWN,
			TexType type = TexType::Tex2D);

		Texture& operator=(const Texture& rhs);

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
		void InitTexture2D(System* pGFX, const std::filesystem::path& path);
		void InitTexture2D(System* pGFX, ID3D11Texture2D* pTex2D);
		void InitTexture2D(System* pGFX, D3D11_TEXTURE2D_DESC desc, DXGI_FORMAT srvFormat = DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT dsvFormat = DXGI_FORMAT_UNKNOWN, DXGI_FORMAT rtvFormat = DXGI_FORMAT_UNKNOWN);

		void InitTextureCube(System* pGFX, const std::filesystem::path& path);
		void InitTextureCube(System* pGFX, ID3D11Texture2D* pTex2D);
		void InitTextureCube(System* pGFX, D3D11_TEXTURE2D_DESC desc, DXGI_FORMAT srvFormat = DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT dsvFormat = DXGI_FORMAT_UNKNOWN, DXGI_FORMAT rtvFormat = DXGI_FORMAT_UNKNOWN);

		void InitViews();
		void UpdateTexture();

		System* m_pGFX;
		mutable Utility::HResult m_hresult;
		std::vector<DirectX::ScratchImage> m_images;
		TexType m_type;
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