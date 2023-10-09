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
        : mFollowSpeed(3.f)
        , mpTarget(nullptr)
        , mbFocusMode(false)
    {
    }

    Component* FocusingScript::Clone(GameObject* _pGameObject)
    {
        return _pGameObject->AddComponent(new FocusingScript);
    }

    void FocusingScript::SetFocusingTarget(GameObject* _pTarget)
    {
        mpTarget = _pTarget;
    }

    void FocusingScript::FixedUpdate()
    {
        if (nullptr == mpTarget)
            return;

        if (IS_DOWN(KeyType::P))
            mbFocusMode = !mbFocusMode;

        if (false == mbFocusMode)
        {
            GetRigidBody()->SetVelocity(Vec3::Zero);
            GetTransform()->SetUpdateByRotMat(false);
            return;
        }

        Vec3 myPos = GetTransform()->GetPosition();
        Vec3 targetPos = mpTarget->GetTransform()->GetPosition();

        // 스무딩된 목표 위치 계산
        Vec3 smoothedTargetPos = myPos + (targetPos - myPos) * 0.2f;

        Vec3 dir = smoothedTargetPos - myPos;
        float distance = dir.Length();
        if (distance < 0.01f)
        {
            GetTransform()->SetPosition(smoothedTargetPos);
            GetRigidBody()->SetVelocity(Vec3::Zero);
            return;
        }

        float fixedSpeed = mFollowSpeed;

        dir.Normalize();

        GetRigidBody()->SetVelocity(dir * fixedSpeed);

        Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
        Vec3 lookDir = playerPos - myPos;

        GetTransform()->SmoothRotateTo(lookDir);  
    }
}

