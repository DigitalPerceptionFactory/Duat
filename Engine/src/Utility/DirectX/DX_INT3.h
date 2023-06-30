#pragma once
#include <utility>

namespace DirectX {

	struct INT2;
	struct INT4;
	struct XMFLOAT2;
	struct XMFLOAT3;
	struct XMFLOAT4;
	struct BOOL2;
	struct BOOL3;
	struct BOOL4;

	struct INT3 {
		int x, y, z;
		INT3() = default;
		INT3(int value) : x(value), y(value), z(value) {}
		INT3(int x, int y, int z) : x(x), y(y), z(z) {}
		INT3(const INT3& rhs) {
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
		}
		INT3(INT3&& rhs) noexcept {
			x = std::move(rhs.x);
			y = std::move(rhs.y);
			z = std::move(rhs.z);
		}
		INT3& operator=(INT3&& rhs) noexcept {
			x = std::move(rhs.x);
			y = std::move(rhs.y);
			z = std::move(rhs.z);
			return *this;
		}

		// operators for INT

		INT3& operator=(int rhs);
		INT3& operator=(const INT2& rhs);
		INT3& operator=(const INT3& rhs);
		INT3& operator=(const INT4& rhs);

		INT3 operator+(int rhs);
		INT3 operator+(const INT2& rhs);
		INT3 operator+(const INT3& rhs);
		INT3 operator+(const INT4& rhs);
		INT3& operator+=(int rhs);
		INT3& operator+=(const INT2& rhs);
		INT3& operator+=(const INT3& rhs);
		INT3& operator+=(const INT4& rhs);

		INT3 operator-(int rhs);
		INT3 operator-(const INT2& rhs);
		INT3 operator-(const INT3& rhs);
		INT3 operator-(const INT4& rhs);
		INT3& operator-=(int rhs);
		INT3& operator-=(const INT2& rhs);
		INT3& operator-=(const INT3& rhs);
		INT3& operator-=(const INT4& rhs);

		INT3 operator*(int rhs);
		INT3 operator*(const INT2& rhs);
		INT3 operator*(const INT3& rhs);
		INT3 operator*(const INT4& rhs);
		INT3& operator*=(int rhs);
		INT3& operator*=(const INT2& rhs);
		INT3& operator*=(const INT3& rhs);
		INT3& operator*=(const INT4& rhs);

		INT3 operator/(int rhs);
		INT3 operator/(const INT2& rhs);
		INT3 operator/(const INT3& rhs);
		INT3 operator/(const INT4& rhs);
		INT3& operator/=(int rhs);
		INT3& operator/=(const INT2& rhs);
		INT3& operator/=(const INT3& rhs);
		INT3& operator/=(const INT4& rhs);

		// bool (INT)

		bool  operator==(int rhs);
		BOOL2 operator==(const INT2& rhs);
		BOOL3 operator==(const INT3& rhs);
		BOOL3 operator==(const INT4& rhs);
		bool  operator!=(int rhs);
		BOOL2 operator!=(const INT2& rhs);
		BOOL3 operator!=(const INT3& rhs);
		BOOL3 operator!=(const INT4& rhs);

		bool  operator>(int rhs);
		BOOL2 operator>(const INT2& rhs);
		BOOL3 operator>(const INT3& rhs);
		BOOL3 operator>(const INT4& rhs);
		bool  operator<(int rhs);
		BOOL2 operator<(const INT2& rhs);
		BOOL3 operator<(const INT3& rhs);
		BOOL3 operator<(const INT4& rhs);

		bool  operator>=(int rhs);
		BOOL2 operator>=(const INT2& rhs);
		BOOL3 operator>=(const INT3& rhs);
		BOOL3 operator>=(const INT4& rhs);
		bool  operator<=(int rhs);
		BOOL2 operator<=(const INT2& rhs);
		BOOL3 operator<=(const INT3& rhs);
		BOOL3 operator<=(const INT4& rhs);



		// operators for FLOAT

		INT3& operator=(float rhs);
		INT3& operator=(const XMFLOAT2& rhs);
		INT3& operator=(const XMFLOAT3& rhs);
		INT3& operator=(const XMFLOAT4& rhs);

		INT3 operator+(float rhs);
		INT3 operator+(const XMFLOAT2& rhs);
		INT3 operator+(const XMFLOAT3& rhs);
		INT3 operator+(const XMFLOAT4& rhs);
		INT3& operator+=(float rhs);
		INT3& operator+=(const XMFLOAT2& rhs);
		INT3& operator+=(const XMFLOAT3& rhs);
		INT3& operator+=(const XMFLOAT4& rhs);

		INT3 operator-(float rhs);
		INT3 operator-(const XMFLOAT2& rhs);
		INT3 operator-(const XMFLOAT3& rhs);
		INT3 operator-(const XMFLOAT4& rhs);
		INT3& operator-=(float rhs);
		INT3& operator-=(const XMFLOAT2& rhs);
		INT3& operator-=(const XMFLOAT3& rhs);
		INT3& operator-=(const XMFLOAT4& rhs);

		INT3 operator*(float rhs);
		INT3 operator*(const XMFLOAT2& rhs);
		INT3 operator*(const XMFLOAT3& rhs);
		INT3 operator*(const XMFLOAT4& rhs);
		INT3& operator*=(float rhs);
		INT3& operator*=(const XMFLOAT2& rhs);
		INT3& operator*=(const XMFLOAT3& rhs);
		INT3& operator*=(const XMFLOAT4& rhs);

		INT3 operator/(float rhs);
		INT3 operator/(const XMFLOAT2& rhs);
		INT3 operator/(const XMFLOAT3& rhs);
		INT3 operator/(const XMFLOAT4& rhs);
		INT3& operator/=(float rhs);
		INT3& operator/=(const XMFLOAT2& rhs);
		INT3& operator/=(const XMFLOAT3& rhs);
		INT3& operator/=(const XMFLOAT4& rhs);

		// bool (FLOAT)

		bool  operator==(float rhs);
		BOOL2 operator==(const XMFLOAT2& rhs);
		BOOL3 operator==(const XMFLOAT3& rhs);
		BOOL3 operator==(const XMFLOAT4& rhs);
		bool  operator!=(float rhs);
		BOOL2 operator!=(const XMFLOAT2& rhs);
		BOOL3 operator!=(const XMFLOAT3& rhs);
		BOOL3 operator!=(const XMFLOAT4& rhs);

		bool  operator>(float rhs);
		BOOL2 operator>(const XMFLOAT2& rhs);
		BOOL3 operator>(const XMFLOAT3& rhs);
		BOOL3 operator>(const XMFLOAT4& rhs);
		bool  operator<(float rhs);
		BOOL2 operator<(const XMFLOAT2& rhs);
		BOOL3 operator<(const XMFLOAT3& rhs);
		BOOL3 operator<(const XMFLOAT4& rhs);

		bool  operator>=(float rhs);
		BOOL2 operator>=(const XMFLOAT2& rhs);
		BOOL3 operator>=(const XMFLOAT3& rhs);
		BOOL3 operator>=(const XMFLOAT4& rhs);
		bool  operator<=(float rhs);
		BOOL2 operator<=(const XMFLOAT2& rhs);
		BOOL3 operator<=(const XMFLOAT3& rhs);
		BOOL3 operator<=(const XMFLOAT4& rhs);

	};

}