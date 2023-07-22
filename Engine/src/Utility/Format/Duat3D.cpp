#include "Duat3D.h"


namespace Duat {

	void Duat3D::Load(const std::filesystem::path& path)
	{
		*this = LoadDuat3DFile(path);
	}

	void Duat3D::Save(const std::filesystem::path& path)
	{
		SaveDuat3DFile(path.string(), *this);
	}

	Duat3D LoadDuat3DFile(const std::filesystem::path& path)
	{
		Duat3D out;
		std::vector<Geometry::Vertex> vertices;
		std::vector<uint32_t> indices;
		auto file = LoadFileAsArray<char>(path.string());
		HeaderDuat3D* header = (HeaderDuat3D*)file.data();

		Geometry::Vertex* pVertices = (Geometry::Vertex*)(header + 1);
		for (int i = 0; i < header->number_of_vertices; ++i)
		{
			vertices.push_back(*pVertices);
			++pVertices;
		}

		uint32_t* pIndices = (uint32_t*)pVertices;
		for (int i = 0; i < header->number_of_indices; ++i)
		{
			indices.push_back(*pIndices);
			++pIndices;
		}

		out.mesh.SetIndices(indices);
		out.mesh.SetVertices(vertices);
		return out;
	}

	void SaveDuat3DFile(const std::string& filename, Duat3D& duat3D)
	{
		std::vector<char> bytes;
		HeaderDuat3D header;
		header.number_of_vertices = duat3D.mesh.GetVertices().size();
		header.number_of_indices = duat3D.mesh.GetIndices().size();

		size_t vSize = header.number_of_vertices * sizeof(Geometry::Vertex);
		size_t iSize = header.number_of_indices * sizeof(uint32_t);
		size_t fileSize = sizeof(header) + vSize + iSize;
		bytes.resize(fileSize);
			
		std::memcpy(bytes.data(), &header, sizeof(header));
		std::memcpy(bytes.data() + sizeof(header), &duat3D.mesh.GetVertices(), vSize);
		std::memcpy(bytes.data() + sizeof(header) + vSize, &duat3D.mesh.GetIndices(), iSize);
		SaveFileAsArray(bytes, filename + ".duat3d");
	}
		
}