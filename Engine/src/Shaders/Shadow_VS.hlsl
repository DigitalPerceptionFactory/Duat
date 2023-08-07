#define VERTEX_SHADER
#include "DefaultBuffer.hlsli"
#include "BasicFunctions.hlsli"

Output main(Input i, uint id : SV_InstanceID)
{
    i.position.w = 1;
    matrix mvp = mul(
        m_lights[m_cameraIndex].projectionMatrix,
        mul(m_instanceData[id].modelMatrix, m_lights[m_cameraIndex].viewMatrix)
    );

    Output o;
    o.position = mul(mvp, i.position);
    o.color = i.color;
    o.normal = ComputeNormal(i.normal, m_instanceData[0].modelMatrix, !m_isClockwise);
    o.uv = i.uv;
    return o;
}