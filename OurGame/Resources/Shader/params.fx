#ifndef _PARAMS_FX_
#define _PARAMS_FX_

Texture2D g_tex_0 : register(t0);
Texture2D g_tex_1 : register(t1);
Texture2D g_tex_2 : register(t2);
Texture2D g_tex_3 : register(t3);
Texture2D g_tex_4 : register(t4);
Texture2D g_tex_5 : register(t5);
Texture2D g_tex_6 : register(t6);
Texture2D g_tex_7 : register(t7);
Texture2D g_tex_8 : register(t8);
Texture2D g_tex_9 : register(t9);
Texture2D g_tex_10 : register(t10);

StructuredBuffer<Matrix> g_mat_bone : register(t16);

SamplerState g_sam_0 : register(s0);
SamplerState g_sam_1 : register(s1);

cbuffer TRANSFORM_PARAMS : register(b0)
{
    row_major matrix g_matWorld;
    row_major matrix g_matView;
    row_major matrix g_matProjection;
    row_major matrix g_matWV;
    row_major matrix g_matWVP;
    row_major matrix g_matWVPInv;
}

cbuffer MATERIAL_PARAMS : register(b1)
{
    int g_int_0;
    int g_int_1;
    int g_int_2;
    int g_int_3;
    
    float g_float_0;
    float g_float_1;
    float g_float_2;
    float g_float_3;
    
    int g_tex_on_0;
    int g_tex_on_1;
    int g_tex_on_2;
    int g_tex_on_3;
    int g_tex_on_4;
    int g_tex_on_5;
    int g_tex_on_6;
    int g_tex_on_7;
    int g_tex_on_8;
    int g_tex_on_9;
    int g_tex_on_10;
    int g_tex_on_11;
    int g_tex_on_12;
    int g_tex_on_13;
    int g_tex_on_14;
    int g_tex_on_15;
    
    float2 g_vec2_0;
    float2 g_vec2_1;
    float2 g_vec2_2;
    float2 g_vec2_3;
    
    float3 g_vec3_0;
    float3 g_vec3_1;
    float3 g_vec3_2;
    float3 g_vec3_3;
    
    float4 g_vec4_0;
    float4 g_vec4_1;
    float4 g_vec4_2;
    float4 g_vec4_3;
}

struct LightColor
{
    float4 diffuse;
    float4 ambient;
    float4 specular;
};

struct LightInfo
{
    LightColor color;
    float4 position;
    float4 direction;
    int lightType;
    float range;
    float angle;
    int padding;
};

cbuffer LIGHT_PARAMS : register(b2)
{
    int g_lightCount;
    float3 g_lightPadding;
    LightInfo g_light[50];
}

#endif