#define VERTEX_SHADER
#include "DefaultRegisters.hlsli"
#include "BasicFunctions.hlsli"

Output main(Input i, uint id : SV_InstanceID)
{
    i.position.w = 1;
    matrix m = m_instanceData[id].modelMatrix;
    matrix v;
    if(m_shadowmapIndex == 1)
        v = m_lights[m_cameraIndex].viewMatrix1;
    else if (m_shadowmapIndex == 2)
        v = m_lights[m_cameraIndex].viewMatrix2;
    else if (m_shadowmapIndex == 3)
        v = m_lights[m_cameraIndex].viewMatrix3;
    else if (m_shadowmapIndex == 4)
        v = m_lights[m_cameraIndex].viewMatrix4;
    else if (m_shadowmapIndex == 5)
        v = m_lights[m_cameraIndex].viewMatrix5;
    else
        v = m_lights[m_cameraIndex].viewMatrix0;

    matrix p = m_lights[m_cameraIndex].projectionMatrix;
    matrix mvp = mul(m, mul(v, p));

    Output o;
    o.screen = mul(i.position, mvp);
    o.position = mul(i.position, m);
    o.uv = i.uv;
    o.color = i.color;
    o.normal = ComputeNormal(i.normal, m_instanceData[0].modelMatrix, !m_isClockwise);
    return o;
}