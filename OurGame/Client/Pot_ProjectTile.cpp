#include "pch.h"
#include "Pot_ProjectTile.h"
/* Manager */
#include "Input.h"
#include "Factory.h"
#include "SceneManager.h"
#include "EventManager.h"
#include "TimerObject.h"
#include "RenderManager.h"
/* Component */
#include "Collider.h"
#include "RigidBody.h"

Pot_ProjectTile::Pot_ProjectTile(GameObject* _pBase)
	:GameObject(LayerType::Monster_ProjectTile)
{
	mpBasePot = _pBase;
	pTimer.SetEndTime(5.f);
	this->SetName(L"Pot_ProjectTile");
}

Pot_ProjectTile::~Pot_ProjectTile()
{
}

void Pot_ProjectTile::Initialize()
{
	PhysicsInfo physicsInfo;
	physicsInfo.eActorType = ActorType::Dynamic;
	physicsInfo.eGeometryType = GeometryType::Convex;
	physicsInfo.massProperties.staticFriction = 1.f;
	physicsInfo.massProperties.dynamicFriction = 0.f;
	physicsInfo.massProperties.restitution = 0.f;

	// 항아리 조각 1
	{
		jh::BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<jh::BreakablePotCell>(Vec3::Zero, physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell1.fbx");

		potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
		potCell->SetRelativePos(Vec3(0.6f, -2.2f, -0.8f));

		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(potCell);
		mpPotCells.push_back(potCell);
	}
	// 항아리 조각 3
	{
		physicsInfo.size = Vec3(1.11f, 1.11f, 1.11f);

		jh::BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<jh::BreakablePotCell>(Vec3::Zero, physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell3.fbx");

		potCell->GetTransform()->SetScale(Vec3(1.11f, 1.11f, 1.11f));
		potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
		potCell->SetRelativePos(Vec3(-0.43f, -1.05f, 0.13f));

		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(potCell);
		mpPotCells.push_back(potCell);
	}
	// 항아리 조각 4
	{
		physicsInfo.size = Vec3(1.276f, 1.276f, 1.276f);

		jh::BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<jh::BreakablePotCell>(Vec3::Zero, physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell4.fbx");

		potCell->GetTransform()->SetScale(Vec3(1.276f, 1.276f, 1.276f));
		potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
		potCell->SetRelativePos(Vec3(-0.19f, -0.23f, -0.11f));

		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(potCell);
		mpPotCells.push_back(potCell);
	}
	// 항아리 조각 6
	{
		physicsInfo.size = Vec3(0.99f, 0.99f, 0.99f);

		jh::BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<jh::BreakablePotCell>(Vec3::Zero, physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell6.fbx");

		potCell->GetTransform()->SetScale(Vec3(0.99f, 0.99f, 0.99f));
		potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
		potCell->SetRelativePos(Vec3(-0.234f, 0.445f, 0.18f));

		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(potCell);
		mpPotCells.push_back(potCell);
	}
	// 항아리 조각 7
	{
		physicsInfo.size = Vec3(1.3f, 1.3f, 1.3f);

		jh::BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<jh::BreakablePotCell>(Vec3::Zero, physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell7.fbx");

		potCell->GetTransform()->SetScale(Vec3(1.3f, 1.3f, 1.3f));
		potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
		potCell->SetRelativePos(Vec3(0.63f, -0.66f, -0.05f));

		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(potCell);
		mpPotCells.push_back(potCell);
	}
	// 항아리 조각 8
	{
		physicsInfo.size = Vec3(1.22f, 1.22f, 1.22f);

		jh::BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<jh::BreakablePotCell>(Vec3::Zero, physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell8.fbx");

		potCell->GetTransform()->SetScale(Vec3(1.22f, 1.22f, 1.22f));
		potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
		potCell->SetRelativePos(Vec3(-0.15f, -0.15f, 0.34f));

		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(potCell);
		mpPotCells.push_back(potCell);
	}
	// 항아리 조각 9
	{
		physicsInfo.size = Vec3(0.8f, 0.8f, 0.8f);

		jh::BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<jh::BreakablePotCell>(Vec3::Zero, physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell9.fbx");

		potCell->GetTransform()->SetScale(Vec3(0.8f, 0.8f, 0.8f));
		potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
		potCell->SetRelativePos(Vec3(0.34f, -1.108f, 0.35f));

		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(potCell);
		mpPotCells.push_back(potCell);
	}
	// 항아리 조각 10
	{
		physicsInfo.size = Vec3(0.87f, 0.87f, 0.87f);

		jh::BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<jh::BreakablePotCell>(Vec3::Zero, physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell10.fbx");

		potCell->GetTransform()->SetScale(Vec3(0.87f, 0.87f, 0.87f));
		potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
		potCell->SetRelativePos(Vec3(-0.19f, 0.48f, -0.4f));

		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(potCell);
		mpPotCells.push_back(potCell);
	}
	// 항아리 조각 11
	{
		physicsInfo.size = Vec3(1.326f, 1.326f, 1.326f);

		jh::BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<jh::BreakablePotCell>(Vec3::Zero, physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell11.fbx");

		potCell->GetTransform()->SetScale(Vec3(1.326f, 1.326f, 1.326f));
		potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
		potCell->SetRelativePos(Vec3(0.36f, 0.31f, 0.f));

		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(potCell);
		mpPotCells.push_back(potCell);
	}
	// 항아리 조각 12
	{
		physicsInfo.size = Vec3(1.179f, 1.179f, 1.179f);

		jh::BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<jh::BreakablePotCell>(Vec3::Zero, physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell12.fbx");

		potCell->GetTransform()->SetScale(Vec3(1.179f, 1.179f, 1.179f));
		potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
		potCell->SetRelativePos(Vec3(0.01f, -1.026f, 0.596f));

		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(potCell);
		mpPotCells.push_back(potCell);
	}
	// 항아리 조각 16
	{
		physicsInfo.size = Vec3(0.96f, 0.96f, 0.96f);

		jh::BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<jh::BreakablePotCell>(Vec3::Zero, physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell16.fbx");

		potCell->GetTransform()->SetScale(Vec3(0.96f, 0.96f, 0.96f));
		potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
		potCell->SetRelativePos(Vec3(0.08f, -0.48f, -0.565f));

		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(potCell);
		mpPotCells.push_back(potCell);
	}
	// 항아리 조각 17
	{
		physicsInfo.size = Vec3(1.26f, 1.26f, 1.26f);

		jh::BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<jh::BreakablePotCell>(Vec3::Zero, physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell17.fbx");

		potCell->GetTransform()->SetScale(Vec3(1.26f, 1.26f, 1.26f));
		potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
		potCell->SetRelativePos(Vec3(0.f, -0.69f, 0.605f));

		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(potCell);
		mpPotCells.push_back(potCell);
	}
	// 항아리 조각 18
	{
		physicsInfo.size = Vec3(1.37f, 1.37f, 1.37f);

		jh::BreakablePotCell* potCell = Factory::CreateObjectHasPhysical<jh::BreakablePotCell>(Vec3::Zero, physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell18.fbx");

		potCell->GetTransform()->SetScale(Vec3(1.37f, 1.37f, 1.37f));
		potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
		potCell->SetRelativePos(Vec3(-0.165f, -0.88f, -0.485f));

		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(potCell);
		mpPotCells.push_back(potCell);
	}
	// 항아리 뚜껑
	{
		physicsInfo.size = Vec3(1.33f, 1.33f, 1.33f);

		jh::BreakablePotCell* potTap = Factory::CreateObjectHasPhysical<jh::BreakablePotCell>(Vec3::Zero, physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Tap.fbx");

		potTap->GetTransform()->SetScale(Vec3(1.33f, 1.33f, 1.33f));
		potTap->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));
		potTap->SetRelativePos(Vec3(0.025f, 1.05f, -0.015f));

		GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(potTap);
		mpPotCells.push_back(potTap);
	}


	for (int i = 0; i < mpPotCells.size(); i++)
	{
		mpPotCells[i]->SetOriginPos(this->GetTransform()->GetPosition() + mpPotCells[i]->GetRelativePos());
		mpPotCells[i]->GetTransform()->SetPosition(mpPotCells[i]->GetOriginPos());
		mpPotCells[i]->GetRigidBody()->GetDynamicActor()->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, true);
		mpPotCells[i]->Initialize();
		mpPotCells[i]->Disable();
		pTimer.Start();
		GET_SINGLE(RenderManager)->AddCameraShakeEffect(0.05f, 0.02f);
	}
	
	GameObject::Initialize();
}

void Pot_ProjectTile::Update()
{
	GameObject::Update();
	pTimer.Update();

	if (pTimer.IsFinished())
	{
		for (int i = 0; i < mpPotCells.size(); i++)
		{
			MapType type = GET_SINGLE(SceneManager)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->PushDeleteGameObjectEvent(type, static_cast<GameObject*>(mpPotCells[i]));
		}
		mpPotCells.clear();
	}

	else if(!pTimer.IsFinished() && isGround == false)
	{
		for (int i = 0; i < mpPotCells.size(); i++)
		{
			Vec3 relativePos = mpPotCells[i]->GetRelativePos();
			Vec3 myPos = GetTransform()->GetPosition();
			mpPotCells[i]->GetTransform()->SetPosition(relativePos + myPos);
		}
	}
}

void Pot_ProjectTile::FixedUpdate()
{
	GameObject::FixedUpdate();
}

void Pot_ProjectTile::Render()
{
	GameObject::Render();
}

void Pot_ProjectTile::OnTriggerEnter(Collider* _pOther)
{
	if (LayerType::Ground == _pOther->GetGameObject()->GetLayerType())
	{
		isGround = true;
		PxSweepHit hit;
		Vec3 dir = GetTransform()->GetPosition() - _pOther->GetGameObject()->GetTransform()->GetPosition();
		dir.Normalize();
		if (GetCollider()->Sweep(-dir, 5.f, _pOther, hit))
		{
			Vec3 pos = hit.position;
			BreakPots(pos);
		}
	}
}

void Pot_ProjectTile::OnTriggerStay(Collider* _pOther)
{
}

void Pot_ProjectTile::OnTriggerExit(Collider* _pOther)
{
}

void Pot_ProjectTile::BreakPots(const Vec3 _hitPos)
{
	mpBasePot->Disable();

	for (int i = 0; i < mpPotCells.size(); i++)
	{
		mpPotCells[i]->GetRigidBody()->GetDynamicActor()->setMass(100.f);
		mpPotCells[i]->GetRigidBody()->GetDynamicActor()->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, false);
		mpPotCells[i]->Enable();

		mpPotCells[i]->CalculateForce(_hitPos);
	}
}

void Pot_ProjectTile::RestorePots(bool _isTemp)
{
	
}
