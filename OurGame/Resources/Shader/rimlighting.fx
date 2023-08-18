#ifndef _RIM_LIGHTING_FX_
#define _RIM_LIGHTING_FX_

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
    float4 projPos : POSITION1;
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

struct PS_OUT
{
    float4 lim : SV_Target0;
};

PS_OUT PS_Main(VS_OUT _in)
{
    PS_OUT output = (PS_OUT) 0;
    
    float3 rimColor = float3(1.f, 1.f, 1.f);
    float rimStrength = g_float_0;
    float rimPower = g_float_1;
    
    float4 viewPos = g_tex_0.Sample(g_sam_0, _in.uv);
    float4 viewNormal = g_tex_1.Sample(g_sam_0, _in.uv);
    
    float isViewNormal = viewNormal.x + viewNormal.y + viewNormal.z;
    if (0.0f == isViewNormal)
        discard;
    
    float4 viewDir = -normalize(viewPos);
    float rim = 1.f - dot(viewDir, viewNormal);
    rim = smoothstep(0.f, 1.f, rim);
    rim = pow(rim, rimPower);
    output.lim = float4(rimColor * rim * rimStrength, 1.f);
   
    return output;
}
#endif