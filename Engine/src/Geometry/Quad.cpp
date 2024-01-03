#include "Quad.h"

namespace Duat::Geometry {

	Quad::Quad()
	{
		m_vertices.resize(4);

		m_vertices[0].position = { -0.5f, 0.5f, 0 };
		m_vertices[1].position = { 0.5f, 0.5f, 0 };
		m_vertices[2].position = { -0.5f, -0.5f, 0 };
		m_vertices[3].position = { 0.5f, -0.5f, 0 };

		m_vertices[0].texCoord = { 0, 1 };
		m_vertices[1].texCoord = { 1, 1 };
		m_vertices[2].texCoord = { 0, 0 };
		m_vertices[3].texCoord = { 1, 0 };

		SetVertexColor(1, 1, 1, 1);

		m_indices = { 2, 0, 1, 2, 1, 3 };
		UpdateNormals();
	}

}