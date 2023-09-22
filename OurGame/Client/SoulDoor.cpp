#include "pch.h"
#include "SoulDoor.h"

#include "Transform.h"

#include "Input.h"
#include "Timer.h"
#include "PaperBurnScript.h"

namespace yj
{
	SoulDoor::SoulDoor(GameObject* _frameObj, GameObject* _doorObj)
		:GameObject(LayerType::DecoObject),
		pFrame(_frameObj),
		pDoor(_doorObj),
		state(Standby),
		mDeceleration(3.0f),
		isMove(false),
		mDropSpeed(30.0f),
		mDownLimit(5.1f)
	{
		
	}
	SoulDoor::~SoulDoor()
	{
		
	}
	
	void SoulDoor::Initialize()
	{
		pFrame->AddComponent<PaperBurnScript>();
	}

	void SoulDoor::Update()
	{

		if (IS_DOWN(KeyType::D))
		{
			pFrame->GetScript<PaperBurnScript>()->SetReverse(true);
			pFrame->GetScript<PaperBurnScript>()->SetPaperBurn();
			pFrame->GetScript<PaperBurnScript>()->SetFinishedCallback(std::bind(&SoulDoor::Drop,this));
		}

		if (GetIsMove())
		{
			Drop();
		}
	}
	void SoulDoor::Drop()
	{
		Vec3 mFramePos = pFrame->GetTransform()->GetPosition();
		Vec3 mFixedPos;
		switch (state)
		{
		case MoveUp:
			mFixedPos = Vec3(mFramePos.x, mFramePos.y + mCurrSpeed * DELTA_TIME, mFramePos.z);
			mCurrSpeed = mCurrSpeed - mDeceleration * DELTA_TIME;
			pFrame->GetTransform()->SetPosition(mFixedPos);

			if (mCurrSpeed <= 0.0f)
			{
				mCurrSpeed = mInitAddSpeed;
				state = MoveDown;
			}
			break;
		case MoveDown:
			mFixedPos = Vec3(mFramePos.x, mFramePos.y - mDropSpeed * DELTA_TIME, mFramePos.z);
			pFrame->GetTransform()->SetPosition(mFixedPos);
			if (mFixedPos.y <= mDownLimit)
			{
				pFrame->GetTransform()->SetPosition(mFixedPos);
				isMove = false;
				state = CloseStandby;
			}
			break;
		}
		pFrame->GetTransform()->SetPosition(mFixedPos);
		//내가 원한곳 y
	}
}	 