#include "pch.h"
#include "RemoveGameObjectEvent.h"
namespace hm
{
	RemoveGameObjectEvent::RemoveGameObjectEvent(SceneType eSceneType, GameObject* _pGameObject)
		: meSceneType(eSceneType)
		, mpGameObject(_pGameObject)
	{
		meEventType = EventType::RemoveGameObjectEvent;
	}
}