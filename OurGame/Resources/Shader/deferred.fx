#ifndef _DEFERRED_FX_
#define _DEFERRED_FX_

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
    
    int instancingFlag = g_int_0;
    int motion_blur_flag = g_vec4_2.x;
    
    if (1 == instancingFlag)
    {
        if (g_int_1 == 1)
            Skinning(_in.pos, _in.normal, _in.tangent, _in.weight, _in.indices);
        
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
        if (g_int_1 == 1)
            Skinning(_in.pos, _in.normal, _in.tangent, _in.weight, _in.indices);
        
        if (g_int_2 == 1)
        {
            row_major matrix matWRV = g_matWorld;
            row_major matrix matWRVP = g_matWorld;
            matWRV = mul(matWRV, g_reflect_mat);
            matWRV = mul(matWRV, g_matView);
            matWRVP = mul(matWRV, g_matProjection);
            
            output.pos = mul(float4(_in.pos, 1.f), matWRVP);
            output.uv = _in.uv;
            output.viewPos = mul(float4(_in.pos, 1.f), matWRV).xyz;
            output.projPos = mul(float4(_in.pos, 1.f), matWRVP);
            output.viewNormal = normalize(mul(float4(_in.normal, 0.f), matWRV)).xyz;
            output.viewTangent = normalize(mul(float4(_in.tangent, 0.f), matWRV)).xyz;
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
    }
    if (1 == motion_blur_flag)
    {
        float4 currentPos = output.pos;
        float4 oldPos = mul(float4(_in.pos, 1.f), g_matOldWorld);
        oldPos = mul(oldPos, g_matOldView);
        oldPos = mul(oldPos, g_matProjection);
    
        float3 dir = currentPos - oldPos;
        float check = dot(normalize(dir), normalize(output.viewNormal));
        output.pos = check < 0.f ? oldPos : currentPos;

        float2 velocity = (currentPos.xy / currentPos.w) - (oldPos.xy / oldPos.w);
        output.dir.xy = velocity * 0.5f;
        output.dir.y *= -1.f;
        output.dir.z *= output.pos.z;
        output.dir.w *= output.pos.w;
    }

    return output;
}

struct PS_OUT
{
    float4 position : SV_Target0;
    float4 normal : SV_Target1;
    float4 color : SV_Target2;
    float4 bloom : SV_Target3;
    float4 depth : SV_Target4;
    float4 dir : SV_Target5;
};

PS_OUT PS_Main(VS_OUT _in)
{
    PS_OUT output = (PS_OUT) 0;
   
    int motion_blur_flag = g_vec4_2.x;
    float4 bloomColor = g_bloomColor;
    float4 color = float4(g_vec4_0.xyz, 1.f);
    
    float2 uv = _in.uv;
    float2 tilingValue = g_vec2_3;
    if (tilingValue.x != 0.f || tilingValue.y != 0.f)
        uv = uv * tilingValue;
    
    if (g_tex_on_0)
        color = g_tex_0.Sample(g_sam_0, uv);
    
    float3 viewNormal = _in.viewNormal;
    if (g_tex_on_1 == 1)
    {
        // [0,255] 범위에서 [0,1]로 변환
        float3 tangentSpaceNormal = g_tex_1.Sample(g_sam_0, uv).xyz;
        // [0,1] 범위에서 [-1,1]로 변환
        tangentSpaceNormal = (tangentSpaceNormal - 0.5f) * 2.f;
        float3x3 matTBN = { _in.viewTangent, _in.viewBinormal, _in.viewNormal };
        viewNormal = normalize(mul(tangentSpaceNormal, matTBN));
    }
    
    float bloomPower = g_bloomPower == 0.f ? 1.25f : g_bloomPower;
    
    float isBloomColor = g_bloomColor.r + g_bloomColor.g + g_bloomColor.b;
    float4 totalBloomColor = 0.f < isBloomColor ? bloomColor : color;
    
    output.position = float4(_in.viewPos, 0.f);
    output.normal = float4(viewNormal, 0.f);
    output.color = 1 == g_bloomEnable ? totalBloomColor : color;
    output.bloom = 1 == g_bloomEnable ? totalBloomColor * bloomPower : float4(0.f, 0.f, 0.f, 0.f);
    output.depth.xyz = (float3) (_in.projPos.z / _in.projPos.w);
    output.depth.w = _in.projPos.w;
    output.depth.yzw = _in.viewPos;
    
    //if (1 == motion_blur_flag)
    //{
    //    output.dir.xy = _in.dir.xy;
    //    output.dir.z = 1.f;
    //    output.dir.w = _in.dir.z / _in.dir.w;
    //}
    
    if (length(g_bloomFilter) > 0)
    {
        output.color = totalBloomColor;
        
        if (totalBloomColor.r >= max(totalBloomColor.g, totalBloomColor.b) + 0.1f)
            output.bloom = float4(1.f, 0.f, 0.f, 1.f);
        
        else if (totalBloomColor.g >= max(totalBloomColor.r, totalBloomColor.b) + 0.1f)
            output.bloom = float4(0.f, 1.f, 0.f, 1.f);
        
        else if (totalBloomColor.b >= max(totalBloomColor.g, totalBloomColor.r) + 0.1f)
            output.bloom = float4(0.f, 0.f, 1.f, 1.f);
        
        else
            output.bloom = float4(0.f, 0.f, 0.f, 0.f);
    }
   
    return output;
}
#endif