#include "Light.h"
#include "System.h"


using namespace DirectX;

namespace Duat::Graphics {

	Light::Light(System* pGFX) : Object3D(pGFX)
	{
		mesh = Geometry::Quad();
		vs = "Billboard";
		ps = "LightGizmo";
		cam = "Default";
		tp = Topology::TriangleList;
		bs = "Default";
		rs = "Billboard";
	}

	void Light::Init(System& gfx, float angleY, size_t shadowmapWidth, size_t shadowmapHeight)
	{
		Init(&gfx, angleY, shadowmapWidth, shadowmapHeight);
	}

	void Light::Init(System* pGFX, float angleY, size_t shadowmapWidth, size_t shadowmapHeight)
	{
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Format = DXGI_FORMAT_R32_TYPELESS;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.MipLevels = 1;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.ArraySize = 1;
		desc.Width = shadowmapWidth;
		desc.Height = shadowmapHeight;

		Texture2D depthTex;
		depthTex.Init(pGFX, desc, DXGI_FORMAT_R32_FLOAT, DXGI_FORMAT_D32_FLOAT);

		desc.BindFlags = D3D11_BIND_RENDER_TARGET;
		desc.Format = DXGI_FORMAT_R32_FLOAT;
		Texture2D renderTargetTex;
		renderTargetTex.Init(pGFX, desc);

		m_shadowMap.Init(renderTargetTex, depthTex);

		m_viewport.TopLeftX = 0;
		m_viewport.TopLeftY = 0;
		m_viewport.Width = shadowmapWidth;
		m_viewport.Height = shadowmapHeight;
		m_viewport.MinDepth = 0.0f;
		m_viewport.MaxDepth = 1.0f;

		m_pojectionMatrix = XMMatrixPerspectiveFovLH(
			XMConvertToRadians(angleY), (float)shadowmapWidth / (float)shadowmapHeight, 0.001f, 1000.0f
		);
		UpdateViewMatrix();
		pGFX->AddDrawCall(*this);
	}

	void Light::Interact(Keyboard& kbd, Mouse& mouse)
	{
			if (kbd.IsKeyDown('S'))
				TranslateZ(-m_moveSpeed * (float)Time::DeltaTime);
			if (kbd.IsKeyDown('W'))
				TranslateZ(m_moveSpeed * (float)Time::DeltaTime);
			if (kbd.IsKeyDown('Q'))
				TranslateX(-m_moveSpeed * (float)Time::DeltaTime);
			if (kbd.IsKeyDown('E'))
				TranslateX(m_moveSpeed * (float)Time::DeltaTime);
			if (kbd.IsKeyDown(VK_SPACE))
				TranslateY(m_moveSpeed * (float)Time::DeltaTime);
			if (kbd.IsKeyDown('Z'))
				TranslateY(-m_moveSpeed * (float)Time::DeltaTime);

			if (mouse.IsRightDown())
			{
				if (kbd.IsKeyDown('A'))
					RotateX(-m_rotationSpeed * (float)Time::DeltaTime);
				if (kbd.IsKeyDown('D'))
					RotateX(m_rotationSpeed * (float)Time::DeltaTime);

				RotateY(mouse.GetRawX() * m_rotationSpeed * (float)Time::DeltaTime);
				RotateX(mouse.GetRawY() * m_rotationSpeed * (float)Time::DeltaTime);
			}
			else
			{
				if (kbd.IsKeyDown('A'))
					RotateY(-20 * m_rotationSpeed * (float)Time::DeltaTime);
				if (kbd.IsKeyDown('D'))
					RotateY(20 * m_rotationSpeed * (float)Time::DeltaTime);
			}
	}

	float Light::GetIntensity() const
	{
		return m_intensity;
	}

	DirectX::XMFLOAT3 Light::GetColor() const
	{
		return m_color;
	}

	DirectX::XMMATRIX Light::GetViewMatrix() const
	{
		return m_viewMatrix;
	}

	DirectX::XMMATRIX Light::GetProjectionMatrix() const
	{
		return m_pojectionMatrix;
	}

	void Light::SetFocus(DirectX::XMFLOAT3* focus)
	{
		m_focus = focus;
	}

	void Light::SetColor(const DirectX::XMFLOAT3& color)
	{
		m_color = color;
	}

	void Light::SetIntensity(float intensity)
	{
		m_intensity = intensity;
	}

	void Light::SetProjectionAngleY(float angleY)
	{
		m_pojectionMatrix = XMMatrixPerspectiveFovLH(
			angleY, (float)m_viewport.Width / (float)m_viewport.Height, 0.0f, 1000.0f
		);
	}

	D3D11_VIEWPORT* Light::GetViewport()
	{
		return&m_viewport;
	}

	RenderTarget& Light::GetShadowmap()
	{
		return m_shadowMap;
	}

	void Light::TransformFF()
	{
		UpdateViewMatrix();
	}

	void Light::UpdateViewMatrix()
	{
		if (m_focus != nullptr) {
			m_viewMatrix = XMMatrixLookAtLH(GetPosition(), *m_focus, { 0,1,0 });
		}
		else {
			static XMFLOAT3 forward = { 0,0,1 };
			m_viewMatrix = XMMatrixLookAtLH(GetPosition(),
				GetPosition() + XMFloat3Transform(forward, GetRotationMatrix()),
				{ 0,1,0 });
		}
	}
}