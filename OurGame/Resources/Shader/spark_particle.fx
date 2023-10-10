#ifndef _SPARK_PARTICLE_FX_
#define _SPARK_PARTICLE_FX_

#include "params.fx"
#include "utils.fx"

struct Particle
{
    float3 position;
    float endTime;
    float3 direction;
    float curTime;
    
    float3 startColor;
    float padd1;
    float3 endColor;
    float padd2;
    
    float speed;
    float2 gravityAcc;
    uint alive;
};

struct ParticleShared
{
    uint add;
};
struct VS_IN
{
    float4 pos : POSITION;
    uint id : SV_InstanceID;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    uint id : SV_InstanceID;
};

VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0.0f;
    
    output.pos = input.pos;
    output.id = input.id;
    
    return output;
}

struct GS_OUT
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
    uint id : SV_InstanceID;
};

// ==========================
//  Particle Geometry Shader
// ==========================
// g_vec3_0 : Particle Scale

StructuredBuffer<Particle> particleBuffer : register(t9);

[maxvertexcount(6)]
void GS_Main(point VS_OUT input[1], inout TriangleStream<GS_OUT> triangleStream)
{
    GS_OUT output[4] = { (GS_OUT) 0.0f, (GS_OUT) 0.0f, (GS_OUT) 0.0f, (GS_OUT) 0.0f };
	
    if (0 == particleBuffer[input[0].id].alive)
        return;
	
    float3 vWorldPos = input[0].pos.xyz + particleBuffer[input[0].id].position.xyz;
    float3 vViewPos = mul(float4(vWorldPos, 1.0f), g_matView).xyz;
    float3 vScale = g_vec4_0.xyz;

    float3 vNewPos[4] =
    {
        vViewPos + float3(-0.5f, 0.5f, 0.0f) * vScale,
        vViewPos + float3(0.5f, 0.5f, 0.0f) * vScale,
        vViewPos + float3(0.5f, -0.5f, 0.0f) * vScale,
        vViewPos + float3(-0.5f, -0.5f, 0.0f) * vScale
    };
	
    for (int i = 0; i < 4; i++)
    {
        output[i].pos = mul(float4(vNewPos[i], 1.0f), g_matProjection);
    }
	
    output[0].uv = float2(0.0f, 0.0f);
    output[1].uv = float2(1.0f, 0.0f);
    output[2].uv = float2(1.0f, 1.0f);
    output[3].uv = float2(0.0f, 1.0f);
	
    output[0].id = input[0].id;
    output[1].id = input[0].id;
    output[2].id = input[0].id;
    output[3].id = input[0].id;
    
    triangleStream.Append(output[0]);
    triangleStream.Append(output[1]);
    triangleStream.Append(output[2]);
    triangleStream.RestartStrip();
    
    triangleStream.Append(output[0]);
    triangleStream.Append(output[2]);
    triangleStream.Append(output[3]);
    triangleStream.RestartStrip();
}

float4 PS_Main(GS_OUT input) : SV_TARGET
{
    float fElapsedTime = g_vec2_0.y;
    float4 output = (float4) 0.0f;
    
    float deltaTime = g_vec2_0.x;
    
    float3 dir = particleBuffer[input.id].direction + particleBuffer[input.id].gravityAcc.y;
    
    float2 uv = input.uv;
    if (dir.y < 0.f)
    {
        float rad90f = 3.1415926535f / 40.f;
        float curRad = dir.y * rad90f;
    
        float2 uvCentered = input.uv - 0.5f;
        float2 rotatedUV = float2(
        uvCentered.x * cos(curRad) - uvCentered.y * sin(curRad),
        uvCentered.x * sin(curRad) + uvCentered.y * cos(curRad)
    );
    
        rotatedUV += 0.5f;
        uv = rotatedUV;

    }
   
    output = g_tex_0.Sample(g_sam_0, uv);

    float fCurTime = particleBuffer[input.id].curTime;
    float fEndTime = particleBuffer[input.id].endTime;

    float3 startColor = particleBuffer[input.id].startColor;
    float3 endColor = particleBuffer[input.id].endColor;
    uint maxCount = g_int_0;

    if (length(startColor) > 0.f || length(endColor) > 0.f)
    {
        float ratio = fCurTime / fEndTime;

        float3 lerpColor = lerp(startColor, endColor, ratio);

        output.xyz = lerpColor;

    }

    return output;
}

// =========================
//  Particle Compute Shader
// =========================
// g_vec3_0  : World Position
// g_int_0   : Particle Max Count
// g_float_0 : Particle Life Time (Maximum)
// g_float_1 : Gravity
// g_vec2_0  : Delta Time / Elapsed Time
// g_vec2_1  : Particle Start Speed (Range) / Particle End Speed (Range)
// g_vec2_2  : Particle Start Angle (Range) / Particle End Angle (Range)

