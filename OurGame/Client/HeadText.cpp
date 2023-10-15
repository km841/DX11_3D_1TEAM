#include "pch.h"
#include "HeadText.h"

#include "Player.h"

#include "Timer.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Factory.h"
#include "Tool.h"

namespace yj
{
	HeadText::HeadText()
	{
	}
	HeadText::~HeadText()
	{
	}
	void HeadText::Initialize()
	{
		Scene* mScene = SceneManager::GetInstance()->GetActiveScene();
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Kinematic;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(2,2,2);

			pDetector = Factory::CreateObjectHasPhysical<GameObject>(Vec3(0.f, -100.f, 0.f), physicsInfo, L"Forward", L"", false, LayerType::InterativeCol);

			mScene->AddGameObject(pDetector);
			pDetector->Initialize();
			pDetector->GetTransform()->SetPosition(mDetectorPos);
			/*TOOL->SetGameObject(pDetector);
			TOOL->UseGizmo();*/
		}
	}

	void HeadText::Update()
	{
		if (pDetector == nullptr)
		{
			return;
		}
		if (pDetector->GetRigidBody()->GetCollider()->CheckIsCollisionObject(LayerType::Player))
		{
			Increase();
			if (!this->GetGameObject()->IsEnable())
			{
				GetGameObject()->Enable();
			}
		}
		else
		{
			Decrease();
		}
	}
	Component* HeadText::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new HeadText);
	}
	void HeadText::Increase()
	{
		if (mState == Apear)
		{
			if (GetTransform()->GetScale().x < mMaxSize.x)
			{
				Vec3 mCurrScale = GetTransform()->GetScale();
				Vec3 mFixedScale = mCurrScale + Vec3(mSpeed, mSpeed, 0.0f);
				GetTransform()->SetScale(mFixedScale);
			}
			if (GetTransform()->GetScale().x >= mMaxSize.x)
			{
				GetTransform()->SetScale(Vec3(mMaxSize));
				mState = Standby;
			}
		}
	}

	void HeadText::Decrease()
	{
		if (GetTransform()->GetScale().x < mMaxSize.x)
		{
			Vec3 mCurrScale = GetTransform()->GetScale();
			Vec3 mFixedScale = mCurrScale + Vec3(mSpeed, mSpeed, 0.0f);
			GetTransform()->SetScale(mFixedScale);
		}
		if (GetTransform()->GetScale().x >= mMaxSize.x)
		{
			GetGameObject()->Disable();
			mState = Standby;
		}
	}
}