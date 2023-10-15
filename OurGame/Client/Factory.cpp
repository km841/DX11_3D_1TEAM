#include "pch.h"
#include "Factory.h"
#include "Animator.h"
#include "AudioSound.h"

namespace hm
{
	Grimace* Factory::CreateGrimace(const Vec3& _pos, const Vec3& _rotation)
	{
		PhysicsInfo info = {};
		info.eActorType = ActorType::Kinematic;
		info.eGeometryType = GeometryType::Box;
		info.size = Vec3(2.f, 8.f, 2.f);

		Grimace* pGrimace = Factory::CreateMonster<Grimace>(_pos, info, L"MonsterDeferred", L"..\\Resources\\FBX\\Monster\\_E_GRIMACE_KNIGHT.fbx");
		pGrimace->GetTransform()->SetScale(Vec3(0.7f, 0.9f, 0.7f));
		pGrimace->GetTransform()->SetRotation(_rotation);
		pGrimace->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -4.f, 0.f));
		pGrimace->GetMeshRenderer()->SetMaterial(pGrimace->GetMeshRenderer()->GetMaterial()->Clone());

		pGrimace->AddComponent(new AudioSound);

		for (size_t i = 0; i < 13; i++)
		{
			pGrimace->GetAnimator()->SetPlaySpeed(i, 0.8f);
		}

		return pGrimace;
	}

	Bat* Factory::CreateBat(const Vec3& _pos, const Vec3& _rotation)
	{
		
		PhysicsInfo info = {};
		info.eActorType = ActorType::Kinematic;
		info.eGeometryType = GeometryType::Box;
		info.size = Vec3(0.5f, 0.5f, 1.0f);

		Bat* p_E_BAT_White = Factory::CreateMonster<Bat>(_pos, info, L"MonsterDeferred", L"..\\Resources\\FBX\\Monster\\_E_BAT_White.fbx");
		p_E_BAT_White->GetMeshRenderer()->SetMaterial(p_E_BAT_White->GetMeshRenderer()->GetMaterial()->Clone());
		p_E_BAT_White->GetTransform()->SetScale(Vec3(0.5f, 0.5f, 0.5f));
		p_E_BAT_White->GetTransform()->SetRotation(_rotation);

		p_E_BAT_White->AddComponent(new AudioSound);

		return p_E_BAT_White;
	}

	Mage* Factory::CreateMage(const Vec3& _pos, const Vec3& _rotation)
	{
		PhysicsInfo info = {};
		info.eActorType = ActorType::Kinematic;
		info.eGeometryType = GeometryType::Box;
		info.size = Vec3(0.5f, 0.5f, 2.f);

		Mage* p_E_MAGE = Factory::CreateMonster<Mage>(_pos, info, L"MonsterDeferred", L"..\\Resources\\FBX\\Monster\\_E_MAGE.fbx");
		p_E_MAGE->GetTransform()->SetScale(Vec3(0.5f, 0.5f, 0.5f));
		p_E_MAGE->GetTransform()->SetRotation(_rotation);
		p_E_MAGE->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -1.f, 0.f));
		p_E_MAGE->GetMeshRenderer()->SetMaterial(p_E_MAGE->GetMeshRenderer()->GetMaterial()->Clone());

		p_E_MAGE->AddComponent(new AudioSound);

		return p_E_MAGE;
	}

	Lurker* Factory::CreateLurker(const Vec3& _pos, const Vec3& _rotation)
	{
		PhysicsInfo info = {};
		info.eActorType = ActorType::Kinematic;
		info.eGeometryType = GeometryType::Box;
		info.size = Vec3(0.5f, 0.5f, 1.f);

		Lurker* p_E_LURKER = Factory::CreateMonster<Lurker>(_pos, info, L"MonsterDeferred", L"..\\Resources\\FBX\\Monster\\_E_LURKER.fbx");
		p_E_LURKER->GetMeshRenderer()->SetMaterial(p_E_LURKER->GetMeshRenderer()->GetMaterial()->Clone());
		p_E_LURKER->GetTransform()->SetScale(Vec3(0.5f, 0.5f, 0.5f));
		p_E_LURKER->GetTransform()->SetRotation(_rotation);
		p_E_LURKER->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -0.4f, 0.f));

		p_E_LURKER->AddComponent(new AudioSound);

		return p_E_LURKER;

	}

	HeadRoller* Factory::CreateHeadRoller(const Vec3& _pos, const Vec3& _rotation)
	{
		PhysicsInfo info = {};
		info.eActorType = ActorType::Kinematic;
		info.eGeometryType = GeometryType::Box;
		info.size = Vec3(1.f, 2.0f, 1.f);

		HeadRoller* p_E_HEADROLLER = Factory::CreateMonster<HeadRoller>(_pos, info, L"MonsterDeferred", L"..\\Resources\\FBX\\Monster\\_E_HEADROLLER.fbx");
		p_E_HEADROLLER->GetMeshRenderer()->SetMaterial(p_E_HEADROLLER->GetMeshRenderer()->GetMaterial()->Clone());
		p_E_HEADROLLER->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));
		p_E_HEADROLLER->GetTransform()->SetRotation(_rotation);
		p_E_HEADROLLER->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -1.f, 0.f));

		p_E_HEADROLLER->AddComponent(new AudioSound);

		return p_E_HEADROLLER;

	}

	

}
