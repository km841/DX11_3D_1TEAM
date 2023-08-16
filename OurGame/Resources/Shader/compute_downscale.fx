#ifndef _DOWNSCALE_FX_
#define _DOWNSCALE_FX_

#include "params.fx"

Texture2D HDRTex : register(t5);
StructuredBuffer<float> AverageValuesID : register(t6);
StructuredBuffer<float> PrevAvgLum : register(t7); 

RWStructuredBuffer<float> AverageLum : register(u0); 
RWTexture2D<float4> HDRDownScale : register(u3); 


groupshared float SharedPositions[1024]; 

static const float4 LUM_FACTOR = float4(0.299, 0.587, 0.114, 0);

static uint2 Res = uint2(g_int_0, g_int_1);
static uint Domain = g_int_2;
static uint GroupSize = g_int_3;
static float Adaptation = g_float_0;
static float fBloomThreshold = g_float_1;

float DownScale4x4(uint2 _CurPixel, uint _groupThreadID)
{
    float avgLum = 0.0;

    if (_CurPixel.y < Res.y)
    {
        float fCount = 0.0f;
        int3 iFullResPos = int3(_CurPixel * 4, 0);
        float4 downScaled = float4(0.0, 0.0, 0.0, 0.0);

		[unroll]
        for (int i = 0; i < 4; i++)
        {
			[unroll]
            for (int j = 0; j < 4; j++)
            {
                downScaled += g_tex_5.Load(iFullResPos, int2(j, i));
            }
        }


        fCount = downScaled.a;
        //downScaled /= 16.0;        
        downScaled.rgb /= (fCount + 0.01f);
        downScaled.a = 1.0f;
        HDRDownScale[_CurPixel.xy] = downScaled; 
        avgLum = dot(downScaled, LUM_FACTOR); 

        SharedPositions[_groupThreadID] = avgLum;

    }


    GroupMemoryBarrierWithGroupSync();

    return avgLum;
}

float DownScale1024to4(uint _dispatchThreadID, uint _groupThreadID, float _avgLum)
{
    [unroll]
    for (uint groupSize = 4, step1 = 1, step2 = 2, step3 = 3; groupSize < 1024; groupSize *= 4, step1 *= 4, step2 *= 4, step3 *= 4)
    {

        if (_groupThreadID % groupSize == 0)
        {

            float stepAvgLum = _avgLum;
            stepAvgLum += (_dispatchThreadID + step1) < Domain ? SharedPositions[_groupThreadID + step1] : _avgLum;
            stepAvgLum += (_dispatchThreadID + step2) < Domain ? SharedPositions[_groupThreadID + step2] : _avgLum;
            stepAvgLum += (_dispatchThreadID + step3) < Domain ? SharedPositions[_groupThreadID + step3] : _avgLum;



            _avgLum = stepAvgLum;
            SharedPositions[_groupThreadID] = stepAvgLum;
        }


        GroupMemoryBarrierWithGroupSync();
    }

    return _avgLum;
}
void DownScale4to1(uint _dispatchTreadID, uint _groupThreadID, uint _groupID, float _avgLum)
{
    if (_groupThreadID == 0)
    {
        float fFinalAvgLum = _avgLum;

        fFinalAvgLum += (_dispatchTreadID + 256) < Domain ? SharedPositions[_groupThreadID + 256] : _avgLum;
        fFinalAvgLum += (_dispatchTreadID + 512) < Domain ? SharedPositions[_groupThreadID + 512] : _avgLum;
        fFinalAvgLum += (_dispatchTreadID + 768) < Domain ? SharedPositions[_groupThreadID + 768] : _avgLum;

        fFinalAvgLum /= 1024.0;

        AverageLum[_groupID] = fFinalAvgLum;
    }
}

[numthreads(1024, 1, 1)]
void DownScaleFirstPass(uint3 _dispatchThreadId : SV_DispatchThreadID,
                        uint3 _groupThreadId : SV_GroupThreadID,
                        uint3 _groupId : SV_GroupID)
{
    uint2 CurPixel = uint2(_dispatchThreadId.x % Res.x, _dispatchThreadId.x / Res.x);

    float avgLum = DownScale4x4(CurPixel, _groupThreadId.x);

    avgLum = DownScale1024to4(_dispatchThreadId.x, _groupThreadId.x, avgLum);

    DownScale4to1(_dispatchThreadId.x, _groupThreadId.x, _groupId.x, avgLum);

}


