#ifndef _BLUR_Y_FX_
#define _BLUR_Y_FX_

#include "params.fx"

static const float weights[5] = { 0.0545, 0.2442, 0.4026, 0.2442, 0.0545 };

struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD;
};

VS_OUT VS_Main(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0;
    
    output.pos = float4(_in.pos, 1.f);
    output.uv = _in.uv;

    return output;
}

float4 PS_Main(VS_OUT _in) : SV_Target
{
    float3 color = float3(0, 0, 0);
    for (int i = 0; i < 5; ++i)
    {
        color += weights[i] * g_tex_0.Sample(g_sam_0, _in.uv + float2(0, g_vec2_0.y) * float(i - 2)).rgb;
    }
    return float4(color, 1.f);
}
#endif