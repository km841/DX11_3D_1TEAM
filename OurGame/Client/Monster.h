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

		void TakeDamage(float _float);

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();
		virtual void Destroy();

	public:
		MonsterBasicState GetBasicState() { return meBasicState; }
		void SetBasicState(MonsterBasicState _BasicState) { meBasicState = _BasicState; }

		bool GetHitCheck() { return mHitCheck; }
		void SetHitCheck(bool _hitcheck) { mHitCheck = _hitcheck; }

		bool GetIsDead() { return isDead; }
		void SetIsDead(bool _isDead) { isDead = _isDead; }

		float GetMaxHP() { return mMaxHP; }
		float GetHP() { return mHP; }
		float GetHPRatio() { return mHP / mMaxHP; }

	protected:
		MonsterBasicState meBasicState;

		bool mHitCheck = false;
		bool isDead = false;

		float mMaxHP; // 피통
		float mHP; // 피통
		float mSpeed; //이동속도
		int mAttackDamage; // 공격력
		float mAttackRange; // 공격 감지 거리
		float mRecogRange; //감지거리

		int mGroundCount;

		
	};
}


