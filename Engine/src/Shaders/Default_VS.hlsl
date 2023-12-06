#define VERTEX_SHADER
#include "DefaultBuffer.hlsli"
#include "BasicFunctions.hlsli"

Output main(Input i, uint id : SV_InstanceID)
{
    i.position.w = 1;
    matrix m = m_instanceData[id].modelMatrix;
    matrix v = m_cameras[m_cameraIndex].viewMatrix;
    matrix p = m_cameras[m_cameraIndex].projectionMatrix;
    matrix mvp = mul(m, mul(v,p));

    Output o;
    o.position = mul(i.position, mvp);
    o.color = i.color;
    o.normal = ComputeNormal(i.normal, m_instanceData[0].modelMatrix, !m_isClockwise);
    o.uv = i.uv;
    o.eye = float4(m_cameras[m_cameraIndex].position, 0);
    return o;

    /*matrix modelMatrix = mul(DPF::transform[0], DPF::animationMatrix);
    matrix cameraMVP = mul(DPF::projection, mul(DPF::view, modelMatrix));
    matrix lightMVP = mul(DPF::lights[0].projection, mul( DPF::lights[0].view, modelMatrix));
    
    o.position = mul(cameraMVP, i.position);
    o.color = i.color;
    o.uv = i.uv;
    o.normal = ComputeNormal(i.normal, modelMatrix, DPF::isClockwise);
    o.shadow = ComputeShadow(i.position,lightMVP);
    o.eye = normalize(DPF::cameraPosition - mul(modelMatrix, i.position));
    //o.position = i.position;
    //o.position.z = 10;
    return o;*/
}
#undef VERTEX_SHADER