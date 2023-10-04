#pragma once

#include "Monobehavior.h"
#include "KeyDoor.h"
#include "SpikeDoor.h"

namespace yj
{
	class MonsterKeyScript : public MonoBehavior
	{
	public:
		MonsterKeyScript();
		~MonsterKeyScript() = default;

		virtual void Update()override;
		virtual Component* Clone(class GameObject* _pGameObject);
	public:
		void SendDeathTrigger();
	private:
		void AddReceiver(GameObject* _receiver) { pReceiverList.push_back(_receiver); }
	private:
		std::vector<GameObject*> pReceiverList;
	};
}

