#define PIXEL_SHADER
#include "DefaultBuffer.hlsli"


float4 main(Input i) : SV_TARGET
{
    float2 center = float2(0.5, 0.5);
    float radius = 0.5;
    float width = 0.00618;
    
    int z = 1000* (pow(i.uv.x - center.x, 2) + pow(i.uv.y - center.y, 2));
    
    //int value_to_mod = pow(i.uv.x - center.x, 2) * pow(i.uv.y - center.y, 2) * 100;
    int value_to_mod = abs(sin(i.uv.x - center.x) + cos(i.uv.y - center.y)) * 100;
    if (
        pow(i.uv.x - center.x, 2) + pow(i.uv.y - center.y, 2) < pow(radius, 2)
        &&
        pow(i.uv.x - center.x, 2) + pow(i.uv.y - center.y, 2) > pow(radius, 2) - width
        &&
        true
        )
        return (1, 1, 1, 1);
    else
        return (0, 0, 0, 0);
}
#undef PIXEL_SHADER