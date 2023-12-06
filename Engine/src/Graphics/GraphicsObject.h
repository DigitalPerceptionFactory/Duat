#pragma once
#include <string>
#include <Geometry/Mesh.h>
#include <Utility/DirectX/EnumWrappers.h>


namespace Duat::Graphics {

	struct GraphicsObject {
		Geometry::Mesh mesh;
		std::string vs = "Default";
		std::string ps = "Default";
		std::string cam = "Default";
		std::string bs = "Default";
		std::string rs = "Default";
		std::string dss = "Default";
		Topology tp = Topology::TriangleList;
	};

}