RWStructuredBuffer<Particle> g_particle : register(u0);
RWStructuredBuffer<ParticleShared> g_shared : register(u1);

[numthreads(1024, 1, 1)]
void CS_Main(uint3 threadIndex : SV_DispatchThreadID)
{
    float3 worldPos = g_vec4_0.xyz;
    
    uint maxCount = g_int_0;

    float startLifeTime = g_float_0;
    float gravity = g_float_1;
    float scatterRadius = g_float_2;
    
    float deltaTime = g_vec2_0.x;
    float elapsedTime = g_vec2_0.y;
    
    int startSpeed = (int) g_vec2_1.x;
    int endSpeed = (int) g_vec2_1.y;
    
    int startAngle = (int) g_vec2_2.x;
    int endAngle = (int) g_vec2_2.y;
    
    float3 standardAngle = g_vec4_1.xyz;
    float3 startColor = g_vec4_2.xyz;
    float3 endColor = g_vec4_3.xyz;
    
    
    if (maxCount <= threadIndex.x)
        return;
    
    if (0 == g_particle[threadIndex.x].alive)
    {
        while (true)
        {
            
            
            int remaining = g_shared[0].add;
            if (remaining <= 0)
                break;

            int expected = remaining;
            int desired = remaining - 1;
            int originalValue;
            InterlockedCompareExchange(g_shared[0].add, expected, desired, originalValue);

            if (originalValue == expected)
            {
                g_particle[threadIndex.x].alive = 1;
                break;
            }
        }
        
        if (1 == g_particle[threadIndex.x].alive)
        {
            float seedValue = ((float) threadIndex.x / (float) maxCount) + elapsedTime;

            float rand1 = Rand(float2(seedValue, elapsedTime));
            float rand2 = Rand(float2(seedValue * elapsedTime, elapsedTime));
            float rand3 = Rand(float2(seedValue * elapsedTime * elapsedTime, elapsedTime * elapsedTime));
            
            float3 noise =
            {
                2.f * rand1 - 1.f,
                2.f * rand2 - 1.f,
                2.f * rand3 - 1.f,
            };

            float randAngleX = lerp((float) standardAngle.x - scatterRadius, (float) standardAngle.x + scatterRadius, noise.x);
            float randAngleY = lerp((float) standardAngle.y - scatterRadius, (float) standardAngle.y + scatterRadius, noise.y);
            float randAngleZ = lerp((float) standardAngle.z - scatterRadius, (float) standardAngle.z + scatterRadius, noise.z);
            
            float randRadianX = randAngleX * 3.1415926535f / 180.f;
            float randRadianY = randAngleY * 3.1415926535f / 180.f;
            float randRadianZ = randAngleZ * 3.1415926535f / 180.f;
            
            float3 frontNormal = float3(0.f, 0.f, 1.f);
            
            float3 rotatedVector = mul(mul(mul(
                                    float3x3(
                                        1, 0, 0,
                                        0, cos(randRadianX), -sin(randRadianX),
                                        0, sin(randRadianX), cos(randRadianX)
                                    ),
                                    float3x3(
                                        cos(randRadianY), 0, sin(randRadianY),
                                        0, 1, 0,
                                        -sin(randRadianY), 0, cos(randRadianY)
                                    )),
                                    float3x3(
                                        cos(randRadianZ), -sin(randRadianZ), 0,
                                        sin(randRadianZ), cos(randRadianZ), 0,
                                        0, 0, 1
                                    )),
                                    frontNormal
                                );
            
           
            float randSpeed = lerp((float) startSpeed, (float) endSpeed, noise.x);
            g_particle[threadIndex.x].direction.xyz = normalize(rotatedVector);
            g_particle[threadIndex.x].position.xyz = worldPos;
            
            g_particle[threadIndex.x].gravityAcc = 0.f;
            g_particle[threadIndex.x].curTime = 0.f;
            g_particle[threadIndex.x].speed = randSpeed;
            g_particle[threadIndex.x].endTime = startLifeTime;
            g_particle[threadIndex.x].startColor = startColor;
            g_particle[threadIndex.x].endColor = endColor;
        }
    }
    else
    {
        g_particle[threadIndex.x].curTime += deltaTime;
 
        if (g_particle[threadIndex.x].endTime < g_particle[threadIndex.x].curTime)
        {
            g_particle[threadIndex.x].alive = 0;
        }
        else
        {
            g_particle[threadIndex.x].gravityAcc.y += gravity * deltaTime;
            g_particle[threadIndex.x].position += g_particle[threadIndex.x].direction * g_particle[threadIndex.x].speed * deltaTime;
            g_particle[threadIndex.x].position.y += g_particle[threadIndex.x].gravityAcc.y * deltaTime;
        }
    }
}

#endif