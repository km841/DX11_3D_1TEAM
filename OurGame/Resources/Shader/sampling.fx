#ifndef _SAMPLING_FX_
#define _SAMPLING_FX_

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
    //return float4(1.f, 1.f, 1.f, 1.f);
    float4 color = g_tex_0.Sample(g_sam_0, _in.uv);
    
    float l = (color.r + color.g + color.b) / 3;
    if (l < 0.4)
        discard;
    
    return color;
}
#endif