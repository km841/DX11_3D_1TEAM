#include "pch.h"
#include "SceneChangeEvent.h"

namespace hm
{
	SceneChangeEvent::SceneChangeEvent(SceneType eSceneType)
		: meSceneType(eSceneType)
	{
		meEventType = EventType::ChangeScene;
	}
}

