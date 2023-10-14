#include "pch.h"
#include "LaserLockOnScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "Player.h"
#include "RenderManager.h"

namespace hm
{
	LaserLockOnScript::LaserLockOnScript()
		: mFlipWidth(0.1f)
	{
	}
	void LaserLockOnScript::Initialize()
	{
	}
	void LaserLockOnScript::FixedUpdate()
	{
		Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
		Vec3 myPos = GetTransform()->GetPosition();
		Vec3 lookDir = playerPos - myPos;

		float distance = lookDir.Length();
		distance *= 0.5f;
		lookDir.Normalize();
		float angleX = lookDir.Dot(Vec3(0.f, 0.f, 1.f)) * 180.f / XM_PI;

		lookDir.Normalize();
		float angleZ = lookDir.Dot(Vec3(1.f, 0.f, 0.f)) * 180.f / XM_PI;
		GetTransform()->SetRotation(Vec3(-(angleX + 5.f), 0.f, angleZ));

		mFlipWidth = -mFlipWidth;
		GetTransform()->SetScale(Vec3(1.f + mFlipWidth, distance, 3.f));
	}
	Component* LaserLockOnScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new LaserLockOnScript);
	}
}