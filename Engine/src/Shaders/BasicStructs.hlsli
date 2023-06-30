struct Light
{
    matrix view;
    matrix projection;
    float4 position;
    float4 direction;
    float4 color;
    float intensity;
    int type;
    float pad0;
    float pad1;
};


#ifdef VERTEX_SHADER
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
#endif

#ifdef PIXEL_SHADER
struct Input
{
    float4 position : SV_POSITION;
    float4 uv : TEXCOORD;
    float4 color : COLOR;
    float4 normal : NORMAL;
    float4 shadow : SHADOW;
    float4 eye : EYE;
};
#endif