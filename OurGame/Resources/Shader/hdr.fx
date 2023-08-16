#ifndef _HDR_FX_
#define _HDR_FX_

#include "params.fx"

// 톤 매핑에 사용하는 픽셀 셰이더는 다음 리소스를 사용 -> HDR, 평균 휘도값
Texture2D<float4> HDRTexture : register(t5); // HDR 적용한 텍스처
StructuredBuffer<float> AvgLum : register(t6); // 평균 휘도값
Texture2D<float4> BloomTexture : register(t8); // 블룸 적용한 텍스처 저장용, 얘는 선형 샘플러 사용
Texture2D<float4> DOFBlurTexture : register(t9); // DOF (Depth Of Filed)용 텍스처
Texture2D<float4> DepthTexture : register(t10); // 깊이 텍스처

// 화면 전체크기
static const float2 vNullPos[4] =
{
    float2(-1.f, 1.f),
	float2(1.f, 1.f),
	float2(-1.f, -1.f),
	float2(1.f, -1.f)
};

// UV
static const float2 vNullUV[4] =
{
    float2(0.f, 0.f),
	float2(1.f, 0.f),
	float2(0.f, 1.f),
	float2(1.f, 1.f)
};

// 풀 스크린 쿼드를 렌더링 하는 것과 동일하게 한다. ( 위에 null로 만든거 있으니까 그거 그대로 사용 )
// NULL 입력 에이아웃 인덱스와 버텍스 버퍼를 바인딩한다.

struct VS_OUTPUT_HDR
{
    float4 Position : SV_Position;
    float2 UV : TEXCOORD;
};


VS_OUTPUT_HDR VS_FullScreenQuad(uint VertexID : SV_VertexID)
{
    VS_OUTPUT_HDR output = (VS_OUTPUT_HDR) 0;

    output.Position = float4(vNullPos[VertexID].xy, 0.0, 1.0);
    output.UV = vNullUV[VertexID].xy;

    return output;
}

static const float3 LUM_FACTOR = float3(0.299, 0.587, 0.114);

// HDR값에 대한 톤 매핑 함수 
float3 ToneMapping(float3 _HDRColor)
{

    float MiddleGrey = g_float_0; // 중간 회색값
    float LumWhiteSqr = g_float_1; // 흰색 값
    float BloomScale = g_float_2; // 블룸 크기
    float2 ProjValue = g_vec2_0; // 투영 값
    float2 DOFFarValue = g_vec2_0; // DOF
    
    // 현재 픽셀에 대한 휘도 스케일 계산
    // LScale : 스케일 조정된 휘도 값
    float LScale = dot(_HDRColor, LUM_FACTOR);

    // HDR -> LDR로 변환 공식    : 픽셀의 휘도값을 원하는 중간 휘도 값으로 스케일을 조정한다.
    LScale *= MiddleGrey / AvgLum[0];
    LScale = (LScale + (LScale * LScale / LumWhiteSqr)) / (1.0 + LScale);

    // 휘도 스케일을 픽셀 색상에 적용
    return _HDRColor * LScale;
}


// DOF - Z버퍼 깊이 값을 성형 깊으로 변환하는 함수
float ConvertZBufferToLinearDepth(float _Depth)
{
    
    float MiddleGrey = g_float_0; // 중간 회색값
    float LumWhiteSqr = g_float_1; // 흰색 값
    float BloomScale = g_float_2; // 블룸 크기
    float2 ProjValue = g_vec2_0; // 투영 값
    float2 DOFFarValue = g_vec2_0; // DOF
    
    float LinearDepth = ProjValue.x / (_Depth + ProjValue.y);
    return LinearDepth;
}

// DOF - HDR 색상 값에 거리 DOF를 적용하는 함수
float3 DistanceDOF(float3 _ColorFocus, float3 _ColorBlurred, float _Depth)
{
    
    float MiddleGrey = g_float_0; // 중간 회색값
    float LumWhiteSqr = g_float_1; // 흰색 값
    float BloomScale = g_float_2; // 블룸 크기
    float2 ProjValue = g_vec2_0; // 투영 값
    float2 DOFFarValue = g_vec2_0; // DOF
    
    // 깊이 기반 블러 값 계산
    float BlurFactor = saturate((_Depth - DOFFarValue.x) * DOFFarValue.y);

    // 블러 색상 보간
    return lerp(_ColorFocus, _ColorBlurred, BlurFactor);

}


// 픽셀 셰이더 엔트리 포인트 표현
float4 PS_FinalPass(VS_OUTPUT_HDR _Input) : SV_TARGET
{
    
    float MiddleGrey = g_float_0; // 중간 회색값
    float LumWhiteSqr = g_float_1; // 흰색 값
    float BloomScale = g_float_2; // 블룸 크기
    float2 ProjValue = g_vec2_0; // 투영 값
    float2 DOFFarValue = g_vec2_0; // DOF
    
    // 색상 샘플 계산
    // Color은 LDR로 변환하기 위한 HDR 색상 휘도 스케일 -> 나중엔 LDR로 변환됨
    float4 Color = g_tex_5.Sample(g_sam_1, _Input.UV.xy);

    if (Color.x == 0.0 && Color.y == 0.0 && Color.z == 0.0)
    {
        clip(-1);
    }

    // 먼 평면에 없는 픽셀에 대해서 거리 DOF 계산
    float2 Depth = g_tex_10.Sample(g_sam_1, _Input.UV.xy).zw;

    if (Depth.x < 1.0)
    {
        // 다운 스케일 HDR 텍스처에 대한 블러 색상 계산
        float3 ColorBlurred = DOFBlurTexture.Sample(g_sam_0, _Input.UV.xy).xyz;
 
        // 전체 해상도 깊이 값을 성형 깊이로 변환
        //Depth = ConvertZBufferToLinearDepth(Depth);

        // 거리 DOF 색상 계산
        Color.xyz = DistanceDOF(Color.xyz, ColorBlurred, Depth.y);
    }

    Color += BloomScale * BloomTexture.Sample(g_sam_0, _Input.UV.xy); // 블룸 적용

    // 톤 매핑   
    Color.xyz = ToneMapping(Color.xyz);

    // LDR 값 출력 ( 이거 화면에 표시하면 됨 )
    return float4(Color.xyz, 1.0);
}
#endif