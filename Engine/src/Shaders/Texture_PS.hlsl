#define PIXEL_SHADER
#include "DefaultRegisters.hlsli"
#include "BasicFunctions.hlsli"

Texture2D tex : register(t4);
//Texture2D normalMap : register(t4);
SamplerState state : register(s0);

float4 main(Input i, uint id : SV_InstanceID) : SV_TARGET
{
    float4 normalVector = i.normal;
    
    //float3 zero = float3(0, 0, 0);
    float3 ambient = float3(0.1618, 0.1618, 0.1618);
    float4 final = tex.Sample(state, float2(i.uv.x, i.uv.y));
    
    if (true)
    {
        for (int it = 0; it < m_lightCount; ++it)
        {
            final.rgb +=
                (
                    m_lights[it].color
                    * max(dot(normalize(i.normal.rgb), normalize(m_lights[it].position.rgb)), 0)
                    ) * m_lights[it].intensity;
        }
    }
    return final;
}
#undef PIXEL_SHADER