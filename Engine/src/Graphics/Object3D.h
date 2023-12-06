#pragma once
#include "GraphicsObject.h"
#include <Geometry/Transform.h>


namespace Duat::Graphics {

	struct System;
	struct Object3D : public GraphicsObject, public Geometry::Transform {
		Object3D(System* pGFX) : m_pGFX(pGFX), m_projectionGizmo(-1) {}
		void SetProjectionGizmo(bool flag);
	protected:
		System* m_pGFX;
	private:
		int m_projectionGizmo;
	};

}