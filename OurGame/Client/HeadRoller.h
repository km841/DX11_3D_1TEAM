#pragma once
#include "Monster.h"

namespace hm
{
	class HeadRoller :
		public Monster
	{
	public:
		HeadRoller();
		virtual ~HeadRoller();
		HeadRoller* Clone()
		{
			HeadRoller* pMonster = GameObject::Clone<HeadRoller>();
			return pMonster;
		}

		virtual void SetBehaviorTree();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();
		virtual void Destroy();

	public:
		virtual void OnCollisionEnter(Collider* _pOtherCollider);
		virtual void OnCollisionStay(Collider* _pOtherCollider);
		virtual void OnCollisionExit(Collider* _pOtherCollider);

		virtual void OnTriggerEnter(Collider* _pOtherCollider);
		virtual void OnTriggerStay(Collider* _pOtherCollider);
		virtual void OnTriggerExit(Collider* _pOtherCollider);


	public:
		bool GetisRoll() { return isRoll; }
		void SetisRoll(bool _is) { isRoll = _is; }

		bool GetisRollStay() { return isRollStay; }
		void SetisRollStay(bool _is) { isRollStay = _is; }
	private:
		Vec3 attackDir = Vec3::Zero;
		Vec3 traceDir = Vec3::Zero;
		Vec3 stunDir = Vec3::Zero;

		bool isRoll = false;
		bool isRollStay = false;
		
	};
}


