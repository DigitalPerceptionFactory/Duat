float4 ComputeNormal(float4 vertexNormal, matrix modelMatrix, bool isClockwise)
{
	matrix mat;
	mat[0].xyz = modelMatrix[0].xyz;
	mat[1].xyz = modelMatrix[1].xyz;
	mat[2].xyz = modelMatrix[2].xyz;
	mat[3].xyz = float3(0, 0, 0);

	mat[0].w = 0.0f;
	mat[1].w = 0.0f;
	mat[2].w = 0.0f;
	mat[3].w = 0.0f;

	if (isClockwise)
		return normalize(mul(mat, vertexNormal));
	else
	{
		vertexNormal.x = -vertexNormal.x;
		vertexNormal.y = -vertexNormal.y;
		vertexNormal.z = -vertexNormal.z;

		return normalize(mul(mat, vertexNormal));
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
	float intensity = max(dot(normalize(reflection), normalize(eye)), 0.0f);
	return pow(intensity, power);
}

float3 GreyGrid(float2 uv)
{
	if (uv.x < 0.5 && uv.y > 0.5)
		return float3(0.236, 0.236, 0.236);
	else if (uv.x > 0.5 && uv.y > 0.5)
		return float3(0.618, 0.618, 0.618);
	else if (uv.x < 0.5 && uv.y < 0.5)
		return float3(0.618, 0.618, 0.618);
	else if (uv.x > 0.5 && uv.y < 0.5)
		return float3(0.236, 0.236, 0.236);
	return float3(1, 1, 1);
}