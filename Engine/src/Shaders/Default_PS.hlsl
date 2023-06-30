#define PIXEL_SHADER
#include "BasicBuffers.hlsli"
#include "BasicFunctions.hlsli"


float4 main(Input i, uint id : SV_InstanceID, uint pid : SV_PrimitiveID) : SV_TARGET
{
    // doesn't really matter coz of being reassigned lower
    float3 ambient = float3(0.1618, 0.1618, 0.1618);
    float3 final = i.color.rgb * ambient;
    
    return float4(1, 1, 1, 1);
    
    float4 position = i.shadow;
    position.xyz /= position.w;
    /*if (position.z > 1.0f)
        return (1, 1, 1, 1);*/
    /*if (shadowMap.Sample(shadowSampler, position.xy).r == 0.0f)
        return (1, 1, 1, 1);*/
        
    //if (IsLit(i.shadow, shadowMap, shadowSampler))
    
    i.uv.x -= (int) (i.uv.x);
    i.uv.y -= (int) (i.uv.y);
    
    if (i.uv.x < 0.5 && i.uv.y > 0.5)
        final = float3(0.236, 0.236, 0.236);
    else if(i.uv.x > 0.5 && i.uv.y > 0.5)
        final = float3(0.618, 0.618, 0.618);
    else if(i.uv.x < 0.5 && i.uv.y < 0.5)
        final = float3(0.618, 0.618, 0.618);
    else if(i.uv.x > 0.5 && i.uv.y < 0.5)
        final = float3(0.236, 0.236, 0.236);
    
    final = float3(0.236, 0.236, 0.236);
    final *= ambient;
    if (true)
    {
        for (int it = 0; it < DPF::lightsCount; ++it)
        {
            if (DPF::lights[it].type == 0) // directional
            {
                final +=
			(
			   DPF::lights[it].color
			   * max(dot(normalize(i.normal.rgb), normalize(DPF::lights[it].position.rgb)), 0)
			) * DPF::lights[it].intensity;
                
                //final += Specular(2,5, i.normal, -lights[it].position, i.eye);
            }
            else if (DPF::lights[it].type == 1) // point
            {
                return float4(1, 0, 0, 1);
            }
            else if (DPF::lights[it].type == 2) // spot
            {
                return float4(1, 0, 0, 1);
            }
        }
    }
    
    return TransparentWindowBiasCorrection(float4(final.rgb, 1.0f));
}