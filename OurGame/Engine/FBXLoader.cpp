#include "pch.h"
#include "FBXLoader.h"
#include "Resources.h"
#include "Texture.h"

namespace hm
{
	FBXLoader::FBXLoader()
		: mbHasAnimation(false)
	{
	}
	FBXLoader::~FBXLoader()
	{
		if (nullptr != mpScene)
			mpScene->Destroy();

		if (nullptr != mpManager)
			mpManager->Destroy();
	}
	void FBXLoader::LoadFbx(const wstring& _path)
	{
		mFilePath = _path;
		Import(_path);

		if (false == mbHasAnimation)
		{
			LoadStaticMesh();
		}
		else
		{
			LoadDynamicMesh();

			//LoadBones(mScene->GetRootNode());
			//LoadAnimationInfo();
		}
	}
	void FBXLoader::Import(const wstring& _path)
	{
		mpManager = FbxManager::Create();

		FbxIOSettings* pSettings = FbxIOSettings::Create(mpManager, IOSROOT);
		mpManager->SetIOSettings(pSettings);

		mpScene = FbxScene::Create(mpManager, "");
		mResourceDirectory =
			fs::path(_path).parent_path().wstring() + L"\\" + fs::path(_path).filename().stem().wstring() + L".fbm";

		mpImporter = FbxImporter::Create(mpManager, "");

		string strPath = ws2s(_path);
		mpImporter->Initialize(strPath.c_str(), -1, mpManager->GetIOSettings());

		mpImporter->Import(mpScene);
		mpScene->GetGlobalSettings().SetAxisSystem(FbxAxisSystem::DirectX);

		FbxArray<FbxString*> mNameArr;
		mpScene->FillAnimStackNameArray(mNameArr);

		if (0 < mNameArr.Size())
		{
			mbHasAnimation = true;

			for (int i = 0; i < mNameArr.Size(); ++i)
				SAFE_DELETE(mNameArr[i]);
		}

		FbxGeometryConverter geometryConverter(mpManager);
		geometryConverter.Triangulate(mpScene, true);

		mpImporter->Destroy();
	}
	void FBXLoader::ParseNode(FbxNode* _pNode)
	{
		FbxNodeAttribute* pAttribute = _pNode->GetNodeAttribute();

		if (nullptr != pAttribute)
		{
			switch (pAttribute->GetAttributeType())
			{
			case FbxNodeAttribute::eMesh:
				LoadMesh(_pNode->GetMesh());
				break;
			}
		}

		const int materialCount = _pNode->GetMaterialCount();
		for (int i = 0; i < materialCount; ++i)
		{
			FbxSurfaceMaterial* pSurfaceMaterial = _pNode->GetMaterial(i);
			LoadMaterial(pSurfaceMaterial);
		}

		const int childCount = _pNode->GetChildCount();
		for (int i = 0; i < childCount; ++i)
			ParseNode(_pNode->GetChild(i));
	}
	void FBXLoader::LoadMesh(FbxMesh* _pMesh)
	{
		mMeshes.push_back(FbxMeshInfo());
		FbxMeshInfo& meshInfo = mMeshes.back();

		meshInfo.name = s2ws(_pMesh->GetName());

		const int vertexCount = _pMesh->GetControlPointsCount();
		if (meshInfo.vertices.empty())
			meshInfo.vertices.resize(1);

		meshInfo.vertices.resize(vertexCount);
		meshInfo.boneWeights.resize(vertexCount);

		FbxVector4* controlPoints = _pMesh->GetControlPoints();
		for (int i = 0; i < vertexCount; ++i)
		{
			meshInfo.vertices[i].pos.x = static_cast<float>(controlPoints[i].mData[0]);
			meshInfo.vertices[i].pos.y = static_cast<float>(controlPoints[i].mData[2]);
			meshInfo.vertices[i].pos.z = static_cast<float>(controlPoints[i].mData[1]);
		}

		const int materialCount = _pMesh->GetNode()->GetMaterialCount();
		meshInfo.indices.resize(materialCount);

		FbxGeometryElementMaterial* pGeometryElementMaterial = _pMesh->GetElementMaterial();
		const int polygonSize = _pMesh->GetPolygonSize(0);
		AssertEx(polygonSize == 3, L"FBXLoader::LoadMesh() - 정점 개수 오류");

		UINT32 arrIdx[3];
		UINT32 vertexCounter = 0;

		const int triCount = _pMesh->GetPolygonCount();
		for (int i = 0; i < triCount; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				int controlPointIndex = _pMesh->GetPolygonVertex(i, j);
				arrIdx[j] = controlPointIndex;

				GetNormal(_pMesh, &meshInfo, controlPointIndex, vertexCounter);
				GetTangent(_pMesh, &meshInfo, controlPointIndex, vertexCounter);
				GetUV(_pMesh, &meshInfo, controlPointIndex, _pMesh->GetTextureUVIndex(i, j));

				vertexCounter++;
			}

			const UINT32 subsetIdx = pGeometryElementMaterial->GetIndexArray().GetAt(i);
			meshInfo.indices[subsetIdx].push_back(arrIdx[0]);
			meshInfo.indices[subsetIdx].push_back(arrIdx[2]);
			meshInfo.indices[subsetIdx].push_back(arrIdx[1]);
		}

