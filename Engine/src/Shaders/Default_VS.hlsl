#define VERTEX_SHADER
#include "DefaultRegisters.hlsli"
#include "BasicFunctions.hlsli"

Output main(Input i, uint id : SV_InstanceID)
{
    i.position.w = 1;
    matrix m = m_instanceData[id].modelMatrix;
    matrix v = m_cameras[m_cameraIndex].viewMatrix;
    matrix p = m_cameras[m_cameraIndex].projectionMatrix;
    matrix mvp = mul(m, mul(v,p));
        
    Output o;
    o.screen = mul(i.position, mvp);
    o.position = mul(i.position, m);
    o.uv = i.uv;
    o.color = i.color;
    o.normal = ComputeNormal(i.normal, m, m_isClockwise);
    return o;
}
#undef VERTEX_SHADER