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

		bool GetIsDead() { return isDead; }
		void SetIsDead(bool _isDead) { isDead = _isDead; }

		float GetMaxHP() { return mMaxHP; }
		float GetHP() { return mHP; }
		float GetHPRatio() { return mHP / mMaxHP; }

		bool GetAttackCheck() { return isAttackCheck; }
		void SetAttackCheck(bool _hitcheck) { isAttackCheck = _hitcheck; }

		bool GetGODState() { return isGODState; }
		void SetGODState(bool _isGODState) { isGODState = _isGODState; }

		void CheckPenetration(RigidBody* _rigidBody, LayerType _eLayertype);
	protected: //몬스터 공격 체크
		bool isAttackCheck = false;
		bool isGODState = false;

	protected: 
		MonsterBasicState meBasicState;

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


