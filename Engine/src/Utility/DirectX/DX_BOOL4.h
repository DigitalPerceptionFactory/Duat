#pragma once
#include <utility>

namespace DirectX {

	struct BOOL2;
	struct BOOL3;

	struct BOOL4 {
		bool x, y, z, w;
		BOOL4() = default;
		BOOL4(bool value);
		BOOL4(bool x, bool y, bool z, bool w);
		BOOL4(BOOL2 value);
		BOOL4(BOOL3 value);
		BOOL4(const BOOL4& rhs) {
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			w = rhs.w;
		}
		BOOL4(BOOL4&& rhs) noexcept {
			x = std::move(rhs.x);
			y = std::move(rhs.y);
			z = std::move(rhs.z);
			w = std::move(rhs.w);
		}
		BOOL4& operator=(BOOL4&& rhs) noexcept {
			x = std::move(rhs.x);
			y = std::move(rhs.y);
			z = std::move(rhs.z);
			w = std::move(rhs.w);
			return *this;
		}


		operator bool()
		{
			return x == true && y == true && z == true && w == true;
		}

		BOOL4& operator=(bool rhs);
		BOOL4& operator=(const BOOL2& rhs);
		BOOL4& operator=(const BOOL3& rhs);
		BOOL4& operator=(const BOOL4& rhs);

	};

}