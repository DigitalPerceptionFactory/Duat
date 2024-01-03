#pragma once
#include "Mesh.h"


namespace Duat::Geometry {

	struct Tetrahedron : public Mesh { Tetrahedron(); };
	struct Cube : public Mesh { Cube(); };
	struct Octahedron : public Mesh { Octahedron(); };
	struct Dodecahedron : public Mesh { Dodecahedron(); };
	struct Icosahedron : public Mesh { Icosahedron(); };

}