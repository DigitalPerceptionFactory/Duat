#include "BasicStructs.hlsli"

cbuffer DrawCallBuffer : register(b0)
{
    float    m_deltaTime;
    bool     m_isClockwise;
    int      m_instanceCount;
    int      m_lightCount;
    int      m_cameraIndex;
};

StructuredBuffer<Camera> m_cameras : register(t10);
StructuredBuffer<Light> m_lights : register(t11);
Texture2DArray<float> m_shadowMaps : register(t12);
StructuredBuffer<InstanceData> m_instanceData : register(t13);