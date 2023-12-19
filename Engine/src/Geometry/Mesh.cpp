#include "Mesh.h"
#include "Solid26.h"
#include <Utility/DirectX/Legacy.h>


namespace Duat::Geometry {
		
	void Mesh::Reset()
	{
		m_vertices.resize(0);
		m_indices.resize(0);
	}

	void Mesh::TestInit()
	{
		*this = Icosahedron();
		for (auto& vtx : m_vertices) vtx.color = { 0.1, 0.1, 0, 1 };
				
		return;
		std::vector<Vertex> vertices(12);
		vertices[0].position = { -2,2,2 };
		vertices[0].texCoord = { 0,0 };
		vertices[1].position = { 2,2,2 };
		vertices[1].texCoord = { 1,0 };
		vertices[2].position = { -2,-2,2 };
		vertices[2].texCoord = { 0,1 };
		vertices[3].position = { 2,-2,2 };
		vertices[3].texCoord = { 1,1 };

		vertices[4].position = { 2,2,2 };
		vertices[5].position = { 2,2,-2 };
		vertices[6].position = { 2,-2,2 };
		vertices[7].position = { 2,-2,-2 };

		vertices[8].position = { -2,-2,2 };
		vertices[9].position = { 2,-2,2 };
		vertices[10].position = { -2,-2,-2 };
		vertices[11].position = { 2,-2,-2 };

		std::vector<unsigned int> indices = {
			0,1,2, 2,1,3,
			4,5,6,6,5,7,
			8,9,10,10,9,11
		};
		for (auto& idx : indices) idx += m_vertices.size();

		for (auto& vtx : m_vertices) vtx.color = { 0.3,0.3,0,1 };
		for (auto& vtx : vertices) vtx.color = { 1,0,0,1 };

		AppendVertices(vertices);
		AppendIndices(indices);
		UpdateNormals();
	}

	void Mesh::CubeInit()
	{
		m_vertices.resize(8);

		m_vertices[0].position = { -1, 1, -1, };
		m_vertices[1].position = { 1, 1, -1, };
		m_vertices[2].position = { -1, -1, -1, };
		m_vertices[3].position = { 1, -1, -1, };
		m_vertices[4].position = { -1, 1, 1, };
		m_vertices[5].position = { 1, 1, 1, };
		m_vertices[6].position = { -1, -1, 1, };
		m_vertices[7].position = { 1, -1, 1, };

		m_vertices[0].texCoord = { 0, 1 };
		m_vertices[1].texCoord = { 1, 1 };
		m_vertices[2].texCoord = { 0, 0 };
		m_vertices[3].texCoord = { 1, 0 };
		m_vertices[4].texCoord = { 0, 1 };
		m_vertices[5].texCoord = { 1, 1 };
		m_vertices[6].texCoord = { 0, 0 };
		m_vertices[7].texCoord = { 1, 0 };

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

		UpdateNormals();
	}

	void Mesh::SetMesh(const Mesh& other)
	{
		m_vertices = other.m_vertices;
		m_indices = other.m_indices;
	}

	void Mesh::SetVertices(const std::vector<Vertex>& vertices)
	{
		m_vertices = vertices;
	}

	void Mesh::SetIndices(const std::vector<unsigned int>& indices)
	{
		m_indices = indices;
	}

	void Mesh::AppendVertices(const std::vector<Vertex>& vertices)
	{
		m_vertices.insert(m_vertices.end(), vertices.begin(), vertices.end());
	}

	void Mesh::AppendIndices(const std::vector<unsigned int>& indices)
	{
		m_indices.insert(m_indices.end(), indices.begin(), indices.end());
	}

	void Mesh::AppendMesh(const Mesh& mesh)
	{
		size_t offset = m_vertices.size();
		for (const auto& idx : mesh.GetIndices())
			m_indices.push_back(idx + offset);

		AppendVertices(mesh.GetVertices());
	}

	void Mesh::SwapTriangleIndexOrder()
	{
		for (int i = 0; i < m_indices.size(); i += 3)
			std::swap(m_indices[i], m_indices[i + 2]);
	}

	void Mesh::UpdateNormals()
	{
		Math::CalculateNormals(m_vertices, m_indices);
	}

	void Mesh::SetVertexColor(float r, float g, float b, float a)
	{
		for (auto& vtx : m_vertices) vtx.color = { r,g,b,a };
	}

	void Mesh::GeneratePointListIndices()
	{
		m_indices.resize(m_vertices.size());
		std::iota(m_indices.begin(), m_indices.end(), 0);
	}

	void Mesh::SeparateTriangles()
	{
		if (m_indices.size() % 3 != 0 || m_indices.size() < 3) return;

		std::vector<unsigned int> vtxCount;
		unsigned int highestIndex = 0;
		for (const auto& idx : m_indices)
			if (idx > highestIndex) highestIndex = idx;
		vtxCount.resize(std::max<int>(highestIndex, m_vertices.size()), 0);

		for (const auto& idx : m_indices)
			++vtxCount[idx];

		std::vector<Vertex> newVertices;
		for (int i = 0; i < vtxCount.size(); ++i)
			newVertices.insert(newVertices.end(), std::max<int>(vtxCount[i], 1), m_vertices[i]);

		std::vector<unsigned int> newIndices(m_indices.size(), 0);
		auto decrement = vtxCount;
		for (int i = 0; i < m_indices.size(); ++i)
		{
			for (int j = 0; j < m_indices[i]; ++j)
				newIndices[i] += std::max<int>(vtxCount[j], 1);
			--decrement[m_indices[i]];
			newIndices[i] += decrement[m_indices[i]];
		}

		m_indices = newIndices;
		m_vertices = newVertices;
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