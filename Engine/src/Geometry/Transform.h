#pragma once
#include <Utility/DirectX.h>


namespace Duat::Geometry {

	struct Transform {
		Transform();

		const DirectX::XMFLOAT3& GetPosition() const;
		const DirectX::XMFLOAT3& GetRotation() const;
		const DirectX::XMFLOAT3& GetScale() const;
		DirectX::XMMATRIX GetTranslationMatrix() const;
		DirectX::XMMATRIX GetRotationMatrix() const;
		DirectX::XMMATRIX GetScaleMatrix() const;
		DirectX::XMMATRIX GetMatrix() const;

		void SetPosition(const DirectX::XMFLOAT3& position);
		void SetPositionX(float x);
		void SetPositionY(float y);
		void SetPositionZ(float z);
		void SetRotation(const DirectX::XMFLOAT3& rotation);
		void SetRotationX(float x);
		void SetRotationY(float y);
		void SetRotationZ(float z);
		void SetScale(const DirectX::XMFLOAT3& scale);
		void SetScaleX(float x);
		void SetScaleY(float y);
		void SetScaleZ(float z);

		void Translate(const DirectX::XMFLOAT3& delta);
		void TranslateX(float delta);
		void TranslateY(float delta);
		void TranslateZ(float delta);
		void PositionAdd(const DirectX::XMFLOAT3& delta);
		void PositionAddX(float delta);
		void PositionAddY(float delta);
		void PositionAddZ(float delta);
		void Rotate(const DirectX::XMFLOAT3& delta);
		void RotateX(float delta);
		void RotateY(float delta);
		void RotateZ(float delta);
		void Scale(const DirectX::XMFLOAT3& factor);
		void ScaleX(float factor);
		void ScaleY(float factor);
		void ScaleZ(float factor);
		void ScaleAdd(const DirectX::XMFLOAT3& delta);
		void ScaleAddX(float delta);
		void ScaleAddY(float delta);
		void ScaleAddZ(float delta);

	private:
		DirectX::XMFLOAT3 m_position;
		DirectX::XMFLOAT3 m_rotation;
		DirectX::XMFLOAT3 m_scale;
	};

}