#pragma once
#include "Object.h"

namespace hm
{
	class Texture :
		public Object
	{
    public:
        Texture();
        virtual ~Texture();
        // Resources에 의해 호출되며 외부 이미지를 로드하는 함수
        virtual void Load(const wstring& _path) override;

    public:

        /* 자체적으로 이미지를 생성하는 함수
        * _type : 현재 이미지가 사용될 타입 (RTV, SRV, DSV ...)
        * _eFormat : 텍스쳐가 가져야할 포맷 (ex R8G8B8 ...)
        * _width : 텍스쳐의 가로 크기
        * _height : 텍스쳐의 세로 크기
        */
        void Create(UINT _type, DXGI_FORMAT _eFormat, int _width, int _height);

        /* 리소스가 존재하는 경우 그 리소스로 텍스쳐를 만드는 함수
        * _type : 현재 이미지가 사용될 타입 (RTV, SRV, DSV ...)
        * _eFormat : 텍스쳐가 가져야할 포맷 (ex R8G8B8 ...)
        * _pTex2D : 리소스
        */
        void CreateFromTexture(UINT _type, DXGI_FORMAT _eFormat, ComPtr<ID3D11Texture2D> _pTex2D);

    public:
        Vec3 GetTexSize() { return mTexSize; }

    public:
        ComPtr<ID3D11Texture2D>           GetTex2D() const { return mpTex2D; }
        ComPtr<ID3D11RenderTargetView>    GetRTV()   const { return mpRTV; }
        ComPtr<ID3D11ShaderResourceView>  GetSRV()   const { return mpSRV; }
        ComPtr<ID3D11DepthStencilView>    GetDSV()   const { return mpDSV; }
        ComPtr<ID3D11UnorderedAccessView> GetUAV()   const { return mpUAV; }

    private:
        UINT                                meTextureType;
        Vec3                                mTexSize;

        ScratchImage                        mScratchImage;
        ComPtr<ID3D11Texture2D>             mpTex2D;

        ComPtr<ID3D11RenderTargetView>      mpRTV;
        ComPtr<ID3D11ShaderResourceView>    mpSRV;
        ComPtr<ID3D11DepthStencilView>      mpDSV;
        ComPtr<ID3D11UnorderedAccessView>   mpUAV;
	};

}

