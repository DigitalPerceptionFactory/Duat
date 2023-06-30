#include "Legacy.h"


namespace DirectX {

	XMFLOAT2 XMFloat2Floor(const XMFLOAT2& value, INT2 digits)
	{
		XMFLOAT2 result;
		result.x = std::floor(value.x);
		result.y = std::floor(value.y);
		if (digits.x > 0) result.x += std::floor(std::pow(10, digits.x) * (value.x - result.x)) / std::pow(10, digits.x);
		else result.x = (int)value.x;
		if (digits.y > 0) result.y += std::floor(std::pow(10, digits.y) * (value.y - result.y)) / std::pow(10, digits.y);
		else result.y = (int)value.y;
		return result;
	}

	XMFLOAT3 XMFloat3Floor(const XMFLOAT3& value, INT3 digits)
	{
		XMFLOAT3 result;
		result.x = std::floor(value.x);
		result.y = std::floor(value.y);
		result.z = std::floor(value.z);
		if (digits.x > 0) result.x += std::floor(std::pow(10, digits.x) * (value.x - result.x)) / std::pow(10, digits.x);
		if (digits.y > 0) result.y += std::floor(std::pow(10, digits.y) * (value.y - result.y)) / std::pow(10, digits.y);
		if (digits.z > 0) result.z += std::floor(std::pow(10, digits.z) * (value.z - result.z)) / std::pow(10, digits.z);
		return result;
	}

	XMFLOAT4 XMFloat4Floor(const XMFLOAT4& value, INT4 digits)
	{
		XMFLOAT4 result;
		result.x = std::floor(value.x);
		result.y = std::floor(value.y);
		result.z = std::floor(value.z);
		result.w = std::floor(value.w);
		if (digits.x > 0) result.x += std::floor(std::pow(10, digits.x) * (value.x - result.x)) / std::pow(10, digits.x);
		if (digits.y > 0) result.y += std::floor(std::pow(10, digits.y) * (value.y - result.y)) / std::pow(10, digits.y);
		if (digits.z > 0) result.z += std::floor(std::pow(10, digits.z) * (value.z - result.z)) / std::pow(10, digits.z);
		if (digits.w > 0) result.w += std::floor(std::pow(10, digits.w) * (value.w - result.w)) / std::pow(10, digits.w);
		return result;
	}

	float XMVectorLength(const XMFLOAT4& vector)
	{
		XMFLOAT4 result;
		XMStoreFloat4(&result,
			XMVector4Length(XMLoadFloat4(&vector))
		);
		return result.x;
	}

	float XMVectorLength(const XMFLOAT3& vector)
	{
		XMFLOAT3 result;
		XMStoreFloat3(&result,
			XMVector3Length(XMLoadFloat3(&vector))
		);
		return result.x;
	}

	float XMVectorLength(const XMFLOAT2& vector)
	{
		XMFLOAT2 result;
		XMStoreFloat2(&result,
			XMVector2Length(XMLoadFloat2(&vector))
		);
		return result.x;
	}

	XMFLOAT2 XMFloat2Min(const XMFLOAT2& a, float b)
	{
		XMFLOAT2 result;
		result.x = a.x < b ? a.x : b;
		result.y = a.y < b ? a.y : b;
		return result;
	}

	XMFLOAT2 XMFloat2Min(const XMFLOAT2& a, const XMFLOAT2& b)
	{
		XMFLOAT2 result;
		result.x = a.x < b.x ? a.x : b.x;
		result.y = a.y < b.y ? a.y : b.y;
		return result;
	}

	XMFLOAT2 XMFloat2Min(const XMFLOAT2& a, const XMFLOAT3& b)
	{
		XMFLOAT2 result;
		result.x = a.x < b.x ? a.x : b.x;
		result.y = a.y < b.y ? a.y : b.y;
		return result;
	}

	XMFLOAT2 XMFloat2Min(const XMFLOAT2& a, const XMFLOAT4& b)
	{
		XMFLOAT2 result;
		result.x = a.x < b.x ? a.x : b.x;
		result.y = a.y < b.y ? a.y : b.y;
		return result;
	}

	XMFLOAT2 XMFloat2Max(const XMFLOAT2& a, float b)
	{
		XMFLOAT2 result;
		result.x = a.x > b ? a.x : b;
		result.y = a.y > b ? a.y : b;
		return result;
	}

	XMFLOAT2 XMFloat2Max(const XMFLOAT2& a, const XMFLOAT2& b)
	{
		XMFLOAT2 result;
		result.x = a.x > b.x ? a.x : b.x;
		result.y = a.y > b.y ? a.y : b.y;
		return result;
	}

	XMFLOAT2 XMFloat2Max(const XMFLOAT2& a, const XMFLOAT3& b)
	{
		XMFLOAT2 result;
		result.x = a.x > b.x ? a.x : b.x;
		result.y = a.y > b.y ? a.y : b.y;
		return result;
	}

	XMFLOAT2 XMFloat2Max(const XMFLOAT2& a, const XMFLOAT4& b)
	{
		XMFLOAT2 result;
		result.x = a.x > b.x ? a.x : b.x;
		result.y = a.y > b.y ? a.y : b.y;
		return result;
	}

	XMFLOAT3 XMFloat3Min(const XMFLOAT3& a, float b)
	{
		XMFLOAT3 result;
		result.x = a.x < b ? a.x : b;
		result.y = a.y < b ? a.y : b;
		result.z = a.z < b ? a.z : b;
		return result;
	}

	XMFLOAT3 XMFloat3Min(const XMFLOAT3& a, const XMFLOAT2& b)
	{
		XMFLOAT3 result;
		result.x = a.x < b.x ? a.x : b.x;
		result.y = a.y < b.y ? a.y : b.y;
		result.z = a.z;
		return result;
	}

