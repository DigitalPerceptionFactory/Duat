#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <filesystem>
#include <DirectXTex/DirectXTex.h>
#include <Utility/ErrorHandling.h>
#include <Utility/DirectX.h>
#include <dxgiformat.h>


namespace Duat::Graphics {
		
	struct System;
	struct Texture {
		enum class Type {
			Uninitialized = 0,
			Tex2D, 
			Array2D, 
			Cube,
			CubeArray
		};

		virtual void ClearDSV(System& gfx, bool clearDepth = true, float depthValue = 0.0f, bool clearStencil = true, float stencilValue = 0.0f) = 0;
		virtual void ClearDSV(System* pGFX, bool clearDepth = true, float depthValue = 0.0f, bool clearStencil = true, float stencilValue = 0.0f) = 0;
		virtual void ClearRTV(System& gfx, DirectX::XMFLOAT4 color = { 0,0,0,0 }) = 0;
		virtual void ClearRTV(System* pGFX, DirectX::XMFLOAT4 color = { 0,0,0,0 }) = 0;

		virtual void Load(System& gfx, const std::filesystem::path& path) = 0;
		virtual void Load(System* pGFX, const std::filesystem::path& path) = 0;
		
		virtual void Save(System& gfx, const std::filesystem::path& path) = 0;
		virtual void Save(System* pGFX, const std::filesystem::path& path) = 0;
						
		virtual void Update(System& gfx) = 0;
		virtual void Update(System* pGFX) = 0;

		Type GetTextureType() const;
		D3D11_TEXTURE2D_DESC GetDesc() const;
		UINT GetWidth() const;
		UINT GetHeight() const;
		UINT GetMipLevels() const;
		UINT GetArraySize() const;
		DXGI_FORMAT GetFormat() const;
		DXGI_FORMAT GetSRVFormat() const;
		DXGI_FORMAT GetDSVFormat() const;
		DXGI_FORMAT GetRTVFormat() const;
		UINT GetSampleCount() const;
		UINT GetSampleQuality() const;
		Usage GetUsage() const;
		UINT GetBindFlags() const;
		UINT GetCPUAccessFlags() const;
		UINT GetMiscFlags() const;

		ID3D11Texture2D*           Get();
		ID3D11Texture2D**          GetAddressOf();
		ID3D11Texture2D**          ReleaseAndGetAddressOf();
		ID3D11ShaderResourceView*  GetSRV();
		ID3D11ShaderResourceView** GetSRVAddressOf();
		ID3D11ShaderResourceView** ReleaseSRVAndGetAddressOf();
		ID3D11DepthStencilView*    GetDSV();
		ID3D11DepthStencilView**   GetDSVAddressOf();
		ID3D11DepthStencilView**   ReleaseDSVAndGetAddressOf();
		ID3D11RenderTargetView*    GetRTV();
		ID3D11RenderTargetView**   GetRTVAddressOf();
		ID3D11RenderTargetView**   ReleaseRTVAndGetAddressOf();

		void SetDesc(D3D11_TEXTURE2D_DESC desc);
		void SetWidth(UINT width);
		void SetHeight(UINT height);
		void SetMipLevels(UINT mipLevels);
		void SetArraySize(UINT arraySize);
		void SetFormat(DXGI_FORMAT format);
		void SetSRVFormat(DXGI_FORMAT format);
		void SetDSVFormat(DXGI_FORMAT format);
		void SetRTVFormat(DXGI_FORMAT format);
		void SetSample(UINT count, UINT quality);
		void SetUsage(Usage usage);
		void SetBindFlags(UINT bindFlags);
		void SetCPUAccessFlags(UINT cpuFlags);
		void SetMiscFlags(UINT miscFlags);

	protected:
		mutable Microsoft::WRL::ComPtr<ID3D11Texture2D> m_texture;

		Type                        m_type = Type::Uninitialized;
		mutable Utility::Result     m_result;
		mutable Utility::HResult    m_hresult;
		D3D11_TEXTURE2D_DESC        m_desc = { 0 };

		DXGI_FORMAT m_srvFormat = DXGI_FORMAT_UNKNOWN;
		DXGI_FORMAT m_dsvFormat = DXGI_FORMAT_UNKNOWN;
		DXGI_FORMAT m_rtvFormat = DXGI_FORMAT_UNKNOWN;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>  m_SRV;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>    m_DSV;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>    m_RTV;
	};

}