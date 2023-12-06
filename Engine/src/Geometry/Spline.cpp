#include "Spline.h"


using namespace DirectX;

namespace Duat::Geometry {


	Bezier_Cubic::Bezier_Cubic(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b, DirectX::XMFLOAT3 c, DirectX::XMFLOAT3 d)
	{
		Set(a, b, c, d);
	}

	void Bezier_Cubic::Set(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b, DirectX::XMFLOAT3 c, DirectX::XMFLOAT3 d)
	{
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
		UpdateArcLength();
	}

	DirectX::XMFLOAT3 Bezier_Cubic::Get(float t) const
	{
		XMFLOAT3 ab = XMVectorLerp(a, b, t);
		XMFLOAT3 bc = XMVectorLerp(b, c, t);
		XMFLOAT3 cd = XMVectorLerp(c, d, t);

		XMFLOAT3 ab_bc = XMVectorLerp(ab, bc, t);
		XMFLOAT3 bc_cd = XMVectorLerp(bc, cd, t);

		return XMVectorLerp(ab_bc, bc_cd, t);
	}

	float Bezier_Cubic::GetArcLength() const
	{
		return m_arcLength;
	}

	void Bezier_Cubic::UpdateArcLength()
	{
		m_arcLength = 0.0f;
		for (int i = 0; i < 1000; ++i)
		{
			XMFLOAT3 current = Get((float)i / 1000.0f);
			XMFLOAT3 next = Get((float)(i + 1) / 1000.0f);
			XMFLOAT3 step = next - current;
			XMFLOAT3 magnitude;
			XMStoreFloat3(&magnitude, XMVector3Length(XMLoadFloat3(&step)));
			m_arcLength += magnitude.x;
		}
	}

	void Spline::Append(Bezier_Cubic segment)
	{
		m_segments.push_back(segment);
		Update();
	}

	void Spline::Append(DirectX::XMFLOAT3 a, DirectX::XMFLOAT3 b, DirectX::XMFLOAT3 c, DirectX::XMFLOAT3 d)
	{
		m_segments.push_back(Bezier_Cubic(a, b, c, d));
		Update();
	}

	DirectX::XMFLOAT3 Spline::Get(float t)
	{
		t = std::clamp(t, 0.0f, 1.0f);

		float accLength = 0.0f;
		for (auto& seg : m_segments)
		{
			accLength += seg.GetArcLength();
			float ratio = accLength / m_totalLength;
			if (ratio >= t)
			{
				t -= (accLength - seg.GetArcLength()) / m_totalLength;
				return seg.Get(t * seg.GetArcLength() / m_totalLength);
			}
		}

		return { 0,0,0 };
	}

	std::vector<DirectX::XMFLOAT3> Spline::Get(size_t pointCount, float from, float to)
	{
		// function needs optimization
		std::vector<DirectX::XMFLOAT3> out;
		float tick = (to - from) / (float)pointCount;
		for (float i = from; i <= to; i += tick)
			out.push_back(Get(i));
		return out;
	}

	void Spline::Update()
	{
		m_totalLength = 0.0f;
		for (auto& seg : m_segments)
			m_totalLength += seg.GetArcLength();
	}

}