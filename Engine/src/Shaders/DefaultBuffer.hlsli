#include "BasicStructs.hlsli"

cbuffer DefaultBuffer : register(b0)
{
    float    m_deltaTime;
    bool     m_isClockwise;
    int      m_instanceCount;
    int      m_lightCount;
    matrix   m_viewMatrix;
    matrix   m_projectionMatrix;
};

StructuredBuffer<InstanceData> m_instanceData : register(t0);
StructuredBuffer<Light> m_lights : register(t1);