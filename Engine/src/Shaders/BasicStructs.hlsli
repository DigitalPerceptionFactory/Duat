#pragma pack_matrix( row_major )

struct InstanceData
{
    matrix modelMatrix;
};

struct Light
{
    float3 position;
    float intensity;
    float3 direction;
    float pad0;
    float3 color;
    float pad1;
    matrix projectionMatrix;
    matrix viewMatrix0;
    matrix viewMatrix1;
    matrix viewMatrix2;
    matrix viewMatrix3;
    matrix viewMatrix4;
    matrix viewMatrix5;
};

struct Camera {
    matrix translationMatrix;
    matrix rotationMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
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
    float4 screen : SV_POSITION;
    float4 position : POSITION;
    float4 uv : TEXCOORD;
    float4 color : COLOR;
    float4 normal : NORMAL;
    float4 shadow : SHADOW;
};
#endif

#ifdef PIXEL_SHADER
struct Input
{
    float4 screen : SV_POSITION;
    float4 position : POSITION;
    float4 uv : TEXCOORD;
    float4 color : COLOR;
    float4 normal : NORMAL;
    float4 shadow : SHADOW;
};
#endif