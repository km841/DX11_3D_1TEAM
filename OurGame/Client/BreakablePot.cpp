#include "pch.h"
#include "BreakablePot.h"

/* Manager */
#include "Input.h"

/* Component */
#include "RigidBody.h"

namespace jh
{
	BreakablePot::BreakablePot(GameObject* _pBase, std::vector<BreakablePotCell*> _vpCells) :
		GameObject(LayerType::DecoObject)
	{
		mpBasePot = _pBase;
		mpPotCells = _vpCells;

		for (int i = 0; i < mpPotCells.size(); i++)
		{
			mpPotCells[i]->GetRigidBody()->GetDynamicActor()->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, true);
			mpPotCells[i]->Disable();
		}

		this->SetName(L"BreakablePot");
	}

	BreakablePot::~BreakablePot()
	{
	}

	void BreakablePot::Initialize()
	{
		GameObject::Initialize();
	}

	void BreakablePot::Update()
	{
		GameObject::Update();

		if (IS_DOWN(KeyType::B))
		{
			BreakPots();
		}
	}

	void BreakablePot::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void BreakablePot::Render()
	{
		GameObject::Render();
	}

	void BreakablePot::BreakPots()
	{
		mpBasePot->Disable();

		for (int i = 0; i < mpPotCells.size(); i++)
		{
			mpPotCells[i]->Enable();
			mpPotCells[i]->GetRigidBody()->GetDynamicActor()->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, false);
		}
	}

	void BreakablePot::RestorePots()
	{
	}

	void BreakablePot::CreateCells()
	{
		//// 항아리 조각 1
		//{
		//	PhysicsInfo physicsInfo;
		//	physicsInfo.eActorType = ActorType::Dynamic;
		//	physicsInfo.eGeometryType = GeometryType::Convex;

		//	ObstacleObject* potCell = Factory::CreateObjectHasPhysical<ObstacleObject>(Vec3(0.f, 0.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell1.fbx");

		//	potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));

		//	AddGameObject(potCell);
		//}
		//// 항아리 조각 3
		//{
		//	PhysicsInfo physicsInfo;
		//	physicsInfo.eActorType = ActorType::Dynamic;
		//	physicsInfo.eGeometryType = GeometryType::Convex;
		//	physicsInfo.size = Vec3(1.11f, 1.11f, 1.11f);

		//	ObstacleObject* potCell = Factory::CreateObjectHasPhysical<ObstacleObject>(Vec3(-0.73f, 0.05f, 0.53f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell3.fbx");

		//	potCell->GetTransform()->SetScale(Vec3(1.11f, 1.11f, 1.11f));
		//	potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));

		//	AddGameObject(potCell);
		//}
		//// 항아리 조각 4
		//{
		//	PhysicsInfo physicsInfo;
		//	physicsInfo.eActorType = ActorType::Dynamic;
		//	physicsInfo.eGeometryType = GeometryType::Convex;
		//	physicsInfo.size = Vec3(1.276f, 1.276f, 1.276f);

		//	ObstacleObject* potCell = Factory::CreateObjectHasPhysical<ObstacleObject>(Vec3(-0.49f, 0.87f, 0.29f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell4.fbx");

		//	potCell->GetTransform()->SetScale(Vec3(1.276f, 1.276f, 1.276f));
		//	potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));

		//	AddGameObject(potCell);
		//}
		//// 항아리 조각 6
		//{
		//	PhysicsInfo physicsInfo;
		//	physicsInfo.eActorType = ActorType::Dynamic;
		//	physicsInfo.eGeometryType = GeometryType::Convex;
		//	physicsInfo.size = Vec3(0.99f, 0.99f, 0.99f);

		//	ObstacleObject* potCell = Factory::CreateObjectHasPhysical<ObstacleObject>(Vec3(-0.534f, 1.545f, 0.58f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell6.fbx");

		//	potCell->GetTransform()->SetScale(Vec3(0.99f, 0.99f, 0.99f));
		//	potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));

		//	AddGameObject(potCell);
		//}
		//// 항아리 조각 7
		//{
		//	PhysicsInfo physicsInfo;
		//	physicsInfo.eActorType = ActorType::Dynamic;
		//	physicsInfo.eGeometryType = GeometryType::Convex;
		//	physicsInfo.size = Vec3(1.3f, 1.3f, 1.3f);

		//	ObstacleObject* potCell = Factory::CreateObjectHasPhysical<ObstacleObject>(Vec3(0.33f, 0.44f, 0.35f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell7.fbx");

		//	potCell->GetTransform()->SetScale(Vec3(1.3f, 1.3f, 1.3f));
		//	potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));

		//	AddGameObject(potCell);
		//}
		//// 항아리 조각 8
		//{
		//	PhysicsInfo physicsInfo;
		//	physicsInfo.eActorType = ActorType::Dynamic;
		//	physicsInfo.eGeometryType = GeometryType::Convex;
		//	physicsInfo.size = Vec3(1.22f, 1.22f, 1.22f);

		//	ObstacleObject* potCell = Factory::CreateObjectHasPhysical<ObstacleObject>(Vec3(-0.45f, 0.95f, 0.74f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell8.fbx");

		//	potCell->GetTransform()->SetScale(Vec3(1.22f, 1.22f, 1.22f));
		//	potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));

		//	AddGameObject(potCell);
		//}
		//// 항아리 조각 9
		//{
		//	PhysicsInfo physicsInfo;
		//	physicsInfo.eActorType = ActorType::Dynamic;
		//	physicsInfo.eGeometryType = GeometryType::Convex;
		//	physicsInfo.size = Vec3(0.8f, 0.8f, 0.8f);

		//	ObstacleObject* potCell = Factory::CreateObjectHasPhysical<ObstacleObject>(Vec3(0.04f, -0.008f, 0.75f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell9.fbx");

		//	potCell->GetTransform()->SetScale(Vec3(0.8f, 0.8f, 0.8f));
		//	potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));

		//	AddGameObject(potCell);
		//}
		//// 항아리 조각 10
		//{
		//	PhysicsInfo physicsInfo;
		//	physicsInfo.eActorType = ActorType::Dynamic;
		//	physicsInfo.eGeometryType = GeometryType::Convex;
		//	physicsInfo.size = Vec3(0.87f, 0.87f, 0.87f);

		//	ObstacleObject* potCell = Factory::CreateObjectHasPhysical<ObstacleObject>(Vec3(-0.49f, 1.58f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell10.fbx");

		//	potCell->GetTransform()->SetScale(Vec3(0.87f, 0.87f, 0.87f));
		//	potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));

		//	AddGameObject(potCell);
		//}
		//// 항아리 조각 11
		//{
		//	PhysicsInfo physicsInfo;
		//	physicsInfo.eActorType = ActorType::Dynamic;
		//	physicsInfo.eGeometryType = GeometryType::Convex;
		//	physicsInfo.size = Vec3(1.326f, 1.326f, 1.326f);

		//	ObstacleObject* potCell = Factory::CreateObjectHasPhysical<ObstacleObject>(Vec3(0.06f, 1.41f, 0.4f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell11.fbx");

		//	potCell->GetTransform()->SetScale(Vec3(1.326f, 1.326f, 1.326f));
		//	potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));

		//	AddGameObject(potCell);
		//}
		//// 항아리 조각 12
		//{
		//	PhysicsInfo physicsInfo;
		//	physicsInfo.eActorType = ActorType::Dynamic;
		//	physicsInfo.eGeometryType = GeometryType::Convex;
		//	physicsInfo.size = Vec3(1.179f, 1.179f, 1.179f);

		//	ObstacleObject* potCell = Factory::CreateObjectHasPhysical<ObstacleObject>(Vec3(-0.29f, 0.074f, 0.996f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell12.fbx");

		//	potCell->GetTransform()->SetScale(Vec3(1.179f, 1.179f, 1.179f));
		//	potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));

		//	AddGameObject(potCell);
		//}
		//// 항아리 조각 16
		//{
		//	PhysicsInfo physicsInfo;
		//	physicsInfo.eActorType = ActorType::Dynamic;
		//	physicsInfo.eGeometryType = GeometryType::Convex;
		//	physicsInfo.size = Vec3(0.96f, 0.96f, 0.96f);

		//	ObstacleObject* potCell = Factory::CreateObjectHasPhysical<ObstacleObject>(Vec3(-0.22f, 0.62f, -0.165f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell16.fbx");

		//	potCell->GetTransform()->SetScale(Vec3(0.96f, 0.96f, 0.96f));
		//	potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));

		//	AddGameObject(potCell);
		//}
		//// 항아리 조각 17
		//{
		//	PhysicsInfo physicsInfo;
		//	physicsInfo.eActorType = ActorType::Dynamic;
		//	physicsInfo.eGeometryType = GeometryType::Convex;
		//	physicsInfo.size = Vec3(1.26f, 1.26f, 1.26f);

		//	ObstacleObject* potCell = Factory::CreateObjectHasPhysical<ObstacleObject>(Vec3(-0.3f, 0.41f, 1.005f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell17.fbx");

		//	potCell->GetTransform()->SetScale(Vec3(1.26f, 1.26f, 1.26f));
		//	potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));

		//	AddGameObject(potCell);
		//}
		//// 항아리 조각 18
		//{
		//	PhysicsInfo physicsInfo;
		//	physicsInfo.eActorType = ActorType::Dynamic;
		//	physicsInfo.eGeometryType = GeometryType::Convex;
		//	physicsInfo.size = Vec3(1.37f, 1.37f, 1.37f);

		//	ObstacleObject* potCell = Factory::CreateObjectHasPhysical<ObstacleObject>(Vec3(-0.465f, 0.22f, -0.085f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Cell18.fbx");

		//	potCell->GetTransform()->SetScale(Vec3(1.37f, 1.37f, 1.37f));
		//	potCell->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));

		//	AddGameObject(potCell);
		//}
		//// 항아리 뚜껑
		//{
		//	PhysicsInfo physicsInfo;
		//	physicsInfo.eActorType = ActorType::Dynamic;
		//	physicsInfo.eGeometryType = GeometryType::Convex;
		//	physicsInfo.size = Vec3(1.33f, 1.33f, 1.33f);

		//	ObstacleObject* potTap = Factory::CreateObjectHasPhysical<ObstacleObject>(Vec3(-0.275f, 2.15f, 0.385f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\Pot_Tap.fbx");

		//	potTap->GetTransform()->SetScale(Vec3(1.33f, 1.33f, 1.33f));
		//	potTap->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 90.f));

		//	//SetGizmoTarget(potTap);
		//	AddGameObject(potTap);
		//}
	}
}