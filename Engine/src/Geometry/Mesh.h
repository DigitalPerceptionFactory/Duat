#pragma once
#include <vector>
#include "Vertex.h"
#include <Utility/Classes.h>


namespace Duat::Geometry {
		
	struct Mesh {
		void TestInit();
		const std::vector<Vertex>& GetVertices() const;
		const std::vector<unsigned int>& GetIndices() const;
	private:
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
	};

}