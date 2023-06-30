#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <Utility/DirectX.h>


namespace Duat::Graphics {

	struct System;
	struct RasterizerState : public Microsoft::WRL::ComPtr<ID3D11RasterizerState> {
		HRESULT Init(System& gfx, bool isClockwise, Fill fill, Cull cull, float width, float height,
			float normalizedWidth = 1.0f, float normalizedHeight = 1.0f,
			float minDepth = 0.0f, float maxDepth = 1.0f,
			DirectX::XMFLOAT2 ndcPosition = { 0.0f,0.0f });
		HRESULT Init(System* pGFX, bool isClockwise, Fill fill, Cull cull, float width, float height,
			float normalizedWidth = 1.0f, float normalizedHeight = 1.0f,
			float minDepth = 0.0f, float maxDepth = 1.0f,
			DirectX::XMFLOAT2 ndcPosition = { 0.0f,0.0f });
		HRESULT Update();

		D3D11_VIEWPORT* GetViewport();
		bool IsClockwise() const;
		Fill GetFill() const;
		Cull GetCull() const;
		float GetNormalizedWidth() const;
		float GetNormalizedHeight() const;
		float GetMinDepth() const;
		float GetMaxDepth() const;
		DirectX::XMFLOAT2 GetNDCPosition() const;
		float GetWidth() const;
		float GetHeight() const;

		void SetClockwise(bool flag);
		void SetFill(Fill fill);
		void SetCull(Cull cull);
		void SetNormalizedWidth(float normalizedWidth);
		void SetNormalizedHeight(float normalizedHeight);
		void SetMinDepth(float minDepth);
		void SetMaxDepth(float maxDepth);
		void SetNDCPosition(DirectX::XMFLOAT2 ndcPosition);
		void SetWidth(float width);
		void SetHeight(float height);
	private:
		void UpdateViewport();

		System* m_pGFX;
		float m_width;
		float m_height;
		float m_normalizedWidth;
		float m_normalizedHeight;
		DirectX::XMFLOAT2 m_ndcPosition;

		D3D11_RASTERIZER_DESC m_desc;
		D3D11_VIEWPORT m_viewport;
	};

}