	XMFLOAT3 XMFloat3Min(const XMFLOAT3& a, const XMFLOAT3& b)
	{
		XMFLOAT3 result;
		result.x = a.x < b.x ? a.x : b.x;
		result.y = a.y < b.y ? a.y : b.y;
		result.z = a.z < b.z ? a.z : b.z;
		return result;
	}

	XMFLOAT3 XMFloat3Min(const XMFLOAT3& a, const XMFLOAT4& b)
	{
		XMFLOAT3 result;
		result.x = a.x < b.x ? a.x : b.x;
		result.y = a.y < b.y ? a.y : b.y;
		result.z = a.z < b.z ? a.z : b.z;
		return result;
	}

	XMFLOAT3 XMFloat3Max(const XMFLOAT3& a, float b)
	{
		XMFLOAT3 result;
		result.x = a.x > b ? a.x : b;
		result.y = a.y > b ? a.y : b;
		result.z = a.z > b ? a.z : b;
		return result;
	}

	XMFLOAT3 XMFloat3Max(const XMFLOAT3& a, const XMFLOAT2& b)
	{
		XMFLOAT3 result;
		result.x = a.x > b.x ? a.x : b.x;
		result.y = a.y > b.y ? a.y : b.y;
		result.z = a.z;
		return result;
	}

	XMFLOAT3 XMFloat3Max(const XMFLOAT3& a, const XMFLOAT3& b)
	{
		XMFLOAT3 result;
		result.x = a.x > b.x ? a.x : b.x;
		result.y = a.y > b.y ? a.y : b.y;
		result.z = a.z > b.z ? a.z : b.z;
		return result;
	}

	XMFLOAT3 XMFloat3Max(const XMFLOAT3& a, const XMFLOAT4& b)
	{
		XMFLOAT3 result;
		result.x = a.x > b.x ? a.x : b.x;
		result.y = a.y > b.y ? a.y : b.y;
		result.z = a.z > b.z ? a.z : b.z;
		return result;
	}

	XMFLOAT4 XMFloat4Min(const XMFLOAT4& a, float b)
	{
		XMFLOAT4 result;
		result.x = a.x < b ? a.x : b;
		result.y = a.y < b ? a.y : b;
		result.z = a.z < b ? a.z : b;
		result.w = a.w < b ? a.w : b;
		return result;
	}

	XMFLOAT4 XMFloat4Min(const XMFLOAT4& a, const XMFLOAT2& b)
	{
		XMFLOAT4 result;
		result.x = a.x < b.x ? a.x : b.x;
		result.y = a.y < b.y ? a.y : b.y;
		result.z = a.z;
		result.w = a.w;
		return result;
	}

	XMFLOAT4 XMFloat4Min(const XMFLOAT4& a, const XMFLOAT3& b)
	{
		XMFLOAT4 result;
		result.x = a.x < b.x ? a.x : b.x;
		result.y = a.y < b.y ? a.y : b.y;
		result.z = a.z < b.z ? a.z : b.z;
		result.w = a.w;
		return result;
	}

	XMFLOAT4 XMFloat4Min(const XMFLOAT4& a, const XMFLOAT4& b)
	{
		XMFLOAT4 result;
		result.x = a.x < b.x ? a.x : b.x;
		result.y = a.y < b.y ? a.y : b.y;
		result.z = a.z < b.z ? a.z : b.z;
		result.w = a.w < b.w ? a.w : b.w;
		return result;
	}

	XMFLOAT4 XMFloat4Max(const XMFLOAT4& a, float b)
	{
		XMFLOAT4 result;
		result.x = a.x > b ? a.x : b;
		result.y = a.y > b ? a.y : b;
		result.z = a.z > b ? a.z : b;
		result.w = a.w > b ? a.w : b;
		return result;
	}

	XMFLOAT4 XMFloat4Max(const XMFLOAT4& a, const XMFLOAT2& b)
	{
		XMFLOAT4 result;
		result.x = a.x > b.x ? a.x : b.x;
		result.y = a.y > b.y ? a.y : b.y;
		result.z = a.z;
		result.w = a.w;
		return result;
	}

	XMFLOAT4 XMFloat4Max(const XMFLOAT4& a, const XMFLOAT3& b)
	{
		XMFLOAT4 result;
		result.x = a.x > b.x ? a.x : b.x;
		result.y = a.y > b.y ? a.y : b.y;
		result.z = a.z > b.z ? a.z : b.z;
		result.w = a.w;
		return result;
	}

	XMFLOAT4 XMFloat4Max(const XMFLOAT4& a, const XMFLOAT4& b)
	{
		XMFLOAT4 result;
		result.x = a.x > b.x ? a.x : b.x;
		result.y = a.y > b.y ? a.y : b.y;
		result.z = a.z > b.z ? a.z : b.z;
		result.w = a.w > b.w ? a.w : b.w;
		return result;
	}

	XMFLOAT2 XMFloat2Abs(XMFLOAT2 f2)
	{
		return { std::abs(f2.x), std::abs(f2.y) };
	}

	XMFLOAT3 XMFloat3Abs(XMFLOAT3 f3)
	{
		return { std::abs(f3.x), std::abs(f3.y), std::abs(f3.z) };
	}

	XMFLOAT4 XMFloat4Abs(XMFLOAT4 f4)
	{
		return { std::abs(f4.x), std::abs(f4.y), std::abs(f4.z), std::abs(f4.w) };
	}

	float XMLerp(float from, float to, float t)
	{
		return std::lerp(from, to, t);
	}

	XMFLOAT4 XMVectorLerp(const XMFLOAT4& v, float t)
	{
		return XMVectorLerp({ 0,0,0,0 }, v, t);
	}

	XMFLOAT4 XMVectorLerp(const XMFLOAT4& from, const XMFLOAT4& to, float t)
	{
		XMFLOAT4 result;
		XMStoreFloat4(&result,
			XMVectorLerp(XMLoadFloat4(&from), XMLoadFloat4(&to), t)
		);
		return result;
	}

