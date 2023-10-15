#ifndef _EXPLOSION_FX_
#define _EXPLOSION_FX_

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
        output.viewNormal = normalize(mul(float4(_in.normal, 0.f), _in.matWV)).xyz;
        output.viewTangent = normalize(mul(float4(_in.tangent, 0.f), _in.matWV)).xyz;
        output.viewBinormal = normalize(cross(output.viewTangent, output.viewNormal));
    }
    else
    {
        if (g_int_1 == 1)
            Skinning(_in.pos, _in.normal, _in.tangent, _in.weight, _in.indices);
        
        if (g_reflect_use == 1)
        {
            row_major matrix reflect_matWV = g_matWorld * g_reflect_mat * g_matView;
            row_major matrix reflect_matVP = g_reflect_mat * g_matView * g_matProjection;
            row_major matrix reflect_matWVP = g_matWorld * g_reflect_mat * g_matView * g_matProjection;
            
            row_major matrix sum = g_matWorld;
            sum = mul(sum, g_reflect_mat);
            sum = mul(sum, g_matView);
            sum = mul(sum, g_matProjection);
            
            output.pos = mul(float4(_in.pos, 1.f), sum);
            output.uv = _in.uv;
            output.viewPos = mul(float4(_in.pos, 1.f), reflect_matWV).xyz;
            output.viewNormal = normalize(mul(float4(_in.normal, 0.f), reflect_matWV)).xyz;
            output.viewTangent = normalize(mul(float4(_in.tangent, 0.f), reflect_matWV)).xyz;
            output.viewBinormal = normalize(cross(output.viewTangent, output.viewNormal));
        }
        else
        {
            output.pos = mul(float4(_in.pos, 1.f), g_matWVP);
            output.uv = _in.uv;
            output.viewPos = mul(float4(_in.pos, 1.f), g_matWV).xyz;
            output.viewNormal = normalize(mul(float4(_in.normal, 0.f), g_matWV)).xyz;
            output.viewTangent = normalize(mul(float4(_in.tangent, 0.f), g_matWV)).xyz;
            output.viewBinormal = normalize(cross(output.viewTangent, output.viewNormal));
        }
    }

    return output;
}

float4 PS_Main(VS_OUT _in) : SV_Target
{
    float elapsedTime = g_float_0;
    
    float2 uv = _in.uv + sin(elapsedTime * 0.5f);
    float4 color = g_tex_on_0 == 1 ? g_tex_0.Sample(g_sam_0, uv) : float4(g_vec4_0.xyz, 1.f);
    
    color.a = color.r;
    color.rgb = color.rgb;
    color.g = 0.3f;
    color.b = 0.7f;
    return color;
}
#endif