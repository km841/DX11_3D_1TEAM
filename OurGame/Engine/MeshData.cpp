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
        , mbHasAnimation(false)
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

        bool bHasAnimation = false;
        for (int i = 0; i < loader.GetMeshCount(); i++)
        {
            if (true == loader.GetMesh(i).bHasAnimation)
                bHasAnimation = true;

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

        if (true == bHasAnimation)
        {
            pMesh->CreateBonesAndAnimations(loader);
            pMeshData->mbHasAnimation = true;
        }

        pMeshData->SetMesh(pMesh);
        pMeshData->SetMaterial(pMaterial);

        fs::path parentPath = fs::path(_path).parent_path();
        wstring fileName = fs::path(_path).filename();
        size_t idx = fileName.rfind(L'.');
        fileName = fileName.substr(0, idx);
        fileName += L".msh";

        wstring fullPath = parentPath.wstring() + L"\\" + fileName;
        pMeshData->Save(fullPath);

        return pMeshData;
    }

    void MeshData::Load(const wstring& _path)
    {
        SetName(_path);

        AssertEx(fs::exists(_path), L"MeshData::Load() - 존재하지 않는 파일 주소");
        FILE* pFile = nullptr;

        _wfopen_s(&pFile, _path.c_str(), L"rb");
        AssertEx(nullptr != pFile, L"MeshData::Load() - 파일 열기 실패!");

        mpMesh = make_shared<Mesh>();

        UINT32 containerCount = 0;
        fread(&containerCount, sizeof(UINT32), 1, pFile);

        for (UINT32 i = 0; i < containerCount; ++i)
        {
            MeshContainer* pMeshContainer = new MeshContainer();
            mpMesh->AddMeshContainer(pMeshContainer);

            // Create Vertex Buffer
            VertexBufferInfo vtxInfo = {};
            fread(&vtxInfo.count, sizeof(UINT32), 1, pFile);

            char* pData = new char[vtxInfo.count * sizeof(Vertex)];

            UINT32 vertexSize = sizeof(Vertex);
            fread(pData, vertexSize, vtxInfo.count, pFile);

            vtxInfo = mpMesh->CreateVertexBuffer(pData, vtxInfo.count);
            SAFE_DELETE_ARRAY(pData);

            // Create Index Buffer
            UINT32 idxBufferCount = 0;
            fread(&idxBufferCount, sizeof(UINT32), 1, pFile);

            std::vector<IndexBufferInfo> idxInfoVec = {};
            for (UINT32 j = 0; j < idxBufferCount; ++j)
            {
                IndexBufferInfo idxInfo = {};
                fread(&idxInfo.count, sizeof(UINT32), 1, pFile);

                pData = new char[idxInfo.count * sizeof(int)];
                fread(pData, sizeof(int), idxInfo.count, pFile);

                idxInfo = mpMesh->CreateIndexBuffer(pData, idxInfo.count);
                SAFE_DELETE_ARRAY(pData);

                idxInfoVec.push_back(idxInfo);
            }

            pMeshContainer->vertexBufferInfo = vtxInfo;
            pMeshContainer->indexBufferGroup = idxInfoVec;
        }

        bool bIsMaterial = false;
        fread(&bIsMaterial, sizeof(bool), 1, pFile);

        if (true == bIsMaterial)
        {
            mpMaterial = make_shared<Material>();
            mpMaterial->ClearMaterialContainers();

            mpMaterial->Load(pFile);
        }
        
        fclose(pFile);
    }

    void MeshData::Save(const wstring& _path)
    {
        if (true == fs::exists(_path))
            return;

        FILE* pFile = nullptr;
        _wfopen_s(&pFile, _path.c_str(), L"wb");

        AssertEx(nullptr != pFile, L"MeshData::Save() - 파일 생성 실패!, 이미 존재하는 파일명일 수 있음");
        AssertEx(nullptr != mpMesh, L"MeshData::Save() - 메쉬가 존재하지 않는 MeshData를 저장하려는 시도");

        UINT32 containerSize = mpMesh->GetMeshContainerCount();
        fwrite(&containerSize, sizeof(UINT32), 1, pFile);
        for (UINT i = 0; i < containerSize; ++i)
        {
            MeshContainer* pMeshContainer = mpMesh->GetMeshContainer(i);

            VertexBufferInfo& vtxInfo = pMeshContainer->vertexBufferInfo;
            fwrite(&vtxInfo.count, sizeof(UINT32), 1, pFile);
            fwrite(vtxInfo.pData, sizeof(Vertex), vtxInfo.count, pFile);

            UINT32 indexBufferCount = static_cast<UINT32>(pMeshContainer->indexBufferGroup.size());
            fwrite(&indexBufferCount, sizeof(UINT32), 1, pFile);
            for (UINT32 j = 0; j < indexBufferCount; ++j)
            {
                IndexBufferInfo& idxInfo = pMeshContainer->indexBufferGroup[j];
                fwrite(&idxInfo.count, sizeof(UINT32), 1, pFile);
                fwrite(idxInfo.pData, sizeof(int), idxInfo.count, pFile);
            }
        }

        bool bIsMaterial = nullptr != mpMaterial;
        fwrite(&bIsMaterial, sizeof(bool), 1, pFile);

        if (true == bIsMaterial)
            mpMaterial->Save(pFile);
        

        fclose(pFile);
    }
}

