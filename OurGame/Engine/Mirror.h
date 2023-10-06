#pragma once
#include "Component.h"

namespace hm
{
    using SimpleMath::Plane;
    class Camera;
	class Mirror :
		public Component
	{
    public:
        Mirror();
        virtual ~Mirror();

    public:
        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FinalUpdate() override;
        virtual void Render() override;

        virtual Component* Clone(GameObject* _pGameObject);

    public:
        const Matrix& GetReflectMatrix() { return mReflectMatrix; }
        void RenderMasking(Camera* _pCamera);
        void RenderReflect(Camera* _pCamera);
        void RenderAlbedo(Camera* _pCamera);

    private:
        void CreateReflectPlane();
        void InitRenderState();

    private:
        Plane mReflectPlane;
        Matrix mReflectMatrix;

        static bool sbIsInit;
        static ComPtr<ID3D11RasterizerState> spSolidRS;
        static ComPtr<ID3D11RasterizerState> spSolidCCWRS; 

        static ComPtr<ID3D11DepthStencilState> spDrawDSS; 
        static ComPtr<ID3D11DepthStencilState> spMaskDSS; 
        static ComPtr<ID3D11DepthStencilState> spDrawMaskedDSS;
        static ComPtr<ID3D11BlendState> spMirrorBS;
	};
}


