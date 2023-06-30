#pragma once
#include <numeric>
#include <random>
#include <algorithm>
#include <vector>
#include <cmath>
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include "DX_INT2.h"
#include "DX_INT3.h"
#include "DX_INT4.h"
#include "DX_BOOL2.h"
#include "DX_BOOL3.h"
#include "DX_BOOL4.h"
#include <Geometry/Vertex.h>
#include <Utility/ErrorHandling.h>


namespace DirectX {

	XMFLOAT2 XMFloat2Floor(const XMFLOAT2& value, INT2 digits = 0);
	XMFLOAT3 XMFloat3Floor(const XMFLOAT3& value, INT3 digits = 0);
	XMFLOAT4 XMFloat4Floor(const XMFLOAT4& value, INT4 digits = 0);

	float XMVectorLength(const XMFLOAT4& vector);
	float XMVectorLength(const XMFLOAT3& vector);
	float XMVectorLength(const XMFLOAT2& vector);

	XMFLOAT2 XMFloat2Min(const XMFLOAT2& a, float b);
	XMFLOAT2 XMFloat2Min(const XMFLOAT2& a, const XMFLOAT2& b);
	XMFLOAT2 XMFloat2Min(const XMFLOAT2& a, const XMFLOAT3& b);
	XMFLOAT2 XMFloat2Min(const XMFLOAT2& a, const XMFLOAT4& b);

	XMFLOAT2 XMFloat2Max(const XMFLOAT2& a, float b);
	XMFLOAT2 XMFloat2Max(const XMFLOAT2& a, const XMFLOAT2& b);
	XMFLOAT2 XMFloat2Max(const XMFLOAT2& a, const XMFLOAT3& b);
	XMFLOAT2 XMFloat2Max(const XMFLOAT2& a, const XMFLOAT4& b);

	XMFLOAT3 XMFloat3Min(const XMFLOAT3& a, float b);
	XMFLOAT3 XMFloat3Min(const XMFLOAT3& a, const XMFLOAT2& b);
	XMFLOAT3 XMFloat3Min(const XMFLOAT3& a, const XMFLOAT3& b);
	XMFLOAT3 XMFloat3Min(const XMFLOAT3& a, const XMFLOAT4& b);

	XMFLOAT3 XMFloat3Max(const XMFLOAT3& a, float b);
	XMFLOAT3 XMFloat3Max(const XMFLOAT3& a, const XMFLOAT2& b);
	XMFLOAT3 XMFloat3Max(const XMFLOAT3& a, const XMFLOAT3& b);
	XMFLOAT3 XMFloat3Max(const XMFLOAT3& a, const XMFLOAT4& b);

	XMFLOAT4 XMFloat4Min(const XMFLOAT4& a, float b);
	XMFLOAT4 XMFloat4Min(const XMFLOAT4& a, const XMFLOAT2& b);
	XMFLOAT4 XMFloat4Min(const XMFLOAT4& a, const XMFLOAT3& b);
	XMFLOAT4 XMFloat4Min(const XMFLOAT4& a, const XMFLOAT4& b);

	XMFLOAT4 XMFloat4Max(const XMFLOAT4& a, float b);
	XMFLOAT4 XMFloat4Max(const XMFLOAT4& a, const XMFLOAT2& b);
	XMFLOAT4 XMFloat4Max(const XMFLOAT4& a, const XMFLOAT3& b);
	XMFLOAT4 XMFloat4Max(const XMFLOAT4& a, const XMFLOAT4& b);

	XMFLOAT2 XMFloat2Abs(XMFLOAT2 f2);
	XMFLOAT3 XMFloat3Abs(XMFLOAT3 f3);
	XMFLOAT4 XMFloat4Abs(XMFLOAT4 f4);


	float XMLerp(float from, float to, float t);

