#include "pch.h"
#include "EntranceHallMap.h"
#include "Engine.h"

/* Resource */
#include "MeshData.h"
#include "Material.h"
#include "Mesh.h"
#include "MeshRenderer.h"

/* Manager */
#include "PrefabManager.h"
#include "EventManager.h"
#include "RenderManager.h"
#include "Factory.h"
#include "CollisionManager.h"
#include "Input.h"
#include "SceneManager.h"
#include "Resources.h"

/* GameObject */
#include "GameObject.h"
#include "TeleportZone.h"
#include "Player.h"
#include "Ground.h"
#include "Monster.h"
#include "JarDoor.h"
#include "KeyDoor.h"
#include "IrreparablePot.h"

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "UIText.h"
#include "Mirror.h"

/* Script */
#include "PaperBurnScript.h"
#include "CameraMoveScript.h"
#include "PlayerMoveScript.h"
#include "PlayerSlashScript.h"
#include "PlayerMoveOverMapScript.h"
#include "PlacementScript.h"
#include "TestAnimationScript.h"

/* Event */
#include "SceneChangeEvent.h"


EntranceHallMap::EntranceHallMap()
	: Map(MapType::EntranceHallMap)
{
}

EntranceHallMap::~EntranceHallMap()
{
}

void EntranceHallMap::Initialize()
{
	Map::Initialize();
}

void EntranceHallMap::Start()
{
	Map::Start();
	if (PLAYER != nullptr)
	{
		mSpawnPoint = PLAYER->GetScript<yj::PlayerMoveOverMapScript>()->GetMoveOverNum();
		switch (mSpawnPoint)
		{
		case 1:
			PLAYER->GetTransform()->SetPosition(Vec3(0.0f, 4.0f, 15.2f));
			break;
		}
	}

	DisableDirLight();
}

void EntranceHallMap::Update()
{
	Map::Update();
}

void EntranceHallMap::FixedUpdate()
{
	Map::FixedUpdate();
}

void EntranceHallMap::FinalUpdate()
{
	Map::FinalUpdate();
}

void EntranceHallMap::Render()
{
	Map::Render();
}

void EntranceHallMap::Enter()
{
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::WallObject);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Obstacle);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Portal);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Obstacle, LayerType::Ground);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::PlayerCol, LayerType::DecoObject);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::PlayerCol, LayerType::DungeonObject);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::ArrowCol, LayerType::DungeonObject);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Ground, LayerType::DungeonObject);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::PotCell, LayerType::Ground);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::PotCell, LayerType::WallObject);
	GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::PotCell, LayerType::PotCell);

	//배경맵 하얀색으로 만들어주는 코드
	//gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));

	InitObjectAdd();
	InitColliderAdd();
	InitFuncObjAdd();
	GET_SINGLE(RenderManager)->AddFadeEffect(ScreenEffectType::FadeIn, 1);

	if (PLAYER)
	{
		int a = 0;
	}
	PLAYER->GetRigidBody()->ApplyGravity();
	PLAYER->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_X, true);
	PLAYER->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_Z, true);

}

void EntranceHallMap::Exit()
{
}

void EntranceHallMap::InitObjectAdd()
{
	{
		DecoObject* pEntranceHall = Factory::CreateObject<DecoObject>(Vec3(0.00f, 0.00f, 0.00f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\EntranceHall.fbx");
		pEntranceHall->GetTransform()->SetScale(Vec3(25.00f, 25.00f, 25.00f));

		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"EntranceHallTexture", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\EntranceHall.fbm\\grandmaWallPaperTexture.png");
		pEntranceHall->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture); // 텍스쳐 강제로 적용시키는법

		pEntranceHall->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.03f, 0.03f));

		AddGameObject(pEntranceHall);
	}

	//바닥 - EntranceHallFloor
	{
		DecoObject* pEntranceHallFloor = Factory::CreateObject<DecoObject>(Vec3(0.05f, -4.85f, 2.10f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\EntranceHallFloor.fbx");
		pEntranceHallFloor->GetTransform()->SetScale(Vec3(29.25f, 0.50f, 29.25f));

		pEntranceHallFloor->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.05f, 0.05f));

		AddGameObject(pEntranceHallFloor);
	}

	// 미러
	{
		GameObject* pMirror = Factory::CreateObject<GameObject>(Vec3(0.05f, -4.80f, 2.10f), L"Forward", L"", false, LayerType::Mirror);

		pMirror->GetTransform()->SetScale(Vec3(25.00f, 25.00f, 25.00f));
		pMirror->AddComponent(new Mirror);
		pMirror->GetMeshRenderer()->SetMesh(GET_SINGLE(Resources)->LoadRectMesh());
		pMirror->GetTransform()->SetRotation(Vec3(45.00f, 0.00f, 0.00f));

		AddGameObject(pMirror);
	}

	//바닥 프레임 - wallPanel_Merged
	{
		DecoObject* pwallPanel_Merged = Factory::CreateObject<DecoObject>(Vec3(-0.20f, -5.30f, 2.25f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\wallPanel_Merged.fbx");
		pwallPanel_Merged->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));
		pwallPanel_Merged->GetTransform()->SetScale(Vec3(20.70f, 20.70f, 20.70f));

		AddGameObject(pwallPanel_Merged);
	}

