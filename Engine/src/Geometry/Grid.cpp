#include "Grid.h"
#include <Graphics/System.h>


namespace Duat::Geometry {

	Grid::Grid(Graphics::System* pGFX) : Graphics::Object3D(pGFX)
	{
		m_width = 100.0f;
		m_height = 100.0f;
		m_widthDensity = 0.01f;
		m_heightDensity = 0.01f;
		SetPosition(0, 0, 0);
		SetRotation(90, 0, 0);
		SetScale(m_width, m_height, 1);
		
		Mesh::SetMesh(Quad());
		SetPS("GridGizmo");
		SetRS_CullMode(Cull::None);
		GraphicsObject::Set(Graphics::Preset::Transparent);

		for (auto& vtx : m_vertices)
		{
			vtx.texCoord.x = 1 / m_widthDensity * vtx.texCoord.x;
			vtx.texCoord.y = 1 / m_heightDensity * vtx.texCoord.y;
		}
	}

	Grid::Grid(Graphics::System* pGFX, float width, float height, DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 rotation, float widthDensity, float heightDensity)
		: Graphics::Object3D(pGFX)
	{
		m_width = width;
		m_height = height;
		m_widthDensity = widthDensity;
		m_heightDensity = heightDensity;
		SetPosition(position);
		SetRotation(rotation);
		SetScale(m_width, m_height, 1);

		Mesh::SetMesh(Quad());
		SetPS("GridGizmo");
		SetRS_CullMode(Cull::None);
		GraphicsObject::Set(Graphics::Preset::Transparent);

		for (auto& vtx : m_vertices)
		{
			vtx.texCoord.x = 1 / m_widthDensity * vtx.texCoord.x;
			vtx.texCoord.y = 1 / m_heightDensity * vtx.texCoord.y;
		}
	}

}