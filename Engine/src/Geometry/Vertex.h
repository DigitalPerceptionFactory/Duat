#pragma once
#include <DirectXMath.h>


namespace Duat::Geometry {

	struct Vertex {
		Vertex() = default;
		Vertex(float x, float y, float z);
		Vertex(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT4& col);
		Vertex(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT2& uv, const DirectX::XMFLOAT4& col);
		Vertex(const Vertex& ref);
		Vertex(DirectX::XMVECTOR pos);
		Vertex(const DirectX::XMFLOAT3& pos);

		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texCoord;
		DirectX::XMFLOAT4 color;
		DirectX::XMFLOAT3 normal;
	};

}