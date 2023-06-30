#include <DirectXMath.h>
#include "DX_INT2.h"
#include "DX_INT3.h"
#include "DX_INT4.h"
#include "DX_BOOL2.h"
#include "DX_BOOL3.h"
#include "DX_BOOL4.h"



namespace DirectX {

	INT4& INT4::operator=(int rhs)
	{
		x = y = z = w = rhs;
		return *this;
	}

	INT4& INT4::operator=(const INT2& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	INT4& INT4::operator=(const INT3& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}

	INT4& INT4::operator=(const INT4& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
		return *this;
	}

	INT4 INT4::operator+(int rhs)
	{
		return { x + rhs, y + rhs, z + rhs, w + rhs };
	}

	INT4 INT4::operator+(const INT2& rhs)
	{
		return { x + rhs.x, y + rhs.y, z, w };
	}

	INT4 INT4::operator+(const INT3& rhs)
	{
		return { x + rhs.x, y + rhs.y, z + rhs.z, w };
	}

	INT4 INT4::operator+(const INT4& rhs)
	{
		return { x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w };
	}

	INT4& INT4::operator+=(int rhs)
	{
		x += rhs;
		y += rhs;
		z += rhs;
		w += rhs;
		return *this;
	}

	INT4& INT4::operator+=(const INT2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	INT4& INT4::operator+=(const INT3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	INT4& INT4::operator+=(const INT4& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}

	INT4 INT4::operator-(int rhs)
	{
		return { x - rhs, y - rhs, z - rhs, w - rhs };
	}

	INT4 INT4::operator-(const INT2& rhs)
	{
		return { x - rhs.x, y - rhs.y, z, w };
	}

	INT4 INT4::operator-(const INT3& rhs)
	{
		return { x - rhs.x, y - rhs.y, z - rhs.z, w };
	}

	INT4 INT4::operator-(const INT4& rhs)
	{
		return { x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w };
	}

	INT4& INT4::operator-=(int rhs)
	{
		x -= rhs;
		y -= rhs;
		z -= rhs;
		w -= rhs;
		return *this;
	}

	INT4& INT4::operator-=(const INT2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	INT4& INT4::operator-=(const INT3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	INT4& INT4::operator-=(const INT4& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}

	INT4 INT4::operator*(int rhs)
	{
		return { x * rhs, y * rhs, z * rhs, w * rhs };
	}

	INT4 INT4::operator*(const INT2& rhs)
	{
		return { x * rhs.x, y * rhs.y, z, w };
	}

	INT4 INT4::operator*(const INT3& rhs)
	{
		return { x * rhs.x, y * rhs.y, z * rhs.z, w };
	}

	INT4 INT4::operator*(const INT4& rhs)
	{
		return { x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w };
	}

	INT4& INT4::operator*=(int rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		w *= rhs;
		return *this;
	}

	INT4& INT4::operator*=(const INT2& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	INT4& INT4::operator*=(const INT3& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}

	INT4& INT4::operator*=(const INT4& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		w *= rhs.w;
		return *this;
	}

	INT4 INT4::operator/(int rhs)
	{
		return { x / rhs, y / rhs, z / rhs, w / rhs };
	}

	INT4 INT4::operator/(const INT2& rhs)
	{
		return { x / rhs.x, y / rhs.y, z, w };
	}

	INT4 INT4::operator/(const INT3& rhs)
	{
		return { x / rhs.x, y / rhs.y, z / rhs.z, w };
	}

	INT4 INT4::operator/(const INT4& rhs)
	{
		return { x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w };
	}

	INT4& INT4::operator/=(int rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;
		w /= rhs;
		return *this;
	}

	INT4& INT4::operator/=(const INT2& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	INT4& INT4::operator/=(const INT3& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}

	INT4& INT4::operator/=(const INT4& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		w /= rhs.w;
		return *this;
	}

	bool INT4::operator==(int rhs)
	{
		if (x == rhs && y == rhs && z == rhs && w == rhs)
			return true;
		return false;
	}

	BOOL2 INT4::operator==(const INT2& rhs)
	{
		BOOL2 result = { false,false };
		if (x == rhs.x) result.x = true;
		if (y == rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT4::operator==(const INT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if (x == rhs.x) result.x = true;
		if (y == rhs.y) result.y = true;
		if (z == rhs.z) result.z = true;
		return result;
	}

	BOOL4 INT4::operator==(const INT4& rhs)
	{
		BOOL4 result = { false,false,false,false };
		if (x == rhs.x) result.x = true;
		if (y == rhs.y) result.y = true;
		if (z == rhs.z) result.z = true;
		if (w == rhs.w) result.w = true;
		return result;
	}

	bool INT4::operator!=(int rhs)
	{
		if (x != rhs && y != rhs && z != rhs && w != rhs)
			return true;
		return false;
	}

	BOOL2 INT4::operator!=(const INT2& rhs)
	{
		BOOL2 result = { false,false };
		if (x != rhs.x) result.x = true;
		if (y != rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT4::operator!=(const INT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if (x != rhs.x) result.x = true;
		if (y != rhs.y) result.y = true;
		if (z != rhs.z) result.z = true;
		return result;
	}

	BOOL4 INT4::operator!=(const INT4& rhs)
	{
		BOOL4 result = { false,false,false,false };
		if (x != rhs.x) result.x = true;
		if (y != rhs.y) result.y = true;
		if (z != rhs.z) result.z = true;
		if (w != rhs.w) result.w = true;
		return result;
	}

	bool INT4::operator>(int rhs)
	{
		if (x > rhs && y > rhs && z > rhs && w > rhs)
			return true;
		return false;
	}

	BOOL2 INT4::operator>(const INT2& rhs)
	{
		BOOL2 result = { false,false };
		if (x > rhs.x) result.x = true;
		if (y > rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT4::operator>(const INT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if (x > rhs.x) result.x = true;
		if (y > rhs.y) result.y = true;
		if (z > rhs.z) result.z = true;
		return result;
	}

	BOOL4 INT4::operator>(const INT4& rhs)
	{
		BOOL4 result = { false,false,false,false };
		if (x > rhs.x) result.x = true;
		if (y > rhs.y) result.y = true;
		if (z > rhs.z) result.z = true;
		if (w > rhs.w) result.w = true;
		return result;
	}

	bool INT4::operator<(int rhs)
	{
		if (x < rhs && y < rhs && z < rhs && w < rhs)
			return true;
		return false;
	}

	BOOL2 INT4::operator<(const INT2& rhs)
	{
		BOOL2 result = { false,false };
		if (x < rhs.x) result.x = true;
		if (y < rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT4::operator<(const INT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if (x < rhs.x) result.x = true;
		if (y < rhs.y) result.y = true;
		if (z < rhs.z) result.z = true;
		return result;
	}

	BOOL4 INT4::operator<(const INT4& rhs)
	{
		BOOL4 result = { false,false,false,false };
		if (x < rhs.x) result.x = true;
		if (y < rhs.y) result.y = true;
		if (z < rhs.z) result.z = true;
		if (w < rhs.w) result.w = true;
		return result;
	}

	bool INT4::operator>=(int rhs)
	{
		if (x >= rhs && y >= rhs && z >= rhs && w >= rhs)
			return true;
		return false;
	}

	BOOL2 INT4::operator>=(const INT2& rhs)
	{
		BOOL2 result = { false,false };
		if (x >= rhs.x) result.x = true;
		if (y >= rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT4::operator>=(const INT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if (x >= rhs.x) result.x = true;
		if (y >= rhs.y) result.y = true;
		if (z >= rhs.z) result.z = true;
		return result;
	}

	BOOL4 INT4::operator>=(const INT4& rhs)
	{
		BOOL4 result = { false,false,false,false };
		if (x >= rhs.x) result.x = true;
		if (y >= rhs.y) result.y = true;
		if (z >= rhs.z) result.z = true;
		if (w >= rhs.w) result.w = true;
		return result;
	}

	bool INT4::operator<=(int rhs)
	{
		if (x <= rhs && y <= rhs && z <= rhs && w <= rhs)
			return true;
		return false;
	}

	BOOL2 INT4::operator<=(const INT2& rhs)
	{
		BOOL2 result = { false,false };
		if (x <= rhs.x) result.x = true;
		if (y <= rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT4::operator<=(const INT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if (x <= rhs.x) result.x = true;
		if (y <= rhs.y) result.y = true;
		if (z <= rhs.z) result.z = true;
		return result;
	}

	BOOL4 INT4::operator<=(const INT4& rhs)
	{
		BOOL4 result = { false,false,false,false };
		if (x <= rhs.x) result.x = true;
		if (y <= rhs.y) result.y = true;
		if (z <= rhs.z) result.z = true;
		if (w <= rhs.w) result.w = true;
		return result;
	}

	INT4& INT4::operator=(float rhs)
	{
		x = y = z = w = (int)rhs;
		return *this;
	}

	INT4& INT4::operator=(const XMFLOAT2& rhs)
	{
		x = (int)rhs.x;
		y = (int)rhs.y;
		return *this;
	}

	INT4& INT4::operator=(const XMFLOAT3& rhs)
	{
		x = (int)rhs.x;
		y = (int)rhs.y;
		z = (int)rhs.z;
		return *this;
	}

	INT4& INT4::operator=(const XMFLOAT4& rhs)
	{
		x = (int)rhs.x;
		y = (int)rhs.y;
		z = (int)rhs.z;
		w = (int)rhs.w;
		return *this;
	}

	INT4 INT4::operator+(float rhs)
	{
		return { x + (int)rhs, y + (int)rhs, z + (int)rhs, w + (int)rhs };
	}

	INT4 INT4::operator+(const XMFLOAT2& rhs)
	{
		return { x + (int)rhs.x, y + (int)rhs.y, z, w};
	}

	INT4 INT4::operator+(const XMFLOAT3& rhs)
	{
		return { x + (int)rhs.x, y + (int)rhs.y, z + (int)rhs.z, w };
	}

	INT4 INT4::operator+(const XMFLOAT4& rhs)
	{
		return { x + (int)rhs.x, y + (int)rhs.y, z + (int)rhs.z, w + (int)rhs.w };
	}

	INT4& INT4::operator+=(float rhs)
	{
		x += (int)rhs;
		y += (int)rhs;
		z += (int)rhs;
		w += (int)rhs;
		return *this;
	}

	INT4& INT4::operator+=(const XMFLOAT2& rhs)
	{
		x += (int)rhs.x;
		y += (int)rhs.y;
		return *this;
	}

	INT4& INT4::operator+=(const XMFLOAT3& rhs)
	{
		x += (int)rhs.x;
		y += (int)rhs.y;
		z += (int)rhs.z;
		return *this;
	}

	INT4& INT4::operator+=(const XMFLOAT4& rhs)
	{
		x += (int)rhs.x;
		y += (int)rhs.y;
		z += (int)rhs.z;
		w += (int)rhs.w;
		return *this;
	}

	INT4 INT4::operator-(float rhs)
	{
		return { x - (int)rhs, y - (int)rhs, z - (int)rhs, w - (int)rhs };
	}

	INT4 INT4::operator-(const XMFLOAT2& rhs)
	{
		return { x - (int)rhs.x, y - (int)rhs.y, z, w };
	}

	INT4 INT4::operator-(const XMFLOAT3& rhs)
	{
		return { x - (int)rhs.x, y - (int)rhs.y, z - (int)rhs.z, w };
	}

	INT4 INT4::operator-(const XMFLOAT4& rhs)
	{
		return { x - (int)rhs.x, y - (int)rhs.y, z - (int)rhs.z, w - (int)rhs.w };
	}

	INT4& INT4::operator-=(float rhs)
	{
		x -= (int)rhs;
		y -= (int)rhs;
		z -= (int)rhs;
		w -= (int)rhs;
		return *this;
	}

	INT4& INT4::operator-=(const XMFLOAT2& rhs)
	{
		x -= (int)rhs.x;
		y -= (int)rhs.y;
		return *this;
	}

	INT4& INT4::operator-=(const XMFLOAT3& rhs)
	{
		x -= (int)rhs.x;
		y -= (int)rhs.y;
		z -= (int)rhs.z;
		return *this;
	}

	INT4& INT4::operator-=(const XMFLOAT4& rhs)
	{
		x -= (int)rhs.x;
		y -= (int)rhs.y;
		z -= (int)rhs.z;
		w -= (int)rhs.w;
		return *this;
	}

	INT4 INT4::operator*(float rhs)
	{
		return { x * (int)rhs, y * (int)rhs, z * (int)rhs, w * (int)rhs };
	}

	INT4 INT4::operator*(const XMFLOAT2& rhs)
	{
		return { x * (int)rhs.x, y * (int)rhs.y, z, w};
	}

	INT4 INT4::operator*(const XMFLOAT3& rhs)
	{
		return { x * (int)rhs.x, y * (int)rhs.y, z * (int)rhs.z, w };
	}

	INT4 INT4::operator*(const XMFLOAT4& rhs)
	{
		return { x * (int)rhs.x, y * (int)rhs.y, z * (int)rhs.z, w * (int)rhs.w };
	}

	INT4& INT4::operator*=(float rhs)
	{
		x *= (int)rhs;
		y *= (int)rhs;
		z *= (int)rhs;
		w *= (int)rhs;
		return *this;
	}

	INT4& INT4::operator*=(const XMFLOAT2& rhs)
	{
		x *= (int)rhs.x;
		y *= (int)rhs.y;
		return *this;
	}

	INT4& INT4::operator*=(const XMFLOAT3& rhs)
	{
		x *= (int)rhs.x;
		y *= (int)rhs.y;
		z *= (int)rhs.z;
		return *this;
	}

	INT4& INT4::operator*=(const XMFLOAT4& rhs)
	{
		x *= (int)rhs.x;
		y *= (int)rhs.y;
		z *= (int)rhs.z;
		w *= (int)rhs.w;
		return *this;
	}

	INT4 INT4::operator/(float rhs)
	{
		return { x / (int)rhs, y / (int)rhs, z / (int)rhs, w / (int)rhs };
	}

	INT4 INT4::operator/(const XMFLOAT2& rhs)
	{
		return { x / (int)rhs.x, y / (int)rhs.y, z, w };
	}

	INT4 INT4::operator/(const XMFLOAT3& rhs)
	{
		return { x / (int)rhs.x, y / (int)rhs.y, z / (int)rhs.z, w };
	}

	INT4 INT4::operator/(const XMFLOAT4& rhs)
	{
		return { x / (int)rhs.x, y / (int)rhs.y, z / (int)rhs.z, w / (int)rhs.w };
	}

	INT4& INT4::operator/=(float rhs)
	{
		x /= (int)rhs;
		y /= (int)rhs;
		z /= (int)rhs;
		w /= (int)rhs;
		return *this;
	}

	INT4& INT4::operator/=(const XMFLOAT2& rhs)
	{
		x /= (int)rhs.x;
		y /= (int)rhs.y;
		return *this;
	}

	INT4& INT4::operator/=(const XMFLOAT3& rhs)
	{
		x /= (int)rhs.x;
		y /= (int)rhs.y;
		z /= (int)rhs.z;
		return *this;
	}

	INT4& INT4::operator/=(const XMFLOAT4& rhs)
	{
		x /= (int)rhs.x;
		y /= (int)rhs.y;
		z /= (int)rhs.z;
		w /= (int)rhs.w;
		return *this;
	}

	bool INT4::operator==(float rhs)
	{
		if ((float)x == rhs && (float)y == rhs && (float)z == rhs && (float)w == rhs)
			return true;
		return false;
	}

	BOOL2 INT4::operator==(const XMFLOAT2& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x == rhs.x) result.x = true;
		if ((float)y == rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT4::operator==(const XMFLOAT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if ((float)x == rhs.x) result.x = true;
		if ((float)y == rhs.y) result.y = true;
		if ((float)z == rhs.z) result.z = true;
		return result;
	}

	BOOL4 INT4::operator==(const XMFLOAT4& rhs)
	{
		BOOL4 result = { false,false,false,false };
		if ((float)x == rhs.x) result.x = true;
		if ((float)y == rhs.y) result.y = true;
		if ((float)z == rhs.z) result.z = true;
		if ((float)w == rhs.w) result.w = true;
		return result;
	}

	bool INT4::operator!=(float rhs)
	{
		if ((float)x != rhs && (float)y != rhs && (float)z != rhs && (float)w != rhs)
			return true;
		return false;
	}

	BOOL2 INT4::operator!=(const XMFLOAT2& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x != rhs.x) result.x = true;
		if ((float)y != rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT4::operator!=(const XMFLOAT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if ((float)x != rhs.x) result.x = true;
		if ((float)y != rhs.y) result.y = true;
		if ((float)z != rhs.z) result.z = true;
		return result;
	}

	BOOL4 INT4::operator!=(const XMFLOAT4& rhs)
	{
		BOOL4 result = { false,false,false,false };
		if ((float)x != rhs.x) result.x = true;
		if ((float)y != rhs.y) result.y = true;
		if ((float)z != rhs.z) result.z = true;
		if ((float)w != rhs.w) result.w = true;
		return result;
	}

	bool INT4::operator>(float rhs)
	{
		if ((float)x > rhs && (float)y > rhs && (float)z > rhs && (float)w > rhs)
			return true;
		return false;
	}

	BOOL2 INT4::operator>(const XMFLOAT2& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x > rhs.x) result.x = true;
		if ((float)y > rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT4::operator>(const XMFLOAT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if ((float)x > rhs.x) result.x = true;
		if ((float)y > rhs.y) result.y = true;
		if ((float)z > rhs.z) result.z = true;
		return result;
	}

	BOOL4 INT4::operator>(const XMFLOAT4& rhs)
	{
		BOOL4 result = { false,false,false,false };
		if ((float)x > rhs.x) result.x = true;
		if ((float)y > rhs.y) result.y = true;
		if ((float)z > rhs.z) result.z = true;
		if ((float)w > rhs.w) result.w = true;
		return result;
	}

	bool INT4::operator<(float rhs)
	{
		if ((float)x < rhs && (float)y < rhs && (float)z < rhs && (float)w < rhs)
			return true;
		return false;
	}

	BOOL2 INT4::operator<(const XMFLOAT2& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x < rhs.x) result.x = true;
		if ((float)y < rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT4::operator<(const XMFLOAT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if ((float)x < rhs.x) result.x = true;
		if ((float)y < rhs.y) result.y = true;
		if ((float)z < rhs.z) result.z = true;
		return result;
	}

	BOOL4 INT4::operator<(const XMFLOAT4& rhs)
	{
		BOOL4 result = { false,false,false,false };
		if ((float)x < rhs.x) result.x = true;
		if ((float)y < rhs.y) result.y = true;
		if ((float)z < rhs.z) result.z = true;
		if ((float)w < rhs.w) result.w = true;
		return result;
	}

	bool INT4::operator>=(float rhs)
	{
		if ((float)x >= rhs && (float)y >= rhs && (float)z >= rhs && (float)w >= rhs)
			return true;
		return false;
	}

	BOOL2 INT4::operator>=(const XMFLOAT2& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x >= rhs.x) result.x = true;
		if ((float)y >= rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT4::operator>=(const XMFLOAT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if ((float)x >= rhs.x) result.x = true;
		if ((float)y >= rhs.y) result.y = true;
		if ((float)z >= rhs.z) result.z = true;
		return result;
	}

	BOOL4 INT4::operator>=(const XMFLOAT4& rhs)
	{
		BOOL4 result = { false,false,false,false };
		if ((float)x >= rhs.x) result.x = true;
		if ((float)y >= rhs.y) result.y = true;
		if ((float)z >= rhs.z) result.z = true;
		if ((float)w >= rhs.w) result.w = true;
		return result;
	}

	bool INT4::operator<=(float rhs)
	{
		if ((float)x <= rhs && (float)y <= rhs && (float)z <= rhs && (float)w <= rhs)
			return true;
		return false;
	}

	BOOL2 INT4::operator<=(const XMFLOAT2& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x <= rhs.x) result.x = true;
		if ((float)y <= rhs.y) result.y = true;
		return result;
	}

	BOOL3 INT4::operator<=(const XMFLOAT3& rhs)
	{
		BOOL3 result = { false,false,false };
		if ((float)x <= rhs.x) result.x = true;
		if ((float)y <= rhs.y) result.y = true;
		if ((float)z <= rhs.z) result.z = true;
		return result;
	}

	BOOL4 INT4::operator<=(const XMFLOAT4& rhs)
	{
		BOOL4 result = { false,false,false,false };
		if ((float)x <= rhs.x) result.x = true;
		if ((float)y <= rhs.y) result.y = true;
		if ((float)z <= rhs.z) result.z = true;
		if ((float)w <= rhs.w) result.w = true;
		return result;
	}

}