	XMFLOAT4 XMVectorLerp(const XMFLOAT4& from, const XMFLOAT3& to, float t)
	{
		XMFLOAT4 result;
		XMStoreFloat4(&result,
			XMVectorLerp(XMLoadFloat4(&from), XMLoadFloat3(&to), t)
		);
		return result;
	}

	XMFLOAT4 XMVectorLerp(const XMFLOAT4& from, const XMFLOAT2& to, float t)
	{
		XMFLOAT4 result;
		XMStoreFloat4(&result,
			XMVectorLerp(XMLoadFloat4(&from), XMLoadFloat2(&to), t)
		);
		return result;
	}

	XMFLOAT3 XMVectorLerp(const XMFLOAT3& v, float t)
	{
		return XMVectorLerp({ 0,0,0 }, v, t);
	}

	XMFLOAT3 XMVectorLerp(const XMFLOAT3& from, const XMFLOAT4& to, float t)
	{
		XMFLOAT3 result;
		XMStoreFloat3(&result,
			XMVectorLerp(XMLoadFloat3(&from), XMLoadFloat4(&to), t)
		);
		return result;
	}

	XMFLOAT3 XMVectorLerp(const XMFLOAT3& from, const XMFLOAT3& to, float t)
	{
		XMFLOAT3 result;
		XMStoreFloat3(&result,
			XMVectorLerp(XMLoadFloat3(&from), XMLoadFloat3(&to), t)
		);
		return result;
	}

	XMFLOAT3 XMVectorLerp(const XMFLOAT3& from, const XMFLOAT2& to, float t)
	{
		XMFLOAT3 result;
		XMStoreFloat3(&result,
			XMVectorLerp(XMLoadFloat3(&from), XMLoadFloat2(&to), t)
		);
		return result;
	}

	XMFLOAT2 XMVectorLerp(const XMFLOAT2& v, float t)
	{
		return XMVectorLerp({ 0,0 }, v, t);
	}

	XMFLOAT2 XMVectorLerp(const XMFLOAT2& from, const XMFLOAT4& to, float t)
	{
		XMFLOAT2 result;
		XMStoreFloat2(&result,
			XMVectorLerp(XMLoadFloat2(&from), XMLoadFloat4(&to), t)
		);
		return result;
	}

	XMFLOAT2 XMVectorLerp(const XMFLOAT2& from, const XMFLOAT3& to, float t)
	{
		XMFLOAT2 result;
		XMStoreFloat2(&result,
			XMVectorLerp(XMLoadFloat2(&from), XMLoadFloat3(&to), t)
		);
		return result;
	}

	XMFLOAT2 XMVectorLerp(const XMFLOAT2& from, const XMFLOAT2& to, float t)
	{
		XMFLOAT2 result;
		XMStoreFloat2(&result,
			XMVectorLerp(XMLoadFloat2(&from), XMLoadFloat2(&to), t)
		);
		return result;
	}

	float XMInverseLerp(float from, float to, float value)
	{
		return (value - from) / (to - from);
	}

	XMMATRIX XMCreateMatrix(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale)
	{
		return XMMatrixIdentity()
			* XMMatrixRotationRollPitchYawDegrees(rot)
			* XMMatrixScaling(scale)
			* XMMatrixTranslation(pos);

	}
	XMMATRIX XMMatrixTranslation(XMFLOAT3 xyz)
	{
		return XMMatrixTranslation(xyz.x, xyz.y, xyz.z);
	}

	XMMATRIX XMMatrixScaling(XMFLOAT3 xyz)
	{
		return XMMatrixScaling(xyz.x, xyz.y, xyz.z);
	}

