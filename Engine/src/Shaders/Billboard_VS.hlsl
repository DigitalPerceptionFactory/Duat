#define VERTEX_SHADER
#include "DefaultBuffer.hlsli"
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
    o.position = mul(i.position, mvp);
    o.color = i.color;
    o.normal = ComputeNormal(i.normal, m_instanceData[0].modelMatrix, !m_isClockwise);
    o.uv = i.uv;
    o.eye = float4(m_cameras[m_cameraIndex].position, 0);
    return o;
}
#undef VERTEX_SHADER