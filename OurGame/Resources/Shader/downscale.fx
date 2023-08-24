#ifndef _DOWNSCALE_FX_
#define _DOWNSCALE_FX_

#include "params.fx"

// Input Texture
Texture2D<float4> InputTexture : register(t0);

// Output Texture
RWTexture2D<float4> DownscaledTexture : register(u1);

[numthreads(1, 1024, 1)] // 8x8 스레드 그룹
void CS_Main(uint3 dispatchThreadId : SV_DispatchThreadID)
{
    // 입력 텍스처의 크기
    uint2 inputSize = g_vec2_0;

    // 다운스케일된 텍스처의 크기
    uint2 outputSize = uint2(400, 225);
    
    if (dispatchThreadId.y < outputSize.y)
    {
    // 다운스케일 비율 계산
        float2 scale = float2(inputSize) / float2(outputSize);

    // 다운스케일된 픽셀 위치 계산
        uint2 outputPixel = uint2(dispatchThreadId.xy * scale);

    // 입력 텍스처에서 해당 픽셀을 샘플링하여 다운스케일된 텍스처에 기록
        DownscaledTexture[outputPixel] = InputTexture.Load(int3(outputPixel, 0));
    }
}
#endif