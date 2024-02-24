#include "DirectionalLight.h"


using namespace DirectX;

namespace Duat::Graphics {

	DirectionalLight::DirectionalLight()
	{
		m_type = Type::Directional;

		Mesh::SetMesh(Geometry::Quad());
		SetVS("Billboard");
		SetPS("LightGizmo");
		SetRS_CullMode(Cull::None);
		GraphicsObject::Set(Preset::Transparent);

		Update();
	}

	void DirectionalLight::Update()
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

	void DirectionalLight::Interact(Keyboard& kbd, Mouse& mouse)
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

    DirectX::XMMATRIX DirectionalLight::GetViewMatrix() const
    {
        return m_viewMatrix;
    }

}