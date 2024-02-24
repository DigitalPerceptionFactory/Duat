#pragma once
#include "Light.h"


namespace Duat::Graphics {

	struct DirectionalLight : public Light {
		DirectionalLight();

		void Update() override;

		void Interact(Keyboard& kbd, Mouse& mouse) override;
		DirectX::XMMATRIX GetViewMatrix() const;

	private:
		DirectX::XMMATRIX m_viewMatrix;
	};

}