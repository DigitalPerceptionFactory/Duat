#pragma once
#include "Light.h"
#include "Texture2D.h"


namespace Duat::Graphics {

	struct System;
	struct SpotLight : public Light {
		SpotLight(System& gfx);
		SpotLight(System* pGFX);

		void Update() override;

		void Interact(Keyboard& kbd, Mouse& mouse) override;
		DirectX::XMMATRIX GetViewMatrix() const;
				
	private:
		System* pGFX = nullptr;
		DirectX::XMMATRIX m_viewMatrix;
	};

}