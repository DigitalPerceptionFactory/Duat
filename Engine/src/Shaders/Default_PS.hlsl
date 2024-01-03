#define PIXEL_SHADER
#include "DefaultBuffer.hlsli"
#include "BasicFunctions.hlsli"


float4 main(Input i) : SV_TARGET
{
    float3 final = i.color / 2;
    if (true)
    {

        for (int it = 0; it < m_lightCount; ++it)
        {
            float3 camPos = mul(float4(0,0,0,1),m_cameras[m_cameraIndex].translationMatrix);

            final +=
			(
			   m_lights[it].color
			   * max(dot(normalize(i.normal.rgb), normalize(m_lights[it].position.rgb)), 0)
			) * m_lights[it].intensity;
            final +=  Specular(64, i.normal, m_lights[it].position - i.position, i.position - camPos);
        }
    }
    
    return float4(final , i.color.a);
}
#undef PIXEL_SHADER