	XMMATRIX XMMatrixRotationRollPitchYawDegrees(float x, float y, float z)
	{
		return XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(x),
			XMConvertToRadians(y),
			XMConvertToRadians(z)
		);
	}

	XMMATRIX XMMatrixRotationRollPitchYawDegrees(XMFLOAT3 euler)
	{
		return XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(euler.x),
			XMConvertToRadians(euler.y),
			XMConvertToRadians(euler.z)
		);
	}

	XMMATRIX XMMatrixRotationRollPitchYawDegrees(XMVECTOR euler)
	{
		XMFLOAT3 f3;
		XMStoreFloat3(&f3, euler);
		return XMMatrixRotationRollPitchYawDegrees(f3);
	}

	XMFLOAT3 XMFloat3Transform(XMFLOAT3 f3, XMMATRIX m)
	{
		XMFLOAT3 result;
		XMVECTOR v = XMLoadFloat3(&f3);
		XMStoreFloat3(&result, XMVector3Transform(v, m));
		return result;
	}

	XMFLOAT4 XMFloat4Transform(XMFLOAT4 f4, XMMATRIX m)
	{
		XMFLOAT4 result;
		XMStoreFloat4(&result, XMVector4Transform(XMLoadFloat4(&f4), m));
		return result;
	}

	XMFLOAT3 XMFloat3Normalize(XMFLOAT3 f3)
	{
		XMFLOAT3 result;
		XMStoreFloat3(&result, XMVector3Normalize(XMLoadFloat3(&f3)));
		return result;
	}

	XMFLOAT4 XMFloat4Normalize(XMFLOAT4 f4)
	{
		XMFLOAT4 result;
		XMStoreFloat4(&result, XMVector3Normalize(XMLoadFloat4(&f4)));
		return result;
	}

	XMFLOAT3 XMFloat3Lerp(XMFLOAT3 from, XMFLOAT3 to, float lerp)
	{
		XMFLOAT3 result;
		XMStoreFloat3(
			&result,
			XMVectorLerp(XMLoadFloat3(&from), XMLoadFloat3(&to), lerp)
		);
		return result;
	}

	XMFLOAT4 XMFloat4Lerp(XMFLOAT4 from, XMFLOAT4 to, float lerp)
	{
		XMFLOAT4 result;
		XMStoreFloat4(
			&result,
			XMVectorLerp(XMLoadFloat4(&from), XMLoadFloat4(&to), lerp)
		);
		return result;
	}

	XMFLOAT3 XMFloat3Cross(XMFLOAT3 a, XMFLOAT3 b)
	{
		XMFLOAT3 result;
		XMStoreFloat3(
			&result,
			XMVector3Cross(
				XMLoadFloat3(&a),
				XMLoadFloat3(&b)
			)
		);
		return result;
	}

	XMFLOAT4 XMFloat4Cross(XMFLOAT4 a, XMFLOAT4 b)
	{
		XMFLOAT4 result;
		XMStoreFloat4(
			&result,
			XMVector3Cross(
				XMLoadFloat4(&a),
				XMLoadFloat4(&b)
			)
		);
		return result;
	}

	XMMATRIX XMMatrixLookAtLH(XMFLOAT3 eye, XMFLOAT3 focus, XMFLOAT3 up)
	{
		return XMMatrixLookAtLH(
			XMLoadFloat3(&eye),
			XMLoadFloat3(&focus),
			XMLoadFloat3(&up)
		);
	}

	XMMATRIX XMMatrixLookAtLH(XMFLOAT4 eye, XMFLOAT4 focus, XMFLOAT4 up)
	{
		return XMMatrixLookAtLH(
			XMLoadFloat4(&eye),
			XMLoadFloat4(&focus),
			XMLoadFloat4(&up)
		);
	}

	void XMAssign(XMFLOAT4& destination, const XMFLOAT3& source)
	{
		destination.x = source.x;
		destination.y = source.y;
		destination.z = source.z;
	}

	void XMAssign(XMFLOAT4& destination, const XMFLOAT2& source)
	{
		destination.x = source.x;
		destination.y = source.y;
	}

	void XMAssign(XMFLOAT3& destination, const XMFLOAT4& source)
	{
		destination.x = source.x;
		destination.y = source.y;
		destination.z = source.z;
	}

	void XMAssign(XMFLOAT3& destination, const XMFLOAT2& source)
	{
		destination.x = source.x;
		destination.y = source.y;
	}

	void XMAssign(XMFLOAT2& destination, const XMFLOAT4& source)
	{
		destination.x = source.x;
		destination.y = source.y;
	}

	void XMAssign(XMFLOAT2& destination, const XMFLOAT3& source)
	{
		destination.x = source.x;
		destination.y = source.y;
	}


	bool operator==(const XMFLOAT4& lhs, const XMFLOAT4& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
	}
	bool operator!=(const XMFLOAT4& lhs, const XMFLOAT4& rhs)
	{
		return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z || lhs.w != rhs.w;
	}
	bool operator==(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
	}
	bool operator!=(const XMFLOAT3& lhs, const XMFLOAT3& rhs) {
		return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z;
	}

	XMFLOAT4 operator+(const XMFLOAT4& lhs, const XMFLOAT4& rhs)
	{
		XMFLOAT4 result;
		result.x = lhs.x + rhs.x;
		result.y = lhs.y + rhs.y;
		result.z = lhs.z + rhs.z;
		result.w = lhs.w + rhs.w;
		return result;
	}

	XMFLOAT4 operator-(const XMFLOAT4& lhs, const XMFLOAT4& rhs)
	{
		XMFLOAT4 result;
		result.x = lhs.x - rhs.x;
		result.y = lhs.y - rhs.y;
		result.z = lhs.z - rhs.z;
		result.w = lhs.w - rhs.w;
		return result;
	}

	XMFLOAT4 operator+(const XMFLOAT4& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT4 result;
		result.x = lhs.x + rhs.x;
		result.y = lhs.y + rhs.y;
		result.z = lhs.z + rhs.z;
		result.w = lhs.w;
		return result;
	}

	XMFLOAT4 operator-(const XMFLOAT4& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT4 result;
		result.x = lhs.x - rhs.x;
		result.y = lhs.y - rhs.y;
		result.z = lhs.z - rhs.z;
		result.w = lhs.w;
		return result;
	}

	XMFLOAT4 operator+(const XMFLOAT4& lhs, const XMFLOAT2& rhs)
	{
		XMFLOAT4 result;
		result.x = lhs.x + rhs.x;
		result.y = lhs.y + rhs.y;
		result.z = lhs.z;
		result.w = lhs.w;
		return result;
	}

	XMFLOAT4 operator-(const XMFLOAT4& lhs, const XMFLOAT2& rhs)
	{
		XMFLOAT4 result;
		result.x = lhs.x - rhs.x;
		result.y = lhs.y - rhs.y;
		result.z = lhs.z;
		result.w = lhs.w;
		return result;
	}

	XMFLOAT4 operator+=(XMFLOAT4& lhs, const XMFLOAT4& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}

	XMFLOAT4 operator-=(XMFLOAT4& lhs, const XMFLOAT4& rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}

	XMFLOAT4 operator+=(XMFLOAT4& lhs, const XMFLOAT3& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}

	XMFLOAT4 operator-=(XMFLOAT4& lhs, const XMFLOAT3& rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}

	XMFLOAT4 operator+=(XMFLOAT4& lhs, const XMFLOAT2& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}

	XMFLOAT4 operator-=(XMFLOAT4& lhs, const XMFLOAT2& rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}

	XMFLOAT3 operator+(const XMFLOAT3& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT3 result;
		result.x = lhs.x + rhs.x;
		result.y = lhs.y + rhs.y;
		result.z = lhs.z + rhs.z;
		return result;
	}

	XMFLOAT3 operator-(const XMFLOAT3& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT3 result;
		result.x = lhs.x - rhs.x;
		result.y = lhs.y - rhs.y;
		result.z = lhs.z - rhs.z;
		return result;
	}

	XMFLOAT3 operator+(const XMFLOAT3& lhs, const XMFLOAT4& rhs)
	{
		XMFLOAT3 result;
		result.x = lhs.x + rhs.x;
		result.y = lhs.y + rhs.y;
		result.z = lhs.z + rhs.z;
		return result;
	}

	XMFLOAT3 operator-(const XMFLOAT3& lhs, const XMFLOAT4& rhs)
	{
		XMFLOAT3 result;
		result.x = lhs.x - rhs.x;
		result.y = lhs.y - rhs.y;
		result.z = lhs.z - rhs.z;
		return result;
	}

	XMFLOAT3 operator+(const XMFLOAT3& lhs, const XMFLOAT2& rhs)
	{
		XMFLOAT3 result;
		result.x = lhs.x + rhs.x;
		result.y = lhs.y + rhs.y;
		result.z = lhs.z;
		return result;
	}

	XMFLOAT3 operator-(const XMFLOAT3& lhs, const XMFLOAT2& rhs)
	{
		XMFLOAT3 result;
		result.x = lhs.x - rhs.x;
		result.y = lhs.y - rhs.y;
		result.z = lhs.z;
		return result;
	}

	XMFLOAT3 operator+=(XMFLOAT3& lhs, const XMFLOAT3& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}

	XMFLOAT3 operator-=(XMFLOAT3& lhs, const XMFLOAT3& rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}

	XMFLOAT3 operator+=(XMFLOAT3& lhs, const XMFLOAT4& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}

	XMFLOAT3 operator-=(XMFLOAT3& lhs, const XMFLOAT4& rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}

	XMFLOAT3 operator+=(XMFLOAT3& lhs, const XMFLOAT2& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}

	XMFLOAT3 operator-=(XMFLOAT3& lhs, const XMFLOAT2& rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}

	XMFLOAT2 operator+(const XMFLOAT2& lhs, const XMFLOAT2& rhs)
	{
		XMFLOAT2 result;
		result.x = lhs.x + rhs.x;
		result.y = lhs.y + rhs.y;
		return result;
	}

	XMFLOAT2 operator-(const XMFLOAT2& lhs, const XMFLOAT2& rhs)
	{
		XMFLOAT2 result;
		result.x = lhs.x - rhs.x;
		result.y = lhs.y - rhs.y;
		return result;
	}

	XMFLOAT2 operator+(const XMFLOAT2& lhs, const XMFLOAT4& rhs)
	{
		XMFLOAT2 result;
		result.x = lhs.x + rhs.x;
		result.y = lhs.y + rhs.y;
		return result;
	}

	XMFLOAT2 operator-(const XMFLOAT2& lhs, const XMFLOAT4& rhs)
	{
		XMFLOAT2 result;
		result.x = lhs.x - rhs.x;
		result.y = lhs.y - rhs.y;
		return result;
	}

	XMFLOAT2 operator+(const XMFLOAT2& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT2 result;
		result.x = lhs.x + rhs.x;
		result.y = lhs.y + rhs.y;
		return result;
	}

	XMFLOAT2 operator-(const XMFLOAT2& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT2 result;
		result.x = lhs.x - rhs.x;
		result.y = lhs.y - rhs.y;
		return result;
	}

	XMFLOAT2 operator+=(XMFLOAT2& lhs, const XMFLOAT2& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}

	XMFLOAT2 operator-=(XMFLOAT2& lhs, const XMFLOAT2& rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}

	XMFLOAT2 operator+=(XMFLOAT2& lhs, const XMFLOAT4& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}

	XMFLOAT2 operator-=(XMFLOAT2& lhs, const XMFLOAT4& rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}

	XMFLOAT2 operator+=(XMFLOAT2& lhs, const XMFLOAT3& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}

	XMFLOAT2 operator-=(XMFLOAT2& lhs, const XMFLOAT3& rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}

	XMFLOAT2 operator+(const XMFLOAT2& lhs, float rhs)
	{
		XMFLOAT2 result;
		result.x = lhs.x + rhs;
		result.y = lhs.y + rhs;
		return result;
	}

	XMFLOAT2 operator-(const XMFLOAT2& lhs, float rhs)
	{
		XMFLOAT2 result;
		result.x = lhs.x - rhs;
		result.y = lhs.y - rhs;
		return result;
	}

	XMFLOAT3 operator+(const XMFLOAT3& lhs, float rhs)
	{
		XMFLOAT3 result;
		result.x = lhs.x + rhs;
		result.y = lhs.y + rhs;
		result.z = lhs.z + rhs;
		return result;
	}

	XMFLOAT3 operator-(const XMFLOAT3& lhs, float rhs)
	{
		XMFLOAT3 result;
		result.x = lhs.x - rhs;
		result.y = lhs.y - rhs;
		result.z = lhs.z - rhs;
		return result;
	}

	XMFLOAT4 operator+(const XMFLOAT4& lhs, float rhs)
	{
		XMFLOAT4 result;
		result.x = lhs.x + rhs;
		result.y = lhs.y + rhs;
		result.z = lhs.z + rhs;
		result.w = lhs.w + rhs;
		return result;
	}

	XMFLOAT4 operator-(const XMFLOAT4& lhs, float rhs)
	{
		XMFLOAT4 result;
		result.x = lhs.x - rhs;
		result.y = lhs.y - rhs;
		result.z = lhs.z - rhs;
		result.w = lhs.w - rhs;
		return result;
	}

	XMFLOAT2 operator+=(XMFLOAT2& lhs, float rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}

	XMFLOAT2 operator-=(XMFLOAT2& lhs, float rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}

	XMFLOAT3 operator+=(XMFLOAT3& lhs, float rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}

	XMFLOAT3 operator-=(XMFLOAT3& lhs, float rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}

	XMFLOAT4 operator+=(XMFLOAT4& lhs, float rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}

	XMFLOAT4 operator-=(XMFLOAT4& lhs, float rhs)
	{
		lhs = lhs - rhs;
		return lhs;
	}

	XMFLOAT4 operator*(const XMFLOAT4& lhs, const XMFLOAT4& rhs)
	{
		XMFLOAT4 result;
		result.x = lhs.x * rhs.x;
		result.y = lhs.y * rhs.y;
		result.z = lhs.z * rhs.z;
		result.w = lhs.w * rhs.w;
		return result;
	}

	XMFLOAT4 operator/(const XMFLOAT4& lhs, const XMFLOAT4& rhs)
	{
		XMFLOAT4 result;
		result.x = lhs.x / rhs.x;
		result.y = lhs.y / rhs.y;
		result.z = lhs.z / rhs.z;
		result.w = lhs.w / rhs.w;
		return result;
	}

	XMFLOAT4 operator*(const XMFLOAT4& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT4 result;
		result.x = lhs.x * rhs.x;
		result.y = lhs.y * rhs.y;
		result.z = lhs.z * rhs.z;
		result.w = lhs.w;
		return result;
	}

	XMFLOAT4 operator/(const XMFLOAT4& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT4 result;
		result.x = lhs.x / rhs.x;
		result.y = lhs.y / rhs.y;
		result.z = lhs.z / rhs.z;
		result.w = lhs.w;
		return result;
	}

	XMFLOAT4 operator*(const XMFLOAT4& lhs, const XMFLOAT2& rhs)
	{
		XMFLOAT4 result;
		result.x = lhs.x * rhs.x;
		result.y = lhs.y * rhs.y;
		result.z = lhs.z;
		result.w = lhs.w;
		return result;
	}

	XMFLOAT4 operator/(const XMFLOAT4& lhs, const XMFLOAT2& rhs)
	{
		XMFLOAT4 result;
		result.x = lhs.x / rhs.x;
		result.y = lhs.y / rhs.y;
		result.z = lhs.z;
		result.w = lhs.w;
		return result;
	}

	XMFLOAT4 operator*=(XMFLOAT4& lhs, const XMFLOAT4& rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}

	XMFLOAT4 operator/=(XMFLOAT4& lhs, const XMFLOAT4& rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}

	XMFLOAT4 operator*=(XMFLOAT4& lhs, const XMFLOAT3& rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}

	XMFLOAT4 operator/=(XMFLOAT4& lhs, const XMFLOAT3& rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}

	XMFLOAT4 operator*=(XMFLOAT4& lhs, const XMFLOAT2& rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}

	XMFLOAT4 operator/=(XMFLOAT4& lhs, const XMFLOAT2& rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}

	XMFLOAT3 operator*(const XMFLOAT3& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT3 result;
		result.x = lhs.x * rhs.x;
		result.y = lhs.y * rhs.y;
		result.z = lhs.z * rhs.z;
		return result;
	}

	XMFLOAT3 operator/(const XMFLOAT3& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT3 result;
		result.x = lhs.x / rhs.x;
		result.y = lhs.y / rhs.y;
		result.z = lhs.z / rhs.z;
		return result;
	}

	XMFLOAT3 operator*(const XMFLOAT3& lhs, const XMFLOAT4& rhs)
	{
		XMFLOAT3 result;
		result.x = lhs.x * rhs.x;
		result.y = lhs.y * rhs.y;
		result.z = lhs.z * rhs.z;
		return result;
	}

	XMFLOAT3 operator/(const XMFLOAT3& lhs, const XMFLOAT4& rhs)
	{
		XMFLOAT3 result;
		result.x = lhs.x / rhs.x;
		result.y = lhs.y / rhs.y;
		result.z = lhs.z / rhs.z;
		return result;
	}

	XMFLOAT3 operator*(const XMFLOAT3& lhs, const XMFLOAT2& rhs)
	{
		XMFLOAT3 result;
		result.x = lhs.x * rhs.x;
		result.y = lhs.y * rhs.y;
		result.z = lhs.z;
		return result;
	}

	XMFLOAT3 operator/(const XMFLOAT3& lhs, const XMFLOAT2& rhs)
	{
		XMFLOAT3 result;
		result.x = lhs.x / rhs.x;
		result.y = lhs.y / rhs.y;
		result.z = lhs.z;
		return result;
	}

	XMFLOAT3 operator*=(XMFLOAT3& lhs, const XMFLOAT3& rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}

	XMFLOAT3 operator/=(XMFLOAT3& lhs, const XMFLOAT3& rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}

	XMFLOAT3 operator*=(XMFLOAT3& lhs, const XMFLOAT4& rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}

	XMFLOAT3 operator/=(XMFLOAT3& lhs, const XMFLOAT4& rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}

	XMFLOAT3 operator*=(XMFLOAT3& lhs, const XMFLOAT2& rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}

	XMFLOAT3 operator/=(XMFLOAT3& lhs, const XMFLOAT2& rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}

	XMFLOAT2 operator*(const XMFLOAT2& lhs, const XMFLOAT2& rhs)
	{
		XMFLOAT2 result;
		result.x = lhs.x * rhs.x;
		result.y = lhs.y * rhs.y;
		return result;
	}

	XMFLOAT2 operator/(const XMFLOAT2& lhs, const XMFLOAT2& rhs)
	{
		XMFLOAT2 result;
		result.x = lhs.x / rhs.x;
		result.y = lhs.y / rhs.y;
		return result;
	}

	XMFLOAT2 operator*(const XMFLOAT2& lhs, const XMFLOAT4& rhs)
	{
		XMFLOAT2 result;
		result.x = lhs.x * rhs.x;
		result.y = lhs.y * rhs.y;
		return result;
	}

	XMFLOAT2 operator/(const XMFLOAT2& lhs, const XMFLOAT4& rhs)
	{
		XMFLOAT2 result;
		result.x = lhs.x / rhs.x;
		result.y = lhs.y / rhs.y;
		return result;
	}

	XMFLOAT2 operator*(const XMFLOAT2& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT2 result;
		result.x = lhs.x * rhs.x;
		result.y = lhs.y * rhs.y;
		return result;
	}

	XMFLOAT2 operator/(const XMFLOAT2& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT2 result;
		result.x = lhs.x / rhs.x;
		result.y = lhs.y / rhs.y;
		return result;
	}

	XMFLOAT2 operator*=(XMFLOAT2& lhs, const XMFLOAT2& rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}

	XMFLOAT2 operator/=(XMFLOAT2& lhs, const XMFLOAT2& rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}

	XMFLOAT2 operator*=(XMFLOAT2& lhs, const XMFLOAT4& rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}

	XMFLOAT2 operator/=(XMFLOAT2& lhs, const XMFLOAT4& rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}

	XMFLOAT2 operator*=(XMFLOAT2& lhs, const XMFLOAT3& rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}

	XMFLOAT2 operator/=(XMFLOAT2& lhs, const XMFLOAT3& rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}

	XMFLOAT2 operator*(const XMFLOAT2& lhs, float rhs)
	{
		XMFLOAT2 result;
		result.x = lhs.x * rhs;
		result.y = lhs.y * rhs;
		return result;
	}

	XMFLOAT2 operator/(const XMFLOAT2& lhs, float rhs)
	{
		XMFLOAT2 result;
		result.x = lhs.x / rhs;
		result.y = lhs.y / rhs;
		return result;
	}

	XMFLOAT3 operator*(const XMFLOAT3& lhs, float rhs)
	{
		XMFLOAT3 result;
		result.x = lhs.x * rhs;
		result.y = lhs.y * rhs;
		result.z = lhs.z * rhs;
		return result;
	}

	XMFLOAT3 operator/(const XMFLOAT3& lhs, float rhs)
	{
		XMFLOAT3 result;
		result.x = lhs.x / rhs;
		result.y = lhs.y / rhs;
		result.z = lhs.z / rhs;
		return result;
	}

	XMFLOAT4 operator*(const XMFLOAT4& lhs, float rhs)
	{
		XMFLOAT4 result;
		result.x = lhs.x * rhs;
		result.y = lhs.y * rhs;
		result.z = lhs.z * rhs;
		result.w = lhs.w * rhs;
		return result;
	}

	XMFLOAT4 operator/(const XMFLOAT4& lhs, float rhs)
	{
		XMFLOAT4 result;
		result.x = lhs.x / rhs;
		result.y = lhs.y / rhs;
		result.z = lhs.z / rhs;
		result.w = lhs.w / rhs;
		return result;
	}

	XMFLOAT2 operator*=(XMFLOAT2& lhs, float rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}

	XMFLOAT2 operator/=(XMFLOAT2& lhs, float rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}

	XMFLOAT3 operator*=(XMFLOAT3& lhs, float rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}

	XMFLOAT3 operator/=(XMFLOAT3& lhs, float rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}

	XMFLOAT4 operator*=(XMFLOAT4& lhs, float rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}

	XMFLOAT4 operator/=(XMFLOAT4& lhs, float rhs)
	{
		lhs = lhs / rhs;
		return lhs;
	}

}

