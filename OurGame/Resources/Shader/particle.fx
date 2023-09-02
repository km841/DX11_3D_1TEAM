#ifndef _PARTICLE_FX_
#define _PARTICLE_FX_

#include "params.fx"
#include "utils.fx"

struct Particle
{
    float3 position;
    float endTime;
    float3 direction;
    float curTime;
    
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
    output = g_tex_0.Sample(g_sam_0, input.uv);
    
    float fCurTime = particleBuffer[input.id].curTime;
    float fEndTime = particleBuffer[input.id].endTime;
    
    if (output.a > 0.1f)
        output.a = 1.f - fCurTime / fEndTime;
    
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
    
    float deltaTime = g_vec2_0.x;
    float elapsedTime = g_vec2_0.y;
    
    int startSpeed = (int) g_vec2_1.x;
    int endSpeed = (int) g_vec2_1.y;
    
    int startAngle = (int) g_vec2_2.x;
    int endAngle = (int) g_vec2_2.y;
    
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
            
            float3 dir = (noise - 0.5f) * 2.f;
            
            float randSpeed = lerp((float) startSpeed, (float) endSpeed, noise.x);
            //float randAngle = lerp((float) startAngle, (float) endAngle, noise.y);
            //float randRadian = randAngle * 3.141592f / 180.f;
            
            //float2 rightNormal = float2(1.f, 0.f);
            //float rotatedX = rightNormal.x * cos(randRadian) + rightNormal.y * sin(randRadian);
            //float rotatedY = rightNormal.x * sin(randRadian) - rightNormal.y * cos(randRadian);

            g_particle[threadIndex.x].direction.xyz = dir;
            g_particle[threadIndex.x].position.xyz = worldPos;
            
            g_particle[threadIndex.x].gravityAcc = 0.f;
            g_particle[threadIndex.x].curTime = 0.f;
            g_particle[threadIndex.x].speed = randSpeed;
            g_particle[threadIndex.x].endTime = startLifeTime;
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