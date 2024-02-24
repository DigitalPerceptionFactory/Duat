#include "SpotLight.h"
#include "System.h"


using namespace DirectX;

namespace Duat::Graphics {

	SpotLight::SpotLight(System& gfx) : SpotLight(&gfx)
	{
	}

	SpotLight::SpotLight(System* pGFX)
	{
		m_type = Type::Spot;

		Mesh::SetMesh(Geometry::Quad());
		SetVS("Billboard");
		SetPS("LightGizmo");
		SetRS_CullMode(Cull::None);
		GraphicsObject::Set(Preset::Transparent);

		std::unique_ptr<Texture2D> pTex = std::make_unique<Texture2D>();
		pTex->SetWidth(4096);
		pTex->SetHeight(2048);
		pTex->SetBindFlags(D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_DEPTH_STENCIL);
		pTex->SetFormat(DXGI_FORMAT_R32_TYPELESS);
		pTex->SetSRVFormat(DXGI_FORMAT_R32_FLOAT);
		pTex->SetDSVFormat(DXGI_FORMAT_D32_FLOAT);
		pTex->Update(pGFX);
		m_pShadowmap = std::move(pTex);

		SetProjectionMatrix(180, -1, 0.0f, 1000.0f);
		Update();
	}

	void SpotLight::Update()
	{
		XMFLOAT3 pos = GetPosition();
		if (m_focus != nullptr) {
			XMFLOAT3 dir = *m_focus - pos;
			dir = XMFloat3Normalize(dir);
			XMFLOAT3 up = XMFloat3Transform(dir, XMMatrixRotationRollPitchYaw(-90, 0, 0));
			m_viewMatrix = XMMatrixLookAtLH(pos, pos + dir, up);
		}
		else {
			XMFLOAT3 dir = { 0,0,1 };
			dir = XMFloat3Transform(dir, GetRotationMatrix());
			XMFLOAT3 up = XMFloat3Transform(dir, XMMatrixRotationRollPitchYaw(-90, 0, 0));
			m_viewMatrix = XMMatrixLookAtLH(pos, pos + dir, up);
		}
	}

	void SpotLight::Interact(Keyboard& kbd, Mouse& mouse)
    {
		if (kbd.IsKeyDown('S'))
			PositionAddZ(-m_moveSpeed * (float)Time::DeltaTime);
		if (kbd.IsKeyDown('W'))
			PositionAddZ(m_moveSpeed * (float)Time::DeltaTime);
		if (kbd.IsKeyDown('A'))
			PositionAddX(-m_moveSpeed * (float)Time::DeltaTime);
		if (kbd.IsKeyDown('D'))
			PositionAddX(m_moveSpeed * (float)Time::DeltaTime);
		if (kbd.IsKeyDown(VK_SPACE))
			PositionAddY(m_moveSpeed * (float)Time::DeltaTime);
		if (kbd.IsKeyDown('Z'))
			PositionAddY(-m_moveSpeed * (float)Time::DeltaTime);
    }

    DirectX::XMMATRIX SpotLight::GetViewMatrix() const
    {
        return m_viewMatrix;
    }

}