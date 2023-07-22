#pragma once
#include <Utility/DirectX.h>


struct SmartVertex {
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;
	DirectX::XMFLOAT3 origin;
	DirectX::INT3 posRef;
	DirectX::INT3 rotRef;
	DirectX::INT3 scaRef;
};