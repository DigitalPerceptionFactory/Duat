#pragma once
#include <utility>

namespace DirectX {

	struct BOOL2;
	struct BOOL4;

	struct BOOL3 {
		bool x, y, z;
		BOOL3() = default;
		BOOL3(bool value);
		BOOL3(bool x, bool y, bool z);
		BOOL3(BOOL2 value);
		BOOL3(BOOL4 value);
		BOOL3(const BOOL3& rhs) {
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
		}
		BOOL3(BOOL3&& rhs) noexcept {
			x = std::move(rhs.x);
			y = std::move(rhs.y);
			z = std::move(rhs.z);
		}
		BOOL3& operator=(BOOL3&& rhs) noexcept {
			x = std::move(rhs.x);
			y = std::move(rhs.y);
			z = std::move(rhs.z);
			return *this;
		}

		operator bool()
		{
			return x == true && y == true && z == true;
		}

		BOOL3& operator=(bool rhs);
		BOOL3& operator=(const BOOL2& rhs);
		BOOL3& operator=(const BOOL3& rhs);
		BOOL3& operator=(const BOOL4& rhs);

		bool operator==(bool rhs)
		{
			return x == rhs && y == rhs && z == rhs;
		}

	};

}