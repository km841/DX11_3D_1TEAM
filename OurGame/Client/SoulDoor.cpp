#include "pch.h"
#include "SoulDoor.h"
#include "Transform.h"
#include "Timer.h"

namespace yj
{
	void SoulDoor::Update()
	{
	}
	void SoulDoor::Drop()
	{
		Vec3 mFramePos = pFrame->GetTransform()->GetPosition();
		switch (state)
		{
		case Standby:

			break;
		case Apear:

			break;
		case MoveUp:
			Vec3 mFixedPos = Vec3(mFramePos.x, mFramePos.y + mCurrAddSpeed * DELTA_TIME, mFramePos.z);
			mCurrAddSpeed = mCurrAddSpeed - mDeceleration * DELTA_TIME;
			pFrame->GetTransform()->SetPosition(mFixedPos);

			if (mCurrAddSpeed <= 0.0f)
			{
				mCurrAddSpeed = mInitAddSpeed;
				state = MoveDown;
			}
			break;
		case MoveDown:
			Vec3 mFixedPos = Vec3(mFramePos.x, mFramePos.y + mDropSpeed * DELTA_TIME, mFramePos.z);
			pFrame->GetTransform()->SetPosition(mFixedPos);
			if (mFixedPos.y <= mDownLimit)
			{
				state = CloseStandby;
			}
			break;
		case CloseStandby:

			break;
		case Open:

			break;
		}


		//내가 원한곳 y
	}
}	 