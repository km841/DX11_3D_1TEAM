#include "pch.h"
#include "DeleteGameObjectEvent.h"

namespace hm
{
	DeleteGameObjectEvent::DeleteGameObjectEvent(SceneType eSceneType, GameObject* _pGameObject)
		: meSceneType(eSceneType)
		, mpGameObject(_pGameObject)
	{
		meEventType = EventType::DeleteGameObjectEvent;
	}

}
