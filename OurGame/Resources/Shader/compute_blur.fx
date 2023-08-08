#ifndef _COMPUTE_BLUR_FX_
#define _COMPUTE_BLUR_FX_

#include "params.fx"

static const float weights[5] = { 0.0545, 0.2442, 0.4026, 0.2442, 0.0545 };
RWTexture2D<float4> g_result : register(u0);

[numthreads(1024, 1, 1)]
void CS_Main(int3 threadIndex : SV_DispatchThreadID)
{
    float2 resolution = g_vec2_0;
    float2 uv = (float2(threadIndex.xy) + 0.5);

    float3 color = float3(0, 0, 0);
    //color = g_tex_1.SampleLevel(g_sam_0, uv, 0).rgb;
    

   for (int i = 0; i < 5; ++i)
   {
   //float2 sampleUV = uv + float2(resolution.x, 0) * float(i - 2);
       color += weights[i] * g_tex_1.SampleLevel(g_sam_0, uv, 0).rgb;
   }
    
    g_result[threadIndex.xy] = float4(color + 0.1, 1.f);
}
#endif