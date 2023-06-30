#pragma once
#include <utility>

namespace DirectX {

	struct INT3;
	struct INT4;
	struct XMFLOAT2;
	struct XMFLOAT3;
	struct XMFLOAT4;
	struct BOOL2;
	struct BOOL3;
	struct BOOL4;

	struct INT2 {
		int x, y;
		INT2() = default;
		INT2(int value) : x(value), y(value) {}
		INT2(int x, int y) : x(x), y(y) {}
		INT2(const INT2& rhs) {
			x = rhs.x;
			y = rhs.y;
		}
		INT2(INT2&& rhs) noexcept {
			x = std::move(rhs.x);
			y = std::move(rhs.y);
		}
		INT2& operator=(INT2&& rhs) noexcept {
			x = std::move(rhs.x);
			y = std::move(rhs.y);
			return *this;
		}

		// operators for INT

		INT2& operator=(int rhs);
		INT2& operator=(const INT2& rhs);
		INT2& operator=(const INT3& rhs);
		INT2& operator=(const INT4& rhs);

		INT2 operator+(int rhs);
		INT2 operator+(const INT2& rhs);
		INT2 operator+(const INT3& rhs);
		INT2 operator+(const INT4& rhs);
		INT2& operator+=(int rhs);
		INT2& operator+=(const INT2& rhs);
		INT2& operator+=(const INT3& rhs);
		INT2& operator+=(const INT4& rhs);

		INT2 operator-(int rhs);
		INT2 operator-(const INT2& rhs);
		INT2 operator-(const INT3& rhs);
		INT2 operator-(const INT4& rhs);
		INT2& operator-=(int rhs);
		INT2& operator-=(const INT2& rhs);
		INT2& operator-=(const INT3& rhs);
		INT2& operator-=(const INT4& rhs);

		INT2 operator*(int rhs);
		INT2 operator*(const INT2& rhs);
		INT2 operator*(const INT3& rhs);
		INT2 operator*(const INT4& rhs);
		INT2& operator*=(int rhs);
		INT2& operator*=(const INT2& rhs);
		INT2& operator*=(const INT3& rhs);
		INT2& operator*=(const INT4& rhs);

		INT2 operator/(int rhs);
		INT2 operator/(const INT2& rhs);
		INT2 operator/(const INT3& rhs);
		INT2 operator/(const INT4& rhs);
		INT2& operator/=(int rhs);
		INT2& operator/=(const INT2& rhs);
		INT2& operator/=(const INT3& rhs);
		INT2& operator/=(const INT4& rhs);

		// bool (INT)

		bool  operator==(int rhs);
		BOOL2 operator==(const INT2& rhs);
		BOOL2 operator==(const INT3& rhs);
		BOOL2 operator==(const INT4& rhs);
		bool  operator!=(int rhs);
		BOOL2 operator!=(const INT2& rhs);
		BOOL2 operator!=(const INT3& rhs);
		BOOL2 operator!=(const INT4& rhs);

		bool  operator>(int rhs);
		BOOL2 operator>(const INT2& rhs);
		BOOL2 operator>(const INT3& rhs);
		BOOL2 operator>(const INT4& rhs);
		bool  operator<(int rhs);
		BOOL2 operator<(const INT2& rhs);
		BOOL2 operator<(const INT3& rhs);
		BOOL2 operator<(const INT4& rhs);

		bool  operator>=(int rhs);
		BOOL2 operator>=(const INT2& rhs);
		BOOL2 operator>=(const INT3& rhs);
		BOOL2 operator>=(const INT4& rhs);
		bool  operator<=(int rhs);
		BOOL2 operator<=(const INT2& rhs);
		BOOL2 operator<=(const INT3& rhs);
		BOOL2 operator<=(const INT4& rhs);



		// operators for FLOAT

		INT2& operator=(float rhs);
		INT2& operator=(const XMFLOAT2& rhs);
		INT2& operator=(const XMFLOAT3& rhs);
		INT2& operator=(const XMFLOAT4& rhs);

		INT2 operator+(float rhs);
		INT2 operator+(const XMFLOAT2& rhs);
		INT2 operator+(const XMFLOAT3& rhs);
		INT2 operator+(const XMFLOAT4& rhs);
		INT2& operator+=(float rhs);
		INT2& operator+=(const XMFLOAT2& rhs);
		INT2& operator+=(const XMFLOAT3& rhs);
		INT2& operator+=(const XMFLOAT4& rhs);

		INT2 operator-(float rhs);
		INT2 operator-(const XMFLOAT2& rhs);
		INT2 operator-(const XMFLOAT3& rhs);
		INT2 operator-(const XMFLOAT4& rhs);
		INT2& operator-=(float rhs);
		INT2& operator-=(const XMFLOAT2& rhs);
		INT2& operator-=(const XMFLOAT3& rhs);
		INT2& operator-=(const XMFLOAT4& rhs);

		INT2 operator*(float rhs);
		INT2 operator*(const XMFLOAT2& rhs);
		INT2 operator*(const XMFLOAT3& rhs);
		INT2 operator*(const XMFLOAT4& rhs);
		INT2& operator*=(float rhs);
		INT2& operator*=(const XMFLOAT2& rhs);
		INT2& operator*=(const XMFLOAT3& rhs);
		INT2& operator*=(const XMFLOAT4& rhs);

		INT2 operator/(float rhs);
		INT2 operator/(const XMFLOAT2& rhs);
		INT2 operator/(const XMFLOAT3& rhs);
		INT2 operator/(const XMFLOAT4& rhs);
		INT2& operator/=(float rhs);
		INT2& operator/=(const XMFLOAT2& rhs);
		INT2& operator/=(const XMFLOAT3& rhs);
		INT2& operator/=(const XMFLOAT4& rhs);

		// bool (FLOAT)

		bool  operator==(float rhs);
		BOOL2 operator==(const XMFLOAT2& rhs);
		BOOL2 operator==(const XMFLOAT3& rhs);
		BOOL2 operator==(const XMFLOAT4& rhs);
		bool  operator!=(float rhs);
		BOOL2 operator!=(const XMFLOAT2& rhs);
		BOOL2 operator!=(const XMFLOAT3& rhs);
		BOOL2 operator!=(const XMFLOAT4& rhs);

		bool  operator>(float rhs);
		BOOL2 operator>(const XMFLOAT2& rhs);
		BOOL2 operator>(const XMFLOAT3& rhs);
		BOOL2 operator>(const XMFLOAT4& rhs);
		bool  operator<(float rhs);
		BOOL2 operator<(const XMFLOAT2& rhs);
		BOOL2 operator<(const XMFLOAT3& rhs);
		BOOL2 operator<(const XMFLOAT4& rhs);

		bool  operator>=(float rhs);
		BOOL2 operator>=(const XMFLOAT2& rhs);
		BOOL2 operator>=(const XMFLOAT3& rhs);
		BOOL2 operator>=(const XMFLOAT4& rhs);
		bool  operator<=(float rhs);
		BOOL2 operator<=(const XMFLOAT2& rhs);
		BOOL2 operator<=(const XMFLOAT3& rhs);
		BOOL2 operator<=(const XMFLOAT4& rhs);

	};

}