#include "pch.h"
#include "MeshData.h"
#include "FBXLoader.h"
#include "Mesh.h"
#include "Material.h"
#include "Resources.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "GameObject.h"

namespace hm
{
    MeshData::MeshData()
       : Object(ObjectType::MeshData)
    {
    }

    MeshData::~MeshData()
    {
    }

    shared_ptr<MeshData> MeshData::LoadFromFBX(const wstring& _path, const wstring& _shaderName, bool _bInvNormal)
    {
        FBXLoader loader;
        loader.SetNormalDirection(_bInvNormal);
        loader.LoadFbx(_path);

        shared_ptr<MeshData> pMeshData = make_shared<MeshData>();

        shared_ptr<Mesh> pMesh = make_shared<Mesh>();
        shared_ptr<Material> pMaterial = make_shared<Material>();
        pMaterial->ClearMaterialContainers();

        for (int i = 0; i < loader.GetMeshCount(); i++)
        {
            pMesh->AddMeshContainer(&loader.GetMesh(i), loader);
            pMaterial->SetShader(GET_SINGLE(Resources)->Get<Shader>(_shaderName));

            MaterialContainer* pMaterialContainer = new MaterialContainer;

            if (0 < loader.GetMesh(i).materials.size())
            {
                for (size_t j = 0; j < loader.GetMesh(i).materials.size(); j++)
                {
                    pMaterialContainer->materialSubsetVec.push_back(new MaterialSubset);
                    MaterialSubset* pSubset = pMaterialContainer->materialSubsetVec.back();

                    if (false == loader.GetMesh(i).materials[j].diffuseTexName.empty())
                        pSubset->SetTexture(0, GET_SINGLE(Resources)->Get<Texture>(loader.GetMesh(i).materials[j].diffuseTexName));

                    if (false == loader.GetMesh(i).materials[j].normalTexName.empty())
                        pSubset->SetTexture(1, GET_SINGLE(Resources)->Get<Texture>(loader.GetMesh(i).materials[j].normalTexName));

                    if (false == loader.GetMesh(i).materials[j].specularTexName.empty())
                        pSubset->SetTexture(2, GET_SINGLE(Resources)->Get<Texture>(loader.GetMesh(i).materials[j].specularTexName));

                    pSubset->name = loader.GetMesh(i).materials[j].name;
                }
            }

            else
            {
                pMaterialContainer->materialSubsetVec.push_back(new MaterialSubset);
            }

            pMaterial->AddMaterialContainer(pMaterialContainer);
        }

        pMaterial->SetName(_path);
        GET_SINGLE(Resources)->Add<Mesh>(pMesh->GetName(), pMesh);
        GET_SINGLE(Resources)->Add<Material>(pMaterial->GetName(), pMaterial);

        pMeshData->SetMesh(pMesh);
        pMeshData->SetMaterial(pMaterial);

        return pMeshData;
    }

    void MeshData::Load(const wstring& _path)
    {
    }

    void MeshData::Save(const wstring& _path)
    {
    }

    GameObject* MeshData::Instantiate()
    {
        GameObject* pGameObject = new GameObject(LayerType::Unknown);
        pGameObject->AddComponent(new Transform);
        pGameObject->AddComponent(new MeshRenderer);
        pGameObject->GetMeshRenderer()->SetMesh(mpMesh);
        pGameObject->GetMeshRenderer()->SetMaterial(mpMaterial);

        //if (info.pMesh->IsAnimMesh())
        //{
        //    Animator* pAnimator = new Animator;
        //    gameObject->AddComponent(pAnimator);
        //    pAnimator->SetBones(info.pMesh->GetBones());
        //    pAnimator->SetAnimClip(info.pMesh->GetAnimClip());
        //}


        return pGameObject;
    }
}

