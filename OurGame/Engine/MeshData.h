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
	{
	public:
		MeshData();
		virtual ~MeshData();

	public:
		static shared_ptr<MeshData> LoadFromFBX(const wstring& _path);
		virtual void Load(const wstring& _path) override;
		virtual void Save(const wstring& _path) override;

		GameObject* Instantiate();

		shared_ptr<Mesh> GetMesh() { return mpMesh; }
		shared_ptr<Material> GetMaterial() { return mpMaterial; }
		void SetMesh(shared_ptr<Mesh> _pMesh) { mpMesh = _pMesh; }
		void SetMaterial(shared_ptr<Material> _pMaterial) { mpMaterial = _pMaterial; }

	private:
		shared_ptr<Mesh> mpMesh;
		shared_ptr<Material> mpMaterial;
		std::vector<MeshRenderInfo> mMeshRenders;
	};
}


