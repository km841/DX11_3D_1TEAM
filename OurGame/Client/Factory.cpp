#include "pch.h"
#include "Factory.h"
#include "Animator.h"

namespace hm
{
	Grimace* Factory::CreateGrimace(const Vec3& _pos, const Vec3& _rotation)
	{
		PhysicsInfo info = {};
		info.eActorType = ActorType::Kinematic;
		info.eGeometryType = GeometryType::Box;
		info.size = Vec3(2.f, 8.f, 2.f);

		Grimace* pGrimace = Factory::CreateMonster<Grimace>(_pos, info, L"MonsterDeferred", L"..\\Resources\\FBX\\Monster\\_E_GRIMACE_KNIGHT.fbx");
		pGrimace->GetTransform()->SetScale(Vec3(0.7f, 1.f, 0.7f));
		pGrimace->GetTransform()->SetRotation(Vec3(180.f, 0.f, 0.f));
		pGrimace->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -4.f, 0.f));
		pGrimace->GetMeshRenderer()->SetMaterial(pGrimace->GetMeshRenderer()->GetMaterial()->Clone());

		for (size_t i = 0; i < 13; i++)
		{
			pGrimace->GetAnimator()->SetPlaySpeed(i, 0.8f);
		}

		return pGrimace;
	}

}
