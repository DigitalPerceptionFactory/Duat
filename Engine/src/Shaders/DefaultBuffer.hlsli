#include "BasicStructs.hlsli"

cbuffer DrawCallBuffer : register(b0)
{
    float    m_deltaTime;
    bool     m_isClockwise;
    int      m_instanceCount;
    int      m_lightCount;
    int      m_cameraIndex;
};

StructuredBuffer<Camera> m_cameras : register(t0);
StructuredBuffer<Light> m_lights : register(t1);
Texture2DArray<float> m_shadowMaps : register(t2);
StructuredBuffer<InstanceData> m_instanceData : register(t3);