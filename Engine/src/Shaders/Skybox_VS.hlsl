#define VERTEX_SHADER
#include "DefaultBuffer.hlsli"
#include "BasicFunctions.hlsli"

Output main(Input i, uint id : SV_InstanceID)
{
    i.position.w = 1;
    matrix v = m_cameras[m_cameraIndex].viewMatrix;
    matrix p = m_cameras[m_cameraIndex].projectionMatrix;
    matrix vp = mul(v, p);

    Output o;
    o.screen = mul(float4(i.position.rgb, 0.0f), vp);
    o.screen.z = o.screen.w;
    o.position = i.position;
    o.uv = i.uv;
    
    return o;
}
#undef VERTEX_SHADER