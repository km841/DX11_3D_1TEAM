#pragma once

#include "GameObject.h"

#include "KeyDoor.h"

namespace yj
{
	class SpikeDoor : public KeyDoor
	{
	public:

		SpikeDoor(GameObject* _frameObj, GameObject* _doorCol,int _keyAmount);
		virtual ~SpikeDoor();

		virtual void Initialize();
		virtual void Update();

	private:
		void DoorMove();

	private:
		GameObject* pDoorObj;
		GameObject* pDoorColObj;
		int mOpenSquence = -1;
		float mCurrMoveDistance = 0.0f;
		float mLimitMoveDistance = 5.2f;
		float mMoveSpeed = 10.0f;
		
	};
}