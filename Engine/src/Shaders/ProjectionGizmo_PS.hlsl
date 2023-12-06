#define PIXEL_SHADER
#include "DefaultBuffer.hlsli"

float4 main(Input i) : SV_TARGET
{
	return float4(1,1,1,1);
}
#undef PIXEL_SHADER