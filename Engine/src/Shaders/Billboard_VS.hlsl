#define VERTEX_SHADER
#include "DefaultRegisters.hlsli"
#include "BasicFunctions.hlsli"

Output main(Input i, uint id : SV_InstanceID)
{
    i.position.w = 1;
    matrix m = m_instanceData[id].modelMatrix;
    matrix v = m_cameras[m_cameraIndex].viewMatrix;
    matrix p = m_cameras[m_cameraIndex].projectionMatrix;
    matrix mvp = mul(m, mul(v, p));

    Output o;
    i.position = mul(i.position, m_cameras[m_cameraIndex].rotationMatrix);
    o.screen = mul(i.position, mvp);
    o.position = mul(float4(0, 0, 0, 1), m_cameras[m_cameraIndex].translationMatrix);
    o.uv = i.uv;
    o.color = i.color;
    o.normal = ComputeNormal(i.normal, mul(m,v), !m_isClockwise);
    return o;
}
#undef VERTEX_SHADER