#pragma once
#include "Object.h"
namespace hm
{
	class Mesh;
	class Material;
	class GameObject;

	struct MeshRenderInfo
	{
		shared_ptr<Mesh> pMesh;
		std::vector<shared_ptr<Material>> materials;
	};

	class MeshData :
		  public Object
		, public std::enable_shared_from_this<MeshData>
	{
	public:
		MeshData();
		virtual ~MeshData();

	public:
		static shared_ptr<MeshData> LoadFromFBX(const wstring& _path, const wstring& _shaderName, bool _bInvNormal = false);
		virtual void Load(const wstring& _path) override;
		virtual void Save(const wstring& _path) override;

		shared_ptr<Mesh> GetMesh() { return mpMesh; }
		shared_ptr<Material> GetMaterial() { return mpMaterial; }
		void SetMesh(shared_ptr<Mesh> _pMesh) { mpMesh = _pMesh; }
		void SetMaterial(shared_ptr<Material> _pMaterial) { mpMaterial = _pMaterial; }

		bool HasAnimation() { return mbHasAnimation; }

	private:
		shared_ptr<Mesh> mpMesh;
		shared_ptr<Material> mpMaterial;
		bool mbHasAnimation;
		std::vector<MeshRenderInfo> mMeshRenders;

	};
}


