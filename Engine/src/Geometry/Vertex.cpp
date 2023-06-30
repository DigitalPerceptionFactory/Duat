#include "Vertex.h"


namespace Duat::Geometry {

	Vertex::Vertex(float x, float y, float z)
	{
		color = { 1.0f, 0.0f, 0.0f, 1.0f };
		normal = { 0.0f, 1.0f, 0.0f, 0.0f };
		texCoord = { 0.0f, 0.0f, 0.0f, 0.0f };

		position.x = x;
		position.y = y;
		position.z = z;
		position.w = 1.0f;
	}

	Vertex::Vertex(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT4& col)
	{
		normal = { 0.0f, 1.0f, 0.0f, 0.0f };
		texCoord = { 0.0f, 0.0f, 0.0f, 0.0f };

		position.x = pos.x;
		position.y = pos.y;
		position.z = pos.z;
		position.w = 1.0f;
		color.x = col.x;
		color.y = col.y;
		color.z = col.z;
		color.w = col.w;
	}

	Vertex::Vertex(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT2& uv, const DirectX::XMFLOAT4& col)
	{
		normal = { 0.0f, 1.0f, 0.0f, 0.0f };

		position.x = pos.x;
		position.y = pos.y;
		position.z = pos.z;
		position.w = 1.0f;
		color.x = col.x;
		color.y = col.y;
		color.z = col.z;
		color.w = col.w;
		texCoord.x = uv.x;
		texCoord.y = uv.y;
	}

	Vertex::Vertex(const Vertex& ref)
	{
		position = ref.position;
		texCoord = ref.texCoord;
		color = ref.color;
		normal = ref.normal;
	}

	Vertex::Vertex(DirectX::XMVECTOR pos)
	{
		color = { 1.0f, 0.0f, 0.0f, 1.0f };
		normal = { 0.0f, 1.0f, 0.0f, 0.0f };
		texCoord = { 0.0f, 0.0f, 0.0f, 0.0f };

		DirectX::XMStoreFloat4(&position, pos);
		position.w = 1.0f;
	}

	Vertex::Vertex(const DirectX::XMFLOAT3& pos)
	{
		color = { 1.0f, 0.0f, 0.0f, 1.0f };
		normal = { 0.0f, 1.0f, 0.0f, 0.0f };
		texCoord = { 0.0f, 0.0f, 0.0f, 0.0f };

		position.x = pos.x;
		position.y = pos.y;
		position.z = pos.z;
		position.w = 1.0f;
	}

}