#pragma region "기둥"
	{
		//첫번째 기둥 - ColumnFull
		DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(5.85f, 0.42f, 12.00f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\ColumnFull.fbx");
		pColumnFull->GetTransform()->SetRotation(Vec3(0.00f, 90.00f, 0.00f));
		pColumnFull->GetTransform()->SetScale(Vec3(15.00f, 10.50f, 15.00f));

		AddGameObject(pColumnFull);
	}
	{
		//두번째 기둥 - ColumnFull
		DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(5.85f, 0.42f, -7.25f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\ColumnFull.fbx");
		pColumnFull->GetTransform()->SetRotation(Vec3(0.00f, 90.00f, 0.00f));
		pColumnFull->GetTransform()->SetScale(Vec3(15.00f, 10.50f, 15.00f));

		AddGameObject(pColumnFull);
	}

	{
		//세번째 기둥 - ColumnFull
		DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-5.65f, 0.42f, -7.40f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\ColumnFull.fbx");
		pColumnFull->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));
		pColumnFull->GetTransform()->SetScale(Vec3(15.00f, 10.50f, 15.00f));

		AddGameObject(pColumnFull);
	}
#pragma endregion

#pragma region "가로줄"
	//가로줄 - bannisterTop
	{
		DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(6.20f, 4.90f, 2.60f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\bannisterTop.fbx");
		pbannisterTop->GetTransform()->SetRotation(Vec3(0.00f, 90.00f, 0.00f));
		pbannisterTop->GetTransform()->SetScale(Vec3(20.00f, 65.00f, 20.00f));


		AddGameObject(pbannisterTop);
	}

	//가로줄 - bannisterTop
	{
		DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(0.20f, 4.90f, -7.40f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\bannisterTop.fbx");
		pbannisterTop->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));
		pbannisterTop->GetTransform()->SetScale(Vec3(12.50f, 65.00f, 20.00f));


		AddGameObject(pbannisterTop);
	}
#pragma endregion

