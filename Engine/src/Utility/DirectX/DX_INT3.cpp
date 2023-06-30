#include <DirectXMath.h>
#include "DX_INT2.h"
#include "DX_INT3.h"
#include "DX_INT4.h"
#include "DX_BOOL2.h"
#include "DX_BOOL3.h"
#include "DX_BOOL4.h"


namespace DirectX {

	INT3& INT3::operator=(int rhs)
	{
		x = y = z = rhs;
		return *this;
	}

	INT3& INT3::operator=(const INT2& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	INT3& INT3::operator=(const INT3& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	INT3& INT3::operator=(const INT4& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	INT3 INT3::operator+(int rhs)
	{
		return { x + rhs, y + rhs, z + rhs };
	}

	INT3 INT3::operator+(const INT2& rhs)
	{
		return { x + rhs.x, y + rhs.y, z };
	}

	INT3 INT3::operator+(const INT3& rhs)
	{
		return { x + rhs.x, y + rhs.y, z + rhs.z };
	}

	INT3 INT3::operator+(const INT4& rhs)
	{
		return { x + rhs.x, y + rhs.y, z + rhs.z };
	}

	INT3& INT3::operator+=(int rhs)
	{
		x += rhs;
		y += rhs;
		z += rhs;
		return *this;
	}

	INT3& INT3::operator+=(const INT2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	INT3& INT3::operator+=(const INT3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	INT3& INT3::operator+=(const INT4& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	INT3 INT3::operator-(int rhs)
	{
		return { x - rhs, y - rhs, z - rhs };
	}

	INT3 INT3::operator-(const INT2& rhs)
	{
		return { x - rhs.x, y - rhs.y, z };
	}

	INT3 INT3::operator-(const INT3& rhs)
	{
		return { x - rhs.x, y - rhs.y, z - rhs.z };
	}

	INT3 INT3::operator-(const INT4& rhs)
	{
		return { x - rhs.x, y - rhs.y, z - rhs.z };
	}

	INT3& INT3::operator-=(int rhs)
	{
		x -= rhs;
		y -= rhs;
		z -= rhs;
		return *this;
	}

	INT3& INT3::operator-=(const INT2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	INT3& INT3::operator-=(const INT3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	INT3& INT3::operator-=(const INT4& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	INT3 INT3::operator*(int rhs)
	{
		return { x * rhs, y * rhs, z * rhs };
	}

	INT3 INT3::operator*(const INT2& rhs)
	{
		return { x * rhs.x, y * rhs.y, z };
	}

	INT3 INT3::operator*(const INT3& rhs)
	{
		return { x * rhs.x, y * rhs.y, z * rhs.z };
	}

	INT3 INT3::operator*(const INT4& rhs)
	{
		return { x * rhs.x, y * rhs.y, z * rhs.z };
	}

	INT3& INT3::operator*=(int rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return *this;
	}

	INT3& INT3::operator*=(const INT2& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	INT3& INT3::operator*=(const INT3& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}

	INT3& INT3::operator*=(const INT4& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}

	INT3 INT3::operator/(int rhs)
	{
		return { x / rhs, y / rhs, z / rhs };
	}

	INT3 INT3::operator/(const INT2& rhs)
	{
		return { x / rhs.x, y / rhs.y, z };
	}

	INT3 INT3::operator/(const INT3& rhs)
	{
		return { x / rhs.x, y / rhs.y, z / rhs.z };
	}

	INT3 INT3::operator/(const INT4& rhs)
	{
		return { x / rhs.x, y / rhs.y, z / rhs.z };
	}

	INT3& INT3::operator/=(int rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}

	INT3& INT3::operator/=(const INT2& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	INT3& INT3::operator/=(const INT3& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}

	INT3& INT3::operator/=(const INT4& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}

	bool INT3::operator==(int rhs)
	{
		if (x == rhs && y == rhs && z == rhs)
			return true;
		return false;
	}

	BOOL2 INT3::operator==(const INT2& rhs)
	{
		BOOL2 result = { false,false };
		if (x == rhs.x) result.x = true;
		if (y == rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT3::operator==(const INT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if (x == rhs.x) result.x = true;
		if (y == rhs.y) result.y = true;
		if (z == rhs.z) result.z = true;
		return result;
	}

	BOOL3 INT3::operator==(const INT4& rhs)
	{
		BOOL3 result = { false,false,false };
		if (x == rhs.x) result.x = true;
		if (y == rhs.y) result.y = true;
		if (z == rhs.z) result.z = true;
		return result;
	}

	bool INT3::operator!=(int rhs)
	{
		if (x != rhs && y != rhs && z != rhs)
			return true;
		return false;
	}

	BOOL2 INT3::operator!=(const INT2& rhs)
	{
		BOOL2 result = { false,false };
		if (x != rhs.x) result.x = true;
		if (y != rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT3::operator!=(const INT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if (x != rhs.x) result.x = true;
		if (y != rhs.y) result.y = true;
		if (z != rhs.z) result.z = true;
		return result;
	}

	BOOL3 INT3::operator!=(const INT4& rhs)
	{
		BOOL3 result = { false,false,false };
		if (x != rhs.x) result.x = true;
		if (y != rhs.y) result.y = true;
		if (z != rhs.z) result.z = true;
		return result;
	}

	bool INT3::operator>(int rhs)
	{
		if (x > rhs && y > rhs && z > rhs)
			return true;
		return false;
	}

	BOOL2 INT3::operator>(const INT2& rhs)
	{
		BOOL2 result = { false,false };
		if (x > rhs.x) result.x = true;
		if (y > rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT3::operator>(const INT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if (x > rhs.x) result.x = true;
		if (y > rhs.y) result.y = true;
		if (z > rhs.z) result.z = true;
		return result;
	}

	BOOL3 INT3::operator>(const INT4& rhs)
	{
		BOOL3 result = { false,false,false };
		if (x > rhs.x) result.x = true;
		if (y > rhs.y) result.y = true;
		if (z > rhs.z) result.z = true;
		return result;
	}

	bool INT3::operator<(int rhs)
	{
		if (x < rhs && y < rhs && z < rhs)
			return true;
		return false;
	}

	BOOL2 INT3::operator<(const INT2& rhs)
	{
		BOOL2 result = { false,false };
		if (x < rhs.x) result.x = true;
		if (y < rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT3::operator<(const INT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if (x < rhs.x) result.x = true;
		if (y < rhs.y) result.y = true;
		if (z < rhs.z) result.z = true;
		return result;
	}

	BOOL3 INT3::operator<(const INT4& rhs)
	{
		BOOL3 result = { false,false,false };
		if (x < rhs.x) result.x = true;
		if (y < rhs.y) result.y = true;
		if (z < rhs.z) result.z = true;
		return result;
	}

	bool INT3::operator>=(int rhs)
	{
		if (x >= rhs && y >= rhs && z >= rhs)
			return true;
		return false;
	}

	BOOL2 INT3::operator>=(const INT2& rhs)
	{
		BOOL2 result = { false,false };
		if (x >= rhs.x) result.x = true;
		if (y >= rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT3::operator>=(const INT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if (x >= rhs.x) result.x = true;
		if (y >= rhs.y) result.y = true;
		if (z >= rhs.z) result.z = true;
		return result;
	}

	BOOL3 INT3::operator>=(const INT4& rhs)
	{
		BOOL3 result = { false,false,false };
		if (x >= rhs.x) result.x = true;
		if (y >= rhs.y) result.y = true;
		if (z >= rhs.z) result.z = true;
		return result;
	}

	bool INT3::operator<=(int rhs)
	{
		if (x <= rhs && y <= rhs && z <= rhs)
			return true;
		return false;
	}

	BOOL2 INT3::operator<=(const INT2& rhs)
	{
		BOOL2 result = { false,false };
		if (x <= rhs.x) result.x = true;
		if (y <= rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT3::operator<=(const INT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if (x <= rhs.x) result.x = true;
		if (y <= rhs.y) result.y = true;
		if (z <= rhs.z) result.z = true;
		return result;
	}

	BOOL3 INT3::operator<=(const INT4& rhs)
	{
		BOOL3 result = { false,false,false };
		if (x <= rhs.x) result.x = true;
		if (y <= rhs.y) result.y = true;
		if (z <= rhs.z) result.z = true;
		return result;
	}

	INT3& INT3::operator=(float rhs)
	{
		x = y = z = (int)rhs;
		return *this;
	}

	INT3& INT3::operator=(const XMFLOAT2& rhs)
	{
		x = (int)rhs.x;
		y = (int)rhs.y;
		return *this;
	}

	INT3& INT3::operator=(const XMFLOAT3& rhs)
	{
		x = (int)rhs.x;
		y = (int)rhs.y;
		z = (int)rhs.z;
		return *this;
	}

	INT3& INT3::operator=(const XMFLOAT4& rhs)
	{
		x = (int)rhs.x;
		y = (int)rhs.y;
		z = (int)rhs.z;
		return *this;
	}

	INT3 INT3::operator+(float rhs)
	{
		return { x + (int)rhs, y + (int)rhs, z + (int)rhs };
	}

	INT3 INT3::operator+(const XMFLOAT2& rhs)
	{
		return { x + (int)rhs.x, y + (int)rhs.y, z};
	}

	INT3 INT3::operator+(const XMFLOAT3& rhs)
	{
		return { x + (int)rhs.x, y + (int)rhs.y, z + (int)rhs.z };
	}

	INT3 INT3::operator+(const XMFLOAT4& rhs)
	{
		return { x + (int)rhs.x, y + (int)rhs.y, z + (int)rhs.z };
	}

	INT3& INT3::operator+=(float rhs)
	{
		x += (int)rhs;
		y += (int)rhs;
		z += (int)rhs;
		return *this;
	}

	INT3& INT3::operator+=(const XMFLOAT2& rhs)
	{
		x += (int)rhs.x;
		y += (int)rhs.y;
		return *this;
	}

	INT3& INT3::operator+=(const XMFLOAT3& rhs)
	{
		x += (int)rhs.x;
		y += (int)rhs.y;
		z += (int)rhs.z;
		return *this;
	}

	INT3& INT3::operator+=(const XMFLOAT4& rhs)
	{
		x += (int)rhs.x;
		y += (int)rhs.y;
		z += (int)rhs.z;
		return *this;
	}

	INT3 INT3::operator-(float rhs)
	{
		return { x - (int)rhs, y - (int)rhs, z - (int)rhs };
	}

	INT3 INT3::operator-(const XMFLOAT2& rhs)
	{
		return { x - (int)rhs.x, y - (int)rhs.y, z };
	}

	INT3 INT3::operator-(const XMFLOAT3& rhs)
	{
		return { x - (int)rhs.x, y - (int)rhs.y, z - (int)rhs.z };
	}

	INT3 INT3::operator-(const XMFLOAT4& rhs)
	{
		return { x - (int)rhs.x, y - (int)rhs.y, z - (int)rhs.z };
	}

	INT3& INT3::operator-=(float rhs)
	{
		x -= (int)rhs;
		y -= (int)rhs;
		z -= (int)rhs;
		return *this;
	}

	INT3& INT3::operator-=(const XMFLOAT2& rhs)
	{
		x -= (int)rhs.x;
		y -= (int)rhs.y;
		return *this;
	}

	INT3& INT3::operator-=(const XMFLOAT3& rhs)
	{
		x -= (int)rhs.x;
		y -= (int)rhs.y;
		z -= (int)rhs.z;
		return *this;
	}

	INT3& INT3::operator-=(const XMFLOAT4& rhs)
	{
		x -= (int)rhs.x;
		y -= (int)rhs.y;
		z -= (int)rhs.z;
		return *this;
	}

	INT3 INT3::operator*(float rhs)
	{
		return { x * (int)rhs, y * (int)rhs, z * (int)rhs };
	}

	INT3 INT3::operator*(const XMFLOAT2& rhs)
	{
		return { x * (int)rhs.x, y * (int)rhs.y, z };
	}

	INT3 INT3::operator*(const XMFLOAT3& rhs)
	{
		return { x * (int)rhs.x, y * (int)rhs.y, z * (int)rhs.z };
	}

	INT3 INT3::operator*(const XMFLOAT4& rhs)
	{
		return { x * (int)rhs.x, y * (int)rhs.y, z * (int)rhs.z };
	}

	INT3& INT3::operator*=(float rhs)
	{
		x *= (int)rhs;
		y *= (int)rhs;
		z *= (int)rhs;
		return *this;
	}

	INT3& INT3::operator*=(const XMFLOAT2& rhs)
	{
		x *= (int)rhs.x;
		y *= (int)rhs.y;
		return *this;
	}

	INT3& INT3::operator*=(const XMFLOAT3& rhs)
	{
		x *= (int)rhs.x;
		y *= (int)rhs.y;
		z *= (int)rhs.z;
		return *this;
	}

	INT3& INT3::operator*=(const XMFLOAT4& rhs)
	{
		x *= (int)rhs.x;
		y *= (int)rhs.y;
		z *= (int)rhs.z;
		return *this;
	}

	INT3 INT3::operator/(float rhs)
	{
		return { x / (int)rhs, y / (int)rhs, z / (int)rhs };
	}

	INT3 INT3::operator/(const XMFLOAT2& rhs)
	{
		return { x / (int)rhs.x, y / (int)rhs.y, z };
	}

	INT3 INT3::operator/(const XMFLOAT3& rhs)
	{
		return { x / (int)rhs.x, y / (int)rhs.y, z / (int)rhs.z };
	}

	INT3 INT3::operator/(const XMFLOAT4& rhs)
	{
		return { x / (int)rhs.x, y / (int)rhs.y, z / (int)rhs.z };
	}

	INT3& INT3::operator/=(float rhs)
	{
		x /= (int)rhs;
		y /= (int)rhs;
		z /= (int)rhs;
		return *this;
	}

	INT3& INT3::operator/=(const XMFLOAT2& rhs)
	{
		x /= (int)rhs.x;
		y /= (int)rhs.y;
		return *this;
	}

	INT3& INT3::operator/=(const XMFLOAT3& rhs)
	{
		x /= (int)rhs.x;
		y /= (int)rhs.y;
		z /= (int)rhs.z;
		return *this;
	}

	INT3& INT3::operator/=(const XMFLOAT4& rhs)
	{
		x /= (int)rhs.x;
		y /= (int)rhs.y;
		z /= (int)rhs.z;
		return *this;
	}

	bool INT3::operator==(float rhs)
	{
		if ((float)x == rhs && (float)y == rhs && (float)z == rhs)
			return true;
		return false;
	}

	BOOL2 INT3::operator==(const XMFLOAT2& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x == rhs.x) result.x = true;
		if ((float)y == rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT3::operator==(const XMFLOAT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if ((float)x == rhs.x) result.x = true;
		if ((float)y == rhs.y) result.y = true;
		if ((float)z == rhs.z) result.z = true;
		return result;
	}

	BOOL3 INT3::operator==(const XMFLOAT4& rhs)
	{
		BOOL3 result = { false,false,false };
		if ((float)x == rhs.x) result.x = true;
		if ((float)y == rhs.y) result.y = true;
		if ((float)z == rhs.z) result.z = true;
		return result;
	}

	bool INT3::operator!=(float rhs)
	{
		if ((float)x != rhs && (float)y != rhs && (float)z != rhs)
			return true;
		return false;
	}

	BOOL2 INT3::operator!=(const XMFLOAT2& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x != rhs.x) result.x = true;
		if ((float)y != rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT3::operator!=(const XMFLOAT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if ((float)x != rhs.x) result.x = true;
		if ((float)y != rhs.y) result.y = true;
		if ((float)z != rhs.z) result.z = true;
		return result;
	}

	BOOL3 INT3::operator!=(const XMFLOAT4& rhs)
	{
		BOOL3 result = { false,false,false };
		if ((float)x != rhs.x) result.x = true;
		if ((float)y != rhs.y) result.y = true;
		if ((float)z != rhs.z) result.z = true;
		return result;
	}

	bool INT3::operator>(float rhs)
	{
		if ((float)x > rhs && (float)y > rhs && (float)z > rhs)
			return true;
		return false;
	}

	BOOL2 INT3::operator>(const XMFLOAT2& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x > rhs.x) result.x = true;
		if ((float)y > rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT3::operator>(const XMFLOAT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if ((float)x > rhs.x) result.x = true;
		if ((float)y > rhs.y) result.y = true;
		if ((float)z > rhs.z) result.z = true;
		return result;
	}

	BOOL3 INT3::operator>(const XMFLOAT4& rhs)
	{
		BOOL3 result = { false,false,false };
		if ((float)x > rhs.x) result.x = true;
		if ((float)y > rhs.y) result.y = true;
		if ((float)z > rhs.z) result.z = true;
		return result;
	}

	bool INT3::operator<(float rhs)
	{
		if ((float)x < rhs && (float)y < rhs && (float)z < rhs)
			return true;
		return false;
	}

	BOOL2 INT3::operator<(const XMFLOAT2& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x < rhs.x) result.x = true;
		if ((float)y < rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT3::operator<(const XMFLOAT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if ((float)x < rhs.x) result.x = true;
		if ((float)y < rhs.y) result.y = true;
		if ((float)z < rhs.z) result.z = true;
		return result;
	}

	BOOL3 INT3::operator<(const XMFLOAT4& rhs)
	{
		BOOL3 result = { false,false,false };
		if ((float)x < rhs.x) result.x = true;
		if ((float)y < rhs.y) result.y = true;
		if ((float)z < rhs.z) result.z = true;
		return result;
	}

	bool INT3::operator>=(float rhs)
	{
		if ((float)x >= rhs && (float)y >= rhs && (float)z >= rhs)
			return true;
		return false;
	}

	BOOL2 INT3::operator>=(const XMFLOAT2& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x >= rhs.x) result.x = true;
		if ((float)y >= rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT3::operator>=(const XMFLOAT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if ((float)x >= rhs.x) result.x = true;
		if ((float)y >= rhs.y) result.y = true;
		if ((float)z >= rhs.z) result.z = true;
		return result;
	}

	BOOL3 INT3::operator>=(const XMFLOAT4& rhs)
	{
		BOOL3 result = { false,false,false };
		if ((float)x >= rhs.x) result.x = true;
		if ((float)y >= rhs.y) result.y = true;
		if ((float)z >= rhs.z) result.z = true;
		return result;
	}

	bool INT3::operator<=(float rhs)
	{
		if ((float)x <= rhs && (float)y <= rhs && (float)z <= rhs)
			return true;
		return false;
	}

	BOOL2 INT3::operator<=(const XMFLOAT2& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x <= rhs.x) result.x = true;
		if ((float)y <= rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT3::operator<=(const XMFLOAT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if ((float)x <= rhs.x) result.x = true;
		if ((float)y <= rhs.y) result.y = true;
		if ((float)z <= rhs.z) result.z = true;
		return result;
	}

	BOOL3 INT3::operator<=(const XMFLOAT4& rhs)
	{
		BOOL3 result = { false,false,false };
		if ((float)x <= rhs.x) result.x = true;
		if ((float)y <= rhs.y) result.y = true;
		if ((float)z <= rhs.z) result.z = true;
		return result;
	}

}