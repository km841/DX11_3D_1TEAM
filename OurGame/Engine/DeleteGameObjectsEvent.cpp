#include "pch.h"
#include "DeleteGameObjectsEvent.h"

namespace hm
{
	DeleteGameObjectsEvent::DeleteGameObjectsEvent(SceneType _eSceneType, LayerType _eLayerType)
		: meSceneType(_eSceneType)
		, meLayerType(_eLayerType)
	{
		meEventType = EventType::DeleteGameObjectsEvent;
	}
}