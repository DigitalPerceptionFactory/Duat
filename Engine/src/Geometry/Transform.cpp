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
		AfterTransform();
	}

	void Transform::SetPosition(float x, float y, float z)
	{
		SetPosition({ x,y,z });
	}

	void Transform::SetPositionX(float x)
	{
		m_position.x = x;
		AfterTransform();
	}

	void Transform::SetPositionY(float y)
	{
		m_position.y = y;
		AfterTransform();
	}

	void Transform::SetPositionZ(float z)
	{
		m_position.z = z;
		AfterTransform();
	}

	void Transform::SetRotation(const DirectX::XMFLOAT3& rotation)
	{
		m_rotation = rotation;
		AfterTransform();
	}

	void Transform::SetRotation(float x, float y, float z)
	{
		SetRotation({ x,y,z });
	}

	void Transform::SetRotationX(float x)
	{
		m_rotation.x = x;
		AfterTransform();
	}

	void Transform::SetRotationY(float y)
	{
		m_rotation.y = y;
		AfterTransform();
	}

	void Transform::SetRotationZ(float z)
	{
		m_rotation.z = z;
		AfterTransform();
	}

	void Transform::SetScale(const DirectX::XMFLOAT3& scale)
	{
		if (scale.x > 0.0f) m_scale.x = scale.x;
		if (scale.y > 0.0f) m_scale.y = scale.y;
		if (scale.z > 0.0f) m_scale.z = scale.z;
		AfterTransform();
	}

	void Transform::SetScale(float x, float y, float z)
	{
		SetScale({ x,y,z });
	}

	void Transform::SetScaleX(float x)
	{
		if (x > 0) m_scale.x = x;
		AfterTransform();
	}

	void Transform::SetScaleY(float y)
	{
		if (y > 0)m_scale.y = y;
		AfterTransform();
	}

	void Transform::SetScaleZ(float z)
	{
		if (z > 0)m_scale.z = z;
		AfterTransform();
	}

	void Transform::Translate(const DirectX::XMFLOAT3& delta)
	{
		m_position += XMFloat3Transform(delta, GetRotationMatrix());;
		AfterTransform();
	}

	void Transform::Translate(float x, float y, float z)
	{
		Translate({ x,y,z });
	}

	void Transform::TranslateX(float delta)
	{
		m_position += XMFloat3Transform({ delta, 0, 0 }, GetRotationMatrix());;
		AfterTransform();
	}

	void Transform::TranslateY(float delta)
	{
		m_position += XMFloat3Transform({ 0, delta, 0 }, GetRotationMatrix());;
		AfterTransform();
	}

	void Transform::TranslateZ(float delta)
	{
		m_position += XMFloat3Transform({ 0, 0, delta }, GetRotationMatrix());;
		AfterTransform();
	}

	void Transform::PositionAdd(const DirectX::XMFLOAT3& delta)
	{
		m_position += delta;
		AfterTransform();
	}

	void Transform::PositionAdd(float x, float y, float z)
	{
		PositionAdd({ x,y,z });
	}

	void Transform::PositionAddX(float delta)
	{
		m_position.x += delta;
		AfterTransform();
	}

	void Transform::PositionAddY(float delta)
	{
		m_position.y += delta;
		AfterTransform();
	}

	void Transform::PositionAddZ(float delta)
	{
		m_position.z += delta;
		AfterTransform();
	}

	void Transform::Rotate(const DirectX::XMFLOAT3& delta)
	{
		m_rotation += delta;
		AfterTransform();
	}

	void Transform::Rotate(float x, float y, float z)
	{
		Rotate({ x,y,z });
	}

	void Transform::RotateX(float delta)
	{
		m_rotation.x += delta;
		AfterTransform();
	}

	void Transform::RotateY(float delta)
	{
		m_rotation.y += delta;
		AfterTransform();
	}

	void Transform::RotateZ(float delta)
	{
		m_rotation.z += delta;
		AfterTransform();
	}

	void Transform::Scale(const DirectX::XMFLOAT3& factor)
	{
		if(factor.x > 0) m_scale.x *= factor.x;
		if(factor.y > 0) m_scale.y *= factor.y;
		if(factor.z > 0) m_scale.z *= factor.z;
		AfterTransform();
	}

	void Transform::Scale(float x, float y, float z)
	{
		Scale({ x,y,z });
	}

	void Transform::ScaleX(float factor)
	{
		if (factor > 0) m_scale.x *= factor;
		AfterTransform();
	}

	void Transform::ScaleY(float factor)
	{
		if (factor > 0) m_scale.y *= factor;
		AfterTransform();
	}

	void Transform::ScaleZ(float factor)
	{
		if (factor > 0) m_scale.z *= factor;
		AfterTransform();
	}

	void Transform::ScaleAdd(const DirectX::XMFLOAT3& delta)
	{
		XMFLOAT3 predict = m_scale + delta;
		if (predict.x > 0) m_scale.x = predict.x;
		if (predict.y > 0) m_scale.y = predict.y;
		if (predict.z > 0) m_scale.z = predict.z;
		AfterTransform();
	}

	void Transform::ScaleAdd(float x, float y, float z)
	{
		ScaleAdd({ x,y,z });
	}

	void Transform::ScaleAddX(float delta)
	{
		float predict = m_scale.x + delta;
		if (predict > 0) m_scale.x = predict;
		AfterTransform();
	}

	void Transform::ScaleAddY(float delta)
	{
		float predict = m_scale.y + delta;
		if (predict > 0) m_scale.y = predict;
		AfterTransform();
	}

	void Transform::ScaleAddZ(float delta)
	{
		float predict = m_scale.z + delta;
		if (predict > 0) m_scale.z = predict;
		AfterTransform();
	}

	void Transform::AfterTransform()
	{
	}

}