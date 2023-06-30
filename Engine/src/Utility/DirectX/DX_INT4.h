#pragma once
#include <utility>

namespace DirectX {

	struct INT2;
	struct INT3;
	struct XMFLOAT2;
	struct XMFLOAT3;
	struct XMFLOAT4;
	struct BOOL2;
	struct BOOL3;
	struct BOOL4;

	struct INT4 {
		int x,y,z,w;
		INT4() = default;
		INT4(int value) : x(value), y(value), z(value), w(value) {}
		INT4(int x, int y, int z, int w) : x(x), y(y), z(z), w(w) {}
		INT4(const INT4& rhs) {
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			w = rhs.w;
		}
		INT4(INT4&& rhs) noexcept {
			x = std::move(rhs.x);
			y = std::move(rhs.y);
			z = std::move(rhs.z);
			w = std::move(rhs.w);
		}
		INT4& operator=(INT4&& rhs) noexcept {
			x = std::move(rhs.x);
			y = std::move(rhs.y);
			z = std::move(rhs.z);
			w = std::move(rhs.w);
			return *this;
		}


		// operators for INT

		INT4& operator=(int rhs);
		INT4& operator=(const INT2& rhs);
		INT4& operator=(const INT3& rhs);
		INT4& operator=(const INT4& rhs);

		INT4 operator+(int rhs);
		INT4 operator+(const INT2& rhs);
		INT4 operator+(const INT3& rhs);
		INT4 operator+(const INT4& rhs);
		INT4& operator+=(int rhs);
		INT4& operator+=(const INT2& rhs);
		INT4& operator+=(const INT3& rhs);
		INT4& operator+=(const INT4& rhs);
		   
		INT4 operator-(int rhs);
		INT4 operator-(const INT2& rhs);
		INT4 operator-(const INT3& rhs);
		INT4 operator-(const INT4& rhs);
		INT4& operator-=(int rhs);
		INT4& operator-=(const INT2& rhs);
		INT4& operator-=(const INT3& rhs);
		INT4& operator-=(const INT4& rhs);

		INT4 operator*(int rhs);
		INT4 operator*(const INT2& rhs);
		INT4 operator*(const INT3& rhs);
		INT4 operator*(const INT4& rhs);
		INT4& operator*=(int rhs);
		INT4& operator*=(const INT2& rhs);
		INT4& operator*=(const INT3& rhs);
		INT4& operator*=(const INT4& rhs);

		INT4 operator/(int rhs);
		INT4 operator/(const INT2& rhs);
		INT4 operator/(const INT3& rhs);
		INT4 operator/(const INT4& rhs);
		INT4& operator/=(int rhs);
		INT4& operator/=(const INT2& rhs);
		INT4& operator/=(const INT3& rhs);
		INT4& operator/=(const INT4& rhs);

		// bool (INT)

		bool  operator==(int rhs);
		BOOL2 operator==(const INT2& rhs);
		BOOL3 operator==(const INT3& rhs);
		BOOL4 operator==(const INT4& rhs);
		bool  operator!=(int rhs);
		BOOL2 operator!=(const INT2& rhs);
		BOOL3 operator!=(const INT3& rhs);
		BOOL4 operator!=(const INT4& rhs);

		bool  operator>(int rhs);
		BOOL2 operator>(const INT2& rhs);
		BOOL3 operator>(const INT3& rhs);
		BOOL4 operator>(const INT4& rhs);
		bool  operator<(int rhs);
		BOOL2 operator<(const INT2& rhs);
		BOOL3 operator<(const INT3& rhs);
		BOOL4 operator<(const INT4& rhs);

		bool  operator>=(int rhs);
		BOOL2 operator>=(const INT2& rhs);
		BOOL3 operator>=(const INT3& rhs);
		BOOL4 operator>=(const INT4& rhs);
		bool  operator<=(int rhs);
		BOOL2 operator<=(const INT2& rhs);
		BOOL3 operator<=(const INT3& rhs);
		BOOL4 operator<=(const INT4& rhs);



		// operators for FLOAT

		INT4& operator=(float rhs);
		INT4& operator=(const XMFLOAT2& rhs);
		INT4& operator=(const XMFLOAT3& rhs);
		INT4& operator=(const XMFLOAT4& rhs);

		INT4 operator+(float rhs);
		INT4 operator+(const XMFLOAT2& rhs);
		INT4 operator+(const XMFLOAT3& rhs);
		INT4 operator+(const XMFLOAT4& rhs);
		INT4& operator+=(float rhs);
		INT4& operator+=(const XMFLOAT2& rhs);
		INT4& operator+=(const XMFLOAT3& rhs);
		INT4& operator+=(const XMFLOAT4& rhs);

		INT4 operator-(float rhs);
		INT4 operator-(const XMFLOAT2& rhs);
		INT4 operator-(const XMFLOAT3& rhs);
		INT4 operator-(const XMFLOAT4& rhs);
		INT4& operator-=(float rhs);
		INT4& operator-=(const XMFLOAT2& rhs);
		INT4& operator-=(const XMFLOAT3& rhs);
		INT4& operator-=(const XMFLOAT4& rhs);

		INT4 operator*(float rhs);
		INT4 operator*(const XMFLOAT2& rhs);
		INT4 operator*(const XMFLOAT3& rhs);
		INT4 operator*(const XMFLOAT4& rhs);
		INT4& operator*=(float rhs);
		INT4& operator*=(const XMFLOAT2& rhs);
		INT4& operator*=(const XMFLOAT3& rhs);
		INT4& operator*=(const XMFLOAT4& rhs);

		INT4 operator/(float rhs);
		INT4 operator/(const XMFLOAT2& rhs);
		INT4 operator/(const XMFLOAT3& rhs);
		INT4 operator/(const XMFLOAT4& rhs);
		INT4& operator/=(float rhs);
		INT4& operator/=(const XMFLOAT2& rhs);
		INT4& operator/=(const XMFLOAT3& rhs);
		INT4& operator/=(const XMFLOAT4& rhs);

		// bool (FLOAT)

		bool  operator==(float rhs);
		BOOL2 operator==(const XMFLOAT2& rhs);
		BOOL3 operator==(const XMFLOAT3& rhs);
		BOOL4 operator==(const XMFLOAT4& rhs);
		bool  operator!=(float rhs);
		BOOL2 operator!=(const XMFLOAT2& rhs);
		BOOL3 operator!=(const XMFLOAT3& rhs);
		BOOL4 operator!=(const XMFLOAT4& rhs);

		bool  operator>(float rhs);
		BOOL2 operator>(const XMFLOAT2& rhs);
		BOOL3 operator>(const XMFLOAT3& rhs);
		BOOL4 operator>(const XMFLOAT4& rhs);
		bool  operator<(float rhs);
		BOOL2 operator<(const XMFLOAT2& rhs);
		BOOL3 operator<(const XMFLOAT3& rhs);
		BOOL4 operator<(const XMFLOAT4& rhs);

		bool  operator>=(float rhs);
		BOOL2 operator>=(const XMFLOAT2& rhs);
		BOOL3 operator>=(const XMFLOAT3& rhs);
		BOOL4 operator>=(const XMFLOAT4& rhs);
		bool  operator<=(float rhs);
		BOOL2 operator<=(const XMFLOAT2& rhs);
		BOOL3 operator<=(const XMFLOAT3& rhs);
		BOOL4 operator<=(const XMFLOAT4& rhs);

	};

}