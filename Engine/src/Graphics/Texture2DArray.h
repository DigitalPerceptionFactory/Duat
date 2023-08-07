#pragma once
#include "Texture2D.h"

/*
namespace Duat::Graphics {

	struct System;
	struct Texture2DArray {
		void Init(System& gfx, size_t arraySize, const Texture2D& tex2DTemplate);
		void Init(System* pGFX, size_t arraySize, const Texture2D& tex2DTemplate);
	private:
		D3D11_TEXTURE2D_DESC m_desc;
		std::vector<DXGI_FORMAT> m_srvFormats;
		std::vector<DXGI_FORMAT> m_dsvFormats;
		std::vector<DXGI_FORMAT> m_rtvFormats;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_textureArray;
		std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>  m_SRV;
		std::vector<Microsoft::WRL::ComPtr<ID3D11RenderTargetView>>    m_RTV;
		std::vector<Microsoft::WRL::ComPtr<ID3D11DepthStencilView>>    m_DSV;
	};

}*/