#ifndef _SCREEN_EFFECT_FX_
#define _SCREEN_EFFECT_FX_

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
    output.pos = float4(_in.pos, 1.f);
    output.uv = _in.uv;
    
    return output;
}

/*
===================
ScreenEffect Shader
===================
g_float_0 : ScreenEffect1_ratio
g_float_1 : ScreenEffect2_ratio

g_int_1 : ScreenEffect1_type
g_int_2 : ScreenEffect2_type
*/

#define NONE 0
#define FADE_IN 1
#define FADE_OUT 2
#define WHITE_IN 3
#define WHITE_OUT 4

void ComputeEffectColor(inout float4 _color, int _effectType, float _ratio)
{
    if (_effectType == NONE)
        return;
    
    if (FADE_IN == _effectType)
    {
        _color *= _ratio;
    }
    
    else if (FADE_OUT == _effectType)
    {
        _color *= (1.f - _ratio);
    }
    
    // 하얀 배경에서 원래 색으로 돌아오는 것
    else if (WHITE_IN == _effectType)
    {
        // 맨 처음 1, 1, 1, 1에서 원래 색의 차이만큼 덜어내는 것
        float4 white = float4(1.f, 1.f, 1.f, 1.f);
        float4 diff = white - _color;
        
        _color = white - diff * _ratio;
    }
    
    // 점점 하얘지는 것
    else if (WHITE_OUT == _effectType)
    {
        float4 white = float4(1.f, 1.f, 1.f, 1.f);
        float4 diff = white - _color;
        
        _color += diff * _ratio;
    }
}

float4 PS_Main(VS_OUT _in) : SV_Target
{
    //return float4(1.f, 1.f, 1.f, 1.f);
    
    float ratio_1 = g_float_0;
    float ratio_2 = g_float_1;
    
    int effectType_1 = g_int_1;
    int effectType_2 = g_int_2;
    
    float4 color = g_tex_on_0 == 1 ? g_tex_0.Sample(g_sam_0, _in.uv) : float4(g_vec4_0.xyz, 1.f);
    
    ComputeEffectColor(color, effectType_1, ratio_1);
    ComputeEffectColor(color, effectType_2, ratio_2);
    
    return color;
}
#endif