#include "Solid26.h"


namespace Duat::Geometry {

	Tetrahedron::Tetrahedron()
	{
		m_vertices.resize(24);

		//m_vertices[0] = {-1.0f, }

	}

	//Cube::Cube()
	//{
	//}

	Octahedron::Octahedron()
	{
	}

	Dodecahedron::Dodecahedron()
	{
		float Phi = 1.618033988749895f;
		float phi = 0.618033988749895f;
		float small = 0.5f * Phi;
		float large = 0.5f * Phi + 0.5f;

		m_vertices.resize(60);

		// face 1
		m_vertices[0].position = { 0.0f, large, -0.5f };
		m_vertices[1].position = { small, small, -small };
		m_vertices[2].position = { 0.5f, 0.0f, -large };
		m_vertices[3].position = { -0.5f, 0.0f, -large };
		m_vertices[4].position = { -small, small, -small };
		
		//face 2
		m_vertices[5].position = { 0.5f, 0.0f, -large };
		m_vertices[6].position = { small, small, -small };
		m_vertices[7].position = { large, 0.5f, 0.0f };
		m_vertices[8].position = { large, -0.5f, 0.0f };
		m_vertices[9].position = { small, -small, -small };

		// face 3
		m_vertices[10].position = { -0.5f, 0.0f, -large };
		m_vertices[11].position = { 0.5f, 0.0f, -large };
		m_vertices[12].position = { small, -small, -small };
		m_vertices[13].position = { 0.0f, -large, -0.5f };
		m_vertices[14].position = { -small, -small, -small };

		// face 4
		m_vertices[15].position = { -small, small, -small };
		m_vertices[16].position = { -0.5f, 0.0f, -large };
		m_vertices[17].position = { -small, -small, -small };
		m_vertices[18].position = { -large, -0.5f, 0.0f };
		m_vertices[19].position = { -large, 0.5f, 0.0f };

		// face 5
		m_vertices[20].position = { 0.0f, large, 0.5f };
		m_vertices[21].position = { -small, small, small };
		m_vertices[22].position = { -0.5f, 0.0f, large };
		m_vertices[23].position = { 0.5f, 0.0f, large };
		m_vertices[24].position = { small, small, small };

		//face 6
		m_vertices[25].position = { 0.5f, 0.0f, large };
		m_vertices[26].position = { small, -small, small };
		m_vertices[27].position = { large, -0.5f, 0.0f };
		m_vertices[28].position = { large, 0.5f, 0.0f };
		m_vertices[29].position = { small, small, small };

		// face 7
		m_vertices[30].position = { 0.5f, 0.0f, large };
		m_vertices[31].position = { -0.5f, 0.0f, large };
		m_vertices[32].position = { -small, -small, small };
		m_vertices[33].position = { 0.0f, -large, 0.5f };
		m_vertices[34].position = { small, -small, small };

		// face 8
		m_vertices[35].position = { -0.5f, 0.0f, large };
		m_vertices[36].position = { -small, small, small };
		m_vertices[37].position = { -large, 0.5f, 0.0f };
		m_vertices[38].position = { -large, -0.5f, 0.0f };
		m_vertices[39].position = { -small, -small, small };

		// face 9
		m_vertices[40].position = { 0.0f, large, -0.5f };
		m_vertices[41].position = { 0.0f, large, 0.5f };
		m_vertices[42].position = { small, small, small };
		m_vertices[43].position = { large, 0.5f, 0.0f };
		m_vertices[44].position = { small, small, -small };

		// face 10
		m_vertices[45].position = { large, -0.5f, 0.0f };
		m_vertices[46].position = { small, -small, small };
		m_vertices[47].position = { 0.0f, -large, 0.5f };
		m_vertices[48].position = { 0.0f, -large, -0.5f };
		m_vertices[49].position = { small, -small, -small };

		// face 11
		m_vertices[50].position = { 0.0f, large, 0.5f };
		m_vertices[51].position = { 0.0f, large, -0.5f };
		m_vertices[52].position = { -small, small, -small };
		m_vertices[53].position = { -large, 0.5f, 0.0f };
		m_vertices[54].position = { -small, small, small };

		// face 12
		m_vertices[55].position = { -large, -0.5f, 0.0f };
		m_vertices[56].position = { -small, -small, -small };
		m_vertices[57].position = { 0.0f, -large, -0.5f };
		m_vertices[58].position = { 0.0f, -large, 0.5f };
		m_vertices[59].position = { -small, -small, small };

		std::vector<unsigned int> indices = {
			0, 1, 2, 0, 2, 3, 0, 3, 4
		};
		AppendIndices(indices);
		for (int i = 1; i < 12; ++i)
		{
			for (auto& idx : indices) idx += 5;
			AppendIndices(indices);
		}

		UpdateNormals();
	}

	Icosahedron::Icosahedron()
	{
		float q = 0.25f * 3;
		float h = 0.5f * 3;

		m_vertices.resize(12);
		
		// bottom
		m_vertices[0] = { -q, -h, 0 };
		m_vertices[1] = { q, -h, 0 };
		
		// right
		m_vertices[2] = {  h, 0, -q };
		m_vertices[3] = { h, 0, q };

		// back
		m_vertices[4] = { 0, -q, h };
		m_vertices[5] = { 0, q, h };

		// left
		m_vertices[6] = { -h, 0, -q };
		m_vertices[7] = { -h, 0, q };

		// front
		m_vertices[8] = { 0, -q, -h };
		m_vertices[9] = { 0, q, -h };

		// top
		m_vertices[10] = { -q, h, 0 };
		m_vertices[11] = { q, h, 0 };

		m_indices =
		{
			1, 8, 2,
			1, 2, 3,
			1, 3, 4,
			1, 4, 0,
			0, 4, 7,
			0, 6, 8,
			0, 8, 1,
			8, 6, 9,
			8, 9, 2,
			9, 11, 2,
			2, 11, 3,
			3, 11, 5,
			3, 5, 4,
			4, 5, 7,
			5, 10, 7,
			5, 11, 10,
			6, 10, 9,
			9, 10, 11,
			0, 7, 6,
			6, 7, 10
		};

		SeparateTriangles();
		UpdateNormals();
	}

}