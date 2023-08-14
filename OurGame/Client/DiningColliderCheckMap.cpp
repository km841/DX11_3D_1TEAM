#include "pch.h"
#include "DiningColliderCheckMap.h"
#include "Engine.h"

/* Resource */
#include "MeshData.h"
#include "Material.h"
#include "Mesh.h"

/* Manager */
#include "PrefabManager.h"
#include "EventManager.h"
#include "Factory.h"
#include "CollisionManager.h"
#include "Input.h"
#include "SceneManager.h"
#include "Resources.h"

/* GameObject */
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "DecoObject.h"
#include "WallObject.h"

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"

/* Script */
#include "PlayerMoveScript.h"

/* Event */
#include "SceneChangeEvent.h"


namespace sy
{
	DiningColliderCheckMap::DiningColliderCheckMap()
		: Map(MapType::DiningColliderCheckMap)
	{
	}

	DiningColliderCheckMap::~DiningColliderCheckMap()
	{
	}

	void DiningColliderCheckMap::Initialize()
	{
		Map::Initialize();
	}

	void DiningColliderCheckMap::Update()
	{
		Map::Update();
	}

	void DiningColliderCheckMap::FixedUpdate()
	{
		Map::FixedUpdate();
	}

	void DiningColliderCheckMap::FinalUpdate()
	{
		Map::FinalUpdate();
	}

	void DiningColliderCheckMap::Render()
	{
		Map::Render();
	}

	void DiningColliderCheckMap::Enter()
	{
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::WallObject);


