#ifndef _PLAYER_SLASH_FX_
#define _PLAYER_SLASH_FX_

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

float4 PS_Main(VS_OUT _in) : SV_Target
{
    float4 color = float4(0, 0, 0, 1);
    float elapsedTime = g_float_0;
    float endTime = g_float_1;
    float attackSpeed = g_float_2;
    int rev = g_int_1;
    
    if (elapsedTime > endTime)
        discard;
    
    if (1 == rev)
        _in.uv.x = 1.f - _in.uv.x;
    
    if (1 == g_tex_on_0)
        color = g_tex_0.Sample(g_sam_0, 1.f - (_in.uv + sin(elapsedTime * attackSpeed)));
    
    float4 subColor = g_tex_1.Sample(g_sam_0, (_in.uv + sin(elapsedTime * attackSpeed)));
    
    if (color.r + color.g + color.b < 0.1f || color.r > 0.8f)
        color.a = 0;
    
    if (length(color) < 1.03f || length(subColor) < 1.03f)
        color.a = 0;
    
    if (_in.uv.y > 0.7f || _in.uv.x < 0.05f)
        color.a = 0;
    
    if (1 == g_bloomEnable)
        color *= 0.f < g_bloomPower ? g_bloomPower : 1.25f;
    
    color = pow(color, 4);
    
    return color;
}
#endif