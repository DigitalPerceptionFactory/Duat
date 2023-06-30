#include "DX_BOOL2.h"
#include "DX_BOOL3.h"
#include "DX_BOOL4.h"



namespace DirectX {

	BOOL2::BOOL2(bool value) : x(value), y(value)
	{
	}

	BOOL2::BOOL2(bool x, bool y) : x(x), y(y)
	{
	}

	BOOL2::BOOL2(BOOL3 value) : x(value.x), y(value.y)
	{
	}

	BOOL2::BOOL2(BOOL4 value) : x(value.x), y(value.y)
	{
	}


	BOOL2& BOOL2::operator=(bool rhs) {
		x = rhs;
		y = rhs;
		return *this;
	}
	BOOL2& BOOL2::operator=(const BOOL2& rhs) {
		x = rhs.x;
		y = rhs.y;
		return *this;
	}
	BOOL2& BOOL2::operator=(const BOOL3& rhs) {
		x = rhs.x;
		y = rhs.y;
		return *this;
	}
	BOOL2& BOOL2::operator=(const BOOL4& rhs) {
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

}