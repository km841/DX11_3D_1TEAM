#include "pch.h"
#include "ManaIconScript.h"

#include "Timer.h"
#include "GameObject.h"

namespace yj
{
	ManaIconScript::ManaIconScript()
		:mSpeed(30.0f)
	{
		mSize[0] = 12;
		mSize[1] = 15;
	}

	ManaIconScript::~ManaIconScript()
	{
	}

	void ManaIconScript::Initialize()
	{
	}

	void ManaIconScript::Update()
	{
		if (mSequence == ApearSeq)
		{
			Vec3 mScale = this->GetTransform()->GetScale();

			float mIncreaseSize = 0;

			if (isBigger)
			{
				mIncreaseSize = mSize[1];
			}
			else
			{
				mIncreaseSize = mSize[0];
			}
			if (this->GetTransform()->GetScale().x < mIncreaseSize)
			{
				Vec3 mFixedScale = mScale += Vec3(DELTA_TIME * mSpeed,DELTA_TIME * mSpeed, 0.0f);
				this->GetTransform()->SetScale(mFixedScale);
			}

			if (mScale.x >= mIncreaseSize)
			{
				this->GetTransform()->SetScale(Vec3(15.f, 18.0, 0.0f));
				mSequence = Standby;
			}
		}
		if (mSequence == DisapearSeq)
		{
			Vec3 mScale = this->GetTransform()->GetScale();

			float mIncreaseSize = 0;

			if (this->GetTransform()->GetScale().x >= 0.05f )
			{
				Vec3 mFixedScale = mScale += Vec3(DELTA_TIME * mSpeed, DELTA_TIME * mSpeed, 1.0f);
				this->GetTransform()->SetScale(mFixedScale);
			}

			if (mScale.x < 0.05f)
			{
				this->GetTransform()->SetScale(Vec3(0.05f, 0.05f, 1.0f));
				mSequence = Standby;
				GetGameObject()->Disable();
			}
		}
	}

	Component* ManaIconScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new ManaIconScript);

	}

	void ManaIconScript::Apear()
	{
		mSequence = ApearSeq;
		this->GetTransform()->SetScale(Vec3(0.15f, 0.18f,1.0f));
	}

	void ManaIconScript::Decrease()
	{
		mSequence = DisapearSeq;
	}

}