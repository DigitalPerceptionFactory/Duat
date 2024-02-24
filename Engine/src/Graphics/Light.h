#pragma once
#include <string>
#include <vector>
#include <d3d11.h>
#include <HID/HID.h>
#include "Texture.h"
#include <Utility/Classes.h>
#include "RenderTarget.h"
#include "RasterizerState.h"
#include "SamplerState.h"
#include "Object3D.h"
#include <Geometry/Quad.h>
 

namespace Duat::Graphics {
		
	struct System;
	struct Light : public HID, public Object3D {
		friend System;
		enum class Type {
			Uninitialized = 0,
			Directional,
			Spot,
			Point
		};

		virtual void Update() = 0;

		Type GetLightType() const;
		float GetIntensity() const;
		DirectX::XMFLOAT3 GetColor() const;
		DirectX::XMMATRIX GetProjectionMatrix() const;
		Texture* GetShadowmap();
		D3D11_VIEWPORT* GetViewport();
		ID3D11RasterizerState* GetLightRS();

		void SetIntensity(float intensity);
		void SetColor(const DirectX::XMFLOAT3& color);
		void SetProjectionMatrix(DirectX::XMMATRIX projectionMatrix);
		void SetProjectionMatrix(float fovAngleY, float aspectRatio = -1, float nearZ = 0, float farZ = 1000);
		void SetViewport(float width, float height, float topLeftX = 0.0f, float topLeftY = 0.0f,
			float minDepth = 0.0f, float maxDepth = 1.0f);
		void SetClipping(float nearZ, float farZ);
		void SetFocus(DirectX::XMFLOAT3* focus);

	protected:
		void TransformFF() override;
		void UpdateProjectionMatrix();

		Type                       m_type = Type::Uninitialized;
		float                      m_intensity = 1.0f;
		DirectX::XMFLOAT3          m_color = { 1,1,1 };
		DirectX::XMMATRIX          m_projectionMatrix;
		std::unique_ptr<Texture>   m_pShadowmap;
		D3D11_VIEWPORT             m_viewport;
		RasterizerState            m_LightRS;
		SamplerState               m_LightSS;
		DirectX::XMFLOAT3*         m_focus = nullptr;

		float m_fovAngleY;
		float m_aspectRatio = -1;
		float m_nearZ = 0.0f;
		float m_farZ = 1000.0f;

		float m_moveSpeed = 10.0f;
		float m_rotationSpeed = 10.0f;
	};

}