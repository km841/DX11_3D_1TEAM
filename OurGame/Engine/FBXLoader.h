#pragma once

namespace hm
{
	struct FbxMaterialInfo
	{
		Vec4 diffuse;
		Vec4 ambient;
		Vec4 specular;
		wstring name;
		wstring diffuseTexName;
		wstring normalTexName;
		wstring specularTexName;
	};

	struct BoneWeight
	{
		using Pair = std::pair<int, double>;
		std::vector<Pair> boneWeights;

		void AddWeights(UINT32 _index, double _weight)
		{
			if (_weight <= 0.f)
				return;

			auto findIt = std::find_if(boneWeights.begin(), boneWeights.end(),
				[=](const Pair& p) { return p.second < _weight; });

			if (findIt != boneWeights.end())
				boneWeights.insert(findIt, Pair(_index, _weight));
			else
				boneWeights.push_back(Pair(_index, _weight));

			if (boneWeights.size() > 4)
				boneWeights.pop_back();
		}

		void Normalize()
		{
			double sum = 0.f;
			std::for_each(boneWeights.begin(), boneWeights.end(), [&](Pair& p) {sum += p.second; });
			std::for_each(boneWeights.begin(), boneWeights.end(), [=](Pair& p) { p.second = p.second / sum; });
		}
	};

	struct FbxMeshInfo
	{
		wstring name;
		std::vector<Vertex> vertices;
		std::vector<std::vector<int>> indices;
		std::vector<FbxMaterialInfo> materials;
		std::vector<BoneWeight> boneWeights;
		bool bHasAnimation;
	};

	struct FbxKeyFrameInfo
	{
		FbxAMatrix matTransform;
		double time;
	};

	struct FbxBoneInfo
	{
		wstring boneName;
		int parentIndex;
		FbxMatrix matOffset;
	};

	struct FbxAnimClipInfo
	{
		wstring name;
		FbxTime startTime;
		FbxTime endTime;
		FbxTime::EMode mode;
		std::vector<std::vector<FbxKeyFrameInfo>> keyFrames;
	};

	class FBXLoader
	{
	public:
		FBXLoader();
		~FBXLoader();

	public:
		void LoadFbx(const wstring& _path);

	public:
		int GetMeshCount() { return static_cast<int>(mMeshes.size()); }
		const FbxMeshInfo& GetMesh(int _index) { return mMeshes[_index]; }
		const std::vector<FbxMeshInfo>& GetMeshes() { return mMeshes; }
		std::vector<shared_ptr<FbxBoneInfo>>& GetBones() { return mBones; }
		std::vector<shared_ptr<FbxAnimClipInfo>>& GetAnimClip() { return mAnimClips; }
		void SetNormalDirection(bool _bInvNormal) { mbInvNormal = _bInvNormal; }

	private:
		void Import(const wstring& _path);
		void ParseNode(FbxNode* _pRoot);
		void ParseNode(aiNode* _pNode, const aiScene* _pScene, Matrix _tr);
		void LoadMesh(FbxMesh* _pMesh);
		void LoadMesh(int _index, aiMesh* _pMesh, const aiScene* _pScene);
		void LoadMaterial(FbxSurfaceMaterial* _pSurfaceMaterial);
		void LoadMaterial(aiMesh* _pMesh, const aiScene* _pScene);

		void GetNormal(FbxMesh* _pMesh, FbxMeshInfo* _pContainer, int _index, int _vertexCount);
		void GetTangent(FbxMesh* _pMesh, FbxMeshInfo* _pContainer, int _index, int _vertexCount);
		void GetUV(FbxMesh* _pMesh, FbxMeshInfo* _pContainer, int _index, int _vertexCount);

		Vec4 GetMaterialData(FbxSurfaceMaterial* _pSurface, const char* _pMaterialName, const char* _pFactorName);
		wstring GetTextureRelativeName(FbxSurfaceMaterial* _pSurface, const char* _pMaterialProperty);

		void CreateTextures();
		void CreateMaterials();

		void LoadStaticMesh();
		void LoadDynamicMesh();

		

	private:
		FbxManager* mpManager = nullptr;
		FbxScene* mpScene = nullptr;
		FbxImporter* mpImporter = nullptr;
		wstring mResourceDirectory;
		wstring mFilePath;

		std::vector<FbxMeshInfo> mMeshes;
		std::vector<shared_ptr<FbxBoneInfo>> mBones;
		std::vector<shared_ptr<FbxAnimClipInfo>> mAnimClips;
		FbxArray<FbxString*> mAnimNames;

		bool mbHasAnimation;
		bool mbInvNormal;
	};
}
