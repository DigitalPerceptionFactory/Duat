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
    matrix viewMatrix;
    matrix projectionMatrix;
};

struct Camera {
    matrix rotationMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
    float3 position;
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