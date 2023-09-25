#pragma once

namespace hm
{
	class NavMesh;
	class Material;
	class NavSceneComponent
	{
		friend class GameObject;
		friend class Camera;
		friend class NavigationThread;

	public:
		NavSceneComponent();
		virtual ~NavSceneComponent();

	public:
		void Initialize();
		void Update();
		void Render();

	public:
		void SetPlayerSpawnPolyIndex(int _index) { mPlayerSpawnPolyIndex = _index; }
		int  GetPlayerSpawnPolyIndex() { return mPlayerSpawnPolyIndex; }
		void SetPlayerSpawnPos(const Vec3& _pos) { mPlayerSpawnPos = _pos; }
		const Vec3& GetPlayerSpawnPos() { return mPlayerSpawnPos; }
		shared_ptr<NavMesh> GetNavMesh() { return mpNavMesh; }
		void SetNavMesh(const wstring& _name);
		void SetNavMesh(shared_ptr<NavMesh> _pNavMesh) { mpNavMesh = _pNavMesh; }

	protected:
		shared_ptr<NavMesh> mpNavMesh;
		shared_ptr<Material> mpMaterial;

		Vec3 mPlayerSpawnPos;
		int mPlayerSpawnPolyIndex;

		std::list<NavigationCell*> mUseCellList;
		std::list<NavigationCell*> mOpenList;
		std::list<NavigationCell*> mCloseList;
		std::unordered_map<int, NavigationCell*> mCellMap;
	};
}


