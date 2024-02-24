#define PIXEL_SHADER
#include "DefaultRegisters.hlsli"
#include "BasicFunctions.hlsli"

TextureCube skybox : register(t0);

// Texture2D skybox0 : register(t0);
// Texture2D skybox1 : register(t1);
// Texture2D skybox2 : register(t2);
// Texture2D skybox3 : register(t3);
// Texture2D skybox4 : register(t4);
// Texture2D skybox5 : register(t5);

SamplerState skyboxSS : register(s0);

float4 main(Input i) : SV_TARGET
{
	//return float4(1,1,1,1);
	return skybox.Sample(skyboxSS, i.position);
}