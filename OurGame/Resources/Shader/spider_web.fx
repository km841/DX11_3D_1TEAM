#ifndef _SPIDER_WEB_FX_
#define _SPIDER_WEB_FX_

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
        
        if (g_int_2 == 1)
        {
            row_major matrix reflect_matWV = g_matWorld * g_reflect_mat * g_matView;
            row_major matrix reflect_matVP = g_reflect_mat * g_matView * g_matProjection;
            row_major matrix reflect_matWVP = g_matWorld * reflect_matVP;
            
            output.pos = mul(float4(_in.pos, 1.f), reflect_matWVP);
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
    if (g_float_0 > 2.f)
        discard;
    int burnFlag = g_int_0;
    
    float4 color = g_tex_on_0 == 1 ? g_tex_0.Sample(g_sam_0, _in.uv) : float4(g_vec4_0.xyz, 1.f);
    color.gb = color.rr;
    color.rgb *= 1.5f;
    color.a = color.r;
    
    if (g_int_3 == 1)
    {
        float2 uv = _in.uv;
 
        float3 fireshape = g_tex_1.Sample(g_sam_0, uv).rrr;
        float3 materialColor = color.rgb;

        float time = frac(g_float_0 * -0.5f);
        float erosion = smoothstep(time - 0.2, time, fireshape.r);
        float border = smoothstep(0.0, 0.7, erosion) - smoothstep(0.5, 1.0, erosion);

        float3 initialColor = float3(1.0, 0.4, 0.1);
        float3 finalColor = float3(0.0, 0.0, 0.0);
        float3 burningColor = lerp(initialColor, finalColor, smoothstep(0.7, 1.0, border)) * 3.0;
    
        float3 finalColorWithBurn = lerp(materialColor, float3(0.0, 0.0, 0.0), erosion) + border * burningColor * 1.5;
    
        if (length(finalColorWithBurn.rgb) < 0.1f)
            discard;
    
        float diff = initialColor.r - finalColorWithBurn.r;
    
        float4 final = float4(finalColorWithBurn, 1.f - diff);

        return final;
    }
    
    return color;

}
#endif