#include "DefaultBuffer.hlsli"
#include "BasicFunctions.hlsli"

struct Input
{
    float4 position : SV_POSITION;
    float4 uv : TEXCOORD;
    float4 color : COLOR;
    float4 normal : NORMAL;
    float4 shadow : SHADOW;
    float4 eye : EYE;
};

float4 main(Input i) : SV_TARGET
{
    // doesn't really matter coz of being reassigned lower
    float3 ambient = float3(0.1618, 0.1618, 0.1618);
    float3 final = i.color.rgb * ambient;
    
    //return float4(1, 1, 1, 0.2f);
    
    float4 position = i.shadow;
    position.xyz /= position.w;
    /*if (position.z > 1.0f)
        return (1, 1, 1, 1);*/
    /*if (shadowMap.Sample(shadowSampler, position.xy).r == 0.0f)
        return (1, 1, 1, 1);*/
        
    //if (IsLit(i.shadow, shadowMap, shadowSampler))
    
    //i.uv.x -= (int) (i.uv.x);
    //i.uv.y -= (int) (i.uv.y);
    
    // grey square grid effect
    if (i.uv.x < 0.5 && i.uv.y > 0.5)
        final = float3(0.236, 0.236, 0.236);
    else if(i.uv.x > 0.5 && i.uv.y > 0.5)
        final = float3(0.618, 0.618, 0.618);
    else if(i.uv.x < 0.5 && i.uv.y < 0.5)
        final = float3(0.618, 0.618, 0.618);
    else if(i.uv.x > 0.5 && i.uv.y < 0.5)
        final = float3(0.236, 0.236, 0.236);
    
    final = float3(0.1, 0.1, 0.1);
    if (true)
    {
        for (int it = 0; it < m_lightCount; ++it)
        {
            final +=
			(
			   m_lights[it].color
			   * max(dot(normalize(i.normal.rgb), normalize(m_lights[it].position.rgb)), 0)
			) * m_lights[it].intensity;
        }
    }

    return float4(final ,1);
}