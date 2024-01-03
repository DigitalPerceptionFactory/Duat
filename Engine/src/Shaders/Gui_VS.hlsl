#define VERTEX_SHADER
#include "BasicStructs.hlsli"

struct GUI_Buffer
{
    matrix m;
    int hover;
};

StructuredBuffer<GUI_Buffer> gb : register(t0);

Output main(Input i, uint id : SV_InstanceID)
{
    Output o;
    o.screen = mul(gb[id].m, i.position);
    //o.position.x += gb[id].position.x - gb[id].position.z;
    //o.position.y += gb[id].position.y - gb[id].position.w;
    o.screen.w = 1;
    o.uv = i.uv;
    o.color = i.color;
    o.normal = i.normal;
    o.shadow = i.shadow;
    return o;
}