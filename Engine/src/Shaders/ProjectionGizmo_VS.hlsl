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
    if (i.position.x == 0 && i.position.y == 0 && i.position.z == 0)
        o.screen = mul(i.position, mul(v, p));
    else if (i.position.y == 0) {
        i.position = float4(0, 0, 0, 1);
        o.screen = mul(i.position, m);
        o.screen.y = 0;
        o.screen = mul(o.screen, mul(v, p));
    }
    else {
        i.position = float4(0, 0, 0, 1);
        o.screen = mul(i.position, mvp);
    }

    o.uv = i.uv;
    o.color = i.color;
    return o;
}
#undef VERTEX_SHADER