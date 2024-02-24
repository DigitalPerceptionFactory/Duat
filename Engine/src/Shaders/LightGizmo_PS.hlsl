#define PIXEL_SHADER
#include "DefaultRegisters.hlsli"
#include "MathConstants.hlsli"


float4 main(Input i) : SV_TARGET
{
	float x = i.uv.x - 0.5f;
	float y = i.uv.y - 0.5f;
	float r = sqrt(x * x + y * y);
	if (r < 0.5) return float4(1, 1, 1, 1);
	return float4(0, 0, 0, 0);
}
#undef PIXEL_SHADER