#define VERTEX_SHADER
#include "BasicBuffers.hlsli"


float4 main( float4 pos : POSITION ) : SV_POSITION
{
    pos.w = 1;
    matrix modelMatrix = mul(DPF::transform[0], DPF::animationMatrix);
    matrix mvp = mul(DPF::projection, mul(DPF::view, modelMatrix));
    return mul(mvp, pos);
}