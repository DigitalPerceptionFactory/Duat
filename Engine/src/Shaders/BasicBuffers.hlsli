#include "BasicStructs.hlsli"

namespace DPF
{

    cbuffer DefaultBuffer : register(b0)
    {
        float deltaTime;
        bool3 myInt3;
        bool isClockwise;
        int lightsCount;
    };

    cbuffer CameraBuffer : register(b1)
    {
        matrix model;
        matrix view;
        matrix projection;
        float4 cameraPosition;
    };

    cbuffer AnimationBuffer : register(b2)
    {
        matrix animationMatrix;
    }

#ifdef VERTEX_SHADER
StructuredBuffer<Light> lights : register(t0);
StructuredBuffer<float4x4> transform : register(t2);
#endif

#ifdef PIXEL_SHADER
StructuredBuffer<Light> lights : register(t0);
Texture2D shadowMap : register(t1);
SamplerState shadowSampler : register(s0);
StructuredBuffer<float4x4> transform : register(t2);
#endif

}