#define MAX_GROUP 64

groupshared float SharedAvgFinal[MAX_GROUP];

[numthreads(MAX_GROUP, 1, 1)]
void DownScaleSecondPass(uint3 _groupID : SV_GroupID,
                        uint3 _groupThreadID : SV_GroupThreadID,
                        uint3 _dispatchThreadID : SV_DispatchThreadID,
                        uint _groupIndex : SV_GroupIndex)
{
    float avgLum = 0.0f;

    if (_dispatchThreadID.x < GroupSize)
    {
        avgLum = AverageValuesID[_dispatchThreadID.x];
    }

    SharedAvgFinal[_dispatchThreadID.x] = avgLum;

    GroupMemoryBarrierWithGroupSync();

    if (_dispatchThreadID.x % 4 == 0)
    {
        float stepAvgLum = avgLum;
        stepAvgLum += (_dispatchThreadID.x + 1) < GroupSize ? SharedAvgFinal[_dispatchThreadID.x + 1] : avgLum;
        stepAvgLum += (_dispatchThreadID.x + 2) < GroupSize ? SharedAvgFinal[_dispatchThreadID.x + 2] : avgLum;
        stepAvgLum += (_dispatchThreadID.x + 3) < GroupSize ? SharedAvgFinal[_dispatchThreadID.x + 3] : avgLum;


        avgLum = stepAvgLum;
        SharedAvgFinal[_dispatchThreadID.x] = stepAvgLum;

    }

    GroupMemoryBarrierWithGroupSync();

    if (_dispatchThreadID.x % 16 == 0)
    {
        float stepAvgLum = avgLum;
        stepAvgLum += (_dispatchThreadID.x + 4) < GroupSize ? SharedAvgFinal[_dispatchThreadID.x + 4] : avgLum;
        stepAvgLum += (_dispatchThreadID.x + 8) < GroupSize ? SharedAvgFinal[_dispatchThreadID.x + 8] : avgLum;
        stepAvgLum += (_dispatchThreadID.x + 12) < GroupSize ? SharedAvgFinal[_dispatchThreadID.x + 12] : avgLum;


        avgLum = stepAvgLum;
        SharedAvgFinal[_dispatchThreadID.x] = stepAvgLum;

    }

    GroupMemoryBarrierWithGroupSync();


    if (_dispatchThreadID.x == 0)
    {
        float fFinalstepAvgLum = avgLum;
        fFinalstepAvgLum += (_dispatchThreadID.x + 16) < GroupSize ? SharedAvgFinal[_dispatchThreadID.x + 16] : avgLum;
        fFinalstepAvgLum += (_dispatchThreadID.x + 32) < GroupSize ? SharedAvgFinal[_dispatchThreadID.x + 32] : avgLum;
        fFinalstepAvgLum += (_dispatchThreadID.x + 48) < GroupSize ? SharedAvgFinal[_dispatchThreadID.x + 48] : avgLum;

        fFinalstepAvgLum /= 64.0f;



        float fAdaptedAverageLum = lerp(PrevAvgLum[0], fFinalstepAvgLum, Adaptation);

        AverageLum[0] = max(fAdaptedAverageLum, 0.0001);   
    }

}

Texture2D<float4> HDRDownScaleTex : register(t5);
StructuredBuffer<float> AvgLum : register(t6);
RWTexture2D<float4> Bloom : register(u0);

[numthreads(1024, 1, 1)]
void BrightPass(uint3 _DispatchThreadID : SV_DispatchThreadID)
{
    uint2 CurPixel = uint2(_DispatchThreadID.x % Res.x, _DispatchThreadID.x / Res.x);

    if (CurPixel.y < Res.y)
    {
        float4 Color = HDRDownScaleTex.Load(int3(CurPixel, 0));
        float Lum = dot(Color, LUM_FACTOR);
        float avgLum = AvgLum[0];

        float ColorScale = saturate(Lum - avgLum * fBloomThreshold);

        Bloom[CurPixel.xy] = Color * ColorScale;
    }
}
#endif