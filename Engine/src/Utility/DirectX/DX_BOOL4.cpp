#include "DX_BOOL2.h"
#include "DX_BOOL3.h"
#include "DX_BOOL4.h"


namespace DirectX {

	BOOL4::BOOL4(bool value) : x(value), y(value), z(value), w(value)
	{
	}

	BOOL4::BOOL4(bool x, bool y, bool z, bool w) : x(x), y(y), z(z), w(w)
	{
	}

	BOOL4::BOOL4(BOOL2 value) : x(value.x), y(value.y), z(false), w(false)
	{
	}

	BOOL4::BOOL4(BOOL3 value) : x(value.x), y(value.y), z(value.z), w(false)
	{
	}

	BOOL4& BOOL4::operator=(bool rhs) {
		x = rhs;
		y = rhs;
		z = rhs;
		w = rhs;
		return *this;
	}
	BOOL4& BOOL4::operator=(const BOOL2& rhs) {
		x = rhs.x;
		y = rhs.y;
		return *this;
	}
	BOOL4& BOOL4::operator=(const BOOL3& rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}
	BOOL4& BOOL4::operator=(const BOOL4& rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
		return *this;
	}

}