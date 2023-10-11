#ifndef _FORWARD_FX_
#define _FORWARD_FX_

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
};

VS_OUT VS_Main(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0;
    
    int instancingFlag = g_int_0;
    
    if (1 == instancingFlag)
    {
        if (g_int_1 == 1)
            Skinning(_in.pos, _in.normal, _in.tangent, _in.weight, _in.indices);
        
        if (g_reflect_use == 1)
        {
            row_major matrix matWRV = _in.matWorld;
            row_major matrix matWRVP = _in.matWorld;
            matWRV = mul(matWRV, g_reflect_mat);
            matWRV = mul(matWRV, g_matView);
            matWRVP = mul(matWRV, g_matProjection);
            
            output.pos = mul(float4(_in.pos, 1.f), matWRVP);
            output.uv = _in.uv;
        }
        else
        {
            output.pos = mul(float4(_in.pos, 1.f), _in.matWVP);
            output.uv = _in.uv;
        }
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
        }
        else
        {
            output.pos = mul(float4(_in.pos, 1.f), g_matWVP);
            output.uv = _in.uv;
        }
    }

    return output;
}

float4 PS_Main(VS_OUT _in) : SV_Target
{
    float4 color = g_tex_on_0 == 1 ? g_tex_0.Sample(g_sam_0, _in.uv) : float4(g_vec4_0.xyz, 1.f);
    
    if (length(g_vec4_0.xyz) > 0.f)
        color.rgb = g_vec4_0.rgb;
    return color;
}
#endif