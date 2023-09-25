#include "pch.h"
#include "FireLamp.h"

#include "Transform.h"
#include "Timer.h"
#include "Input.h"

namespace yj
{
	FireLamp::FireLamp(GameObject* _UpperPart, GameObject* _BelowPart)
		:GameObject(LayerType::Item)
	{
		pUpperPart = _UpperPart;
		pBelowPart = _BelowPart;
	}
	FireLamp::~FireLamp()
	{
	}
	void FireLamp::Initialize()
	{
		GameObject::Initialize();
	}
	void FireLamp::Update()
	{
		GameObject::Update();
		if (IS_DOWN(KeyType::R))
		{
			if (mLampSequence == -1)
			{
				mLampSequence = 1;
			}
		}
		if (mLampSequence > 0)
		{
			Active();
		}
	}
	void FireLamp::Render()
	{
		GameObject::Render();
	}
	void FireLamp::Active()
	{
		if (mLampSequence == 1)
		{
			Vec3 mUpperPartPos = pUpperPart->GetTransform()->GetPosition();
			Vec3 mFixedUpperPartPos;

			mFixedUpperPartPos = Vec3(mUpperPartPos.x, mUpperPartPos.y + mFlowSpeed * DELTA_TIME, mUpperPartPos.z);
			mCurrFlowDist = mCurrFlowDist + mFlowSpeed * DELTA_TIME;

			if (mCurrFlowDist >= mFlowLimit)
			{
				pUpperPart->GetTransform()->SetPosition(mFixedUpperPartPos);
				mLampSequence = 2;
			}
			pUpperPart->GetTransform()->SetPosition(mFixedUpperPartPos);
		}
		if (mLampSequence == 2)
		{
			Vec3 mUpperPartRot = pUpperPart->GetTransform()->GetRotation();
			Vec3 mFixedUpperPartRot;

			mFixedUpperPartRot = Vec3(mUpperPartRot.x, mUpperPartRot.y + mTurnSpeed * DELTA_TIME, mUpperPartRot.z);
			pUpperPart->GetTransform()->SetRotation(mFixedUpperPartRot);
		}
	}
}