	XMFLOAT4 XMVectorLerp(const XMFLOAT4& v, float t);
	XMFLOAT4 XMVectorLerp(const XMFLOAT4& from, const XMFLOAT4& to, float t);
	XMFLOAT4 XMVectorLerp(const XMFLOAT4& from, const XMFLOAT3& to, float t);
	XMFLOAT4 XMVectorLerp(const XMFLOAT4& from, const XMFLOAT2& to, float t);

	XMFLOAT3 XMVectorLerp(const XMFLOAT3& v, float t);
	XMFLOAT3 XMVectorLerp(const XMFLOAT3& from, const XMFLOAT4& to, float t);
	XMFLOAT3 XMVectorLerp(const XMFLOAT3& from, const XMFLOAT3& to, float t);
	XMFLOAT3 XMVectorLerp(const XMFLOAT3& from, const XMFLOAT2& to, float t);

	XMFLOAT2 XMVectorLerp(const XMFLOAT2& v, float t);
	XMFLOAT2 XMVectorLerp(const XMFLOAT2& from, const XMFLOAT4& to, float t);
	XMFLOAT2 XMVectorLerp(const XMFLOAT2& from, const XMFLOAT3& to, float t);
	XMFLOAT2 XMVectorLerp(const XMFLOAT2& from, const XMFLOAT2& to, float t);

	float XMInverseLerp(float from, float to, float value);

	XMMATRIX XMCreateMatrix(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale);

	XMMATRIX XMMatrixTranslation(XMFLOAT3 xyz);

	XMMATRIX XMMatrixScaling(XMFLOAT3 xyz);

	XMMATRIX XMMatrixRotationRollPitchYawDegrees(float x, float y, float z);
	XMMATRIX XMMatrixRotationRollPitchYawDegrees(XMFLOAT3 euler);
	XMMATRIX XMMatrixRotationRollPitchYawDegrees(XMVECTOR euler);

	XMFLOAT3 XMFloat3Transform(XMFLOAT3 f3, XMMATRIX m);
	XMFLOAT4 XMFloat4Transform(XMFLOAT4 f4, XMMATRIX m);

	XMFLOAT3 XMFloat3Normalize(XMFLOAT3 f3);
	XMFLOAT4 XMFloat4Normalize(XMFLOAT4 f4);

	XMFLOAT3 XMFloat3Lerp(XMFLOAT3 from, XMFLOAT3 to, float lerp);
	XMFLOAT4 XMFloat4Lerp(XMFLOAT4 from, XMFLOAT4 to, float lerp);

	XMFLOAT3 XMFloat3Cross(XMFLOAT3 a, XMFLOAT3 b);
	XMFLOAT4 XMFloat4Cross(XMFLOAT4 a, XMFLOAT4 b);

	XMMATRIX XMMatrixLookAtLH(XMFLOAT3 eye, XMFLOAT3 focus, XMFLOAT3 up);
	XMMATRIX XMMatrixLookAtLH(XMFLOAT4 eye, XMFLOAT4 focus, XMFLOAT4 up);

	void XMAssign(XMFLOAT4& destination, const XMFLOAT3& source);
	void XMAssign(XMFLOAT4& destination, const XMFLOAT2& source);

	void XMAssign(XMFLOAT3& destination, const XMFLOAT4& source);
	void XMAssign(XMFLOAT3& destination, const XMFLOAT2& source);

	void XMAssign(XMFLOAT2& destination, const XMFLOAT4& source);
	void XMAssign(XMFLOAT2& destination, const XMFLOAT3& source);

	bool operator==(const XMFLOAT4& lhs, const XMFLOAT4& rhs);
	bool operator!=(const XMFLOAT4& lhs, const XMFLOAT4& rhs);
	bool operator==(const XMFLOAT3& lhs, const XMFLOAT3& rhs);
	bool operator!=(const XMFLOAT3& lhs, const XMFLOAT3& rhs);

