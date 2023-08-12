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


/* Event */
#include "SceneChangeEvent.h"


namespace hm
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
		//배경 흰색으로 바꿔주는 코드
		//gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f)); 
		

		//DecoObject == 맵 장식품용 오브젝트
		//WallObject == 콜라이더 가지고있는 오브젝트

		//L"Forward" == 빛의 계산을 받지않는
		//L"Deferred" == 빛의 계산을 하는

		// 전체맵의 큰 가이드라인
		{
			DecoObject* pNormalBase = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Forward", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Diningroom.fbx");

			pNormalBase->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));
			pNormalBase->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
			pNormalBase->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.f, 0.f));

			AddGameObject(pNormalBase);
		}

		// 전체맵의 1층 바닥 //안보임;;;;;;;;;;;;;;;;
		/*{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(1.f, 1.f, 1.f);

			WallObject* POT_Door_4_Variant = Factory::CreateObjectHasPhysical<WallObject>(Vec3(0.0f, 0.0f, 0.0f), info, L"Forward", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Diningroom_detach2.fbx");

			POT_Door_4_Variant->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));
			POT_Door_4_Variant->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
			POT_Door_4_Variant->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.f, 0.0f));

			AddGameObject(POT_Door_4_Variant);
		}*/

		// 핑크색 문제풀이해결 벽
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Static;
			info.size = Vec3(4.f, 6.f, 0.5f);

			WallObject* POT_Door_4_Variant = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-8.7f, -5.6f, -5.6f), info, L"Forward", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\POT_Door_4_Variant.fbx");

			POT_Door_4_Variant->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
			POT_Door_4_Variant->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
			POT_Door_4_Variant->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.f, -4.7f));

			AddGameObject(POT_Door_4_Variant);
		}

		//핑크색 문제풀이해결 벽 - 프레임
		{
			DecoObject* pDoorFrameBig = Factory::CreateObject<DecoObject>(Vec3(-8.7f, -5.6f, 10.2f), L"Forward", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\DoorFrameBig.fbx");

			pDoorFrameBig->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
			pDoorFrameBig->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			pDoorFrameBig->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.f, 0.f));

			AddGameObject(pDoorFrameBig);
		}





		// Wall
		/*for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 12; ++x)
			{
				DecoObject* pDecoObject = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\GrandmaBossWall1.fbx");
				pDecoObject->GetRigidBody()->RemoveGravity();

				float radian = (225.f + (x * 16.f)) * XM_PI / 180.f;
				float radius = 13.f;

				pDecoObject->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
				pDecoObject->GetTransform()->SetRotation(Vec3(0.f, 50.f + x * 16.f, 0.f));

				pDecoObject->GetTransform()->SetPosition(
					Vec3(radius * cosf(radian) + radius * sinf(radian),
						-20.f + y * 10.f,
						(radius * cosf(radian) - radius * sinf(radian)) + 10.f));
				AddGameObject(pDecoObject);
			}
		}*/

		// Create Desk
		/*{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Static;
			info.size = Vec3(10.f, 3.f, 1.f);

			Player* pGameObject = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 0.f, 0.f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Hall\\Desk.fbx");
			pGameObject->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));
			pGameObject->GetTransform()->SetRotationExcludingColliders(Vec3(0.f, -45.f, 0.f));
			pGameObject->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.f, -1.f));

			AddGameObject(pGameObject);
			GET_SINGLE(PrefabManager)->AddPrefab(L"Test2", pGameObject);
		}*/
	}

	void DiningColliderCheckMap::Exit()
	{
	}
}
