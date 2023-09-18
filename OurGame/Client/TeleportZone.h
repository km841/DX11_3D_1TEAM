#pragma once
#include "GameObject.h"
#include "SceneManager.h"


namespace yj
{
	class TeleportZone : public GameObject
	{
	public:
		TeleportZone(MapType _mSceneType);
		virtual ~TeleportZone();

		virtual void Update();

	private:
		MapType mMapType;
		
		bool isActive = false;
		bool CheckPlayerIn();
		void ChangeScene();

	};
}

