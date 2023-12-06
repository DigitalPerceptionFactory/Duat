#define PIXEL_SHADER
#include "DefaultBuffer.hlsli"
#include "BasicFunctions.hlsli"


float4 main(Input i) : SV_TARGET
{
    // doesn't really matter coz of being reassigned lower
    float3 ambient = float3(0.1618, 0.1618, 0.1618);
    float3 final = i.color.rgb * ambient;
    
    //return float4(1, 1, 1, 1);
    
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
    final = i.color;
    if (true)
    {
        for (int it = 0; it < m_lightCount; ++it)
        {
            final +=
			(
			   m_lights[it].color
			   * max(dot(normalize(i.normal.rgb), normalize(m_lights[it].position.rgb)), 0)
			) * m_lights[it].intensity;
            /*final += 0.5 * Specular(32, i.normal,
                mul(m_lights[it].position, m_cameras[m_cameraIndex].viewMatrix),
                i.position);*/
        }
    }
    
    return float4(final , i.color.a);
}
#undef PIXEL_SHADER