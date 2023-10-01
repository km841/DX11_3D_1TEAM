#ifndef _MONSTER_DEFERRED_FX_
#define _MONSTER_DEFERRED_FX_

#include "params.fx"
#include "utils.fx"

struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float4 weight : WEIGHT;
    float4 indices : INDICES;
    
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
    float4 projPos : POSITION1;
    float3 viewNormal : NORMAL;
    float3 viewTangent : TANGENT;
    float3 viewBinormal : BINORMAL;
};

VS_OUT VS_Main(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0;
    
    int instancingFlag = g_int_0;
    
    if (1 == instancingFlag)
    {
        if (g_int_1 == 1)
            Skinning(_in.pos, _in.normal, _in.tangent, _in.weight, _in.indices);
        
        output.pos = mul(float4(_in.pos, 1.f), _in.matWVP);
        output.uv = _in.uv;
        output.viewPos = mul(float4(_in.pos, 1.f), _in.matWV).xyz;
        output.projPos = mul(float4(_in.pos, 1.f), _in.matWVP);
        output.viewNormal = normalize(mul(float4(_in.normal, 0.f), _in.matWV)).xyz;
        output.viewTangent = normalize(mul(float4(_in.tangent, 0.f), _in.matWV)).xyz;
        output.viewBinormal = normalize(cross(output.viewTangent, output.viewNormal));
    }
    else
    {
        if (g_int_1 == 1)
            Skinning(_in.pos, _in.normal, _in.tangent, _in.weight, _in.indices);
        
        output.pos = mul(float4(_in.pos, 1.f), g_matWVP);
        output.uv = _in.uv;
        output.viewPos = mul(float4(_in.pos, 1.f), g_matWV).xyz;
        output.projPos = mul(float4(_in.pos, 1.f), g_matWVP);
        output.viewNormal = normalize(mul(float4(_in.normal, 0.f), g_matWV)).xyz;
        output.viewTangent = normalize(mul(float4(_in.tangent, 0.f), g_matWV)).xyz;
        output.viewBinormal = normalize(cross(output.viewTangent, output.viewNormal));
    }

    return output;
}

struct PS_OUT
{
    float4 position : SV_Target0;
    float4 normal : SV_Target1;
    float4 color : SV_Target2;
    float4 bloom : SV_Target3;
    float4 depth : SV_Target4;
};

PS_OUT PS_Main(VS_OUT _in)
{
    PS_OUT output = (PS_OUT) 0;
   
    float hpRatio = g_float_3;
    float4 bloomColor = g_bloomColor;
    float4 color = float4(g_vec4_0.xyz, 1.f);
    float4 crackColor = float4(0.f, 0.f, 0.f, 0.f);
    
    float2 uv = _in.uv;
    if (g_tex_on_0)
        color = g_tex_0.Sample(g_sam_0, uv);
    
    if (g_tex_on_2)
        crackColor = g_tex_2.Sample(g_sam_0, uv);
    
    float crackColorAvg = (crackColor.r + crackColor.g + crackColor.b + crackColor.a) / 4.0f;
    crackColorAvg -= hpRatio;
    crackColorAvg = 0.f > crackColorAvg ? 0.f : crackColorAvg;

    output.position = float4(_in.viewPos, 0.f);
    output.normal = float4(_in.viewNormal, 0.f);
    output.color = crackColorAvg > 0.f ? float4(0.f, 0.f, 0.f, 0.f) : color;
    output.bloom = crackColorAvg > 0.f ? float4(1.f, 0.f, 0.f, 1.f) : float4(0.f, 0.f, 0.f, 0.f); 
    output.depth.xyz = (float3) (_in.projPos.z / _in.projPos.w);
    output.depth.w = _in.projPos.w;
    output.depth.yzw = _in.viewPos;
    
    return output;
}
#endif