#pragma once
#include <string>
#include <vector>
#include <d3d11.h>
#include <HID/HID.h>
#include "Texture2D.h"
#include <Utility/Classes.h>
#include "RenderTarget.h"
#include "Object3D.h"
#include <Geometry/Quad.h>


namespace Duat::Graphics {
		
	struct System;
	struct Light : public HID, public Object3D {
		friend System;
		Light(System* pGFX);

		void Init(System& gfx, float angleY, size_t shadowmapWidth = 4096, size_t shadowmapHeight = 4096);
		void Init(System* pGFX, float angleY, size_t shadowmapWidth = 4096, size_t shadowmapHeight = 4096);

		void Interact(Keyboard& kbd, Mouse& mouse);

		float GetIntensity() const;
		DirectX::XMFLOAT3 GetColor() const;
		DirectX::XMMATRIX GetViewMatrix() const;
		DirectX::XMMATRIX GetProjectionMatrix() const;

		void SetFocus(DirectX::XMFLOAT3* focus);
		void SetColor(const DirectX::XMFLOAT3& color);
		void SetIntensity(float intensity);
		void SetProjectionAngleY(float angleY);

		D3D11_VIEWPORT* GetViewport();
		RenderTarget& GetShadowmap();
	private:
		void TransformFF() override;
		void UpdateViewMatrix();

		float m_moveSpeed = 10.0f;
		float m_rotationSpeed = 10.0f;

		DirectX::XMFLOAT3* m_focus = nullptr;
		DirectX::XMFLOAT3 m_color = { 1,1,1 };
		float m_intensity = 1.0f;

		//Texture2D m_shadowMap;
		RenderTarget m_shadowMap;
		D3D11_VIEWPORT    m_viewport;
		DirectX::XMMATRIX m_viewMatrix;
		DirectX::XMMATRIX m_pojectionMatrix;
	};

}