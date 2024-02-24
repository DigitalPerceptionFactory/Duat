#include "PointLight.h"
#include "System.h"


using namespace DirectX;

namespace Duat::Graphics {

	PointLight::PointLight(System& gfx) : PointLight(&gfx)
	{
	}

	PointLight::PointLight(System* pGFX)
	{
		m_type = Type::Point;

		Mesh::SetMesh(Geometry::Quad());
		SetVS("Billboard");
		SetPS("LightGizmo");
		SetRS_CullMode(Cull::None);
		GraphicsObject::Set(Preset::Transparent);

		std::unique_ptr<TextureCube> pTex = std::make_unique<TextureCube>();

		pTex->SetWidth(4096);
		pTex->SetHeight(4096);
		pTex->SetBindFlags(D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_DEPTH_STENCIL);
		pTex->SetFormat(DXGI_FORMAT_R32_TYPELESS);
		pTex->SetSRVFormat(DXGI_FORMAT_R32_FLOAT);
		pTex->SetDSVFormat(DXGI_FORMAT_D32_FLOAT);
		pTex->Update(pGFX);
		m_pShadowmap = std::move(pTex);

		m_LightRS.SetClockwise(true);
		m_LightRS.SetCull(Cull::Back);
		m_LightRS.SetFill(Fill::Solid);
		m_LightRS.SetDepthBias(40);
		m_LightRS.SetDepthBiasClamp(0.05f);
		m_LightRS.SetSlopeScaledDepthBias(6.0f);

		m_LightSS.SetFilter(TextureFiltering(Filter::Linear, FilterMode::Comparison));
		m_LightSS.SetAddressU(Address::Border);
		m_LightSS.SetAddressV(Address::Border);
		m_LightSS.SetComparison(Comparison::LessEqual);

		SetProjectionMatrix(90, 1.0f, 0.5f, 1000.0f);
		m_viewport.MinDepth = 0.0f;
		m_viewport.MaxDepth = 1.0f;
		Update();
	}

	void PointLight::Update()
	{
		m_viewport.Width = m_pShadowmap->GetWidth();
		m_viewport.Height = m_pShadowmap->GetHeight();

		XMFLOAT3 pos = GetPosition();
		if (m_focus != nullptr) {
			XMFLOAT3 dir = *m_focus - pos;
			dir = XMFloat3Normalize(dir);

			XMFLOAT3 right = XMFloat3Transform(dir, XMMatrixRotationRollPitchYaw(0, 90, 0));
			XMFLOAT3 left = XMFloat3Transform(dir, XMMatrixRotationRollPitchYaw(0, -90, 0));
			XMFLOAT3 up = XMFloat3Transform(dir, XMMatrixRotationRollPitchYaw(-90, 0, 0));
			XMFLOAT3 down = XMFloat3Transform(dir, XMMatrixRotationRollPitchYaw(90, 0, 0));
			XMFLOAT3 front = dir;
			XMFLOAT3 back = dir * -1.0f;

			m_viewMatrix[0] = XMMatrixLookAtLH(pos, pos + right, up);
			m_viewMatrix[1] = XMMatrixLookAtLH(pos, pos + left, up);
			m_viewMatrix[2] = XMMatrixLookAtLH(pos, pos + up, back);
			m_viewMatrix[3] = XMMatrixLookAtLH(pos, pos + down, front);
			m_viewMatrix[4] = XMMatrixLookAtLH(pos, pos + front, up);
			m_viewMatrix[5] = XMMatrixLookAtLH(pos, pos + back, up);
		}
		else {
			XMFLOAT3 right = { 1,0,0 };
			XMFLOAT3 left = { -1,0,0 };
			XMFLOAT3 up = { 0,1,0 };
			XMFLOAT3 down = { 0,-1,0 };
			XMFLOAT3 front = { 0,0,1 };
			XMFLOAT3 back = { 0,0,-1 };

			m_viewMatrix[0] = XMMatrixLookAtLH(pos, pos + right, up);
			m_viewMatrix[1] = XMMatrixLookAtLH(pos, pos + left, up);
			m_viewMatrix[2] = XMMatrixLookAtLH(pos, pos + up, back);
			m_viewMatrix[3] = XMMatrixLookAtLH(pos, pos + down, front);
			m_viewMatrix[4] = XMMatrixLookAtLH(pos, pos + front, up);
			m_viewMatrix[5] = XMMatrixLookAtLH(pos, pos + back, up);
		}
	}

	void PointLight::Interact(Keyboard& kbd, Mouse& mouse)
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

	TextureCube* PointLight::GetShadowmap()
	{
		return (TextureCube*)m_pShadowmap.get();
	}

	DirectX::XMMATRIX PointLight::GetViewMatrix(size_t index) const
	{
		return m_viewMatrix[std::clamp<size_t>(index, 0, 5)];
	}

}