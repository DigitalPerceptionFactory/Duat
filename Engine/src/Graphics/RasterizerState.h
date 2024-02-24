#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <Utility/DirectX.h>


namespace Duat::Graphics {

	struct System;
	struct RasterizerState : public Microsoft::WRL::ComPtr<ID3D11RasterizerState> {
		RasterizerState();
		HRESULT Init(System& gfx, D3D11_RASTERIZER_DESC rsDesc, std::vector< D3D11_VIEWPORT> vpDesc);
		HRESULT Init(System* pGFX, D3D11_RASTERIZER_DESC rsDesc, std::vector< D3D11_VIEWPORT> vpDesc);
		HRESULT Init(System& gfx, bool isClockwise, Fill fill, Cull cull, float width, float height,
			float normalizedWidth = 1.0f, float normalizedHeight = 1.0f,
			float minDepth = 0.0f, float maxDepth = 1.0f,
			DirectX::XMFLOAT2 ndcPosition = { 0.0f,0.0f });
		HRESULT Init(System* pGFX, bool isClockwise, Fill fill, Cull cull, float width, float height,
			float normalizedWidth = 1.0f, float normalizedHeight = 1.0f,
			float minDepth = 0.0f, float maxDepth = 1.0f,
			DirectX::XMFLOAT2 ndcPosition = { 0.0f,0.0f });
		HRESULT Update();

		D3D11_VIEWPORT* GetViewports();
		bool IsClockwise() const;
		Fill GetFill() const;
		Cull GetCull() const;
		float GetNormalizedWidth(int viewportIndex = 0) const;
		float GetNormalizedHeight(int viewportIndex = 0) const;
		float GetMinDepth(int viewportIndex = 0) const;
		float GetMaxDepth(int viewportIndex = 0) const;
		DirectX::XMFLOAT2 GetNDCPosition(int viewportIndex = 0) const;
		float GetWidth(int viewportIndex = 0) const;
		float GetHeight(int viewportIndex = 0) const;

		void SetClockwise(bool flag);
		void SetFill(Fill fill);
		void SetCull(Cull cull);
		void SetNormalizedWidth(float normalizedWidth, int viewportIndex = 0);
		void SetNormalizedHeight(float normalizedHeight, int viewportIndex = 0);
		void SetMinDepth(float minDepth, int viewportIndex = 0);
		void SetMaxDepth(float maxDepth, int viewportIndex = 0);
		void SetNDCPosition(DirectX::XMFLOAT2 ndcPosition, int viewportIndex = 0);
		void SetWidth(float width, int viewportIndex = 0);
		void SetHeight(float height, int viewportIndex = 0);
		void SetDepthBias(int bias);
		void SetDepthBiasClamp(float depthClamp);
		void SetSlopeScaledDepthBias(float slope);
		void SetScissorEnable(bool flag);
		void SetAntialiasedLineEnable(bool flag);
		void SetDepthClipEnable(bool flag);
	private:
		void UpdateViewports();

		System* m_pGFX;
		D3D11_RASTERIZER_DESC m_desc;

		std::unordered_map<int, float> m_width;
		std::unordered_map<int, float> m_height;
		std::unordered_map<int, float> m_normalizedWidth;
		std::unordered_map<int, float> m_normalizedHeight;
		std::unordered_map<int, DirectX::XMFLOAT2> m_ndcPosition;
		std::unordered_map<int, D3D11_VIEWPORT> m_viewports;
		std::vector<D3D11_VIEWPORT> m_VPcache;
	};

}