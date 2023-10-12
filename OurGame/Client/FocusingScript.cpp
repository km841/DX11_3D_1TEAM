#include "pch.h"
#include "FocusingScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "RigidBody.h"
#include "Input.h"
#include "Player.h"

namespace hm
{
	FocusingScript::FocusingScript()
		: mFollowSpeed(5.f)
		, mpFollowTarget(nullptr)
		, mpFocusingTarget(nullptr)
		, mbFocusMode(false)
		, mbFollowMode(false)
	{
	}

	Component* FocusingScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new FocusingScript);
	}

	void FocusingScript::SetFollowTarget(GameObject* _pTarget)
	{
		mpFollowTarget = _pTarget;
	}

	void FocusingScript::SetFocusingTarget(GameObject* _pTarget)
	{
		mpFocusingTarget = _pTarget;
	}

	void FocusingScript::FixedUpdate()
	{
		if (nullptr == mpFollowTarget)
			return;

		if (false == mbFocusMode)
		{
			GetRigidBody()->SetVelocity(Vec3::Zero);
			GetTransform()->SetUpdateByRotMat(false);
			return;
		}
		else
		{
			Vec3 myPos = GetTransform()->GetPosition();
			Vec3 targetPos = mpFollowTarget->GetTransform()->GetPosition();

			// 스무딩된 목표 위치 계산
			Vec3 smoothedTargetPos = myPos + (targetPos - myPos) * 0.2f;
			Vec3 dir = smoothedTargetPos - myPos;

			float distance = dir.Length();
			if (distance < 0.1f)
			{
				GetTransform()->SetPosition(smoothedTargetPos);
				GetRigidBody()->SetVelocity(Vec3::Zero);
				return;
			}

			float fixedSpeed = mFollowSpeed;

			dir.Normalize();
			GetRigidBody()->SetVelocity(dir * fixedSpeed);
		}

		if (nullptr == mpFocusingTarget)
			return;

		if (true == mbFocusMode)
		{
			Vec3 myPos = GetTransform()->GetPosition();
			Vec3 focusPos = mpFocusingTarget->GetTransform()->GetPosition();
			Vec3 lookDir = focusPos - myPos;

			GetTransform()->SmoothRotateTo(lookDir);
		}

	}
}

