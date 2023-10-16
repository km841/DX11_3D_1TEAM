#include "pch.h"
#include "FireLamp.h"

#include "Transform.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "Timer.h"
#include "Input.h"
#include "ArrowScript.h"
#include "Player.h"
#include "AudioSound.h"
#include "SceneManager.h"

namespace yj
{
	FireLamp::FireLamp(GameObject* _UpperPart, GameObject* _BelowPart, GameObject* _Fire, GameObject* _Light)
		:GameObject(LayerType::Item)
	{
		pUpperPart = _UpperPart;
		pBelowPart = _BelowPart;
		pFire = _Fire;
		pLight = _Light;
		pFire->Disable();
		pLight->Disable();

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

		if (true == isBurn)
		{
			pFire->Enable();
			pLight->Enable();
		}

	}

	void FireLamp::Render()
	{
		GameObject::Render();
	}

	void FireLamp::OnCollisionEnter(Collider* pOtherCollider)
	{
		if (pOtherCollider->GetGameObject()->GetLayerType() == LayerType::ArrowCol)
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
				if (pOtherCollider->GetGameObject()->GetScript<ArrowScript>()->GetIsBurn())
				{
					if (false == isBurn)
					{
						PLAYER->GetAudioSound()->SetSound(L"Burn", GET_SINGLE(SceneManager)->GetActiveScene(), false, "..\\Resources\\Sound\\Burn.mp3");
						PLAYER->GetAudioSound()->Play();
					}

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