	XMFLOAT4 operator+(const XMFLOAT4& lhs, const XMFLOAT4& rhs);
	XMFLOAT4 operator-(const XMFLOAT4& lhs, const XMFLOAT4& rhs);
	XMFLOAT4 operator+(const XMFLOAT4& lhs, const XMFLOAT3& rhs);
	XMFLOAT4 operator-(const XMFLOAT4& lhs, const XMFLOAT3& rhs);
	XMFLOAT4 operator+(const XMFLOAT4& lhs, const XMFLOAT2& rhs);
	XMFLOAT4 operator-(const XMFLOAT4& lhs, const XMFLOAT2& rhs);
	XMFLOAT4 operator+=(XMFLOAT4& lhs, const XMFLOAT4& rhs);
	XMFLOAT4 operator-=(XMFLOAT4& lhs, const XMFLOAT4& rhs);
	XMFLOAT4 operator+=(XMFLOAT4& lhs, const XMFLOAT3& rhs);
	XMFLOAT4 operator-=(XMFLOAT4& lhs, const XMFLOAT3& rhs);
	XMFLOAT4 operator+=(XMFLOAT4& lhs, const XMFLOAT2& rhs);
	XMFLOAT4 operator-=(XMFLOAT4& lhs, const XMFLOAT2& rhs);


	XMFLOAT3 operator+(const XMFLOAT3& lhs, const XMFLOAT3& rhs);
	XMFLOAT3 operator-(const XMFLOAT3& lhs, const XMFLOAT3& rhs);
	XMFLOAT3 operator+(const XMFLOAT3& lhs, const XMFLOAT4& rhs);
	XMFLOAT3 operator-(const XMFLOAT3& lhs, const XMFLOAT4& rhs);
	XMFLOAT3 operator+(const XMFLOAT3& lhs, const XMFLOAT2& rhs);
	XMFLOAT3 operator-(const XMFLOAT3& lhs, const XMFLOAT2& rhs);
	XMFLOAT3 operator+=(XMFLOAT3& lhs, const XMFLOAT3& rhs);
	XMFLOAT3 operator-=(XMFLOAT3& lhs, const XMFLOAT3& rhs);
	XMFLOAT3 operator+=(XMFLOAT3& lhs, const XMFLOAT4& rhs);
	XMFLOAT3 operator-=(XMFLOAT3& lhs, const XMFLOAT4& rhs);
	XMFLOAT3 operator+=(XMFLOAT3& lhs, const XMFLOAT2& rhs);
	XMFLOAT3 operator-=(XMFLOAT3& lhs, const XMFLOAT2& rhs);


	XMFLOAT2 operator+(const XMFLOAT2& lhs, const XMFLOAT2& rhs);
	XMFLOAT2 operator-(const XMFLOAT2& lhs, const XMFLOAT2& rhs);
	XMFLOAT2 operator+(const XMFLOAT2& lhs, const XMFLOAT4& rhs);
	XMFLOAT2 operator-(const XMFLOAT2& lhs, const XMFLOAT4& rhs);
	XMFLOAT2 operator+(const XMFLOAT2& lhs, const XMFLOAT3& rhs);
	XMFLOAT2 operator-(const XMFLOAT2& lhs, const XMFLOAT3& rhs);
	XMFLOAT2 operator+=(XMFLOAT2& lhs, const XMFLOAT2& rhs);
	XMFLOAT2 operator-=(XMFLOAT2& lhs, const XMFLOAT2& rhs);
	XMFLOAT2 operator+=(XMFLOAT2& lhs, const XMFLOAT4& rhs);
	XMFLOAT2 operator-=(XMFLOAT2& lhs, const XMFLOAT4& rhs);
	XMFLOAT2 operator+=(XMFLOAT2& lhs, const XMFLOAT3& rhs);
	XMFLOAT2 operator-=(XMFLOAT2& lhs, const XMFLOAT3& rhs);

