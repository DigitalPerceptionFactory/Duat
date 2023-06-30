#define PIXEL_SHADER
#include "BasicBuffers.hlsli"
#include "BasicFunctions.hlsli"

struct GUI_Buffer
{
    matrix m;
    int type; // Empty = 0, Button, Text, Select, Slider, HSlider, VSlider, Bar, Background
    int hover;
};

StructuredBuffer<GUI_Buffer> gb : register(t0);
Texture2D bmp : register(t1);
SamplerState state : register(s1);

float4 main(Input i, uint id : SV_InstanceID) : SV_TARGET
{
    float4 color = bmp.Sample(state, i.uv.xy);
    
    /*if (i.uv.x <= 0.01 || i.uv.x >= 0.99 || i.uv.y <= 0.01 || i.uv.y >= 0.99)
    {
        if (gb[id].type == 0)
            color = TransparentWindowBiasCorrection(float4(0.1618, 0.1618, 0.1618, 1));
        else if (gb[id].type == 1)
            color = TransparentWindowBiasCorrection(float4(0, 0, 0, 1));

    }
    else
        color = bmp.Sample(state, i.uv.xy);*/
    
    
    color = TransparentWindowBiasCorrection(color);
    bool highlight = gb[id].type == 1 || gb[id].type == 5 || gb[id].type == 6;
    if (gb[id].hover > 0 && highlight)
        return color + float4(0.2, 0.2, 0.2, 0);
    else
        return color;
            
    if (i.uv.x < 0.5 && i.uv.y < 0.5)
        return float4(1, 1, 1, 1);
    else if (i.uv.x > 0.5 && i.uv.y > 0.5)
        return float4(1, 1, 1, 1);
    else
        return 0;
    
    float offset = 0.001;
    float barheight = 0.95;
    float button1 = 1 - (1 - barheight) * 3;
    float button2 = 1 - (1 - barheight) * 2;
    float button3 = 1 - (1 - barheight);
    
    if (i.uv.x > 1 - offset || i.uv.x < offset || i.uv.y > 1 - offset || i.uv.y < offset
        ||
        (i.uv.y > barheight && i.uv.y < barheight + offset)
        ||
        (i.uv.x > button1 && i.uv.x < button1 + offset && i.uv.y > barheight)
        ||
        (i.uv.x > button2 && i.uv.x < button2 + offset && i.uv.y > barheight)
        ||
        (i.uv.x > button3 && i.uv.x < button3 + offset && i.uv.y > barheight)
        )
        return float4(1, 1, 1, 1);
    else if
        (
        i.uv.y > barheight
        )
        return float4(0.3, 0.3, 0.3, 1);
    else
        return float4(1, 1, 1, 0);
    
    /*float3 texColor = tex.Sample(state, float2(i.uv.x, i.uv.y)).rgb;
    if (texColor.r == 1 && texColor.g == 1 && texColor.b == 1)
        return float4(1, 1, 1, 0);
    else
        return float4(texColor, 1);*/
}