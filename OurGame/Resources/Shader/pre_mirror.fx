#ifndef _PRE_MIRROR_FX_
#define _PRE_MIRROR_FX_

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
    float3 viewNormal : NORMAL;
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
    }
    else
    {
        if (g_int_1 == 1)
            Skinning(_in.pos, _in.normal, _in.tangent, _in.weight, _in.indices);
        
        if (g_reflect_use == 1)
        {
            row_major matrix matWRV = g_matWorld;
            row_major matrix matWRVP = g_matWorld;
            matWRV = mul(matWRV, g_reflect_mat);
            matWRV = mul(matWRV, g_matView);
            matWRVP = mul(matWRV, g_matProjection);
            
            output.pos = mul(float4(_in.pos, 1.f), matWRVP);
            output.uv = _in.uv;
            output.viewPos = mul(float4(_in.pos, 1.f), matWRV).xyz;
            output.viewNormal = normalize(mul(float4(_in.normal, 0.f), matWRV)).xyz;
            
        }
        else
        {
            output.pos = mul(float4(_in.pos, 1.f), g_matWVP);
            output.uv = _in.uv;
            output.viewPos = mul(float4(_in.pos, 1.f), g_matWV).xyz;
            output.viewNormal = normalize(mul(float4(_in.normal, 0.f), g_matWV)).xyz;
        }
    }

    return output;
}

float4 PS_Main(VS_OUT _in) : SV_Target0
{
    return mul(_in.pos, g_matWV);
}
#endif