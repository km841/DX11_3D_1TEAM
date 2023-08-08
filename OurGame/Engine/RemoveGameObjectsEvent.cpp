#include "pch.h"
#include "RemoveGameObjectsEvent.h"
namespace hm
{
	RemoveGameObjectsEvent::RemoveGameObjectsEvent(SceneType _eSceneType, LayerType _eLayerType)
		: meSceneType(_eSceneType)
		, meLayerType(_eLayerType)
	{
		meEventType = EventType::RemoveGameObjectsEvent;
	}
}