#pragma region "벽패널"
	//벽패널 1 - WallPanel	
	{
		DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(5.90f, -3.30f, 8.75f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\WallPanel.fbx");
		pWallPanel->GetTransform()->SetRotation(Vec3(0.00f, 90.00f, 0.00f));
		pWallPanel->GetTransform()->SetScale(Vec3(5.00f, 5.00f, 5.00f));

		AddGameObject(pWallPanel);
	}

	//벽패널 2 - WallPanel	
	{
		DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(5.90f, -3.30f, 3.75f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\WallPanel.fbx");
		pWallPanel->GetTransform()->SetRotation(Vec3(0.00f, 90.00f, 0.00f));
		pWallPanel->GetTransform()->SetScale(Vec3(5.00f, 5.00f, 5.00f));

		AddGameObject(pWallPanel);
	}

	//벽패널 3 - WallPanel	
	{
		DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(5.90f, -3.30f, -1.25f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\WallPanel.fbx");
		pWallPanel->GetTransform()->SetRotation(Vec3(0.00f, 90.00f, 0.00f));
		pWallPanel->GetTransform()->SetScale(Vec3(5.00f, 5.00f, 5.00f));

		AddGameObject(pWallPanel);
	}

	//벽패널 4 - WallPanel	
	{
		DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(5.90f, -3.30f, -6.25f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\WallPanel.fbx");
		pWallPanel->GetTransform()->SetRotation(Vec3(0.00f, 90.00f, 0.00f));
		pWallPanel->GetTransform()->SetScale(Vec3(5.00f, 5.00f, 5.00f));

		AddGameObject(pWallPanel);
	}

	//벽패널 세로칸 - WallPanel_shot
	{
		DecoObject* pWallPanel_shot = Factory::CreateObject<DecoObject>(Vec3(4.65f, -4.25f, -7.50f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\WallPanel_shot.fbx");
		pWallPanel_shot->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));
		pWallPanel_shot->GetTransform()->SetScale(Vec3(5.00f, 5.00f, 5.00f));

		AddGameObject(pWallPanel_shot);
	}

	//벽패널 세로칸 2  - WallPanel_shot
	{
		DecoObject* pWallPanel_shot = Factory::CreateObject<DecoObject>(Vec3(-3.65f, -4.25f, -7.50f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\WallPanel_shot.fbx");
		pWallPanel_shot->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));
		pWallPanel_shot->GetTransform()->SetScale(Vec3(3.00f, 5.00f, 5.00f));

		AddGameObject(pWallPanel_shot);
	}

	//벽패널 문 테두리 - DoorFrameBig
	{
		DecoObject* pDoorFrameBig = Factory::CreateObject<DecoObject>(Vec3(0.00f, -1.95f, -7.45f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\DoorFrameBig.fbx");
		pDoorFrameBig->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));
		pDoorFrameBig->GetTransform()->SetScale(Vec3(7.00f, 7.00f, 7.00f));

		AddGameObject(pDoorFrameBig);
	}
#pragma endregion

	//커튼 - CurtainHorizontal
	{
		DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(0.00f, 3.20f, -6.60f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\CurtainHorizontal.fbx");
		pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.00f, 180.00f, 0.00f));
		pCurtainHorizontal->GetTransform()->SetScale(Vec3(11.00f, 11.00f, 11.00f));


		AddGameObject(pCurtainHorizontal);
	}

	//보라색 문 - jarDoor
	{
		pJarRDoor = Factory::CreateObject<DecoObject>(Vec3(0.00f, -1.80f, -7.95f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\jarDoor.fbx");
		pJarRDoor->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));
		pJarRDoor->GetTransform()->SetScale(Vec3(7.00f, 7.00f, 7.00f));
		AddGameObject(pJarRDoor);
		pJarRDoor->GetMeshRenderer()->SetSubsetRenderFlag(1, false);
		pJarRDoor->GetMeshRenderer()->SetSubsetRenderFlag(2, false);
		pJarRDoor->GetMeshRenderer()->SetSubsetRenderFlag(3, false);
		pJarRDoor->GetMeshRenderer()->SetSubsetRenderFlag(0, false);
	}

	{
		pJarLDoor = Factory::CreateObject<DecoObject>(Vec3(0.00f, -1.80f, -7.95f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\jarDoor.fbx");
		pJarLDoor->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));
		pJarLDoor->GetTransform()->SetScale(Vec3(7.00f, 7.00f, 7.00f));
		AddGameObject(pJarLDoor);
		pJarLDoor->GetMeshRenderer()->SetSubsetRenderFlag(4, false);
		pJarLDoor->GetMeshRenderer()->SetSubsetRenderFlag(5, false);
		pJarLDoor->GetMeshRenderer()->SetSubsetRenderFlag(6, false);
		pJarLDoor->GetMeshRenderer()->SetSubsetRenderFlag(7, false);
	}


	//탁자 - MiddleShelf
	{
		DecoObject* pMiddleShelf = Factory::CreateObject<DecoObject>(Vec3(4.30f, -3.60f, 2.55f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\MiddleShelf.fbx");
		pMiddleShelf->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));
		pMiddleShelf->GetTransform()->SetScale(Vec3(6.50f, 6.50f, 6.50f));

		AddGameObject(pMiddleShelf);
	}

	//탁자위 꽃 화분 - MansionPlantPot
	{
		DecoObject* pMansionPlantPot = Factory::CreateObject<DecoObject>(Vec3(4.30f, -1.20f, 4.55f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\MansionPlantPot.fbx");
		pMansionPlantPot->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));
		pMansionPlantPot->GetTransform()->SetScale(Vec3(2.50f, 2.50f, 2.50f));

		AddGameObject(pMansionPlantPot);
	}

	//탁자위 작은 화분들 1 - MansionSpicePot_small
	{
		DecoObject* pMansionSpicePot_small = Factory::CreateObject<DecoObject>(Vec3(3.95f, -1.95f, 1.55f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\MansionSpicePot_small.fbx");
		pMansionSpicePot_small->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));
		pMansionSpicePot_small->GetTransform()->SetScale(Vec3(1.00f, 1.00f, 1.00f));

		AddGameObject(pMansionSpicePot_small);
	}

	//탁자위 작은 화분들 2 - MansionSpicePot_small
	{
		DecoObject* pMansionSpicePot_small = Factory::CreateObject<DecoObject>(Vec3(4.50f, -1.95f, 0.55f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\MansionSpicePot_small.fbx");
		pMansionSpicePot_small->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));
		pMansionSpicePot_small->GetTransform()->SetScale(Vec3(1.00f, 1.00f, 1.00f));

		AddGameObject(pMansionSpicePot_small);
	}

	//의자 - Chair
	{
		DecoObject* pChair = Factory::CreateObject<DecoObject>(Vec3(3.15f, -2.55f, 10.75f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\Chair.fbx");
		pChair->GetTransform()->SetRotation(Vec3(0.00f, 75.0f, 0.00f));
		pChair->GetTransform()->SetScale(Vec3(4.50f, 4.50f, 4.50f));

		AddGameObject(pChair);
	}

	//그림액자 1 - paintingFrame
	{
		DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(6.00f, 1.60f, 7.85f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\paintingFrame.fbx");
		pPaintingFrame->GetTransform()->SetRotation(Vec3(0.00f, 90.00f, 0.00f));
		pPaintingFrame->GetTransform()->SetScale(Vec3(6.00f, 6.00f, 6.00f));

		AddGameObject(pPaintingFrame);
	}

	//그림액자 2 - paintingFrame2
	{
		DecoObject* pPaintingFrame2 = Factory::CreateObject<DecoObject>(Vec3(6.00f, 1.55f, 2.00f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\paintingFrame2.fbx");
		pPaintingFrame2->GetTransform()->SetRotation(Vec3(0.00f, 90.00f, 0.00f));
		pPaintingFrame2->GetTransform()->SetScale(Vec3(3.00f, 3.00f, 3.00f));

		AddGameObject(pPaintingFrame2);
	}

	//그림액자 3 - paintingFrame4
	{
		DecoObject* pPaintingFrame4 = Factory::CreateObject<DecoObject>(Vec3(5.95f, 1.55f, -3.55f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\paintingFrame4.fbx");
		pPaintingFrame4->GetTransform()->SetRotation(Vec3(0.00f, 90.00f, 0.00f));
		pPaintingFrame4->GetTransform()->SetScale(Vec3(6.00f, 6.00f, 6.00f));

		AddGameObject(pPaintingFrame4);
	}



	////////////yj
	{

		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(5.17f, 6.50f, 0.50f);

		DecoObject* pDoorCollider = Factory::CreateObjectHasPhysical<DecoObject>(Vec3(-0.05f, -1.60f, -7.50f), physicsInfo, L"Deferred", L"");
		AddGameObject(pDoorCollider);

		yj::JarDoor* pJarDoor = Factory::CreateObject<yj::JarDoor>(Vec3::Zero, L"Deferred", L"", false, 2, pJarLDoor, pJarRDoor, pDoorCollider);
		AddGameObject(pJarDoor);

		//키+파란색 항아리 - POT_Key
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Kinematic;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(2.f, 3.1f, 2.f);

			pPot1 = Factory::CreateObjectHasPhysical<yj::KeyPot>(Vec3(3.55f, -3.85f, -6.05f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\OrgPot.fbx");
			pPot1->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));
			pPot1->GetTransform()->SetScale(Vec3(3.15f, 2.85f, 3.15f));
			pPot1->SetReceiver(pJarDoor);
			AddGameObject(pPot1);

			PhysicsInfo basePhysicsInfo;
			basePhysicsInfo.eActorType = ActorType::Kinematic;
			basePhysicsInfo.eGeometryType = GeometryType::Box;
			basePhysicsInfo.size = Vec3(2.f, 3.1f, 2.f);

			jh::IrreparablePot* pIrreparablePot = Factory::CreateObjectHasPhysical<jh::IrreparablePot>(Vec3(3.55f, -3.85f, -6.05f), basePhysicsInfo, L"Deferred", L"", false, pPot1);

			AddGameObject(pIrreparablePot);
		}

		//키+파란색 항아리 두번째 - POT_Key
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Kinematic;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(2.f, 3.1f, 2.f);

			yj::KeyPot* pPot2 = Factory::CreateObjectHasPhysical<yj::KeyPot>(Vec3(-3.55f, -3.85f, -6.05f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Pots\\OrgPot.fbx");
			pPot2->GetTransform()->SetRotation(Vec3(0.00f, 0.00f, 0.00f));
			pPot2->GetTransform()->SetScale(Vec3(3.15f, 2.85f, 3.15f));
			pPot2->SetReceiver(pJarDoor);
			AddGameObject(pPot2);

			PhysicsInfo basePhysicsInfo;
			basePhysicsInfo.eActorType = ActorType::Kinematic;
			basePhysicsInfo.eGeometryType = GeometryType::Box;
			basePhysicsInfo.size = Vec3(2.f, 3.1f, 2.f);

			jh::IrreparablePot* pIrreparablePot = Factory::CreateObjectHasPhysical<jh::IrreparablePot>(Vec3(-3.55f, -3.85f, -6.05f), basePhysicsInfo, L"Deferred", L"", false, pPot2);

			AddGameObject(pIrreparablePot);
		}
	}


	// 샹들리에 라이트
	{
		GameObject* pGameObject = new GameObject(LayerType::Unknown);
		Transform* pTransform = pGameObject->AddComponent(new Transform);
		pTransform->SetPosition(Vec3(-4.8f, 8.5f, 37.5f));
		pTransform->SetRotation(Vec3(60.5f, 150.6f, 218.5f));
		pTransform->SetScale(Vec3(100.f, 100.f, 100.f));
		Light* pLight = pGameObject->AddComponent(new Light);
		pLight->SetDiffuse(Vec3(1.0f, 1.0f, 1.0f));
		pLight->SetAmbient(Vec3(0.0f, 0.0f, 0.0f));
		pLight->SetLightRange(100.f);
		pLight->SetLightType(LightType::PointLight);
		AddGameObject(pGameObject);
	}

}

void EntranceHallMap::InitColliderAdd()
{
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(24.50f, 0.49f, 39.20f);

		Ground* pGroundCol = Factory::CreateObjectHasPhysical<Ground>(Vec3(-3.05f, -5.05f, -0.25f), physicsInfo, L"Forward", L"");
		AddGameObject(pGroundCol);
	}



	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(0.49f, 24.87f, 39.20f);

		WallObject* pLWallCol = Factory::CreateObjectHasPhysical<WallObject>(Vec3(5.85f, -5.05f, -0.25f), physicsInfo, L"Forward", L"");
		AddGameObject(pLWallCol);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(0.49f, 24.87f, 39.20f);

		WallObject* pRWallCol = Factory::CreateObjectHasPhysical<WallObject>(Vec3(5.85f, -5.05f, -0.25f), physicsInfo, L"Forward", L"");
		AddGameObject(pRWallCol);
	}

	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(0.49f, 24.87f, 39.20f);

		WallObject* pRWallCol = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-5.70f, -5.45f, -0.25f), physicsInfo, L"Forward", L"");
		AddGameObject(pRWallCol);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(3.25f, 2.20f, 4.86f);

		WallObject* pRWallCol = Factory::CreateObjectHasPhysical<WallObject>(Vec3(3.75f, -3.70f, 14.95f), physicsInfo, L"Forward", L"");
		AddGameObject(pRWallCol);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(3.25f, 2.20f, 4.86f);

		WallObject* pRWallCol = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-3.60f, -3.70f, 14.95f), physicsInfo, L"Forward", L"");
		AddGameObject(pRWallCol);

	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(4.00f, 3.70f, 10.35f);

		WallObject* pRWallCol = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-3.60f, -3.70f, 14.95f), physicsInfo, L"Forward", L"");
		AddGameObject(pRWallCol);

	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(4.00f, 3.70f, 10.35f);

		WallObject* pRWallCol = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-3.60f, -3.70f, 14.95f), physicsInfo, L"Forward", L"");
		AddGameObject(pRWallCol);

	}
}

void EntranceHallMap::InitFuncObjAdd()
{
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Kinematic;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(4.6f, 1.9f, 4.35f);

		yj::TeleportZone* pTelZone = Factory::CreateObjectHasPhysical<yj::TeleportZone>(Vec3(0.05f, -3.85f, -10.3f), physicsInfo, L"Forward", L"", false, MapType::HallColliderCheckMap, 3);
		AddGameObject(pTelZone);
	}

	//{
	//	PhysicsInfo physicsInfo;
	//	physicsInfo.eActorType = ActorType::Kinematic;
	//	physicsInfo.eGeometryType = GeometryType::Box;
	//	physicsInfo.size = Vec3(9.2, 3.8f, 8.75f);

	//	yj::TeleportZone* pTelZone = Factory::CreateObjectHasPhysical<yj::TeleportZone>(Vec3(0.1f, -7.7f, -21.6f), physicsInfo, L"Forward", L"", false, MapType::HallColliderCheckMap, 2);
	//	AddGameObject(pTelZone);
	//}
}
