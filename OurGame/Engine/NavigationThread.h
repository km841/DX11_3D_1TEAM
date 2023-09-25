#pragma once
#include "ThreadBase.h"
#include "ThreadQueue.h"

namespace hm
{
	class NavigationManager;
	class NavSceneComponent;
	class NavigationThread :
		public ThreadBase
	{
		friend class NavigationManager;

	public:
		NavigationThread();
		virtual ~NavigationThread();

	public:
		int GetWorkCount() { return mWorkQueue.Size(); }

		void SetNavSceneComponent(NavSceneComponent* _pNavSceneComp) { mpNavSceneComponent = _pNavSceneComp; }
		void SetNavigationManager(NavigationManager* _pNavManager) { mpNavManager = _pNavManager; }

	public:
		virtual void Run();

	public:
		void DisableCell(std::vector<Vec3>& _exceptPos);
		void DisableCell(std::vector<NavigationCell*>& _exceptCell);

		template<typename T, typename ComponentType>
		void AddWork(T* _pObj, void(T::* _func)(const std::list<Vec3>&), ComponentType* _pOwner, const Vec3& _end)
		{
			NavWorkData data;
			data.callback = std::bind(_func, _pObj, std::placeholders::_1);
			data.pTransform = static_cast<class Transform*>(_pOwner);
			data.end = _end;

			mWorkQueue.Push(data);
		}

	private:
		NavigationManager* mpNavManager;
		ThreadQueue<NavWorkData> mWorkQueue;
		NavSceneComponent* mpNavSceneComponent;
		HANDLE mExitEvent;
	};
}


