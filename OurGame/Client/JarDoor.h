#pragma once
#include "KeyDoor.h"
#include "GameObject.h"

namespace yj
{
	class JarDoor : public KeyDoor
	{
	public:
		JarDoor(int _requireKey, GameObject* _doorL, GameObject* _doorR, GameObject* _doorCol);
		virtual ~JarDoor();

		virtual void Initialize();
		virtual void Update();

	private:
		void DoorMove();

	private:
		GameObject* pDoorObjs[2];
		GameObject* pDoorColObj;
		int mOpenSquence = -1;
		float mCurrMoveDistance = 0.0f;
		float mLimitMoveDistance = 5.2f;
		float mMoveSpeed = 10.0f;

	};
}

