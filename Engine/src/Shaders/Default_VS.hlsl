#define VERTEX_SHADER
#include "BasicBuffers.hlsli"
#include "BasicFunctions.hlsli"


Output main(Input i, uint id : SV_InstanceID)
{
    i.position.w = 1;
    Output o;
    o.position = i.position;
    o.uv = i.uv;
    o.color = i.color;
    return o;

    matrix modelMatrix = mul(DPF::transform[0], DPF::animationMatrix);
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
    return o;
}