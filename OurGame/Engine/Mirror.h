#pragma once
#include "Component.h"
#include "InstancingBuffer.h"

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
        void RenderInstancing(Camera* _pCamera, const std::vector<GameObject*> _gameObjects);
        void RenderAlbedo(Camera* _pCamera);
        void CreateReflectPlane();
    private:
        
        void ClearInstancingBuffer();
        void InitRenderState();
        void AddParam(UINT64 _instanceID, InstancingParams& _params);

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

        std::map<UINT64, class InstancingBuffer*> mBuffers;
	};
}


