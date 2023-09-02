#ifndef _COLLIDER_FX_
#define _COLLIDER_FX_

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
    
    output.pos = mul(float4(_in.pos, 1.f), g_matWVP);
    output.uv = _in.uv;

    return output;
}

float4 PS_Main(VS_OUT _in) : SV_Target
{
    float3 color = g_vec4_0.xyz;
    //if (color.x ==0.f && color.y == 0.f&& color.z == 0.f)
    //    color = float3(0.f, 0.f, 1.f);
    return float4(color, 1.f);
}
#endif