#include "pch.h"
#include "SpikeDoor.h"

#include "Transform.h"
#include "Timer.h"

namespace yj
{
	SpikeDoor::SpikeDoor(GameObject* _frameObj, GameObject* _doorCol,int _keyAmount)
	{
		pDoorObj = _frameObj;
		pDoorColObj = _doorCol;
		SetRequireKey(_keyAmount);

		mName = L"SpikeDoor";
	}

	SpikeDoor::~SpikeDoor()
	{
	}

	void SpikeDoor::Initialize()
	{
		GameObject::Initialize();
	}

	void SpikeDoor::Update()
	{
		GameObject::Update();
		if (mOpenSquence == -1)
		{
			if (CheckKeyFufill())
			{
				mOpenSquence = 1;
			}
		}

		if (mOpenSquence > 0)
		{
			DoorMove();
		}
	}

	void SpikeDoor::DoorMove()
	{
		Vec3 mDoorPos = pDoorObj->GetTransform()->GetPosition();
		Vec3 mFixedPos = Vec3(mDoorPos.x , mDoorPos.y - mMoveSpeed * DELTA_TIME, mDoorPos.z);
		pDoorObj->GetTransform()->SetPosition(mFixedPos);

		mCurrMoveDistance = mCurrMoveDistance + mMoveSpeed * DELTA_TIME;

		if (mCurrMoveDistance >= mLimitMoveDistance)
		{
			pDoorColObj->Disable();
			mOpenSquence = 0;
		}
	}
}