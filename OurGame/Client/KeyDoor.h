#pragma once
#include "GameObject.h"

namespace yj
{
	class KeyDoor : public GameObject
	{
	public:

		KeyDoor();
		virtual ~KeyDoor();

		virtual void Initialize();
		virtual void Update();

	public:
		virtual void SetRequireKey(int amount) { mRequireKey = amount; }
		virtual void AddKey() { mKeyAmount += 1; }
		virtual bool CheckKeyFufill() { if (mKeyAmount == mRequireKey) { return true; } else { return false; } }
		virtual void ResetKeyAmount() { mKeyAmount = 0; }

	private:

	
		int mKeyAmount = 0;
		int mRequireKey;
	};
}
