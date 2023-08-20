#ifndef _LIGHTBLEND_FX_
#define _LIGHTBLEND_FX_

#include "params.fx"

struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    
    row_major matrix matWorld : W;
    row_major matrix matWV : WV;
    row_major matrix matWVP : WVP;
    uint instanceID : SV_InstanceID;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD;
    float3 viewPos : POSITION;
    float3 viewNormal : NORMAL;
    float3 viewTangent : TANGENT;
    float3 viewBinormal : BINORMAL;
};

VS_OUT VS_Main(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0;
    output.pos = float4(_in.pos, 1.f);
    output.uv = _in.uv;

    return output;
}

struct PS_OUT
{
    float4 lightblend : SV_Target0;
};

PS_OUT PS_Main(VS_OUT _in)
{
    PS_OUT output = (PS_OUT) 0;
    
    float4 lightPower = g_tex_1.Sample(g_sam_0, _in.uv);
    //if (lightPower.x == 0.f && lightPower.y == 0.f && lightPower.z == 0.f)
    //    clip(-1);
    
    float4 color = g_tex_0.Sample(g_sam_0, _in.uv);
    
    float4 rimColor = g_tex_2.Sample(g_sam_0, _in.uv);
    float4 totalColor = color * (lightPower + 0.2f) + rimColor;
    output.lightblend = totalColor;
    
    return output;
}
#endif