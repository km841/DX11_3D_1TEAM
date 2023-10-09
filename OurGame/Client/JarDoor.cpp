#include "pch.h"
#include "JarDoor.h"

#include "Transform.h"
#include "Timer.h"

namespace yj
{
	JarDoor::JarDoor(int _requireKey, GameObject* _doorL, GameObject* _doorR, GameObject* _doorCol)
	{
		SetRequireKey(_requireKey);
		pDoorObjs[0] = _doorL;
		pDoorObjs[1] = _doorR;
		pDoorColObj = _doorCol;
	}
	

	JarDoor::~JarDoor()
	{

	}

	void JarDoor::Initialize()
	{
		GameObject::Initialize();
	}

	void JarDoor::Update()
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

	void JarDoor::DoorMove()
	{
		Vec3 mLDoorPos = pDoorObjs[0]->GetTransform()->GetPosition();
		Vec3 mLFixedPos = Vec3(mLDoorPos.x + mMoveSpeed * DELTA_TIME, mLDoorPos.y , mLDoorPos.z);
		pDoorObjs[0]->GetTransform()->SetPosition(mLFixedPos);

		Vec3 mRDoorPos = pDoorObjs[1]->GetTransform()->GetPosition();
		Vec3 mRFixedPos = Vec3(mRDoorPos.x - mMoveSpeed * DELTA_TIME, mRDoorPos.y , mRDoorPos.z);
		pDoorObjs[1]->GetTransform()->SetPosition(mRFixedPos);

		mCurrMoveDistance = mCurrMoveDistance + mMoveSpeed * DELTA_TIME;

		if (mCurrMoveDistance >= mLimitMoveDistance)
		{
			pDoorColObj->GetTransform()->SetPosition(Vec3(10000.0f,10000.0f,10000.0f));
			mOpenSquence = 0;
		}
	}
}