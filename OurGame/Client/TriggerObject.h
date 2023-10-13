#pragma once
#include "GameObject.h"

namespace jh
{
	class TriggerObject : public GameObject
	{
	public:
		TriggerObject();
		virtual ~TriggerObject();
		TriggerObject* Clone()
		{
			TriggerObject* pTriggerObject = GameObject::Clone<TriggerObject>();
			return pTriggerObject;
		}

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnTriggerEnter(Collider* _pOther);
		virtual void OnTriggerStay(Collider* _pOther);
		virtual void OnTriggerExit(Collider* _pOther);
	};
}
