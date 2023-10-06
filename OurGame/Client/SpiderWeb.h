#pragma once
#include "GameObject.h"
#include "TimerObject.h"

namespace hm
{
	class SpiderWeb :
		public GameObject
	{
	public:
		SpiderWeb();
		virtual ~SpiderWeb();
		SpiderWeb* Clone()
		{
			SpiderWeb* pWeb = GameObject::Clone<SpiderWeb>();
			return pWeb;
		}

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

	private:
		TimerObject mTimer;
		int mBurn;
	};

}

