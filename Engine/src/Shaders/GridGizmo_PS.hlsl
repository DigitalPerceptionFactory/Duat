#define PIXEL_SHADER
#include "DefaultRegisters.hlsli"
#include "MathConstants.hlsli"


float4 main(Input i) : SV_TARGET
{
	float4 final;
	float x = i.uv.x - 0.5f;
	float y = i.uv.y - 0.5f;
	float r = sqrt(x * x + y * y);

	for (int j = 0; j < 50; ++j)
	{
		if (i.uv.x > 1.0f) i.uv.x -= 1.0f;
		else break;
	}

	for (int j = 0; j < 50; ++j)
	{
		if (i.uv.y > 1.0f) i.uv.y -= 1.0f;
		else break;
	}

	float thickness = 0.01;
	if (i.uv.x < thickness || 1 - i.uv.x < thickness || i.uv.y < thickness || 1 - i.uv.y < thickness)
		final = float4(1, 1, 1, 1);
	else final = float4(0, 0, 0, 0);
		
	return final;

	int fraX = i.uv.x * 1000;
	int fraY = i.uv.y * 1000;

	if (fraX % 30 && fraY % 30) {

		return float4(0, 0, 0, 0);
	}
	if (r < 0.45) return float4(1, 1, 1, 1 - 2 * r);

	return float4(0, 0, 0, 0);
}
#undef PIXEL_SHADER