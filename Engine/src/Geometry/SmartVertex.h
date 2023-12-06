#pragma once
#include "Transform.h"


struct SmartVertex : public Duat::Geometry::Transform {
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;
	DirectX::XMFLOAT3 origin;
	DirectX::INT3 posRef;
	DirectX::INT3 rotRef;
	DirectX::INT3 scaRef;
};