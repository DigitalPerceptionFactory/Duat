#pragma once
#include <string>
#include <vector>
#include <d3d11.h>
#include "RenderTarget.h"
#include <HID/HID.h>
#include <Geometry/Transform.h>


namespace Duat::Graphics {
	
	struct System;
	struct Camera : public HID, public Geometry::Transform {
		void Init(System& gfx, const std::string& rtName, UINT topLeftX = 0, UINT topLeftY = 0,	UINT width = 0, UINT height = 0,
			float fovAngleY = 60, float nearZ = 0.01f, float farZ = 1000.0f);
		void Init(System* pGFX, const std::string& rtName, UINT topLeftX = 0, UINT topLeftY = 0, UINT width = 0, UINT height = 0,
			float fovAngleY = 60, float nearZ = 0.01f, float farZ = 1000.0f);

		void Interact(Keyboard& kbd, Mouse& mouse);

		void SetRT(const std::string& name);
		void SetFocus(DirectX::XMFLOAT3* pFocus);
		std::string GetRT();
		const std::vector<D3D11_VIEWPORT>& GetViewports() const;
		DirectX::XMMATRIX GetViewMatrix();
		DirectX::XMMATRIX GetProjectionMatrix();
		DirectX::XMMATRIX GetMVP(const DirectX::XMMATRIX& modelMatrix);

		void SetProjectionMatrix(float fovAngleY, float aspectRatio, float nearZ, float farZ);
	private:
		void UpdateViewMatrix();

		float m_moveSpeed = 10.0f;
		float m_rotationSpeed = 10.0f;
		DirectX::XMFLOAT3* m_focus;

		std::string m_RT;
		std::vector<D3D11_VIEWPORT> m_viewports;
		DirectX::XMMATRIX m_viewMatrix;
		DirectX::XMMATRIX m_pojectionMatrix;
	};
	
}