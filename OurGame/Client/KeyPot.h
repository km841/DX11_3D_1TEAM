#pragma once

#include "GameObject.h"

#include "JarDoor.h"


namespace yj
{
	class KeyPot : public GameObject
	{
	public:
		KeyPot();
		virtual ~KeyPot();
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		KeyPot* Clone()
		{
			KeyPot* pKeyPot = GameObject::Clone<KeyPot>();
			return pKeyPot;
		}
	public:
		void SetReceiver(JarDoor* _receiver);
		void CheckHitBySword();
		void Break();

		bool GetIsBreak() { return isBreak; }
		int mBreakSequence = -1;

		virtual void OnTriggerEnter(Collider* _pOther);
		virtual void OnTriggerStay(Collider* _pOther);
		virtual void OnTriggerExit(Collider* _pOther);

	private:

		bool isBreak;
		JarDoor* pReceiver;
		GameObject* pGlowFly;
	};
}
