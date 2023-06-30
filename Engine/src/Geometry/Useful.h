#pragma once
#include <DirectXMath.h>


namespace Duat::Geometry {
		
	struct InterpolatedIndex {
		unsigned int value;
		DirectX::XMFLOAT2 uv;
	};

	template<typename T>
	struct Rect {
		T left, right, top, bottom;
	};

	template<typename T>
	struct Cube {
		T left, right, top, bottom, front, back;
	};

}