using namespace DirectX;

namespace Duat::Math {

	float PHI(int exp)
	{
		return std::pow(1.618, exp);
	}

	float phi(int exp)
	{
		return std::pow(0.618, exp);
	}

	std::pair<std::vector<Geometry::Vertex>, std::vector<unsigned int>> MeshFusion(
		std::vector<std::vector<Geometry::Vertex>>& vList, std::vector<std::vector<unsigned int>>& iList)
	{
		Utility::Result result;
		if (vList.size() != iList.size()) result << "vList.size() and iList.size() must be equal.";

		std::pair<std::vector<Geometry::Vertex>, std::vector<unsigned int>> out;
		for (int i = 0; i < vList.size(); ++i)
		{
			for (auto& index : iList[i])
				out.second.push_back(index + out.first.size());

			for (auto& vertex : vList[i])
				out.first.push_back(vertex);
		}
		return out;
	}

	void CalculateNormals(std::vector<Geometry::Vertex>& vertices, std::vector<unsigned int>& indices)
	{
		XMFLOAT3 centroid = Centroid(vertices);
		XMFLOAT4 zero = { 0.0f, 0.0f, 0.0f, 0.0f };
		for (auto& v : vertices)
			v.normal = zero;

		for (int j = 0; j < indices.size(); j += 3)
		{
			int index0 = indices[j];
			int index1 = indices[j + 1];
			int index2 = indices[j + 2];
			XMFLOAT4 v1 = (vertices[index1].position - centroid) - (vertices[index0].position - centroid);
			XMFLOAT4 v2 = (vertices[index2].position - centroid) - (vertices[index1].position - centroid);
			XMVECTOR cross = XMVector3Cross(XMLoadFloat4(&v1), XMLoadFloat4(&v2));

			size_t at = index0;
			if (vertices[at].normal == zero) XMStoreFloat4(&vertices[at].normal, XMVector3Normalize(cross));
			else {
				XMStoreFloat4(
					&vertices[at].normal,
					XMVector3Normalize(XMVectorAdd(XMVector3Normalize(cross), XMLoadFloat4(&vertices[at].normal)))
				);
			}
			at = index1;
			if (vertices[at].normal == zero) XMStoreFloat4(&vertices[at].normal, XMVector3Normalize(cross));
			else {
				XMStoreFloat4(
					&vertices[at].normal,
					XMVector3Normalize(XMVectorAdd(XMVector3Normalize(cross), XMLoadFloat4(&vertices[at].normal)))
				);
			}
			at = index2;
			if (vertices[at].normal == zero) XMStoreFloat4(&vertices[at].normal, XMVector3Normalize(cross));
			else {
				XMStoreFloat4(
					&vertices[at].normal,
					XMVector3Normalize(XMVectorAdd(XMVector3Normalize(cross), XMLoadFloat4(&vertices[at].normal)))
				);
			}
		}
	}

