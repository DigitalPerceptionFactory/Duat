#define PIXEL_SHADER
#include "BasicBuffers.hlsli"
#include "BasicFunctions.hlsli"

Texture2D tex : register(t3);
//Texture2D normalMap : register(t4);
SamplerState state : register(s1);

float4 main(Input i, uint id : SV_InstanceID) : SV_TARGET
{
    i.uv.y = 1 - i.uv.y;
    float4 normalVector = i.normal;
    
    //float3 zero = float3(0, 0, 0);
    float3 ambient = float3(0.1618, 0.1618, 0.1618);
    float3 final = tex.Sample(state, float2(i.uv.x, i.uv.y)).rgb;
    if (final.r == 0 && final.g == 0 && final.b == 0)
        return TransparentWindowBiasCorrection(float4(1, 0, 0, 0));
    else
        return TransparentWindowBiasCorrection(float4(final.rgb, 1));
    
    
    final *= ambient;
    
    for (int it = 1; it < DPF::lights[0].type; ++it)
    {
        if (DPF::lights[it].type == 0) // directional
        {
            final +=
			(
			   DPF::lights[it].color
			   * max(dot(normalVector.rgb, normalize(DPF::lights[it].position.rgb)), 0)
			) * DPF::lights[it].intensity;
            //final += Specular(20, 100, normalVector, lights[it].position, i.eye);
        }
        else if (DPF::lights[it].type == 1) // point
        {
            return float4(1, 1, 1, 1);
        }
        else if (DPF::lights[it].type == 1) // spot
        {
            return float4(1, 1, 1, 1);
        }

    }
    return TransparentWindowBiasCorrection(float4(final.rgb, 1));
    
    float3 texColor = tex.Sample(state, float2(i.uv.x, i.uv.y)).rgb;
    //texColor = float3(0.2, 0.2, 0.2);
    final *= texColor;
    
    if (final.r < 0.0)
        final.r = 0.0;
    if (final.g < 0.0)
        final.g = 0.0;
    if (final.b < 0.0)
        final.b = 0.0;
    
    
    
    final += float4(0.05, 0.05, 0.05, 0.0f); // for transparent window to avoid flickering
    
    // idk what happens here -_-
    //float alpha = 0.5;
    //if (texColor.r == 0 && texColor.g == 0 && texColor.b == 0)
    //    alpha = 0;
    
    return float4(texColor.rgb, 1);
}