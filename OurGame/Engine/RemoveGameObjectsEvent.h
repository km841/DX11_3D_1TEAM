#pragma once
#include "Event.h"
namespace hm
{
	class GameObject;
	class RemoveGameObjectsEvent :
		public Event
	{
	public:
		RemoveGameObjectsEvent(SceneType _eSceneType, LayerType _eLayerType);
		SceneType GetSceneType() { return meSceneType; }
		LayerType GetLayerType() { return meLayerType; }

	private:
		SceneType meSceneType;
		LayerType meLayerType;
	};
}
