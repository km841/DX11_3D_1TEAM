#pragma once
#include "Event.h"
namespace hm
{
	class GameObject;
	class DeleteGameObjectEvent :
		public Event
	{
	public:
		DeleteGameObjectEvent(SceneType eSceneType, GameObject* _pGameObject);
		SceneType GetSceneType() { return meSceneType; }
		GameObject* GetGameObject() { return mpGameObject; }

	private:
		SceneType meSceneType;
		GameObject* mpGameObject;
	};

}

