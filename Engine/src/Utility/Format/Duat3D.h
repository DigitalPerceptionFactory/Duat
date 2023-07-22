#pragma once
#include <filesystem>
#include <Geometry/Mesh.h>
#include "Loader.h"


namespace Duat {

	struct HeaderDuat3D {
		int32_t number_of_vertices;
		int32_t number_of_indices;
	};
	
	struct Duat3D
	{
		void Load(const std::filesystem::path& path);
		void Save(const std::filesystem::path& path);

		Geometry::Mesh mesh;
	};

	Duat3D LoadDuat3DFile(const std::filesystem::path& path);
	void SaveDuat3DFile(const std::string& filename, Duat3D& duat3D);
}