	XMFLOAT3 Centroid(const std::vector<Geometry::Vertex>& vertices)
	{
		float x, y, z;
		x = y = z = 0.0f;
		for (const auto& v : vertices)
		{
			x += v.position.x;
			y += v.position.y;
			z += v.position.z;
		}
		return { x / vertices.size(), y / vertices.size(),z / vertices.size() };
	}

	PerlinNoise::PerlinNoise()
	{
		// Initialize the permutation vector with the reference values
		p = {
			151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
			8,99,37,240,21,10,23,190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
			35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,
			134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
			55,46,245,40,244,102,143,54, 65,25,63,161,1,216,80,73,209,76,132,187,208, 89,
			18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,
			250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
			189,28,42,223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167,
			43,172,9,129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,
			97,228,251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,
			107,49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
			138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180 };
		// Duplicate the permutation vector
		p.insert(p.end(), p.begin(), p.end());
	}

	PerlinNoise::PerlinNoise(unsigned int seed)
	{
		p.resize(256);

		// Fill p with values from 0 to 255
		std::iota(p.begin(), p.end(), 0);

		// Initialize a random engine with seed
		std::default_random_engine engine(seed);

		// Suffle  using the above random engine
		std::shuffle(p.begin(), p.end(), engine);

		// Duplicate the permutation vector
		p.insert(p.end(), p.begin(), p.end());
	}

