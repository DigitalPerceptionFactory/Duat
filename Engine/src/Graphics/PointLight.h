#pragma once
#include "Light.h"
#include "TextureCube.h"


namespace Duat::Graphics {

	struct System;
	struct PointLight : public Light {
		PointLight(System& gfx);
		PointLight(System* pGFX);

		void Update();

		void Interact(Keyboard& kbd, Mouse& mouse) override;
		TextureCube* GetShadowmap();
		DirectX::XMMATRIX GetViewMatrix(size_t index) const;

	private:
		DirectX::XMMATRIX m_viewMatrix[6];
	};

}