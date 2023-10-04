#include "pch.h"
#include "MonsterKeyScript.h"

namespace yj
{
	MonsterKeyScript::MonsterKeyScript()
	{

	}
	
	void MonsterKeyScript::Update()
	{
	}

	Component* MonsterKeyScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new MonsterKeyScript);
	}
	void MonsterKeyScript::SendDeathTrigger()
	{
		for (int i = 0; i < pReceiverList.size(); i++)
		{
			if (pReceiverList[i]->GetScript<KeyDoor>())
			{
				pReceiverList[i]->GetScript<KeyDoor>()->AddKey();
			}
			if (pReceiverList[i]->GetScript<SpikeDoor>())
			{
				pReceiverList[i]->GetScript<SpikeDoor>()->AddKey();
			}
		}
	}
}
