#pragma once
#include "Event.h"
namespace hm
{
	class GameObject;
	class RemoveGameObjectEvent :
		public Event
	{
	public:
		RemoveGameObjectEvent(SceneType eSceneType, GameObject* _pGameObject);
		SceneType GetSceneType() { return meSceneType; }
		GameObject* GetGameObject() { return mpGameObject; }

	private:
		SceneType meSceneType;
		GameObject* mpGameObject;
	};
}
