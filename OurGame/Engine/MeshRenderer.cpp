#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Material.h"
#include "Engine.h"
#include "Mesh.h"
#include "InstancingBuffer.h"
#include "MeshData.h"
#include "Animator.h"

namespace hm
{
	MeshRenderer::MeshRenderer()
		: Component(ComponentType::MeshRenderer)
	{
	}
	MeshRenderer::~MeshRenderer()
	{
	}
	Component* MeshRenderer::Clone(GameObject* _pGameObject)
	{
		MeshRenderer* pMeshRenderer = _pGameObject->AddComponent(new MeshRenderer);
		pMeshRenderer->mpMesh = mpMesh;
		pMeshRenderer->mpMaterial = mpMaterial;
		return pMeshRenderer;
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

			if (nullptr != GetAnimator())
				GetAnimator()->PushData(i);

			for (UINT32 j = 0; j < pContainer->materialSubsetVec.size(); ++j)
			{
				if (nullptr != GetAnimator())
					mpMaterial->SetInt(1, 1, i, j);

				mpMaterial->PushGraphicData(i, j);
				CONST_BUFFER(ConstantBufferType::Material)->Mapping();

				mpMesh->RenderInstancing(1, i);
				mpMaterial->ClearGraphicData();
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

			if (nullptr != GetAnimator())
				GetAnimator()->PushData(i);
		
			for (UINT32 j = 0; j < pContainer->materialSubsetVec.size(); ++j)
			{
				if (nullptr != GetAnimator())
					mpMaterial->SetInt(1, 1, i, j);
				
				mpMaterial->PushGraphicData(i, j);
				CONST_BUFFER(ConstantBufferType::Material)->Mapping();

				mpMesh->RenderInstancing(_pBuffer, i);
				mpMaterial->ClearGraphicData();
			}
		}
	}
	void MeshRenderer::SetMaterial(shared_ptr<Material> _pMaterial)
	{
		mpMaterial = _pMaterial;
	}
	void MeshRenderer::SetMeshData(shared_ptr<MeshData> _pMeshData)
	{
		mpMesh = _pMeshData->GetMesh();
		mpMaterial = _pMeshData->GetMaterial();

		if (true == _pMeshData->HasAnimation())
		{
			if (nullptr == GetAnimator())
				mpGameObject->AddComponent(new Animator);

			GetAnimator()->SetAnimContainer(mpMesh->GetAnimationContainers());
			GetAnimator()->SetBones(mpMesh->GetBones());
			GetAnimator()->SetAnimClip(mpMesh->GetAnimClip());
		}
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