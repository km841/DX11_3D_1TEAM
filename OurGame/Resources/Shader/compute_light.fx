#ifndef _COMPUTE_LIGHT_FX_
#define _COMPUTE_LIGHT_FX_

#include "params.fx"
#include "utils.fx"


RWTexture2D<float4> g_rwtex_0 : register(u0);

[numthreads(1000, 1, 1)]
void CS_Main(int3 threadIndex : SV_DispatchThreadID)
{
    g_rwtex_0[threadIndex.xy] = float4(1.f, 0.f, 0.f, 1.f);
    
    float x = threadIndex.x;
    
    if (threadIndex.x < 600.f)
    {
        int2 newIndex = int2(x + 1000.f, threadIndex.y);
        g_rwtex_0[newIndex] = float4(0.f, 1.f, 0.f, 1.f);
    }
        

}

#endif