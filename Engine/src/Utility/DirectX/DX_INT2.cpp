#include <DirectXMath.h>
#include "DX_INT2.h"
#include "DX_INT3.h"
#include "DX_INT4.h"
#include "DX_BOOL2.h"
#include "DX_BOOL3.h"
#include "DX_BOOL4.h"



namespace DirectX {

	INT2& INT2::operator=(int rhs)
	{
		x = y = rhs;
		return *this;
	}

	INT2& INT2::operator=(const INT2& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	INT2& INT2::operator=(const INT3& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	INT2& INT2::operator=(const INT4& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}

	INT2 INT2::operator+(int rhs)
	{
		return { x + rhs, y + rhs };
	}

	INT2 INT2::operator+(const INT2& rhs)
	{
		return { x + rhs.x, y + rhs.y };
	}

	INT2 INT2::operator+(const INT3& rhs)
	{
		return { x + rhs.x, y + rhs.y };
	}

	INT2 INT2::operator+(const INT4& rhs)
	{
		return { x + rhs.x, y + rhs.y };
	}

	INT2& INT2::operator+=(int rhs)
	{
		x += rhs;
		y += rhs;
		return *this;
	}

	INT2& INT2::operator+=(const INT2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	INT2& INT2::operator+=(const INT3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	INT2& INT2::operator+=(const INT4& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	INT2 INT2::operator-(int rhs)
	{
		return { x - rhs, y - rhs };
	}

	INT2 INT2::operator-(const INT2& rhs)
	{
		return { x - rhs.x, y - rhs.y };
	}

	INT2 INT2::operator-(const INT3& rhs)
	{
		return { x - rhs.x, y - rhs.y };
	}

	INT2 INT2::operator-(const INT4& rhs)
	{
		return { x - rhs.x, y - rhs.y };
	}

	INT2& INT2::operator-=(int rhs)
	{
		x -= rhs;
		y -= rhs;
		return *this;
	}

	INT2& INT2::operator-=(const INT2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	INT2& INT2::operator-=(const INT3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	INT2& INT2::operator-=(const INT4& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	INT2 INT2::operator*(int rhs)
	{
		return { x * rhs, y * rhs };
	}

	INT2 INT2::operator*(const INT2& rhs)
	{
		return { x * rhs.x, y * rhs.y };
	}

	INT2 INT2::operator*(const INT3& rhs)
	{
		return { x * rhs.x, y * rhs.y };
	}

	INT2 INT2::operator*(const INT4& rhs)
	{
		return { x * rhs.x, y * rhs.y };
	}

	INT2& INT2::operator*=(int rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}

	INT2& INT2::operator*=(const INT2& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	INT2& INT2::operator*=(const INT3& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	INT2& INT2::operator*=(const INT4& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}

	INT2 INT2::operator/(int rhs)
	{
		return { x / rhs, y / rhs };
	}

	INT2 INT2::operator/(const INT2& rhs)
	{
		return { x / rhs.x, y / rhs.y };
	}

	INT2 INT2::operator/(const INT3& rhs)
	{
		return { x / rhs.x, y / rhs.y };
	}

	INT2 INT2::operator/(const INT4& rhs)
	{
		return { x / rhs.x, y / rhs.y };
	}

	INT2& INT2::operator/=(int rhs)
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}

	INT2& INT2::operator/=(const INT2& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	INT2& INT2::operator/=(const INT3& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	INT2& INT2::operator/=(const INT4& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	bool INT2::operator==(int rhs)
	{
		if (x == rhs && y == rhs)
			return true;
		return false;
	}

	BOOL2 INT2::operator==(const INT2& rhs)
	{
		BOOL2 result = { false,false };
		if (x == rhs.x) result.x = true;
		if (y == rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator==(const INT3& rhs)
	{
		BOOL2 result = { false,false };
		if (x == rhs.x) result.x = true;
		if (y == rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator==(const INT4& rhs)
	{
		BOOL2 result = { false,false };
		if (x == rhs.x) result.x = true;
		if (y == rhs.y) result.y = true;
		return result;
	}

	bool INT2::operator!=(int rhs)
	{
		if (x != rhs && y != rhs)
			return true;
		return false;
	}

	BOOL2 INT2::operator!=(const INT2& rhs)
	{
		BOOL2 result = { false,false };
		if (x != rhs.x) result.x = true;
		if (y != rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator!=(const INT3& rhs)
	{
		BOOL2 result = { false,false };
		if (x != rhs.x) result.x = true;
		if (y != rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator!=(const INT4& rhs)
	{
		BOOL2 result = { false,false };
		if (x != rhs.x) result.x = true;
		if (y != rhs.y) result.y = true;
		return result;
	}

	bool INT2::operator>(int rhs)
	{
		if (x > rhs && y > rhs)
			return true;
		return false;
	}

	BOOL2 INT2::operator>(const INT2& rhs)
	{
		BOOL2 result = { false,false };
		if (x > rhs.x) result.x = true;
		if (y > rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator>(const INT3& rhs)
	{
		BOOL2 result = { false,false };
		if (x > rhs.x) result.x = true;
		if (y > rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator>(const INT4& rhs)
	{
		BOOL2 result = { false,false };
		if (x > rhs.x) result.x = true;
		if (y > rhs.y) result.y = true;
		return result;
	}

	bool INT2::operator<(int rhs)
	{
		if (x < rhs && y < rhs)
			return true;
		return false;
	}

	BOOL2 INT2::operator<(const INT2& rhs)
	{
		BOOL2 result = { false,false };
		if (x < rhs.x) result.x = true;
		if (y < rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator<(const INT3& rhs)
	{
		BOOL2 result = { false,false };
		if (x < rhs.x) result.x = true;
		if (y < rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator<(const INT4& rhs)
	{
		BOOL2 result = { false,false };
		if (x < rhs.x) result.x = true;
		if (y < rhs.y) result.y = true;
		return result;
	}

	bool INT2::operator>=(int rhs)
	{
		if (x >= rhs && y >= rhs)
			return true;
		return false;
	}

	BOOL2 INT2::operator>=(const INT2& rhs)
	{
		BOOL2 result = { false,false };
		if (x >= rhs.x) result.x = true;
		if (y >= rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator>=(const INT3& rhs)
	{
		BOOL2 result = { false,false };
		if (x >= rhs.x) result.x = true;
		if (y >= rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator>=(const INT4& rhs)
	{
		BOOL2 result = { false,false };
		if (x >= rhs.x) result.x = true;
		if (y >= rhs.y) result.y = true;
		return result;
	}

	bool INT2::operator<=(int rhs)
	{
		if (x <= rhs && y <= rhs)
			return true;
		return false;
	}

	BOOL2 INT2::operator<=(const INT2& rhs)
	{
		BOOL2 result = { false,false };
		if (x <= rhs.x) result.x = true;
		if (y <= rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator<=(const INT3& rhs)
	{
		BOOL2 result = { false,false };
		if (x <= rhs.x) result.x = true;
		if (y <= rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator<=(const INT4& rhs)
	{
		BOOL2 result = { false,false };
		if (x <= rhs.x) result.x = true;
		if (y <= rhs.y) result.y = true;
		return result;
	}

	INT2& INT2::operator=(float rhs)
	{
		x = y = (int)rhs;
		return *this;
	}

	INT2& INT2::operator=(const XMFLOAT2& rhs)
	{
		x = (int)rhs.x;
		y = (int)rhs.y;
		return *this;
	}

	INT2& INT2::operator=(const XMFLOAT3& rhs)
	{
		x = (int)rhs.x;
		y = (int)rhs.y;
		return *this;
	}

	INT2& INT2::operator=(const XMFLOAT4& rhs)
	{
		x = (int)rhs.x;
		y = (int)rhs.y;
		return *this;
	}

	INT2 INT2::operator+(float rhs)
	{
		return { x + (int)rhs, y + (int)rhs };
	}

	INT2 INT2::operator+(const XMFLOAT2& rhs)
	{
		return { x + (int)rhs.x, y + (int)rhs.y };
	}

	INT2 INT2::operator+(const XMFLOAT3& rhs)
	{
		return { x + (int)rhs.x, y + (int)rhs.y };
	}

	INT2 INT2::operator+(const XMFLOAT4& rhs)
	{
		return { x + (int)rhs.x, y + (int)rhs.y };
	}

	INT2& INT2::operator+=(float rhs)
	{
		x += (int)rhs;
		y += (int)rhs;
		return *this;
	}

	INT2& INT2::operator+=(const XMFLOAT2& rhs)
	{
		x += (int)rhs.x;
		y += (int)rhs.y;
		return *this;
	}

	INT2& INT2::operator+=(const XMFLOAT3& rhs)
	{
		x += (int)rhs.x;
		y += (int)rhs.y;
		return *this;
	}

	INT2& INT2::operator+=(const XMFLOAT4& rhs)
	{
		x += (int)rhs.x;
		y += (int)rhs.y;
		return *this;
	}

	INT2 INT2::operator-(float rhs)
	{
		return { x - (int)rhs, y - (int)rhs };
	}

	INT2 INT2::operator-(const XMFLOAT2& rhs)
	{
		return { x - (int)rhs.x, y - (int)rhs.y };
	}

	INT2 INT2::operator-(const XMFLOAT3& rhs)
	{
		return { x - (int)rhs.x, y - (int)rhs.y };
	}

	INT2 INT2::operator-(const XMFLOAT4& rhs)
	{
		return { x - (int)rhs.x, y - (int)rhs.y };
	}

	INT2& INT2::operator-=(float rhs)
	{
		x -= (int)rhs;
		y -= (int)rhs;
		return *this;
	}

	INT2& INT2::operator-=(const XMFLOAT2& rhs)
	{
		x -= (int)rhs.x;
		y -= (int)rhs.y;
		return *this;
	}

	INT2& INT2::operator-=(const XMFLOAT3& rhs)
	{
		x -= (int)rhs.x;
		y -= (int)rhs.y;
		return *this;
	}

	INT2& INT2::operator-=(const XMFLOAT4& rhs)
	{
		x -= (int)rhs.x;
		y -= (int)rhs.y;
		return *this;
	}

	INT2 INT2::operator*(float rhs)
	{
		return { x * (int)rhs, y * (int)rhs };
	}

	INT2 INT2::operator*(const XMFLOAT2& rhs)
	{
		return { x * (int)rhs.x, y * (int)rhs.y };
	}

	INT2 INT2::operator*(const XMFLOAT3& rhs)
	{
		return { x * (int)rhs.x, y * (int)rhs.y };
	}

	INT2 INT2::operator*(const XMFLOAT4& rhs)
	{
		return { x * (int)rhs.x, y * (int)rhs.y };
	}

	INT2& INT2::operator*=(float rhs)
	{
		x *= (int)rhs;
		y *= (int)rhs;
		return *this;
	}

	INT2& INT2::operator*=(const XMFLOAT2& rhs)
	{
		x *= (int)rhs.x;
		y *= (int)rhs.y;
		return *this;
	}

	INT2& INT2::operator*=(const XMFLOAT3& rhs)
	{
		x *= (int)rhs.x;
		y *= (int)rhs.y;
		return *this;
	}

	INT2& INT2::operator*=(const XMFLOAT4& rhs)
	{
		x *= (int)rhs.x;
		y *= (int)rhs.y;
		return *this;
	}

	INT2 INT2::operator/(float rhs)
	{
		return { x / (int)rhs, y / (int)rhs };
	}

	INT2 INT2::operator/(const XMFLOAT2& rhs)
	{
		return { x / (int)rhs.x, y / (int)rhs.y };
	}

	INT2 INT2::operator/(const XMFLOAT3& rhs)
	{
		return { x / (int)rhs.x, y / (int)rhs.y };
	}

	INT2 INT2::operator/(const XMFLOAT4& rhs)
	{
		return { x / (int)rhs.x, y / (int)rhs.y };
	}

	INT2& INT2::operator/=(float rhs)
	{
		x /= (int)rhs;
		y /= (int)rhs;
		return *this;
	}

	INT2& INT2::operator/=(const XMFLOAT2& rhs)
	{
		x /= (int)rhs.x;
		y /= (int)rhs.y;
		return *this;
	}

	INT2& INT2::operator/=(const XMFLOAT3& rhs)
	{
		x /= (int)rhs.x;
		y /= (int)rhs.y;
		return *this;
	}

	INT2& INT2::operator/=(const XMFLOAT4& rhs)
	{
		x /= (int)rhs.x;
		y /= (int)rhs.y;
		return *this;
	}

	bool INT2::operator==(float rhs)
	{
		if ((float)x == rhs && (float)y == rhs)
			return true;
		return false;
	}

	BOOL2 INT2::operator==(const XMFLOAT2& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x == rhs.x) result.x = true;
		if ((float)y == rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator==(const XMFLOAT3& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x == rhs.x) result.x = true;
		if ((float)y == rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator==(const XMFLOAT4& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x == rhs.x) result.x = true;
		if ((float)y == rhs.y) result.y = true;
		return result;
	}

	bool INT2::operator!=(float rhs)
	{
		if ((float)x != rhs && (float)y != rhs)
			return true;
		return false;
	}

	BOOL2 INT2::operator!=(const XMFLOAT2& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x != rhs.x) result.x = true;
		if ((float)y != rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator!=(const XMFLOAT3& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x != rhs.x) result.x = true;
		if ((float)y != rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator!=(const XMFLOAT4& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x != rhs.x) result.x = true;
		if ((float)y != rhs.y) result.y = true;
		return result;
	}

	bool INT2::operator>(float rhs)
	{
		if ((float)x > rhs && (float)y > rhs)
			return true;
		return false;
	}

	BOOL2 INT2::operator>(const XMFLOAT2& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x > rhs.x) result.x = true;
		if ((float)y > rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator>(const XMFLOAT3& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x > rhs.x) result.x = true;
		if ((float)y > rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator>(const XMFLOAT4& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x > rhs.x) result.x = true;
		if ((float)y > rhs.y) result.y = true;
		return result;
	}

	bool INT2::operator<(float rhs)
	{
		if ((float)x < rhs && (float)y < rhs)
			return true;
		return false;
	}

	BOOL2 INT2::operator<(const XMFLOAT2& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x < rhs.x) result.x = true;
		if ((float)y < rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator<(const XMFLOAT3& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x < rhs.x) result.x = true;
		if ((float)y < rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator<(const XMFLOAT4& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x < rhs.x) result.x = true;
		if ((float)y < rhs.y) result.y = true;
		return result;
	}

	bool INT2::operator>=(float rhs)
	{
		if ((float)x >= rhs && (float)y >= rhs)
			return true;
		return false;
	}

	BOOL2 INT2::operator>=(const XMFLOAT2& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x >= rhs.x) result.x = true;
		if ((float)y >= rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator>=(const XMFLOAT3& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x >= rhs.x) result.x = true;
		if ((float)y >= rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator>=(const XMFLOAT4& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x >= rhs.x) result.x = true;
		if ((float)y >= rhs.y) result.y = true;
		return result;
	}

	bool INT2::operator<=(float rhs)
	{
		if ((float)x <= rhs && (float)y <= rhs)
			return true;
		return false;
	}

	BOOL2 INT2::operator<=(const XMFLOAT2& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x <= rhs.x) result.x = true;
		if ((float)y <= rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator<=(const XMFLOAT3& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x <= rhs.x) result.x = true;
		if ((float)y <= rhs.y) result.y = true;
		return result;
	}

	BOOL2 INT2::operator<=(const XMFLOAT4& rhs)
	{
		BOOL2 result = { false,false };
		if ((float)x <= rhs.x) result.x = true;
		if ((float)y <= rhs.y) result.y = true;
		return result;
	}

}