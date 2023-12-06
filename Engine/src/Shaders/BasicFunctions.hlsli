float4 ComputeNormal(float4 vertexNormal, matrix modelMatrix, bool isClockwise)
{
    if (isClockwise)
        return normalize(mul(modelMatrix, vertexNormal));
    else
    {
        vertexNormal.x = -vertexNormal.x;
        vertexNormal.y = -vertexNormal.y;
        vertexNormal.z = -vertexNormal.z;
        
        return normalize(mul(modelMatrix, vertexNormal));
    }
}


float4 ComputeShadow(float4 position, matrix lightMVP)
{
    position = mul(lightMVP, position);
    return position * float4(0.5f, -0.5f, 1.0f, 1.0f)
    + float4(0.5f, 0.5f, 0.0f, 0.0f) * position.w;
}

bool IsLit(float4 position, Texture2D shadowMap, SamplerState shadowSampler)
{
    position.xyz /= position.w;
    if (position.z > 1.0f) return true;
    return shadowMap.Sample(shadowSampler, position.xy).r > position.z - 0.005;
}

float4 TransparentWindowBiasCorrection(float4 color)
{
    if (color.r < 0.0) color.r = 0.0;
    if (color.g < 0.0) color.g = 0.0;
    if (color.b < 0.0) color.b = 0.0;
    color += float4(0.05, 0.05, 0.05, 0.0f);
    return color;
}

float4 Specular(float power, float3 normal, float3 light, float3 eye)
{
    float3 reflection = reflect(normalize(light), normalize(normal));
    float intensity = saturate(max(dot(reflection, normalize(eye)), 0.0));
    return pow(intensity, power);
}