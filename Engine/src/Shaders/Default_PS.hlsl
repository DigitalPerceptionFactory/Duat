#define PIXEL_SHADER
#include "DefaultBuffer.hlsli"
#include "BasicFunctions.hlsli"


float4 main(Input i) : SV_TARGET
{
    float3 final = i.color;
    if (true)
    {

        for (int it = 0; it < m_lightCount; ++it)
        {
            float3 fragToLight = mul(m_lights[it].position, m_cameras[m_cameraIndex].viewMatrix);
            fragToLight = fragToLight - i.eye;

            /*final +=
			(
			   m_lights[it].color
			   * max(dot(normalize(i.normal.rgb), normalize(m_lights[it].position.rgb)), 0)
			) * m_lights[it].intensity;*/
            final += Specular(32, i.normal, fragToLight, -i.eye);
        }
    }
    
    return float4(final , i.color.a);
}
#undef PIXEL_SHADER