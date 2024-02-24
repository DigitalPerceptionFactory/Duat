#pragma once
#include "Texture2D.h"


namespace Duat::Graphics {
		
	struct TextureCube : public Texture {
		TextureCube();
		TextureCube(size_t cubeFaceWidth);

		void ClearDSV(System& gfx, bool clearDepth = true, float depthValue = 0.0f, bool clearStencil = true, float stencilValue = 0.0f) override;
		void ClearDSV(System* pGFX, bool clearDepth = true, float depthValue = 0.0f, bool clearStencil = true, float stencilValue = 0.0f) override;
		void ClearRTV(System& gfx, DirectX::XMFLOAT4 color = { 0,0,0,0 }) override;
		void ClearRTV(System* pGFX, DirectX::XMFLOAT4 color = { 0,0,0,0 }) override;

		void Load(System& gfx, const std::filesystem::path& path) override;
		void Load(System* pGFX, const std::filesystem::path& path) override;

		void Save(System& gfx, const std::filesystem::path& path) override;
		void Save(System* pGFX, const std::filesystem::path& path) override;

		void Update(System& gfx) override;
		void Update(System* pGFX) override;

		using Texture::GetSRV;
		using Texture::GetSRVAddressOf;
		using Texture::ReleaseSRVAndGetAddressOf;
		using Texture::GetDSV;
		using Texture::GetDSVAddressOf;
		using Texture::ReleaseDSVAndGetAddressOf;
		using Texture::GetRTV;
		using Texture::GetRTVAddressOf;
		using Texture::ReleaseRTVAndGetAddressOf;

		ID3D11ShaderResourceView*  GetSRV(size_t index);
		ID3D11ShaderResourceView** GetSRVAddressOf(size_t index);
		ID3D11ShaderResourceView** ReleaseSRVAndGetAddressOf(size_t index);
		ID3D11DepthStencilView*    GetDSV(size_t index);
		ID3D11DepthStencilView**   GetDSVAddressOf(size_t index);
		ID3D11DepthStencilView**   ReleaseDSVAndGetAddressOf(size_t index);
		ID3D11RenderTargetView*    GetRTV(size_t index);
		ID3D11RenderTargetView**   GetRTVAddressOf(size_t index);
		ID3D11RenderTargetView**   ReleaseRTVAndGetAddressOf(size_t index);

		//  Texture2D& GetFace(size_t index);
	private:
		//  void SyncDesc();
		//  Texture2D m_faces[6];

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>  m_faceSRV[6];
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>    m_faceDSV[6];
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>    m_faceRTV[6];
	};

}