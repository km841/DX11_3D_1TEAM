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
#include "Factory.h"
#include "OwnerFollowScript.h"

namespace hm
{
	LaserLockOnScript::LaserLockOnScript(GameObject* _pBoss)
		: mFlipWidth(0.1f)
		, mpBoss(_pBoss)
		, mbInitAngleSetting(false)
		, mbHitFlag(false)
	{
		mDuration.SetEndTime(0.01f);
		mDuration.Start();

		mDeleteTimer.SetEndTime(4.5f);
		mDeleteTimer.Start();

		mStartDuration.SetEndTime(1.f);
		mStartDuration.Start();

		mScaleTimer.SetEndTime(1.f);
		mScaleTimer.Start();
	}
	void LaserLockOnScript::Initialize()
	{
	}
	void LaserLockOnScript::FixedUpdate()
	{
		if (nullptr == mpMarker)
		{
			CreateMarker();
		}

		Vec3 myPos = GetTransform()->GetPosition();
		Vec3 camPos = GET_SINGLE(SceneManager)->GetActiveScene()->GetMainCamera()->GetTransform()->GetPosition();
		Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
		if (false == mbInitAngleSetting)
		{
			GetTransform()->LookAt(playerPos - myPos);
			mbInitAngleSetting = true;
		}
		
		mScaleTimer.Update();
		mStartDuration.Update();
		if (false == mPlayerPath.empty())
		{
			Vec3 targetPos = mPlayerPath.front();
			mPlayerPath.pop();

			Vec3 targetDir = targetPos - myPos;
			targetDir.Normalize();

			GetTransform()->SmoothRotateTo(targetDir);

			mFlipWidth = -mFlipWidth;
			GetTransform()->SetScale(Vec3(1.f + mFlipWidth, 3.f, 3.f));
			Vec3 lookDir = GetTransform()->GetLook();
			if (mpBoss->IsRaysCollide(myPos, lookDir, LayerType::Ground, 100.f))
			{
				float distance = mpBoss->GetCollider()->GetRaycastHit().distance;

				float scaleX = Lerp(0.f, 1.f, mScaleTimer.GetProgress());
				GetTransform()->SetScale(Vec3(scaleX + mFlipWidth, 3.f, distance / 2.f));

				if (nullptr != mpMarker)
					mpMarker->GetTransform()->SetPosition(mpBoss->GetCollider()->GetRaycastHit().position);
			}

			if (mStartDuration.IsFinished() && false == mbHitFlag && mpBoss->IsRaysCollide(myPos, lookDir, LayerType::Player, 100.f))
			{
				mbHitFlag = true;
				PLAYER->GetDamage();
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

			if (nullptr != mpMarker)
			{
				MapType type = GET_SINGLE(SceneManager)->GetActiveScene()->GetSceneType();
				GET_SINGLE(EventManager)->PushDeleteGameObjectEvent(type, mpMarker);
			}
		}
	}

	Component* LaserLockOnScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new LaserLockOnScript(mpBoss));
	}
	void LaserLockOnScript::CreateMarker()
	{
		mpMarker = Factory::CreateObject<GameObject>(Vec3(0.f, 0.f, 0.f), L"AlphaRemove", L"", false, LayerType::Unknown);
		mpMarker->GetMeshRenderer()->SetMesh(GET_SINGLE(Resources)->LoadRectMesh());
		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"LockOnTexture", L"..\\Resources\\FBX\\Monster\\SilenceEffect.fbm\\target.png");
		mpMarker->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture);
		mpMarker->GetTransform()->SetRotation(AXIS_X, 90.f);
		mpMarker->GetTransform()->SetScale(Vec3(1.f, 1.f, 1.f));
		mpMarker->Initialize();
		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(mpMarker);
	}
}