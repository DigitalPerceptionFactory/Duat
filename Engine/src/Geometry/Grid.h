#pragma once
#include <Graphics/Object3D.h>
#include "Quad.h"


namespace Duat::Geometry {

	struct Graphics::System;
	struct Grid : public Graphics::Object3D {
		Grid(Graphics::System* pGFX);
		Grid(Graphics::System* pGFX, float width, float height,
			DirectX::XMFLOAT3 position = { 0,0,0 },
			DirectX::XMFLOAT3 rotation = { 90,0,0 },
			float widthDensity = 0.1f, float heightDensity = 0.1f);
	private:
		float m_width;
		float m_height;
		float m_widthDensity;
		float m_heightDensity;
	};

}