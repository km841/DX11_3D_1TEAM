#include "pch.h"
#include "SoulDoor.h"

#include "RenderManager.h"
#include "EventManager.h"

#include "Player.h"

#include "Transform.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Input.h"
#include "Timer.h"
#include "EventSystem.h"

#include "PaperBurnScript.h"
#include "PlayerMoveOverMapScript.h"

namespace yj
{
	SoulDoor::SoulDoor(GameObject* _DoorObj, GameObject* _BackUVObj,GameObject* _EntranceCol,MapType _MapType, int _SpawnPoint)
		:GameObject(LayerType::DecoObject),
		pDoorObj(_DoorObj),
		pBackUVObj(_BackUVObj),
		pEntranceColObj(_EntranceCol),
		mSpawnPoint(_SpawnPoint),
		state(Standby),
		mMapType(_MapType)
	{
		
	}
	SoulDoor::~SoulDoor()
	{
		
	}
	
	void SoulDoor::Initialize()
	{
		pDoorObj->AddComponent<PaperBurnScript>();
		pEntranceColObj->SetName(L"SoulDoorCollider");
		pBackUVObj->Disable();
	
		if (mStartNum == 0)
		{
			pDoorObj->Disable();
			pBackUVObj->Disable();
			pEntranceColObj->Disable();
		}
		else if (mStartNum == 1)
		{

		}
	}

	void SoulDoor::Update()
	{
		
		if (IS_DOWN(KeyType::D))
		{
			pDoorObj->GetScript<PaperBurnScript>()->SetReverse(true);
			pDoorObj->GetScript<PaperBurnScript>()->SetPaperBurn();
			pDoorObj->GetScript<PaperBurnScript>()->SetFinishedCallback(std::bind(&SoulDoor::SetMove, this));
		}
		if (mOpenSequnce < 1)
		{
			if (pEntranceColObj->GetRigidBody()->GetCollider()->CheckIsCollisionObject(LayerType::Player))
			{
				if (IS_DOWN(KeyType::E))
				{
					mOpenSequnce = 1;
				}
			}
		}
	}
	void SoulDoor::FixedUpdate()
	{
		if (EVENTSYSTEM->CheckEventOn("DoorApearEvent"))
		{
			pDoorObj->GetScript<PaperBurnScript>()->SetReverse(true);
			pDoorObj->GetScript<PaperBurnScript>()->SetPaperBurn();
			pDoorObj->GetScript<PaperBurnScript>()->SetFinishedCallback(std::bind(&SoulDoor::SetMove, this));
		}
		if (GetIsMove())
		{
			Drop();
		}
		if (mOpenSequnce >= 1)
		{
			Open();
		}
	}
	void SoulDoor::Drop()
	{
		Vec3 mFramePos = pDoorObj->GetTransform()->GetPosition();
		Vec3 mFixedPos;
		switch (state)
		{
		case DoorMoveUp:
			mFixedPos = Vec3(mFramePos.x, mFramePos.y + mFlowSpeed * DELTA_TIME, mFramePos.z);
			mFlowSpeed = mFlowSpeed - mDeceleration * DELTA_TIME;
			pDoorObj->GetTransform()->SetPosition(mFixedPos);

			if (mFlowSpeed <= 0.0f)
			{
				mFlowSpeed = 0.0f;
				state = DoorMoveDown;
			}
			break;
		case DoorMoveDown:
			mFixedPos = Vec3(mFramePos.x, mFramePos.y - mDropSpeed * DELTA_TIME, mFramePos.z);
			pDoorObj->GetTransform()->SetPosition(mFixedPos);
			if (mFixedPos.y <= mDownLimit)
			{
				pDoorObj->GetTransform()->SetPosition(mFixedPos);
				isMove = false;
				state = DoorCloseStandby;
			}
			break;
		}
		pDoorObj->GetTransform()->SetPosition(mFixedPos);
		//내가 원한곳 y
	}
	void SoulDoor::Open()
	{
		pBackUVObj->Enable();
		pBackUVObj->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(1.0f, 1.0f, 1.0f, 1.0f));
		pBackUVObj->GetMeshRenderer()->GetMaterial()->SetBloom(true);
		Vec3 mFrameRot = pDoorObj->GetTransform()->GetRotation();

		pDoorObj->GetTransform()->SetRotation(Vec3(mFrameRot.x, mFrameRot.y - 20 * DELTA_TIME , mFrameRot.z));
		if (mFrameRot.y <= 160)
		{
			pDoorObj->GetTransform()->SetRotation(Vec3(mFrameRot.x, 160.0f, mFrameRot.z));
			mOpenSequnce = 0;

			PLAYER->GetScript<PlayerMoveOverMapScript>()->SetMoveOverNum(mSpawnPoint);
			GET_SINGLE(RenderManager)->AddFadeEffect(ScreenEffectType::FadeOut, 1);
			GET_SINGLE(RenderManager)->AddFadeEffect(ScreenEffectType::FadeIn, 0.5,
				std::bind(&SoulDoor::ChangeScene, this), nullptr);
		}
	}
	void SoulDoor::ChangeScene()
	{
		GET_SINGLE(EventManager)->PushSceneChangeEvent(mMapType);
	}
}	 