#pragma once
#include <vector>
#include "Vertex.h"


namespace Duat::Geometry {
		
	struct Mesh {
		void Reset();
		void TestInit();
		void CubeInit();
		void SetMesh(const Mesh& other);
		void SetVertices(const std::vector<Vertex>& vertices);
		void SetIndices(const std::vector<unsigned int>& indices);
		void AppendVertices(const std::vector<Vertex>& vertices);
		void AppendIndices(const std::vector<unsigned int>& indices);
		void AppendMesh(const Mesh& mesh);
		void SwapTriangleIndexOrder();
		void UpdateNormals();

		void SetVertexColor(float r, float g, float b, float a = 1.0f);

		void GeneratePointListIndices();
		void SeparateTriangles();

		const std::vector<Vertex>& GetVertices() const;
		const std::vector<unsigned int>& GetIndices() const;
	protected:
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
	};

}