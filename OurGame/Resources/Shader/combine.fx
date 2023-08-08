#ifndef _COMBINE_FX_
#define _COMBINE_FX_

#include "params.fx"

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
    float3 originColor = g_tex_0.Sample(g_sam_0, _in.uv).rgb;
    float3 addColor = g_tex_1.Sample(g_sam_0, _in.uv).rgb;
    return float4(originColor + addColor * 0.7f, 1.f);
}
#endif