	XMFLOAT2 operator+(const XMFLOAT2& lhs, float rhs);
	XMFLOAT2 operator-(const XMFLOAT2& lhs, float rhs);
	XMFLOAT3 operator+(const XMFLOAT3& lhs, float rhs);
	XMFLOAT3 operator-(const XMFLOAT3& lhs, float rhs);
	XMFLOAT4 operator+(const XMFLOAT4& lhs, float rhs);
	XMFLOAT4 operator-(const XMFLOAT4& lhs, float rhs);
	XMFLOAT2 operator+=(XMFLOAT2& lhs, float rhs);
	XMFLOAT2 operator-=(XMFLOAT2& lhs, float rhs);
	XMFLOAT3 operator+=(XMFLOAT3& lhs, float rhs);
	XMFLOAT3 operator-=(XMFLOAT3& lhs, float rhs);
	XMFLOAT4 operator+=(XMFLOAT4& lhs, float rhs);
	XMFLOAT4 operator-=(XMFLOAT4& lhs, float rhs);



	XMFLOAT4 operator*(const XMFLOAT4& lhs, const XMFLOAT4& rhs);
	XMFLOAT4 operator/(const XMFLOAT4& lhs, const XMFLOAT4& rhs);
	XMFLOAT4 operator*(const XMFLOAT4& lhs, const XMFLOAT3& rhs);
	XMFLOAT4 operator/(const XMFLOAT4& lhs, const XMFLOAT3& rhs);
	XMFLOAT4 operator*(const XMFLOAT4& lhs, const XMFLOAT2& rhs);
	XMFLOAT4 operator/(const XMFLOAT4& lhs, const XMFLOAT2& rhs);
	XMFLOAT4 operator*=(XMFLOAT4& lhs, const XMFLOAT4& rhs);
	XMFLOAT4 operator/=(XMFLOAT4& lhs, const XMFLOAT4& rhs);
	XMFLOAT4 operator*=(XMFLOAT4& lhs, const XMFLOAT3& rhs);
	XMFLOAT4 operator/=(XMFLOAT4& lhs, const XMFLOAT3& rhs);
	XMFLOAT4 operator*=(XMFLOAT4& lhs, const XMFLOAT2& rhs);
	XMFLOAT4 operator/=(XMFLOAT4& lhs, const XMFLOAT2& rhs);

	XMFLOAT3 operator*(const XMFLOAT3& lhs, const XMFLOAT3& rhs);
	XMFLOAT3 operator/(const XMFLOAT3& lhs, const XMFLOAT3& rhs);
	XMFLOAT3 operator*(const XMFLOAT3& lhs, const XMFLOAT4& rhs);
	XMFLOAT3 operator/(const XMFLOAT3& lhs, const XMFLOAT4& rhs);
	XMFLOAT3 operator*(const XMFLOAT3& lhs, const XMFLOAT2& rhs);
	XMFLOAT3 operator/(const XMFLOAT3& lhs, const XMFLOAT2& rhs);
	XMFLOAT3 operator*=(XMFLOAT3& lhs, const XMFLOAT3& rhs);
	XMFLOAT3 operator/=(XMFLOAT3& lhs, const XMFLOAT3& rhs);
	XMFLOAT3 operator*=(XMFLOAT3& lhs, const XMFLOAT4& rhs);
	XMFLOAT3 operator/=(XMFLOAT3& lhs, const XMFLOAT4& rhs);
	XMFLOAT3 operator*=(XMFLOAT3& lhs, const XMFLOAT2& rhs);
	XMFLOAT3 operator/=(XMFLOAT3& lhs, const XMFLOAT2& rhs);

