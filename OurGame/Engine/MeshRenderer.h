#pragma once
#include "Component.h"
#include "Material.h"
namespace hm
{
    class Mesh;
    class Camera;
    class InstancingBuffer;
    class MeshData;
    class Shader;

    class MeshRenderer :
        public Component
    {
    public:
        MeshRenderer();
        virtual ~MeshRenderer();

        virtual Component* Clone(GameObject* _pGameObject);

        /* 메쉬를 그려주는 함수
        * 인자로 전달되는 카메라를 통해 뷰행렬, 투영행렬을 받아온다.
        * _pCamera : 이 메쉬를 그려줄 카메라의 포인터
        */
        void                 Render(Camera* _pCamera);
        void                 Render(Camera* _pCamera, InstancingBuffer* _pBuffer);
        void                 RenderExceptForShader(Camera* _pCamera, shared_ptr<Shader> _pShader, bool _bIsReflect = false);
        void                 RenderEffect(Camera* _pCamera);
        void                 RenderShadow(Camera* _pCamera);

        void                 SetMaterial(shared_ptr<Material> _pMaterial);
        shared_ptr<Material> GetMaterial() const { return mpMaterial; }

        void                 SetMesh(shared_ptr<Mesh> _pMesh) { mpMesh = _pMesh; }
        shared_ptr<Mesh>     GetMesh()     const { return mpMesh; }
        void                 SetMeshData(shared_ptr<MeshData> _pMeshData);

        void                 PushScriptData();

        UINT64 GetInstanceID();

        void SetSubsetRenderFlag(UINT32 _index, bool _flag);

    private:
        shared_ptr<Material> mpMaterial; // 고유의 id 
        shared_ptr<Mesh>     mpMesh; // 고유의 id
        std::vector<bool>    mSubsetRenderFlags;
	};
}


