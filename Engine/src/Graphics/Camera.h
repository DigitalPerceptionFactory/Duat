#pragma once
#include <string>
#include <vector>
#include <d3d11.h>
#include "RenderTarget.h"


namespace Duat::Graphics {

	struct System;
	struct Camera {
		void Init(const std::string& rtName, UINT topLeftX = 0, UINT topLeftY = 0, UINT width = 0, UINT height = 0);
		void SyncWithRT(System& gfx);
		void SyncWithRT(System* pGFX);

		void SetRT(const std::string& name);
		std::string GetRT();
		const std::vector<D3D11_VIEWPORT>& GetViewports() const;
		DirectX::XMMATRIX GetViewMatrix();
		DirectX::XMMATRIX GetProjectionMatrix();
	private:
		std::string m_RT;
		std::vector<D3D11_VIEWPORT> m_viewports;
		DirectX::XMFLOAT3 m_position;
		DirectX::XMFLOAT3 m_rotation;
		DirectX::XMMATRIX m_viewMatrix;
		DirectX::XMMATRIX m_pojectionMatrix;
	};

}