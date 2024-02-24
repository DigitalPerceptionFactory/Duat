#include "Light.h"
#include "System.h"


using namespace DirectX;

namespace Duat::Graphics {

	Light::Type Light::GetLightType() const
	{
		return m_type;
	}

	float Light::GetIntensity() const
	{
		return m_intensity;
	}

	DirectX::XMFLOAT3 Light::GetColor() const
	{
		return m_color;
	}
		
	DirectX::XMMATRIX Light::GetProjectionMatrix() const
	{
		return m_projectionMatrix;
	}

	D3D11_VIEWPORT* Light::GetViewport()
	{
		return &m_viewport;
	}

	ID3D11RasterizerState* Light::GetLightRS()
	{
		return m_LightRS.Get();
	}

	Texture* Light::GetShadowmap()
	{
		return m_pShadowmap.get();
	}

	void Light::SetIntensity(float intensity)
	{
		m_intensity = intensity;
	}

	void Light::SetColor(const DirectX::XMFLOAT3& color)
	{
		m_color = color;
	}

	void Light::SetProjectionMatrix(DirectX::XMMATRIX projectionMatrix)
	{
		m_projectionMatrix = projectionMatrix;
	}

	void Light::SetProjectionMatrix(float fovAngleY, float aspectRatio, float nearZ, float farZ)
	{
		m_fovAngleY = fovAngleY;
		m_aspectRatio = aspectRatio;
		m_nearZ = nearZ;
		m_farZ = farZ;
		UpdateProjectionMatrix();

		//   Utility::Result result;
		//   float m22 = m_projectionMatrix.r[2].m128_f32[2];
		//   fovAngleY = atanf(1.0f / m22) * 2.0f;
		//   result << "FovAngleY: " + std::to_string(fovAngleY);
	}

	void Light::SetViewport(float width, float height, float topLeftX, float topLeftY, float minDepth, float maxDepth)
	{
		m_viewport.Width = width;
		m_viewport.Height= height;
		m_viewport.TopLeftX = topLeftX;
		m_viewport.TopLeftY = topLeftY;
		m_viewport.MinDepth = minDepth;
		m_viewport.MaxDepth = maxDepth;
		UpdateProjectionMatrix();
	}

	void Light::SetClipping(float nearZ, float farZ)
	{
		m_nearZ = nearZ;
		m_farZ = farZ;
		UpdateProjectionMatrix();
	}

	void Light::SetFocus(DirectX::XMFLOAT3* focus)
	{
		m_focus = focus;
	}
		
	void Light::TransformFF()
	{
		Update();
	}

	void Light::UpdateProjectionMatrix()
	{
		m_projectionMatrix = XMMatrixPerspectiveFovLH(
			XMConvertToRadians(m_fovAngleY),
			m_aspectRatio <= 0 ? (float)m_viewport.Width / (float)m_viewport.Height : m_aspectRatio,
			m_nearZ,
			m_farZ);
	}


}