	XMFLOAT2 operator*(const XMFLOAT2& lhs, const XMFLOAT2& rhs);
	XMFLOAT2 operator/(const XMFLOAT2& lhs, const XMFLOAT2& rhs);
	XMFLOAT2 operator*(const XMFLOAT2& lhs, const XMFLOAT4& rhs);
	XMFLOAT2 operator/(const XMFLOAT2& lhs, const XMFLOAT4& rhs);
	XMFLOAT2 operator*(const XMFLOAT2& lhs, const XMFLOAT3& rhs);
	XMFLOAT2 operator/(const XMFLOAT2& lhs, const XMFLOAT3& rhs);
	XMFLOAT2 operator*=(XMFLOAT2& lhs, const XMFLOAT2& rhs);
	XMFLOAT2 operator/=(XMFLOAT2& lhs, const XMFLOAT2& rhs);
	XMFLOAT2 operator*=(XMFLOAT2& lhs, const XMFLOAT4& rhs);
	XMFLOAT2 operator/=(XMFLOAT2& lhs, const XMFLOAT4& rhs);
	XMFLOAT2 operator*=(XMFLOAT2& lhs, const XMFLOAT3& rhs);
	XMFLOAT2 operator/=(XMFLOAT2& lhs, const XMFLOAT3& rhs);

	XMFLOAT2 operator*(const XMFLOAT2& lhs, float rhs);
	XMFLOAT2 operator/(const XMFLOAT2& lhs, float rhs);
	XMFLOAT3 operator*(const XMFLOAT3& lhs, float rhs);
	XMFLOAT3 operator/(const XMFLOAT3& lhs, float rhs);
	XMFLOAT4 operator*(const XMFLOAT4& lhs, float rhs);
	XMFLOAT4 operator/(const XMFLOAT4& lhs, float rhs);
	XMFLOAT2 operator*=(XMFLOAT2& lhs, float rhs);
	XMFLOAT2 operator/=(XMFLOAT2& lhs, float rhs);
	XMFLOAT3 operator*=(XMFLOAT3& lhs, float rhs);
	XMFLOAT3 operator/=(XMFLOAT3& lhs, float rhs);
	XMFLOAT4 operator*=(XMFLOAT4& lhs, float rhs);
	XMFLOAT4 operator/=(XMFLOAT4& lhs, float rhs);
}

namespace Duat::Math {

	float PHI(int exp);
	float phi(int exp);

	std::pair<std::vector<Geometry::Vertex>, std::vector<unsigned int>> MeshFusion(
		std::vector<std::vector<Geometry::Vertex>>& vList, std::vector<std::vector<unsigned int>>& iList);

	void CalculateNormals(std::vector<Geometry::Vertex>& vertices, std::vector<unsigned int>& indices);

	DirectX::XMFLOAT3 Centroid(const std::vector<Geometry::Vertex>& vertices);

	class PerlinNoise {
		std::vector<int> p;
	public:
		PerlinNoise();
		PerlinNoise(unsigned int seed);
		double noise(double x, double y, double z);
	private:
		double fade(double t);
		double lerp(double t, double a, double b);
		double grad(int hash, double x, double y, double z);
	};


	float Interpolate(float value, float from, float to);
	DirectX::XMFLOAT2 Interpolate(float value, DirectX::XMFLOAT2 from, DirectX::XMFLOAT2 to);
	DirectX::XMFLOAT3 Interpolate(float value, DirectX::XMFLOAT3 from, DirectX::XMFLOAT3 to);
	DirectX::XMFLOAT4 Interpolate(float value, DirectX::XMFLOAT4 from, DirectX::XMFLOAT4 to);

	float GetLerpValue(float value, float from, float to);
	DirectX::XMFLOAT2 GetLerpValue(float value, DirectX::XMFLOAT2 from, DirectX::XMFLOAT2 to);
	DirectX::XMFLOAT3 GetLerpValue(float value, DirectX::XMFLOAT3 from, DirectX::XMFLOAT3 to);
	DirectX::XMFLOAT4 GetLerpValue(float value, DirectX::XMFLOAT4 from, DirectX::XMFLOAT4 to);

}