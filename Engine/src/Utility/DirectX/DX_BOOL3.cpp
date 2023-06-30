#include "DX_BOOL2.h"
#include "DX_BOOL3.h"
#include "DX_BOOL4.h"



namespace DirectX {

	BOOL3::BOOL3(bool value) : x(value), y(value), z(value)
	{
	}

	BOOL3::BOOL3(bool x, bool y, bool z) : x(x), y(y), z(z)
	{
	}

	BOOL3::BOOL3(BOOL2 value) : x(value.x), y(value.y), z(false)
	{
	}

	BOOL3::BOOL3(BOOL4 value) : x(value.x), y(value.y), z(value.z)
	{
	}

	BOOL3& BOOL3::operator=(bool rhs) {
		x = rhs;
		y = rhs;
		z = rhs;
		return *this;
	}
	BOOL3& BOOL3::operator=(const BOOL2& rhs) {
		x = rhs.x;
		y = rhs.y;
		return *this;
	}
	BOOL3& BOOL3::operator=(const BOOL3& rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}
	BOOL3& BOOL3::operator=(const BOOL4& rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

}