	double PerlinNoise::noise(double x, double y, double z)
	{
		// Find the unit cube that contains the point
		int X = (int)floor(x) & 255;
		int Y = (int)floor(y) & 255;
		int Z = (int)floor(z) & 255;

		// Find relative x, y,z of point in cube
		x -= floor(x);
		y -= floor(y);
		z -= floor(z);

		// Compute fade curves for each of x, y, z
		double u = fade(x);
		double v = fade(y);
		double w = fade(z);

		// Hash coordinates of the 8 cube corners
		int A = p[X] + Y;
		int AA = p[A] + Z;
		int AB = p[A + 1] + Z;
		int B = p[X + 1] + Y;
		int BA = p[B] + Z;
		int BB = p[B + 1] + Z;

		// Add blended results from 8 corners of cube
		double res = lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z), grad(p[BA], x - 1, y, z)), lerp(u, grad(p[AB], x, y - 1, z), grad(p[BB], x - 1, y - 1, z))), lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1), grad(p[BA + 1], x - 1, y, z - 1)), lerp(u, grad(p[AB + 1], x, y - 1, z - 1), grad(p[BB + 1], x - 1, y - 1, z - 1))));
		return (res + 1.0) / 2.0;
	}

	double PerlinNoise::fade(double t)
	{
		return t * t * t * (t * (t * 6 - 15) + 10);
	}

	double PerlinNoise::lerp(double t, double a, double b)
	{
		return a + t * (b - a);
	}

	double PerlinNoise::grad(int hash, double x, double y, double z)
	{
		int h = hash & 15;
		// Convert lower 4 bits of hash into 12 gradient directions
		double u = h < 8 ? x : y,
			v = h < 4 ? y : h == 12 || h == 14 ? x : z;
		return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
	}

	float Interpolate(float value, float from, float to)
	{
		return std::lerp(from, to, value);
	}

	DirectX::XMFLOAT2 Interpolate(float value, DirectX::XMFLOAT2 from, DirectX::XMFLOAT2 to)
	{
		XMFLOAT2 result;
		result.x = Interpolate(value, from.x, to.x);
		result.y = Interpolate(value, from.y, to.y);
		return result;
	}

	DirectX::XMFLOAT3 Interpolate(float value, DirectX::XMFLOAT3 from, DirectX::XMFLOAT3 to)
	{
		XMFLOAT3 result;
		result.x = Interpolate(value, from.x, to.x);
		result.y = Interpolate(value, from.y, to.y);
		result.z = Interpolate(value, from.z, to.z);
		return result;
	}

	DirectX::XMFLOAT4 Interpolate(float value, DirectX::XMFLOAT4 from, DirectX::XMFLOAT4 to)
	{
		XMFLOAT4 result;
		result.x = Interpolate(value, from.x, to.x);
		result.y = Interpolate(value, from.y, to.y);
		result.z = Interpolate(value, from.z, to.z);
		result.w = Interpolate(value, from.w, to.w);
		return result;
	}

	float GetLerpValue(float value, float from, float to)
	{
		if (from > to)
		{
			float temp = from;
			from = to;
			to = temp;
		}
		if (value < from) return 0.0f;
		if (value > to) return 1.0f;

		return (value - from) / (to - from);
	}

	DirectX::XMFLOAT2 GetLerpValue(float value, DirectX::XMFLOAT2 from, DirectX::XMFLOAT2 to)
	{
		XMFLOAT2 result;
		result.x = GetLerpValue(value, from.x, to.x);
		result.y = GetLerpValue(value, from.y, to.y);
		return result;
	}

	DirectX::XMFLOAT3 GetLerpValue(float value, DirectX::XMFLOAT3 from, DirectX::XMFLOAT3 to)
	{
		XMFLOAT3 result;
		result.x = GetLerpValue(value, from.x, to.x);
		result.y = GetLerpValue(value, from.y, to.y);
		result.z = GetLerpValue(value, from.z, to.z);
		return result;
	}

	DirectX::XMFLOAT4 GetLerpValue(float value, DirectX::XMFLOAT4 from, DirectX::XMFLOAT4 to)
	{
		XMFLOAT4 result;
		result.x = GetLerpValue(value, from.x, to.x);
		result.y = GetLerpValue(value, from.y, to.y);
		result.z = GetLerpValue(value, from.z, to.z);
		result.w = GetLerpValue(value, from.w, to.w);
		return result;
	}

}
