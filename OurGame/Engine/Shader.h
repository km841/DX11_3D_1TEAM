#pragma once
#include "Object.h"

namespace hm
{
    enum class ShaderType
    {
        Forward,
        Deferred,
        Light,
        Particle,
        Compute,
    };

    enum class DepthStencilType
    {
        Less,
        LessEqual,
        Greater,
        GreaterEqual,
        LessNoWrite, // 깊이 테스트 O + 깊이 기록 X
        NoDepthTest, // 깊이 테스트 X + 깊이 기록 O
        NoDepthTestNoWrite, // 깊이 테스트 X + 깊이 기록 X
    };

    enum class RasterizerType
    {
        CullNone,
        CullFront,
        CullBack,
        WireFrame,
    };

    enum class BlendType
    {
        Default,
        AlphaBlend,
        OneToOneBlend,
        End,
    };
    
    enum class SamplerType
    {
        Wrap,
        Clamp,
        End,
    };

    struct ShaderArg
    {
        string vsFuncName = "VS_Main";
        string gsFuncName = "";
        string psFuncName = "PS_Main";
    };

    struct ShaderInfo
    {
        ShaderInfo(ShaderType _eShaderType = ShaderType::Forward,
            DepthStencilType _eDepthStencilType = DepthStencilType::Less,
            RasterizerType _eRasterizerType = RasterizerType::CullBack,
            BlendType _eBlendType = BlendType::Default,
            D3D_PRIMITIVE_TOPOLOGY _eTopology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
            : eShaderType(_eShaderType)
            , eDepthStencilType(_eDepthStencilType)
            , eRasterizerType(_eRasterizerType)
            , eBlendType(_eBlendType)
            , eTopology(_eTopology)
        {}

        ShaderType eShaderType;
        DepthStencilType eDepthStencilType;
        RasterizerType eRasterizerType;
        BlendType eBlendType;
        D3D_PRIMITIVE_TOPOLOGY eTopology;
    };


	class Shader :
		public Object
	{
    public:
        Shader();
        virtual ~Shader();
        virtual void Load(const wstring& _path) override;

        /* 전달 받은 인자들을 통해 내부적으로 CreateXXXShader 류의 함수들을 호출하여 셰이더를 생성하는 함수
        * _path : 셰이더 파일의 주소
        * _shaderInfo : 셰이더의 정보(DepthStencilType, BlendType, RasterizerType 등등)
        * _shaderArg : 셰이더 함수들의 이름 (VS_Main, PS_Main ...)
        */
        void CreateGraphicsShader(const wstring& _path, ShaderInfo _shaderInfo = ShaderInfo(), ShaderArg _shaderArg = ShaderArg());

        /* 그리기에 필요한 각종 상태들을 적용한다.
        * DepthStencilState 
        * BlendState
        * RasterizerState
        * PrimitiveTopology 
        * InputLayout
        */
        void Update();

    public:
        void CreateComputeShader(const wstring& _path, const string& _name, const string& _version);
        void CreateVertexShader(const wstring& _path, const string& _name, const string& _version);
        void CreatePixelShader(const wstring& _path, const string& _name, const string& _version);
        void CreateGeometryShader(const wstring& _path, const string& _name, const string& _version);

        void SetSamplerType(SamplerType _eSamplerType);

    public:
        ShaderType GetShaderType() const { return mShaderInfo.eShaderType; }

    private:
        /* 전달받은 인자들로 Shader를 생성하는 함수*/
        void CreateShader(const wstring& _path, const string& _name, const string& _version, ComPtr<ID3DBlob>& _pBlob);
        // 샘플러를 생성하는 함수
        void CreateSampler();

    private:
        ShaderInfo                      mShaderInfo;

        SamplerType                     meSamplerType;

        ComPtr<ID3D11VertexShader>      mpVertexShader;
        ComPtr<ID3D11GeometryShader>    mpGeometryShader;
        ComPtr<ID3D11PixelShader>       mpPixelShader;
        ComPtr<ID3D11ComputeShader>     mpComputeShader;

        ComPtr<ID3D11InputLayout>       mpInputLayout;

        ComPtr<ID3D11SamplerState>      mpLinearWrapSamplerState;
        ComPtr<ID3D11SamplerState>      mpPointWrapSamplerState;
        ComPtr<ID3D11SamplerState>      mpPointClampSamplerState;
        ComPtr<ID3D11SamplerState>      mpLinearClampSamplerState;

        ComPtr<ID3D11DepthStencilState> mpDepthStencilState;
        ComPtr<ID3D11RasterizerState>   mpRasterizerState;
        ComPtr<ID3D11BlendState>        mpBlendState;

        ComPtr<ID3DBlob>                mpVSBlob;
        ComPtr<ID3DBlob>                mpPSBlob;
        ComPtr<ID3DBlob>                mpGSBlob;
        ComPtr<ID3DBlob>                mpCSBlob;
        ComPtr<ID3DBlob>                mpErrBlob;
	};
}


