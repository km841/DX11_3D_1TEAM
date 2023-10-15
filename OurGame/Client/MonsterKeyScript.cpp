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
			if (pReceiverList[i]->GetName() == L"KeyDoor")
			{
				static_cast<KeyDoor*>(pReceiverList[i])->AddKey();
			}
			if (pReceiverList[i]->GetName() == L"SpikeDoor")
			{
				static_cast<SpikeDoor*>(pReceiverList[i])->AddKey();
			}
		}
	}
}
