#ifndef _COMPUTE_BLUR_FX_
#define _COMPUTE_BLUR_FX_

#include "params.fx"

static const float SampleWeights[13] =
{
    0.002216,
    0.008764,
    0.026995,
    0.064759,
    0.120985,
    0.176033,
    0.199471,
    0.176033,
    0.120985,
    0.064759,
    0.026995,
    0.008764,
    0.002216,
};

RWTexture2D<float4> g_temp : register(u1);
RWTexture2D<float4> g_result : register(u2);

#define kernelhalf 6

[numthreads(1024, 1, 1)]
void CS_VerticalBlur_Main(uint3 _DispatchThreadID : SV_DispatchThreadID)
{
    // 다운스케일된 HDR과 SRV의 평균 휘도를 계산 후 임시로 UAV에 저장
    // 그 후에 첫 패스에서 휘도 다운스케일에 쓰인 그룹 숫자만큼 컴퓨트 셰이더를 적용한다.
    float2 Res = g_vec2_0;
    uint2 CurPixel = uint2(_DispatchThreadID.x % Res.x, _DispatchThreadID.x / Res.x);

    // 수직
    if (CurPixel.y < Res.y)
    {
        float4 vColor = float4(0.0, 0.0, 0.0, 0.0);

        for (int i = -kernelhalf; i <= kernelhalf; ++i)
        {
            uint2 CurVerticlPixel = CurPixel;
            CurVerticlPixel.y += i;
            vColor += g_tex_0.Load(int3(CurVerticlPixel, 0)) * SampleWeights[i + kernelhalf];
        }

        g_temp[CurPixel] = float4(vColor.rgb, 1.0f);

    }
    GroupMemoryBarrierWithGroupSync();
}

[numthreads(1024, 1, 1)]
void CS_HorizonBlur_Main(uint3 _DispatchThreadID : SV_DispatchThreadID)
{
    // 다운스케일된 HDR과 SRV의 평균 휘도를 계산 후 임시로 UAV에 저장
    // 그 후에 첫 패스에서 휘도 다운스케일에 쓰인 그룹 숫자만큼 컴퓨트 셰이더를 적용한다.
    float2 Res = g_vec2_0;
    uint2 CurPixel = uint2(_DispatchThreadID.x % Res.x, _DispatchThreadID.x / Res.x);

    // 수평
    if (CurPixel.y < Res.y)
    {
        float4 vColor = float4(0.0, 0.0, 0.0, 0.0);

        for (int i = -kernelhalf; i <= kernelhalf; ++i)
        {
            uint2 CurVerticlPixel = CurPixel;
            CurVerticlPixel.x += i;
            vColor += g_tex_1.Load(int3(CurVerticlPixel, 0)) * SampleWeights[i + kernelhalf];
        }
        g_result[CurPixel] = float4(vColor.rgb, 1.0f);
    }

    GroupMemoryBarrierWithGroupSync();
}
#endif