		//배경맵 하얀색으로 만들어주는 코드
		gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));
		

		//DecoObject == 콜라이더 없는 오브젝트
		//WallObject == 콜라이더 있는 오브젝트

		//Forward == 빛 계산이 없는 명령어
		//Deferred == 빛 계산이 있는 명령어
		
		//->GetTransform()->SetPositionExcludingColliders == 콜라이더를 제외하고 오브젝트만 [이동] 시키는 함수
		//->GetTransform()->SetRotationExcludingColliders == 콜라이더를 제외하고 오브젝트만 [회전] 시키는 함수
		


		// 전체맵 가이드라인 벽
		{
			DecoObject* pNormalBase = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Diningroom.fbx");

			pNormalBase->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));
			pNormalBase->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pNormalBase);
		}


		// 1층 바닥 - Floor
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(30.f, 0.1f, 37.f);

			Ground* pFloor = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, -8.5f, 6.6f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Floor.fbx");

			pFloor->GetTransform()->SetScale(Vec3(37.f, 37.f, 37.f));

			AddGameObject(pFloor);
		}

		// 2층 바닥 - floorextension_nocollider
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(27.2f, 0.1f, 19.f);

			Ground* pfloorextension_nocollider = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, -1.87f, -15.4f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\floorextension_nocollider.fbx");

			pfloorextension_nocollider->GetTransform()->SetScale(Vec3(110.f, 10.f, 145.f));
			pfloorextension_nocollider->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.f, 62.5f));
			AddGameObject(pfloorextension_nocollider);
		}

		//1층 계단 - Stairs
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(5.f, 0.1f, 14.f);

			Ground* pStairs = Factory::CreateObjectHasPhysical<Ground>(Vec3(-12.f, -5.2f, 0.5f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Stairs.fbx");

			pStairs->GetTransform()->SetScale(Vec3(15.f, 15.f, 15.f));
			pStairs->GetTransform()->SetRotation(Vec3(28.f, 0.f, 0.f));
			pStairs->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.f, 1.f));
			pStairs->GetTransform()->SetRotationExcludingColliders(Vec3(-28.f, 0.f, 0.f));
			AddGameObject(pStairs);
		}

		//1층 계단 벽 - Cube1 //현모님이 봐주셔야 할 코드
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(0.7f, 3.f, 16.f);

			Ground* pCube1 = Factory::CreateObjectHasPhysical<Ground>(Vec3(-9.8f, -4.f, 1.5f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Cube1.fbx");

			pCube1->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCube1->GetTransform()->SetRotation(Vec3(28.f, 0.f, 0.f));
			pCube1->GetTransform()->SetPositionExcludingColliders(Vec3(8.f, 0.f, 0.0f));
			pCube1->GetTransform()->SetRotationExcludingColliders(Vec3(0.f, 90.f, 0.f));
			AddGameObject(pCube1);
		}


		//2층 계단 - Stairs
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(5.f, 0.1f, 14.2f);

			Ground* pStairs_2floor = Factory::CreateObjectHasPhysical<Ground>(Vec3(2.2f, 1.6f, -22.5f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Stairs.fbx");

			pStairs_2floor->GetTransform()->SetScale(Vec3(15.f, 15.5f, 15.f));
			pStairs_2floor->GetTransform()->SetRotation(Vec3(28.f, -90.f, 0.f));
			pStairs_2floor->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.1f, 0.f));
			pStairs_2floor->GetTransform()->SetRotationExcludingColliders(Vec3(-28.f, 0.f, 0.f));
			AddGameObject(pStairs_2floor);
		}

		//2층 계단 벽 - Cube2
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(0.7f, 3.f, 16.f);

			Ground* pCube2 = Factory::CreateObjectHasPhysical<Ground>(Vec3(1.3f, 2.f, -20.f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Cube2.fbx");

			pCube2->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCube2->GetTransform()->SetRotation(Vec3(28.f, -90.f, 0.f));
			pCube2->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.f, 12.0f));
			pCube2->GetTransform()->SetRotationExcludingColliders(Vec3(0.f, 90.f, 0.f));
			AddGameObject(pCube2);
		}

		// 2층 계단 아랫벽 - Cube3
		{
			DecoObject* pCube3 = Factory::CreateObject<DecoObject>(Vec3(3.f, 0.5f, -20.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Cube3.fbx");

			pCube3->GetTransform()->SetScale(Vec3(13.f, 13.f, 13.f));
			pCube3->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			AddGameObject(pCube3);
		}


		// 3층 바닥 콜라이더
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(5.5f, 0.1f, 50.f);

			Ground* pWallObject = Factory::CreateObjectHasPhysical<Ground>(Vec3(11.f, 4.9f, 0.f), info, L"Forward", L"");
			AddGameObject(pWallObject);
		}






		//외곽 감싸주는 계단 ㄱ자 라인 줄 -wallPanel_Merged
		{
			DecoObject* pWallPanel_Merged = Factory::CreateObject<DecoObject>(Vec3(0.2f, -5.35f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\wallPanel_Merged.fbx");

			pWallPanel_Merged->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));

			AddGameObject(pWallPanel_Merged);
		}

		//기둥 모음집 - ColumnFull
		{
			{
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(0.f, 3.f, 25.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(30.f, 40.f, 30.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);
			}

			{
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(0.5f, -2.8f, -5.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(30.f, 22.f, 30.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);
			}
		}









		
		// 핑크색 잠금 여는 문 -POT_Door_4_Variant
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Static;
			info.size = Vec3(3.8f, 5.f, 0.4f);

			WallObject* pPOT_Door = Factory::CreateObjectHasPhysical<WallObject>(Vec3(8.75f, -5.5f, -5.8f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\POT_Door_4_Variant.fbx");
			pPOT_Door->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
			pPOT_Door->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -0.5f, 4.7f));

			AddGameObject(pPOT_Door);
		}

		// 핑크색 문 프레임 나무 - DoorFrame
		{
			DecoObject* pDoorFrame = Factory::CreateObject<DecoObject>(Vec3(8.75f, -6.0f, -1.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\DoorFrame.fbx");

			pDoorFrame->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));

			AddGameObject(pDoorFrame);
		}

		//벽난로 -fireplace
		{
			DecoObject* pfireplace = Factory::CreateObject<DecoObject>(Vec3(-0.4f, -5.f, -1.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\fireplace.fbx");

			pfireplace->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
			

			AddGameObject(pfireplace);
		}

		//1층 바닥 구멍 테두리 - RimStarter
		{
			DecoObject* pRimStarter = Factory::CreateObject<DecoObject>(Vec3(-0.3f, -8.5f, 3.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\RimStarter.fbx");

			pRimStarter->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));


			AddGameObject(pRimStarter);
		}

		









		// Toy 까마귀 일단 배치
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Dynamic;
			physicsInfo.eGeometryType = GeometryType::Sphere;
			physicsInfo.size = Vec3(2.f, 2.f, 2.f);

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 0.f, 0.f), physicsInfo, L"Forward", L"..\\Resources\\FBX\\Player\\Crow2.fbx");
			pPlayer->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));

			PlayerMoveScript* pPlayerSc =  pPlayer->AddComponent(new PlayerMoveScript);
	
			AddGameObject(pPlayer);
		}






		// Table // 그냥 하는거 예시
		/*{
			DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(5.f, 10.f, 20.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\GrandmaBossMap\\GrandmaBossTable.fbx");
			pDecoObject->GetRigidBody()->RemoveGravity();

			pDecoObject->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
			pDecoObject->GetTransform()->SetRotation(Vec3(-90.f, 20.f, 0.f));
			AddGameObject(pDecoObject);
		}*/

		// Left Collider // 그래픽 안가져오고 콜라이더만 설정하는거
		/*{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(13.f, 5.f, 17.f);

			WallObject* pWallObject = Factory::CreateObjectHasPhysical<WallObject>(Vec3(9.f, 2.5f, -36.f), info, L"Forward", L"");
			AddGameObject(pWallObject);
		}*/
	}

	void DiningColliderCheckMap::Exit()
	{
	}
}
