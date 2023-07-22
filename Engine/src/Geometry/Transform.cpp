#include "Transform.h"


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
	}

	void Transform::SetPositionX(float x)
	{
		m_position.x = x;
	}

	void Transform::SetPositionY(float y)
	{
		m_position.y = y;
	}

	void Transform::SetPositionZ(float z)
	{
		m_position.z = z;
	}

	void Transform::SetRotation(const DirectX::XMFLOAT3& rotation)
	{
		m_rotation = rotation;
	}

	void Transform::SetRotationX(float x)
	{
		m_rotation.x = x;
	}

	void Transform::SetRotationY(float y)
	{
		m_rotation.y = y;
	}

	void Transform::SetRotationZ(float z)
	{
		m_rotation.z = z;
	}

	void Transform::SetScale(const DirectX::XMFLOAT3& scale)
	{
		if (scale.x > 0.0f) m_scale.x = scale.x;
		if (scale.y > 0.0f) m_scale.y = scale.y;
		if (scale.z > 0.0f) m_scale.z = scale.z;
	}

	void Transform::SetScaleX(float x)
	{
		if (x > 0) m_scale.x = x;
	}

	void Transform::SetScaleY(float y)
	{
		if (y > 0)m_scale.y = y;
	}

	void Transform::SetScaleZ(float z)
	{
		if (z > 0)m_scale.z = z;
	}

	void Transform::Translate(const DirectX::XMFLOAT3& delta)
	{
		m_position += DirectX::XMFloat3Transform(delta, GetRotationMatrix());;
	}

	void Transform::TranslateX(float delta)
	{
		m_position += DirectX::XMFloat3Transform({ delta, 0, 0 }, GetRotationMatrix());;
	}

	void Transform::TranslateY(float delta)
	{
		m_position += DirectX::XMFloat3Transform({ 0, delta, 0 }, GetRotationMatrix());;
	}

	void Transform::TranslateZ(float delta)
	{
		m_position += DirectX::XMFloat3Transform({ 0, 0, delta }, GetRotationMatrix());;
	}

	void Transform::PositionAdd(const DirectX::XMFLOAT3& delta)
	{
		m_position += delta;
	}

	void Transform::PositionAddX(float delta)
	{
		m_position.x += delta;
	}

	void Transform::PositionAddY(float delta)
	{
		m_position.y += delta;
	}

	void Transform::PositionAddZ(float delta)
	{
		m_position.z += delta;
	}

	void Transform::Rotate(const DirectX::XMFLOAT3& delta)
	{
		m_rotation += delta;
	}

	void Transform::RotateX(float delta)
	{
		m_rotation.x += delta;
	}

	void Transform::RotateY(float delta)
	{
		m_rotation.y += delta;
	}

	void Transform::RotateZ(float delta)
	{
		m_rotation.z += delta;
	}

	void Transform::Scale(const DirectX::XMFLOAT3& factor)
	{
		if(factor.x > 0) m_scale.x *= factor.x;
		if(factor.y > 0) m_scale.y *= factor.y;
		if(factor.z > 0) m_scale.z *= factor.z;
	}

	void Transform::ScaleX(float factor)
	{
		if (factor > 0) m_scale.x *= factor;
	}

	void Transform::ScaleY(float factor)
	{
		if (factor > 0) m_scale.y *= factor;
	}

	void Transform::ScaleZ(float factor)
	{
		if (factor > 0) m_scale.z *= factor;
	}

	void Transform::ScaleAdd(const DirectX::XMFLOAT3& delta)
	{
		DirectX::XMFLOAT3 predict = m_scale + delta;
		if (predict.x > 0) m_scale.x = predict.x;
		if (predict.y > 0) m_scale.y = predict.y;
		if (predict.z > 0) m_scale.z = predict.z;
	}

	void Transform::ScaleAddX(float delta)
	{
		float predict = m_scale.x + delta;
		if (predict > 0) m_scale.x = predict;
	}

	void Transform::ScaleAddY(float delta)
	{
		float predict = m_scale.y + delta;
		if (predict > 0) m_scale.y = predict;
	}

	void Transform::ScaleAddZ(float delta)
	{
		float predict = m_scale.z + delta;
		if (predict > 0) m_scale.z = predict;
	}

}