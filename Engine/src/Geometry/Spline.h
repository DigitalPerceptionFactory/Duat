#pragma once
#include <Utility/DirectX.h>
#include <Utility/Classes.h>


namespace Duat::Geometry {

	struct Bezier_Cubic
	{
		Bezier_Cubic(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b, DirectX::XMFLOAT3 c, DirectX::XMFLOAT3 d);
		void Set(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b, DirectX::XMFLOAT3 c, DirectX::XMFLOAT3 d);
		DirectX::XMFLOAT3 Get(float t) const;
		float GetArcLength() const;
	private:
		void UpdateArcLength();
		float m_arcLength;
		DirectX::XMFLOAT3 a, b, c, d;
	};

	struct Spline
	{
		void Append(Bezier_Cubic segment);
		void Append(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b, DirectX::XMFLOAT3 c, DirectX::XMFLOAT3 d);
		DirectX::XMFLOAT3 Get(float t);
		std::vector<DirectX::XMFLOAT3> Get(size_t pointCount, float from, float to);
	private:
		void Update();
		Utility::ring<Bezier_Cubic> m_segments;
		float m_totalLength;
	};

}