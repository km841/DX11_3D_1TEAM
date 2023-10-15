#include "pch.h"
#include "LaserLockOnScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Player.h"
#include "RenderManager.h"
#include "Timer.h"
#include "Collider.h"
#include "Camera.h"
#include "SceneManager.h"
#include "Input.h"
#include "BossLaser.h"
#include "LORD_BOSS.h"
#include "EventManager.h"

namespace hm
{
	LaserLockOnScript::LaserLockOnScript(GameObject* _pBoss)
		: mFlipWidth(0.1f)
		, mpBoss(_pBoss)
	{
		mDuration.SetEndTime(0.05f);
		mDuration.Start();
		mDeleteTimer.SetEndTime(4.5f);
		mDeleteTimer.Start();
	}
	void LaserLockOnScript::Initialize()
	{
	}
	void LaserLockOnScript::FixedUpdate()
	{
		Vec3 myPos = GetTransform()->GetPosition();
		Vec3 camPos = GET_SINGLE(SceneManager)->GetActiveScene()->GetMainCamera()->GetTransform()->GetPosition();
		Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
		
		if (false == mPlayerPath.empty())
		{
			Vec3 targetPos = mPlayerPath.front();
			mPlayerPath.pop();

			Vec3 targetDir = targetPos - myPos;
			targetDir.Normalize();

			GetTransform()->SmoothRotateTo(targetDir);

			mFlipWidth = -mFlipWidth;
			GetTransform()->SetScale(Vec3(1.f + mFlipWidth, 3.f, 3.f));
			if (mpBoss->IsRaysCollide(myPos, targetDir, LayerType::Ground, 100.f))
			{
				float distance = mpBoss->GetCollider()->GetRaycastHit().distance;
				GetTransform()->SetScale(Vec3(1.f + mFlipWidth, 3.f, distance / 2.f));
			}
		}

		mDuration.Update();
		if (mDuration.IsFinished())
		{
			mDuration.Stop();
			mDuration.Start();
			mPlayerPath.push(PLAYER->GetTransform()->GetPosition());
		}

		mDeleteTimer.Update();
		if (mDeleteTimer.IsFinished())
		{
			GET_SINGLE(RenderManager)->SetBloomScale(1.0f);
			MapType type = GET_SINGLE(SceneManager)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->PushDeleteGameObjectEvent(type, static_cast<GameObject*>(GetGameObject()));
		}
	}

	Component* LaserLockOnScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new LaserLockOnScript(mpBoss));
	}
}