#pragma once
#include "GameObject.h"
#include "Selector.h"
#include "Sequence.h"
#include "BehaviorCondition.h"
#include "BehaviorTask.h"

namespace hm
{
	class Monster :
		public GameObject
	{
	public:
		Monster();
		virtual ~Monster();
		Monster* Clone()
		{
			Monster* pMonster = GameObject::Clone<Monster>();
			return pMonster;
		}

		virtual void SetBehaviorTree() { }

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();
		virtual void Destroy();

	public:
		MonsterBasicState GetBasicState() { return meBasicState; }

	protected:
		MonsterBasicState meBasicState;
	};
}


