#pragma once
#include "GraphicsObject.h"
#include <Geometry/Transform.h>


namespace Duat::Graphics {

	struct System;
	struct Object3D : public Geometry::Mesh, public GraphicsObject, public Geometry::Transform {
		Object3D() = default;
		Object3D(System& gfx);
		Object3D(System* pGFX);
		Object3D(System& gfx, const Geometry::Mesh& mesh, const GraphicsObject& gObj);
		Object3D(System* pGFX, const Geometry::Mesh& mesh, const GraphicsObject& gObj);
		Geometry::Mesh GetMesh() const;

		bool IsDrawCallEnabled() const;
		bool IsGizmoEnabled() const;

		void DrawCallEnabled(bool flag);
		void GizmoEnabled(bool flag);
	protected:
		System* m_pGFX;
	private:
		int m_DCIndex;
		int m_GizmoDCIndex;
	};

}