#include "pch.h"
#include "PlayerMoveOverMapScript.h"

namespace yj
{
	PlayerMoveOverMapScript::PlayerMoveOverMapScript()
	{
	}
	Component* PlayerMoveOverMapScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new PlayerMoveOverMapScript);
	}
}
