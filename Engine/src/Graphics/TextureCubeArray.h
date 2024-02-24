#pragma once
#include "Texture2D.h"


namespace Duat::Graphics {

	struct System;
	struct TextureCubeArray : public Texture {
		TextureCubeArray();
		TextureCubeArray(System& gfx, size_t arraySize, size_t cubeFaceWidth = 4096);
		TextureCubeArray(System* pGFX, size_t arraySize, size_t cubeFaceWidth = 4096);

		void ForceResize(System& gfx, size_t newSize);
		void ForceResize(System* pGFX, size_t newSize);

		void ClearDSV(System& gfx, bool clearDepth = true, float depthValue = 0.0f, bool clearStencil = true, float stencilValue = 0.0f) override;
		void ClearDSV(System* pGFX, bool clearDepth = true, float depthValue = 0.0f, bool clearStencil = true, float stencilValue = 0.0f) override;
		void ClearDSV(System& gfx, size_t dsvIndex, bool clearDepth = true, float depthValue = 0.0f, bool clearStencil = true, float stencilValue = 0.0f);
		void ClearDSV(System* pGFX, size_t dsvIndex, bool clearDepth = true, float depthValue = 0.0f, bool clearStencil = true, float stencilValue = 0.0f);
		void ClearRTV(System& gfx, DirectX::XMFLOAT4 color = { 0,0,0,0 }) override;
		void ClearRTV(System* pGFX, DirectX::XMFLOAT4 color = { 0,0,0,0 }) override;

		void Load(System& gfx, const std::filesystem::path& path) override;
		void Load(System* pGFX, const std::filesystem::path& path) override;
		void Load(System& gfx, const std::filesystem::path& path, size_t index);
		void Load(System* pGFX, const std::filesystem::path& path, size_t index);

		void Save(System& gfx, const std::filesystem::path& path) override;
		void Save(System* pGFX, const std::filesystem::path& path) override;
		void Save(System& gfx, const std::filesystem::path& path, size_t index);
		void Save(System* pGFX, const std::filesystem::path& path, size_t index);

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

		ID3D11ShaderResourceView* GetSRV(size_t arrayIndex, size_t faceIndex);
		ID3D11ShaderResourceView** GetSRVAddressOf(size_t arrayIndex, size_t faceIndex);
		ID3D11ShaderResourceView** ReleaseSRVAndGetAddressOf(size_t arrayIndex, size_t faceIndex);
		ID3D11DepthStencilView* GetDSV(size_t arrayIndex, size_t faceIndex);
		ID3D11DepthStencilView** GetDSVAddressOf(size_t arrayIndex, size_t faceIndex);
		ID3D11DepthStencilView** ReleaseDSVAndGetAddressOf(size_t arrayIndex, size_t faceIndex);
		ID3D11RenderTargetView* GetRTV(size_t arrayIndex, size_t faceIndex);
		ID3D11RenderTargetView** GetRTVAddressOf(size_t arrayIndex, size_t faceIndex);
		ID3D11RenderTargetView** ReleaseRTVAndGetAddressOf(size_t arrayIndex, size_t faceIndex);

		void SetWidth(UINT width);
		void SetHeight(UINT height);

	private:
		std::vector<std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>>  m_faceSRV;
		std::vector<std::vector<Microsoft::WRL::ComPtr<ID3D11DepthStencilView>>>    m_faceDSV;
		std::vector<std::vector<Microsoft::WRL::ComPtr<ID3D11RenderTargetView>>>    m_faceRTV;
	};

}