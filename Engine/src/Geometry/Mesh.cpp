#include "Mesh.h"
#include <Utility/DirectX/Legacy.h>


namespace Duat::Geometry {

	void Mesh::TestInit()
	{
		Vertex a;
		a.position = { -1,-1,0, 1 };
		a.texCoord.x = 0;
		a.texCoord.y = 0;
		a.color = { 1,0,0, 1 };

		Vertex b;
		b.position = { 0,1,0, 1 };
		b.texCoord.x = 0.5f;
		b.texCoord.y = 1;
		b.color = { 1,0,0, 1 };

		Vertex c;
		c.position = { 1,-1,0,1 };
		c.texCoord.x = 1;
		c.texCoord.y = 0;
		c.color = { 1,0,0, 1 };

		Vertex d;
		d.position = { -1,1,0, 1 };
		d.texCoord.x = 0;
		d.texCoord.y = 0;
		d.color = { 1,0,0, 1 };

		Vertex e;
		e.position = { 1,1,0, 1 };
		e.texCoord.x = 0.5f;
		e.texCoord.y = 1;
		e.color = { 1,0,0, 1 };

		Vertex f;
		f.position = { 0,-1,0, 1 };
		f.texCoord.x = 1;
		f.texCoord.y = 0;
		f.color = { 1,0,0, 1 };

		m_vertices.push_back(a);
		m_vertices.push_back(b);
		m_vertices.push_back(c);
		m_vertices.push_back(d);
		m_vertices.push_back(e);
		m_vertices.push_back(f);

		m_indices = { 0,1,2,3,4,5 };
	}

	void Mesh::CubeInit()
	{
		m_vertices.resize(8);

		m_vertices[0].position = { -1, 1,-1, 1 };
		m_vertices[1].position = { 1, 1,-1, 1 };
		m_vertices[2].position = { -1, -1,-1, 1 };
		m_vertices[3].position = { 1, -1,-1, 1 };
		m_vertices[4].position = { -1, 1,1, 1 };
		m_vertices[5].position = { 1, 1,1, 1 };
		m_vertices[6].position = { -1, -1,1, 1 };
		m_vertices[7].position = { 1, -1,1, 1 };

		m_vertices[0].texCoord = { 0, 1, 0, 0 };
		m_vertices[1].texCoord = { 1, 1, 0, 0 };
		m_vertices[2].texCoord = { 0, 0, 0, 0 };
		m_vertices[3].texCoord = { 1, 0, 0, 0 };
		m_vertices[4].texCoord = { 0, 1, 0, 0 };
		m_vertices[5].texCoord = { 1, 1, 0, 0 };
		m_vertices[6].texCoord = { 0, 0, 0, 0 };
		m_vertices[7].texCoord = { 1, 0, 0, 0 };

		for (auto& vtx : m_vertices) vtx.color = { 0.4,0.6,0.8,1 };

		m_indices = {
			4,5,6,
			6,5,7,
			7,5,1,
			7,1,3,
			3,1,0,
			3,0,2,
			2,0,4,
			2,4,6,
			4,0,1,
			4,1,5,
			2,6,7,
			2,7,3
		};

		Math::CalculateNormals(m_vertices, m_indices);
	}

	void Mesh::SetVertices(const std::vector<Vertex>& vertices)
	{
		m_vertices = vertices;
	}

	void Mesh::SetIndices(const std::vector<unsigned int>& indices)
	{
		m_indices = indices;
	}

	const std::vector<Vertex>& Mesh::GetVertices() const
	{
		return m_vertices;
	}

	const std::vector<unsigned int>& Mesh::GetIndices() const
	{
		return m_indices;
	}

}