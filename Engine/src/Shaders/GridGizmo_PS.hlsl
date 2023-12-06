#define PIXEL_SHADER
#include "DefaultBuffer.hlsli"
#include "MathConstants.hlsli"


float4 main(Input i) : SV_TARGET
{
	float x = i.uv.x - 0.5f;
	float y = i.uv.y - 0.5f;
	float r = sqrt(x * x + y * y);

	int fraX = i.uv.x * 1000;
	int fraY = i.uv.y * 1000;

	if (fraX % 30 && fraY % 30) {

		return float4(0, 0, 0, 0);
	}
	if(r < 0.45) return float4(1, 1, 1, 1 - 2*r);
	
	return float4(0, 0, 0, 0);
}
#undef PIXEL_SHADER