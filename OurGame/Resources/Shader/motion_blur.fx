#ifndef _MOTION_BLUR_FX_
#define _MOTION_BLUR_FX_

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
    float4 dir : DIR;
};

VS_OUT VS_Main(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0;
    output.pos = float4(_in.pos, 1.f);
    output.uv = _in.uv;
    
    return output;
}

float4 PS_Main(VS_OUT _in) : SV_Target
{
    float4 color= (float4) 0;
   
    float4 velocity = g_tex_0.Sample(g_sam_0, _in.uv);
    
    if (length(velocity.xy) == 0)
        discard;
    
    int numBlurSample = 5;
    
    velocity /= (float) numBlurSample;
    
    int count = 1;
    float4 bColor;
    
    for (int i = 0; i < numBlurSample; ++i)
    {
        bColor = g_tex_0.Sample(g_sam_0, _in.uv * velocity.xy * (float) i);
        
        if (velocity.a < bColor.a + 0.04)
        {
            count++;
            color += bColor;
        }
    }
   
    return color;
}
#endif