#pragma once
#include "GameObject.h"
#include "SceneManager.h"


namespace yj
{
	class TeleportZone : public GameObject
	{
	public:
		TeleportZone(MapType _mSceneType, int _mSpawnPoint);
		virtual ~TeleportZone();

		virtual void Update();


	public:
		virtual void OnTriggerEnter(Collider* _pOtherCollider);


	private:
		bool CheckPlayerIn();
		void ChangeScene();
	private:
		MapType mMapType;
		
		bool isActive = false;
		int mSpawnPoint = -1;
	};
}

