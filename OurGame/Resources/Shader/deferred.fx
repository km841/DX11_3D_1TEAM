#ifndef _DEFERRED_FX_
#define _DEFERRED_FX_

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
    float4 emissive : SV_Target3;
    float4 depth : SV_Target4;
};

PS_OUT PS_Main(VS_OUT _in)
{
    PS_OUT output = (PS_OUT) 0;
   
    float bloomFlag = g_int_3;
    float4 color = float4(g_vec3_0, 1.f);
    
    if (g_tex_on_0)
        color = g_tex_0.Sample(g_sam_0, _in.uv);
    
    float3 viewNormal = _in.viewNormal;
    if (g_tex_on_1 == 1)
    {
        // [0,255] 범위에서 [0,1]로 변환
        float3 tangentSpaceNormal = g_tex_1.Sample(g_sam_0, _in.uv).xyz;
        // [0,1] 범위에서 [-1,1]로 변환
        tangentSpaceNormal = (tangentSpaceNormal - 0.5f) * 2.f;
        float3x3 matTBN = { _in.viewTangent, _in.viewBinormal, _in.viewNormal };
        viewNormal = normalize(mul(tangentSpaceNormal, matTBN));
    }
    
    output.position = 1 == bloomFlag ? float4(0, 0, 0, 0) : float4(_in.viewPos, 0.f);
    output.normal = float4(viewNormal, 0.f);
    output.color = 1 == bloomFlag ? color * 2 : color;
    output.depth.xyz = (float3) (_in.projPos.z / _in.projPos.w);
    output.depth.w = _in.projPos.w;
    output.depth.yzw = _in.viewPos;
   
    return output;
}
#endif