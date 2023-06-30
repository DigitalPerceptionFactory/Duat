#pragma once
#include <utility>

namespace DirectX {

	struct BOOL3;
	struct BOOL4;

	struct BOOL2 {
		bool x, y;
		BOOL2() = default;
		BOOL2(bool value);
		BOOL2(bool x, bool y);
		BOOL2(BOOL3 value);
		BOOL2(BOOL4 value);
		BOOL2(const BOOL2& rhs) {
			x = rhs.x;
			y = rhs.y;
		}
		BOOL2(BOOL2&& rhs) noexcept {
			x = std::move(rhs.x);
			y = std::move(rhs.y);
		}
		BOOL2& operator=(BOOL2&& rhs) noexcept {
			x = std::move(rhs.x);
			y = std::move(rhs.y);
			return *this;
		}


		operator bool()
		{
			return x == true && y == true;
		}

		BOOL2& operator=(bool rhs);
		BOOL2& operator=(const BOOL2& rhs);
		BOOL2& operator=(const BOOL3& rhs);
		BOOL2& operator=(const BOOL4& rhs);

	};

}