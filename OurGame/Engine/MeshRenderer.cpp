#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Material.h"
#include "Engine.h"
#include "Mesh.h"
#include "InstancingBuffer.h"

namespace hm
{
    MeshRenderer::MeshRenderer()
        : Component(ComponentType::MeshRenderer)
    {
    }
    MeshRenderer::~MeshRenderer()
    {
    }
    void MeshRenderer::Render(Camera* _pCamera)
    {
        AssertEx(nullptr != mpMaterial, L"MeshRenderer::Render() - Material is empty");
        AssertEx(nullptr != mpMaterial->GetShader(), L"MeshRenderer::Render() - Shader is empty");
        AssertEx(nullptr != mpMesh, L"MeshRenderer::Render() - Mesh is empty");

        GetTransform()->PushData(_pCamera);
        CONST_BUFFER(ConstantBufferType::Transform)->Mapping();
        
        UINT32 meshCount = mpMesh->GetMeshContainerCount();
        for (UINT i = 0; i < meshCount; ++i)
        {
            MaterialContainer* pContainer = mpMaterial->GetMaterialContainer(i);
            for (int j = 0; j < pContainer->materialSubsetVec.size(); ++j)
            {
                mpMaterial->PushGraphicData(i, j);
                CONST_BUFFER(ConstantBufferType::Material)->Mapping();

                mpMesh->Render(1, i);
            }
        }
    }

    void MeshRenderer::Render(Camera* _pCamera, InstancingBuffer* _pBuffer)
    {
        AssertEx(nullptr != mpMaterial, L"MeshRenderer::Render() - Material is empty");
        AssertEx(nullptr != mpMesh, L"MeshRenderer::Render() - Mesh is empty");

        _pBuffer->PushData();
        GetTransform()->PushData(_pCamera);
        CONST_BUFFER(ConstantBufferType::Transform)->Mapping();

        UINT32 meshCount = mpMesh->GetMeshContainerCount();
        for (UINT32 i = 0; i < meshCount; ++i)
        {
            MaterialContainer* pContainer = mpMaterial->GetMaterialContainer(i);

            for (UINT32 j = 0; j < pContainer->materialSubsetVec.size(); ++j)
            {
                mpMaterial->PushGraphicData(i, j);
                CONST_BUFFER(ConstantBufferType::Material)->Mapping();

                mpMesh->Render(_pBuffer, i);
            }
        }

    }
    void MeshRenderer::SetMaterial(shared_ptr<Material> _pMaterial)
    {
        mpMaterial = _pMaterial;
    }
    UINT64 MeshRenderer::GetInstanceID()
    {
        if (mpMesh == nullptr || mpMaterial == nullptr)
            return 0;

        UINT32 meshID = mpMesh->GetID();
        UINT32 materialID = mpMaterial->GetID();

        InstanceID instanceID = { meshID, materialID };
        return instanceID.id;
    }
}