		//LoadAnimationData(_pMesh, &meshInfo);
	}
	void FBXLoader::ParseNode(aiNode* _pNode, const aiScene* _pScene, Matrix _tr)
	{
		Matrix m;
		ai_real* temp = &_pNode->mTransformation.a1;
		float* mTemp = &m._11;
		for (int t = 0; t < 16; t++) {
			mTemp[t] = float(temp[t]);
		}
		m = m.Transpose() * _tr;

		for (UINT i = 0; i < _pNode->mNumMeshes; i++)
		{
			aiMesh* mesh = _pScene->mMeshes[_pNode->mMeshes[i]];
			LoadMesh(i, mesh, _pScene);
			FbxMeshInfo& meshInfo = mMeshes.back();

			for (auto& v : meshInfo.vertices) {
				v.pos = Vec3::Transform(v.pos, m);
			}
		}

		for (UINT i = 0; i < _pNode->mNumChildren; i++) {
			ParseNode(_pNode->mChildren[i], _pScene, m);
		}
	}
	void FBXLoader::LoadMaterial(FbxSurfaceMaterial* _pSurfaceMaterial)
	{
		FbxMaterialInfo material{};

		material.name = s2ws(_pSurfaceMaterial->GetName());

		material.diffuse = GetMaterialData(_pSurfaceMaterial, FbxSurfaceMaterial::sDiffuse, FbxSurfaceMaterial::sDiffuseFactor);
		material.ambient = GetMaterialData(_pSurfaceMaterial, FbxSurfaceMaterial::sAmbient, FbxSurfaceMaterial::sAmbientFactor);
		material.diffuse = GetMaterialData(_pSurfaceMaterial, FbxSurfaceMaterial::sSpecular, FbxSurfaceMaterial::sSpecularFactor);

		material.diffuseTexName = GetTextureRelativeName(_pSurfaceMaterial, FbxSurfaceMaterial::sDiffuse);
		material.normalTexName = GetTextureRelativeName(_pSurfaceMaterial, FbxSurfaceMaterial::sNormalMap);
		material.specularTexName = GetTextureRelativeName(_pSurfaceMaterial, FbxSurfaceMaterial::sSpecular);

		mMeshes.back().materials.push_back(material);

	}
	void FBXLoader::LoadMesh(int _index, aiMesh* _pMesh, const aiScene* _pScene)
	{
		mMeshes.push_back(FbxMeshInfo());
		FbxMeshInfo& meshInfo = mMeshes.back();

		meshInfo.indices.push_back(std::vector<int>());
		auto& indices = meshInfo.indices.back();

		meshInfo.name = s2ws(_pMesh->mName.C_Str());

		for (UINT32 i = 0; i < _pMesh->mNumVertices; i++) {
			Vertex vertex;

			vertex.pos.x = _pMesh->mVertices[i].x;
			vertex.pos.y = _pMesh->mVertices[i].y;
			vertex.pos.z = _pMesh->mVertices[i].z;

			vertex.normal.x = _pMesh->mNormals[i].x;
			vertex.normal.y = _pMesh->mNormals[i].y;
			vertex.normal.z = _pMesh->mNormals[i].z;
			vertex.normal.Normalize();

			if (_pMesh->mTextureCoords[0]) 
			{
				vertex.uv.x = _pMesh->mTextureCoords[0][i].x;
				vertex.uv.y = _pMesh->mTextureCoords[0][i].y;
			}

			meshInfo.vertices.push_back(vertex);
		}

		for (UINT32 i = 0; i < _pMesh->mNumFaces; i++) {
			aiFace face = _pMesh->mFaces[i];
			for (UINT32 j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		LoadMaterial(_pMesh, _pScene);
	}
	void FBXLoader::GetNormal(FbxMesh* _pMesh, FbxMeshInfo* _pContainer, int _index, int _vertexCount)
	{
		if (_pMesh->GetElementNormalCount() == 0)
			return;

		FbxGeometryElementNormal* normal = _pMesh->GetElementNormal();
		UINT32 normalIdx = 0;

		if (FbxGeometryElement::eByPolygonVertex == normal->GetMappingMode())
		{
			if (FbxGeometryElement::eDirect == normal->GetReferenceMode())
				normalIdx = _vertexCount;
			else
				normalIdx = normal->GetIndexArray().GetAt(_vertexCount);
		}

		else if (FbxGeometryElement::eByControlPoint == normal->GetMappingMode())
		{
			if (FbxGeometryElement::eDirect == normal->GetReferenceMode())
				normalIdx = _index;
			else
				normalIdx = normal->GetIndexArray().GetAt(_index);
		}

		FbxVector4 vec = normal->GetDirectArray().GetAt(normalIdx);
		_pContainer->vertices[_index].normal.x = static_cast<float>(vec.mData[0]);
		_pContainer->vertices[_index].normal.y = static_cast<float>(vec.mData[2]);
		_pContainer->vertices[_index].normal.z = static_cast<float>(vec.mData[1]);

	}
	void FBXLoader::GetTangent(FbxMesh* _pMesh, FbxMeshInfo* _pContainer, int _index, int _vertexCount)
	{
		if (_pMesh->GetElementTangentCount() == 0)
		{
			_pContainer->vertices[_index].tangent.x = 1.f;
			_pContainer->vertices[_index].tangent.y = 0.f;
			_pContainer->vertices[_index].tangent.z = 0.f;
			return;
		}

		FbxGeometryElementTangent* pTangent = _pMesh->GetElementTangent();
		UINT32 tangentIdx = 0;

		if (pTangent->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
		{
			if (pTangent->GetReferenceMode() == FbxGeometryElement::eDirect)
				tangentIdx = _vertexCount;
			else
				tangentIdx = pTangent->GetIndexArray().GetAt(_vertexCount);
		}
		else if (pTangent->GetMappingMode() == FbxGeometryElement::eByControlPoint)
		{
			if (pTangent->GetReferenceMode() == FbxGeometryElement::eDirect)
				tangentIdx = _index;
			else
				tangentIdx = pTangent->GetIndexArray().GetAt(_index);
		}

		FbxVector4 vec = pTangent->GetDirectArray().GetAt(tangentIdx);
		_pContainer->vertices[_index].tangent.x = static_cast<float>(vec.mData[0]);
		_pContainer->vertices[_index].tangent.y = static_cast<float>(vec.mData[2]);
		_pContainer->vertices[_index].tangent.z = static_cast<float>(vec.mData[1]);
	}
	void FBXLoader::LoadMaterial(aiMesh* _pMesh, const aiScene* _pScene)
	{
		FbxMeshInfo& meshInfo = mMeshes.back();
		FbxMaterialInfo materialInfo = {};

		if (_pMesh->mMaterialIndex >= 0) {
			aiMaterial* material = _pScene->mMaterials[_pMesh->mMaterialIndex];

			if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
				aiString filepath;
				material->GetTexture(aiTextureType_DIFFUSE, 0, &filepath);

				std::wstring fileName = fs::path(filepath.C_Str()).filename();
				std::wstring fullPath = mResourceDirectory + L"\\" + fileName;

				materialInfo.name = fullPath;
				materialInfo.diffuseTexName = fileName;
				meshInfo.materials.push_back(materialInfo);
			}
		}
	}
	void FBXLoader::GetUV(FbxMesh* _pMesh, FbxMeshInfo* _pContainer, int _index, int _vertexCount)
	{
		FbxGeometryElementUV* pUV = _pMesh->GetElementUV(0);

		FbxVector2 uv = pUV->GetDirectArray().GetAt(_index);
		_pContainer->vertices[_index].uv.x = static_cast<float>(uv.mData[0] - static_cast<int>(uv.mData[0]));
		_pContainer->vertices[_index].uv.y = static_cast<float>(1.f - (uv.mData[1] - static_cast<int>(uv.mData[1])));
	}
	Vec4 FBXLoader::GetMaterialData(FbxSurfaceMaterial* _pSurface, const char* _pMaterialName, const char* _pFactorName)
	{
		FbxDouble3  material;
		FbxDouble	factor = 0.f;

		FbxProperty materialProperty = _pSurface->FindProperty(_pMaterialName);
		FbxProperty factorProperty = _pSurface->FindProperty(_pFactorName);

		if (materialProperty.IsValid() && factorProperty.IsValid())
		{
			material = materialProperty.Get<FbxDouble3>();
			factor = factorProperty.Get<FbxDouble>();
		}

		Vec4 ret = Vec4(
			static_cast<float>(material.mData[0] * factor),
			static_cast<float>(material.mData[1] * factor),
			static_cast<float>(material.mData[2] * factor),
			static_cast<float>(factor));

		return ret;
	}
	wstring FBXLoader::GetTextureRelativeName(FbxSurfaceMaterial* _pSurface, const char* _pMaterialProperty)
	{
		string name;

		FbxProperty textureProperty = _pSurface->FindProperty(_pMaterialProperty);
		if (textureProperty.IsValid())
		{
			UINT32 count = textureProperty.GetSrcObjectCount();

			if (1 <= count)
			{
				FbxFileTexture* pTexture = textureProperty.GetSrcObject<FbxFileTexture>(0);
				if (pTexture)
					name = pTexture->GetRelativeFileName();
			}
		}

		return s2ws(name);
	}
	void FBXLoader::CreateTextures()
	{
		for (size_t i = 0; i < mMeshes.size(); i++)
		{
			for (size_t j = 0; j < mMeshes[i].materials.size(); j++)
			{
				// Diffuse Texture
				{
					wstring relativePath = mMeshes[i].materials[j].diffuseTexName.c_str();
					wstring filename = fs::path(relativePath).filename();
					wstring fullPath = mResourceDirectory + L"\\" + filename;
					if (filename.empty() == false)
						GET_SINGLE(Resources)->Load<Texture>(filename, fullPath);
				}

				// Normal Texture
				{
					wstring relativePath = mMeshes[i].materials[j].normalTexName.c_str();
					wstring filename = fs::path(relativePath).filename();
					wstring fullPath = mResourceDirectory + L"\\" + filename;
					if (filename.empty() == false)
						GET_SINGLE(Resources)->Load<Texture>(filename, fullPath);
				}

				// Specular Texture
				{
					wstring relativePath = mMeshes[i].materials[j].specularTexName.c_str();
					wstring filename = fs::path(relativePath).filename();
					wstring fullPath = mResourceDirectory + L"\\" + filename;
					if (filename.empty() == false)
						GET_SINGLE(Resources)->Load<Texture>(filename, fullPath);
				}
			}
		}
	}
	void FBXLoader::CreateMaterials()
	{
		for (size_t i = 0; i < mMeshes.size(); i++)
		{
			for (size_t j = 0; j < mMeshes[i].materials.size(); j++)
			{
				shared_ptr<Material> pMaterial = make_shared<Material>();
				wstring key = mMeshes[i].materials[j].name;
				pMaterial->SetName(key);
				pMaterial->SetShader(GET_SINGLE(Resources)->Get<Shader>(L"Deferred"));

				// Set Diffuse Texture
				{
					wstring diffuseName = mMeshes[i].materials[j].diffuseTexName.c_str();
					wstring filename = fs::path(diffuseName).filename();
					wstring key = filename;
					shared_ptr<Texture> pDiffuseTexture = GET_SINGLE(Resources)->Get<Texture>(key);
					if (pDiffuseTexture)
						pMaterial->SetTexture(0, pDiffuseTexture);
				}

				// Set Normal Texture
				{
					wstring normalName = mMeshes[i].materials[j].normalTexName.c_str();
					wstring filename = fs::path(normalName).filename();
					wstring key = filename;
					shared_ptr<Texture> pNormalTexture = GET_SINGLE(Resources)->Get<Texture>(key);
					if (pNormalTexture)
						pMaterial->SetTexture(1, pNormalTexture);
				}

				// Set Specular Texture
				{
					wstring specularName = mMeshes[i].materials[j].specularTexName.c_str();
					wstring filename = fs::path(specularName).filename();
					wstring key = filename;
					shared_ptr<Texture> pSpecularTexture = GET_SINGLE(Resources)->Get<Texture>(key);
					if (pSpecularTexture)
						pMaterial->SetTexture(2, pSpecularTexture);
				}

				GET_SINGLE(Resources)->Add<Material>(pMaterial->GetName(), pMaterial);
			}
		}
	}
	void FBXLoader::LoadStaticMesh()
	{
		Assimp::Importer importer;

		const aiScene* pScene = importer.ReadFile(
			ws2s(mFilePath),
			aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

		AssertEx(pScene, L"FBXLoader::LoadStaticMesh() - Scene이 생성되지 않음, FBX 파일 경로 문제일 가능성 높음");

		Matrix tr; // Initial transformations
		ParseNode(pScene->mRootNode, pScene, tr);

		Vec3 vmin(1000, 1000, 1000);
		Vec3 vmax(-1000, -1000, -1000);
		for (auto& meshInfo : mMeshes) {

			std::vector<Vertex>& vertices = meshInfo.vertices;

			for (auto& v : vertices) {
				vmin.x = XMMin(vmin.x, v.pos.x);
				vmin.y = XMMin(vmin.y, v.pos.y);
				vmin.z = XMMin(vmin.z, v.pos.z);
				vmax.x = XMMax(vmax.x, v.pos.x);
				vmax.y = XMMax(vmax.y, v.pos.y);
				vmax.z = XMMax(vmax.z, v.pos.z);
			}
		}

		float dx = vmax.x - vmin.x, dy = vmax.y - vmin.y, dz = vmax.z - vmin.z;
		float dl = XMMax(XMMax(dx, dy), dz);
		float cx = (vmax.x + vmin.x) * 0.5f, cy = (vmax.y + vmin.y) * 0.5f,
			cz = (vmax.z + vmin.z) * 0.5f;

		for (auto& meshInfo : mMeshes) {

			std::vector<Vertex>& vertices = meshInfo.vertices;

			for (auto& v : vertices) {
				v.pos.x = (v.pos.x - cx) / dl;
				v.pos.y = (v.pos.y - cy) / dl;
				v.pos.z = (v.pos.z - cz) / dl;
			}
		}

		CreateTextures();
		//CreateMaterials();

	}
	void FBXLoader::LoadDynamicMesh()
	{
		ParseNode(mpScene->GetRootNode());
		CreateTextures();
		//CreateMaterials();
	}
}