#ifndef _PAPER_BURN_DEFERRED_FX_
#define _PAPER_BURN_DEFERRED_FX_

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
    int instancingFlag = g_int_0;
    
    if (1 == instancingFlag)
    {
        output.pos = mul(float4(_in.pos, 1.f), _in.matWVP);
        output.uv = _in.uv;
        output.viewPos = mul(float4(_in.pos, 1.f), _in.matWV).xyz;
        output.viewNormal = normalize(mul(float4(_in.normal, 0.f), _in.matWV)).xyz;
        output.viewTangent = normalize(mul(float4(_in.tangent, 0.f), _in.matWV)).xyz;
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
    
    return output;
}


struct PS_OUT
{
    float4 position : SV_Target0;
    float4 normal : SV_Target1;
    float4 color : SV_Target2;
};

// Paper Burn Shader
// g_tex_0 : Color texture
// g_tex_1 : Noise texture
// g_float_0 : Elapsed time
PS_OUT PS_Main(VS_OUT _in) : SV_Target
{
    PS_OUT output = (PS_OUT) 0;
    
    float2 uv = _in.uv;
    float elapsedTime = g_float_0;
    
    float3 col = float3(0.0, 0.0, 0.0);
    
    float3 fireshape = g_tex_1.Sample(g_sam_0, uv).rrr;
    float3 background = float3(0.0, 0.0, 0.0);
    float3 material = g_tex_0.Sample(g_sam_0, uv).rgb;
    
    float time = frac(-elapsedTime * 0.2);
    float3 erosion = smoothstep(time - 0.2, time, fireshape);
    
    float3 border = smoothstep(0.0, 0.7, erosion) - smoothstep(0.5, 1.0, erosion);
    
    col = (1.0 - erosion) * material + erosion * background;

    float3 lcol = float3(1.0, 0.5, 0.1);
    float3 tcol = float3(0.6, 0.8, 1.0);
    float3 fire = lerp(lcol, tcol, smoothstep(0.7, 1.0, border)) * 3.0;
    
    col += border * fire;
    
    float a = 1;
    if (col.r == 0 && col.g == 0 && col.b == 0)
        a = 0;
    
    output.position = float4(_in.viewPos, 0.f);
    output.normal = float4(_in.viewNormal, 0.f);
    output.color = float4(col, a);
    
    return output;
}
#endif