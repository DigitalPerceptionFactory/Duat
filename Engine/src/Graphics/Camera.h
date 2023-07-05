#pragma once
#include <string>
#include <vector>
#include <d3d11.h>
#include "RenderTarget.h"


namespace Duat::Graphics {

	struct Camera {
		void Init(const std::string& rtName, UINT topLeftX = 0, UINT topLeftY = 0, UINT width = 0, UINT height = 0);
		void SetRT(const std::string& name);
		std::string GetRT();
		const std::vector<D3D11_VIEWPORT>& GetViewports() const;
	private:
		std::string m_RT;
		std::vector<D3D11_VIEWPORT> m_viewports;
		DirectX::XMMATRIX m_matrix;
	};

}