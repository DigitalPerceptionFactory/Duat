#define PIXEL_SHADER
#include "DefaultBuffer.hlsli"
#include "BasicFunctions.hlsli"

TextureCube skybox : register(t0);
SamplerState skyboxSS : register(s0);

float4 main(Input i) : SV_TARGET
{
	//return float4(1,1,1,1);
	return skybox.Sample(skyboxSS, i.position);
}