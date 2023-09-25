#include "pch.h"
#include "FireLamp.h"

#include "Transform.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "Timer.h"
#include "Input.h"
#include "ArrowScript.h"

namespace yj
{
	FireLamp::FireLamp(GameObject* _UpperPart, GameObject* _BelowPart)
		:GameObject(LayerType::Item)
	{
		pUpperPart = _UpperPart;
		pBelowPart = _BelowPart;
		this->SetName(L"FireLamp");
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

	void FireLamp::OnCollisionEnter(Collider* pOtherCollider)
	{
		if (pOtherCollider->GetGameObject()->GetLayerType() == LayerType::ArrowCols)
		{

		}
	}
	void FireLamp::OnCollisionStay(Collider* pOtherCollider)
	{

	}
	void FireLamp::OnCollisionExit(Collider* pOtherCollider)
	{

	}
	void FireLamp::OnTriggerEnter(Collider* pOtherCollider)
	{
		if (GetIsBurn())
		{
			if (pOtherCollider->GetGameObject()->GetLayerType() == LayerType::ArrowCol)
			{
				//상대 화살에 불을 붙여준다
				pOtherCollider->GetGameObject()->GetScript<ArrowScript>()->SetBurn();
			}
		}
		else
		{
			if (pOtherCollider->GetGameObject()->GetLayerType() == LayerType::ArrowCol)
			{
				if (pOtherCollider->GetGameObject()->GetScript<ArrowScript>()->GetIsBurn());
				{
					isBurn = true;
					if (mLampSequence == -1)
					{
						mLampSequence = 1;
					}
				}
			}
		}
	}
	void FireLamp::OnTriggerStay(Collider* pOtherCollider)
	{

	}
	void FireLamp::OnTriggerExit(Collider* pOtherCollider)
	{

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