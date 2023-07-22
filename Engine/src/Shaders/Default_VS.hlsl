#include "DefaultBuffer.hlsli"
#include "BasicFunctions.hlsli"

struct Input
{
    float4 position : POSITION;
    float4 uv : TEXCOORD;
    float4 color : COLOR;
    float4 normal : NORMAL;
    float4 shadow : SHADOW;
};

struct Output
{
    float4 position : SV_POSITION;
    float4 uv : TEXCOORD;
    float4 color : COLOR;
    float4 normal : NORMAL;
    float4 shadow : SHADOW;
    float4 eye : EYE;
};

Output main(Input i, uint id : SV_InstanceID)
{
    i.position.w = 1;
    matrix mvp = mul(m_projectionMatrix, mul(m_instanceData[0].modelMatrix, m_viewMatrix));

    Output o;
    o.position = mul(mvp, i.position);
    o.color = i.color;
    o.normal = ComputeNormal(i.normal, m_instanceData[0].modelMatrix, m_isClockwise);
    o.uv = i.uv;
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