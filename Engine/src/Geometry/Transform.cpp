#include "Transform.h"


using namespace DirectX;

namespace Duat::Geometry {

	Transform::Transform()
	{
		m_position = { 0,0,0 };
		m_rotation = { 0,0,0 };
		m_scale = { 1,1,1 };
	}

	const DirectX::XMFLOAT3& Transform::GetPosition() const
	{
		return m_position;
	}

	const DirectX::XMFLOAT3& Transform::GetRotation() const
	{
		return m_rotation;
	}

	const DirectX::XMFLOAT3& Transform::GetScale() const
	{
		return m_scale;
	}

	DirectX::XMMATRIX Transform::GetTranslationMatrix() const
	{
		return DirectX::XMMatrixTranslation(m_position);
	}

	DirectX::XMMATRIX Transform::GetRotationMatrix() const
	{
		return DirectX::XMMatrixRotationRollPitchYawDegrees(m_rotation);
	}

	DirectX::XMMATRIX Transform::GetScaleMatrix() const
	{
		return DirectX::XMMatrixScaling(m_scale);
	}

	DirectX::XMMATRIX Transform::GetMatrix() const
	{
		return GetScaleMatrix() * GetRotationMatrix() * GetTranslationMatrix();
	}

	void Transform::SetPosition(const DirectX::XMFLOAT3& position)
	{
		m_position = position;
		TransformFF();
	}

	void Transform::SetPosition(float x, float y, float z)
	{
		SetPosition({ x,y,z });
	}

	void Transform::SetPositionX(float x)
	{
		m_position.x = x;
		TransformFF();
	}

	void Transform::SetPositionY(float y)
	{
		m_position.y = y;
		TransformFF();
	}

	void Transform::SetPositionZ(float z)
	{
		m_position.z = z;
		TransformFF();
	}

	void Transform::SetRotation(const DirectX::XMFLOAT3& rotation)
	{
		m_rotation = rotation;
		TransformFF();
	}

	void Transform::SetRotation(float x, float y, float z)
	{
		SetRotation({ x,y,z });
	}

	void Transform::SetRotationX(float x)
	{
		m_rotation.x = x;
		TransformFF();
	}

	void Transform::SetRotationY(float y)
	{
		m_rotation.y = y;
		TransformFF();
	}

	void Transform::SetRotationZ(float z)
	{
		m_rotation.z = z;
		TransformFF();
	}

	void Transform::SetScale(const DirectX::XMFLOAT3& scale)
	{
		if (scale.x > 0.0f) m_scale.x = scale.x;
		if (scale.y > 0.0f) m_scale.y = scale.y;
		if (scale.z > 0.0f) m_scale.z = scale.z;
		TransformFF();
	}

	void Transform::SetScale(float x, float y, float z)
	{
		SetScale({ x,y,z });
	}

	void Transform::SetScaleX(float x)
	{
		if (x > 0) m_scale.x = x;
		TransformFF();
	}

	void Transform::SetScaleY(float y)
	{
		if (y > 0)m_scale.y = y;
		TransformFF();
	}

	void Transform::SetScaleZ(float z)
	{
		if (z > 0)m_scale.z = z;
		TransformFF();
	}

	void Transform::Translate(const DirectX::XMFLOAT3& delta)
	{
		m_position += XMFloat3Transform(delta, GetRotationMatrix());;
		TransformFF();
	}

	void Transform::Translate(float x, float y, float z)
	{
		Translate({ x,y,z });
	}

	void Transform::TranslateX(float delta)
	{
		m_position += XMFloat3Transform({ delta, 0, 0 }, GetRotationMatrix());;
		TransformFF();
	}

	void Transform::TranslateY(float delta)
	{
		m_position += XMFloat3Transform({ 0, delta, 0 }, GetRotationMatrix());;
		TransformFF();
	}

	void Transform::TranslateZ(float delta)
	{
		m_position += XMFloat3Transform({ 0, 0, delta }, GetRotationMatrix());;
		TransformFF();
	}

	void Transform::PositionAdd(const DirectX::XMFLOAT3& delta)
	{
		m_position += delta;
		TransformFF();
	}

	void Transform::PositionAdd(float x, float y, float z)
	{
		PositionAdd({ x,y,z });
	}

	void Transform::PositionAddX(float delta)
	{
		m_position.x += delta;
		TransformFF();
	}

	void Transform::PositionAddY(float delta)
	{
		m_position.y += delta;
		TransformFF();
	}

	void Transform::PositionAddZ(float delta)
	{
		m_position.z += delta;
		TransformFF();
	}

	void Transform::Rotate(const DirectX::XMFLOAT3& delta)
	{
		m_rotation += delta;
		TransformFF();
	}

	void Transform::Rotate(float x, float y, float z)
	{
		Rotate({ x,y,z });
	}

	void Transform::RotateX(float delta)
	{
		m_rotation.x += delta;
		TransformFF();
	}

	void Transform::RotateY(float delta)
	{
		m_rotation.y += delta;
		TransformFF();
	}

	void Transform::RotateZ(float delta)
	{
		m_rotation.z += delta;
		TransformFF();
	}

	void Transform::Scale(const DirectX::XMFLOAT3& factor)
	{
		if(factor.x > 0) m_scale.x *= factor.x;
		if(factor.y > 0) m_scale.y *= factor.y;
		if(factor.z > 0) m_scale.z *= factor.z;
		TransformFF();
	}

	void Transform::Scale(float x, float y, float z)
	{
		Scale({ x,y,z });
	}

	void Transform::ScaleX(float factor)
	{
		if (factor > 0) m_scale.x *= factor;
		TransformFF();
	}

	void Transform::ScaleY(float factor)
	{
		if (factor > 0) m_scale.y *= factor;
		TransformFF();
	}

	void Transform::ScaleZ(float factor)
	{
		if (factor > 0) m_scale.z *= factor;
		TransformFF();
	}

	void Transform::ScaleAdd(const DirectX::XMFLOAT3& delta)
	{
		XMFLOAT3 predict = m_scale + delta;
		if (predict.x > 0) m_scale.x = predict.x;
		if (predict.y > 0) m_scale.y = predict.y;
		if (predict.z > 0) m_scale.z = predict.z;
		TransformFF();
	}

	void Transform::ScaleAdd(float x, float y, float z)
	{
		ScaleAdd({ x,y,z });
	}

	void Transform::ScaleAddX(float delta)
	{
		float predict = m_scale.x + delta;
		if (predict > 0) m_scale.x = predict;
		TransformFF();
	}

	void Transform::ScaleAddY(float delta)
	{
		float predict = m_scale.y + delta;
		if (predict > 0) m_scale.y = predict;
		TransformFF();
	}

	void Transform::ScaleAddZ(float delta)
	{
		float predict = m_scale.z + delta;
		if (predict > 0) m_scale.z = predict;
		TransformFF();
	}

	void Transform::TransformFF()
	{
	}

}