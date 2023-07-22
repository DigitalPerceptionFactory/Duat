#pragma once
#include <vector>
#include "Vertex.h"


namespace Duat::Geometry {
		
	struct Mesh {
		void TestInit();
		void CubeInit();
		void SetVertices(const std::vector<Vertex>& vertices);
		void SetIndices(const std::vector<unsigned int>& indices);
		const std::vector<Vertex>& GetVertices() const;
		const std::vector<unsigned int>& GetIndices() const;
	private:
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
	};

}