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
#include "PlacementScript.h"
#include "PaperBurnScript.h"

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

	void DiningColliderCheckMap::Start()
	{
		Map::Start();
	}

	void DiningColliderCheckMap::Update()
	{
		Map::Update();

		//if (mTarget != nullptr)
		//{
		//	if (IS_UP(KeyType::LEFT))
		//	{
		//		Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
		//		Vec3 fixed_pos = Vec3(target_pos.x -= 0.1f, target_pos.y, target_pos.z);
		//		mTarget->GetTransform()->SetPosition(fixed_pos);
		//	}
		//	if (IS_UP(KeyType::RIGHT))
		//	{
		//		Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
		//		Vec3 fixed_pos = Vec3(target_pos.x += 0.1f, target_pos.y, target_pos.z);
		//		mTarget->GetTransform()->GetTransform()->SetPosition(fixed_pos);
		//	}
		//	if (IS_UP(KeyType::UP))
		//	{
		//		Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
		//		Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y, target_pos.z += 0.1f);
		//		mTarget->GetTransform()->GetTransform()->SetPosition(fixed_pos);
		//	}
		//	if (IS_UP(KeyType::DOWN))
		//	{
		//		Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
		//		Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y, target_pos.z -= 0.1f);
		//		mTarget->GetTransform()->GetTransform()->SetPosition(fixed_pos);
		//	}
		//	if (IS_UP(KeyType::Z))
		//	{
		//		Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
		//		Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y += 0.1f, target_pos.z);
		//		mTarget->GetTransform()->GetTransform()->SetPosition(fixed_pos);
		//	}
		//	if (IS_UP(KeyType::X))
		//	{
		//		Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
		//		Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y -= 0.1f, target_pos.z);
		//		mTarget->GetTransform()->SetPosition(fixed_pos);

		//	}
		//	if (IS_UP(KeyType::R)) //회전
		//	{
		//		Vec3 target_rot = Vec3(mTarget->GetTransform()->GetRotation());
		//		Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y += 10.0f, target_rot.z);
		//		mTarget->GetTransform()->GetTransform()->SetRotation(fixed_rot);
		//	}
		//	if (IS_UP(KeyType::T)) //회전
		//	{
		//		Vec3 target_rot = Vec3(mTarget->GetTransform()->GetRotation());
		//		Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y -= 10.0f, target_rot.z);
		//		mTarget->GetTransform()->GetTransform()->SetRotation(fixed_rot);
		//	}

		//	if (IS_UP(KeyType::Y)) //회전
		//	{
		//		Vec3 target_rot = Vec3(mTarget->GetTransform()->GetRotation());
		//		Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y += 1.0f, target_rot.z);
		//		mTarget->GetTransform()->GetTransform()->SetRotation(fixed_rot);
		//	}
		//	if (IS_UP(KeyType::U)) //회전
		//	{
		//		Vec3 target_rot = Vec3(mTarget->GetTransform()->GetRotation());
		//		Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y -= 1.0f, target_rot.z);
		//		mTarget->GetTransform()->GetTransform()->SetRotation(fixed_rot);
		//	}

		//	if (IS_UP(KeyType::O)) //스케일 - 전체적 키우기
		//	{
		//		Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
		//		Vec3 fixed_scale = Vec3(target_scale.x += 0.5f, target_scale.y += 0.5f, target_scale.z += 0.5f);
		//		mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
		//	}
		//	if (IS_UP(KeyType::P)) //스케일 - 전체적 줄이기
		//	{
		//		Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
		//		Vec3 fixed_scale = Vec3(target_scale.x -= 0.5f, target_scale.y -= 0.5f, target_scale.z -= 0.5f);
		//		mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
		//	}

		//	if (IS_UP(KeyType::K)) //스케일 - y축제외 키우기
		//	{
		//		Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
		//		Vec3 fixed_scale = Vec3(target_scale.x += 0.5f, target_scale.y, target_scale.z += 0.5f);
		//		mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
		//	}
		//	if (IS_UP(KeyType::L)) //스케일 - y축 제외 줄이기
		//	{
		//		Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
		//		Vec3 fixed_scale = Vec3(target_scale.x -= 0.5f, target_scale.y, target_scale.z -= 0.5f);
		//		mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
		//	}
		//	if (IS_UP(KeyType::N)) //스케일 -y축만 키우기
		//	{
		//		Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
		//		Vec3 fixed_scale = Vec3(target_scale.x, target_scale.y += 0.5, target_scale.z);
		//		mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
		//	}
		//	if (IS_UP(KeyType::M)) //스케일 -y축만 줄이기
		//	{
		//		Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
		//		Vec3 fixed_scale = Vec3(target_scale.x, target_scale.y -= 0.5, target_scale.z);
		//		mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
		//	}

		//	if (IS_UP(KeyType::H)) //스케일 - x축만 키우기
		//	{
		//		Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
		//		Vec3 fixed_scale = Vec3(target_scale.x +=0.5, target_scale.y, target_scale.z);
		//		mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
		//	}
		//	if (IS_UP(KeyType::J)) //스케일 -x축만 줄이기
		//	{
		//		Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
		//		Vec3 fixed_scale = Vec3(target_scale.x -=0.5, target_scale.y, target_scale.z);
		//		mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
		//	}

		//	if (IS_UP(KeyType::F)) //스케일 -z축만 키우기
		//	{
		//		Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
		//		Vec3 fixed_scale = Vec3(target_scale.x, target_scale.y, target_scale.z += 0.5);
		//		mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
		//	}
		//	if (IS_UP(KeyType::G)) //스케일 -z축만 줄이기
		//	{
		//		Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
		//		Vec3 fixed_scale = Vec3(target_scale.x, target_scale.y, target_scale.z -= 0.5);
		//		mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
		//	}

		//	if (IS_UP(KeyType::ENTER))
		//	{
		//		Vec3 a = mTarget->GetTransform()->GetPosition();
		//		Vec3 b = mTarget->GetTransform()->GetRotation();
		//		Vec3 c = mTarget->GetTransform()->GetScale();
		//		int d = 0;


		//	}
		//}
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
		//gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));


#pragma region "어드민"
#pragma endregion

		//DecoObject == 콜라이더 없는 오브젝트
		//WallObject == 콜라이더 있는 오브젝트

		//Forward == 빛 계산이 없는 명령어
		//Deferred == 빛 계산이 있는 명령어

		//->GetTransform()->SetPositionExcludingColliders == 콜라이더를 제외하고 오브젝트만 [이동] 시키는 함수
		//->GetTransform()->SetRotationExcludingColliders == 콜라이더를 제외하고 오브젝트만 [회전] 시키는 함수



		// 전체맵 가이드라인 벽
		{
			DecoObject* pNormalBase = Factory::CreateObject<DecoObject>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Diningroom.fbx",true);

			pNormalBase->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));
			pNormalBase->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			pNormalBase->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr,2,0); //3번째인자 == 텍스처 첫번째 png 인지 두번째 png인지 구별하게 해주는거
			pNormalBase->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(115, 118, 128),2,0); //3번째인자 == 텍스처 첫번째 png 인지 두번째 png인지 구별하게 해주는거
			AddGameObject(pNormalBase);
		}

#pragma region "1층"
		//1층
		{
			// 1층 바닥 - Floor
			{
				PhysicsInfo info;
				info.eActorType = ActorType::Static;
				info.eGeometryType = GeometryType::Box;
				info.size = Vec3(30.f, 0.1f, 37.f);

				Ground* pFloor = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, -8.5f, 6.6f), info, L"Forward", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Floor.fbx");

				pFloor->GetTransform()->SetScale(Vec3(37.f, 37.f, 37.f));
				pFloor->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
				pFloor->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(164, 164, 145));

				AddGameObject(pFloor);
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

			{
				//1-2층 계단 앞 기둥
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-16.7f, -0.7f, -6.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(15.f, 4.0f, 15.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			
				AddGameObject(pColumnFull);
			}

			//1층 계단 벽 - Cube1 
			{
				PhysicsInfo info;
				info.eActorType = ActorType::Static;
				info.eGeometryType = GeometryType::Box;
				info.size = Vec3(0.7f, 3.f, 16.f);

				Ground* pCube1 = Factory::CreateObjectHasPhysical<Ground>(Vec3(-9.8f, -4.f, 1.5f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Cube1.fbx");

				pCube1->GetTransform()->SetScale(Vec3(30.f, 26.f, 25.f));
				pCube1->GetTransform()->SetRotation(Vec3(28.f, 0.f, 0.f));
				pCube1->GetTransform()->SetPositionExcludingColliders(Vec3(8.f, -0.3f, -1.0f));
				pCube1->GetTransform()->SetRotationExcludingColliders(Vec3(0.f, 90.f, -28.f));
				AddGameObject(pCube1);
			}

			{
				//1층 맨앞 기둥
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(0.f, 3.f, 25.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(30.f, 40.f, 30.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);
			}

			{
				//1층 ㄱ자 사이 기둥
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(0.5f, -2.8f, -5.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(30.f, 22.f, 30.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);
			}



			//외곽 감싸주는 계단 ㄱ자 라인 줄 -wallPanel_Merged
			{
				DecoObject* pWallPanel_Merged = Factory::CreateObject<DecoObject>(Vec3(0.2f, -5.35f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\wallPanel_Merged.fbx");

				pWallPanel_Merged->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));

				AddGameObject(pWallPanel_Merged);
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

			//1층 벽에 붙은 벽돌모양 테두리 오른쪽 벽1 - WallPanel
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(13.5f, -7.2f, -5.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallPanel.fbx");

				pWallPanel->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pWallPanel->GetTransform()->SetRotation(Vec3(0.0f, 90.f, 0.f));
			
				AddGameObject(pWallPanel);
			}

			//1층 벽에 붙은 벽돌모양 테두리 오른쪽 벽2 - WallPanel
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(4.0f, -7.2f, -5.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallPanel.fbx");

				pWallPanel->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pWallPanel->GetTransform()->SetRotation(Vec3(0.0f, 90.f, 0.f));
			

				AddGameObject(pWallPanel);
			}

			//1층 벽에 붙은 벽돌모양 테두리 오른쪽 벽3 - WallPanel
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(-6.8f, -7.2f, -5.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallPanel.fbx");

				pWallPanel->GetTransform()->SetScale(Vec3(5.f, 5.f, 6.f));
				pWallPanel->GetTransform()->SetRotation(Vec3(0.0f, 90.f, 0.f));
				

				AddGameObject(pWallPanel);
			}

			//1층 벽에 붙은 벽돌모양 테두리 왼쪽벽1 - WallPanel
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(14.01f, -7.2f, -2.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallPanel.fbx");

				pWallPanel->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pWallPanel->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));
			

				AddGameObject(pWallPanel);
			}

			//1층 벽에 붙은 벽돌모양 테두리 왼쪽벽2 - WallPanel
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(14.01f, -7.2f, 2.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallPanel.fbx");

				pWallPanel->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pWallPanel->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));
				

				AddGameObject(pWallPanel);
			}

			//1층 벽에 붙은 벽돌모양 테두리 왼쪽벽3 - WallPanel
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(14.01f, -7.2f, 7.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallPanel.fbx");

				pWallPanel->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pWallPanel->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));

				AddGameObject(pWallPanel);
			}
			//1층 벽에 붙은 벽돌모양 테두리 왼쪽벽4 - WallPanel
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(14.01f, -7.2f, 12.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallPanel.fbx");

				pWallPanel->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pWallPanel->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));


				AddGameObject(pWallPanel);
			}

			//1층 벽에 붙은 벽돌모양 테두리 왼쪽벽4 - WallPanel
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(14.01f, -7.2f, 16.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallPanel.fbx");

				pWallPanel->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pWallPanel->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));


				AddGameObject(pWallPanel);
			}

			//1층 벽에 붙은 벽돌모양 테두리 왼쪽벽5 - WallPanel
			{
				DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(14.01f, -7.2f, 21.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallPanel.fbx");

				pWallPanel->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pWallPanel->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));
				

				AddGameObject(pWallPanel);
			}

			// 1층 천장 샹들리에 - ChandelierWithChain
			{
				DecoObject* pChandelierWithChain = Factory::CreateObject<DecoObject>(Vec3(0.0f, 20.0f, 16.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ChandelierWithChain.fbx");

				pChandelierWithChain->GetTransform()->SetScale(Vec3(30.f, 30.f, 30.f));
				pChandelierWithChain->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));

				AddGameObject(pChandelierWithChain);
			}

			//1층 테이블 1 -CofeeTableWithCloth
			{
				PhysicsInfo Info;
				Info.eActorType = ActorType::Static;
				Info.eGeometryType = GeometryType::Box;
				Info.size = Vec3(4.5f, 2.f, 6.5f);

				WallObject* pCofeeTableWithCloth = Factory::CreateObjectHasPhysical<WallObject>(Vec3(5.67f, -7.4f, 16.1f), Info, L"Deferred",  L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CofeeTableWithCloth.fbx");

				pCofeeTableWithCloth->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));
				pCofeeTableWithCloth->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));
				
				AddGameObject(pCofeeTableWithCloth);
			}

			//1층 테이블 2 -CofeeTableWithCloth
			{
				PhysicsInfo Info;
				Info.eActorType = ActorType::Static;
				Info.eGeometryType = GeometryType::Box;
				Info.size = Vec3(4.5f, 2.f, 6.5f);

				WallObject* pCofeeTableWithCloth = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-6.3f, -7.4f, 16.1f), Info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CofeeTableWithCloth.fbx");

				pCofeeTableWithCloth->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));
				pCofeeTableWithCloth->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));
				
				AddGameObject(pCofeeTableWithCloth);
			}

			//1층 러그 - Rug_Mark
			{
				DecoObject* pRug_Mark = Factory::CreateObject<DecoObject>(Vec3(-0.2f, -8.5f, 16.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Rug_Mark.fbx");

				pRug_Mark->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));
				pRug_Mark->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
				AddGameObject(pRug_Mark);
			}

			//1층 체어 1 - Chair
			{
				PhysicsInfo Info;
				Info.eActorType = ActorType::Static;
				Info.eGeometryType = GeometryType::Box;
				Info.size = Vec3(2.f, 1.f, 2.f);

				WallObject* pChair = Factory::CreateObjectHasPhysical<WallObject>(Vec3(11.0f, -7.6f, 17.0f), Info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pChair->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));
				pChair->GetTransform()->SetRotationExcludingColliders(Vec3(0.0f, 20.f, 0.f));
				pChair->GetTransform()->SetPositionExcludingColliders(Vec3(0.0f, 1.6f, 0.f));
				
				AddGameObject(pChair);
			}

			//1층 체어 2 - Chair
			{
				PhysicsInfo Info;
				Info.eActorType = ActorType::Static;
				Info.eGeometryType = GeometryType::Box;
				Info.size = Vec3(2.f, 1.f, 2.f);

				WallObject* pChair = Factory::CreateObjectHasPhysical<WallObject>(Vec3(3.0f, -7.6f, 22.0f), Info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pChair->GetTransform()->SetRotation(Vec3(0.0f, -120.f, 0.f));
				pChair->GetTransform()->SetRotationExcludingColliders(Vec3(0.0f, 20.f, 0.f));
				pChair->GetTransform()->SetPositionExcludingColliders(Vec3(0.0f, 1.6f, 0.f));
				
				AddGameObject(pChair);
			}

			//1층 체어 3 - Chair
			{
				PhysicsInfo Info;
				Info.eActorType = ActorType::Static;
				Info.eGeometryType = GeometryType::Box;
				Info.size = Vec3(2.f, 1.f, 2.f);

				WallObject* pChair = Factory::CreateObjectHasPhysical<WallObject>(Vec3(3.0f, -7.6f, 10.5f), Info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pChair->GetTransform()->SetRotation(Vec3(0.0f, 120.f, 0.f));
				pChair->GetTransform()->SetRotationExcludingColliders(Vec3(0.0f, 20.f, 0.f));
				pChair->GetTransform()->SetPositionExcludingColliders(Vec3(0.0f, 1.6f, 0.f));
				AddGameObject(pChair);
			}

			//1층 체어 4 - Chair
			{
				PhysicsInfo Info;
				Info.eActorType = ActorType::Static;
				Info.eGeometryType = GeometryType::Box;
				Info.size = Vec3(2.f, 1.f, 2.f);

				WallObject* pChair = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-3.8f, -7.6f, 22.0f), Info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pChair->GetTransform()->SetRotation(Vec3(0.0f, -60.f, 0.f));
				pChair->GetTransform()->SetRotationExcludingColliders(Vec3(0.0f, 20.f, 0.f));
				pChair->GetTransform()->SetPositionExcludingColliders(Vec3(0.0f, 1.6f, 0.f));
				
				AddGameObject(pChair);
			}

			//1층 체어 5 - Chair
			{
				PhysicsInfo Info;
				Info.eActorType = ActorType::Static;
				Info.eGeometryType = GeometryType::Box;
				Info.size = Vec3(2.f, 1.f, 2.f);

				WallObject* pChair = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-10.f, -7.6f, 22.0f), Info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pChair->GetTransform()->SetRotation(Vec3(0.0f, -150.f, 0.f));
				pChair->GetTransform()->SetRotationExcludingColliders(Vec3(0.0f, 20.f, 0.f));
				pChair->GetTransform()->SetPositionExcludingColliders(Vec3(0.0f, 1.6f, 0.f));
			
				AddGameObject(pChair);
			}

			//1층 체어 6 - Chair
			{
				PhysicsInfo Info;
				Info.eActorType = ActorType::Static;
				Info.eGeometryType = GeometryType::Box;
				Info.size = Vec3(2.f, 1.f, 2.f);

				WallObject* pChair = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-3.8f, -7.6f, 11.0f), Info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Chair.fbx");

				pChair->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
				pChair->GetTransform()->SetRotation(Vec3(0.0f, 60.f, 0.f));
				pChair->GetTransform()->SetRotationExcludingColliders(Vec3(0.0f, 20.f, 0.f));
				pChair->GetTransform()->SetPositionExcludingColliders(Vec3(0.0f, 1.6f, 0.f));
				
				AddGameObject(pChair);
			}

			
		}
#pragma endregion




#pragma region "2층"

		//2층
		{
			// 2층 바닥 - floorextension_nocollider
			{
				PhysicsInfo info;
				info.eActorType = ActorType::Static;
				info.eGeometryType = GeometryType::Box;
				info.size = Vec3(27.2f, 0.1f, 19.f);

				Ground* pfloorextension_nocollider = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, -1.87f, -15.4f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\floorextension_nocollider.fbx");

				pfloorextension_nocollider->GetTransform()->SetScale(Vec3(110.f, 10.f, 145.f));
				pfloorextension_nocollider->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, 0.f, 62.5f));
				pfloorextension_nocollider->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
				pfloorextension_nocollider->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(164, 164, 145));
				AddGameObject(pfloorextension_nocollider);
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

			{
				//2층 계단 아래 가로줄 - WallRim
				DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(5.6f, -1.8f, -20.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

				pWallRim->GetTransform()->SetScale(Vec3(29.5f, 51.f, 21.5f));
				pWallRim->GetTransform()->SetRotation(Vec3(0.f, 90.0f, 0.f));
			
				AddGameObject(pWallRim);

			}

			{
				//2층 계단-벽 사이 가로줄 - WallRim
				DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(-3.4f, -1.8f, -25.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

				pWallRim->GetTransform()->SetScale(Vec3(29.5f, 51.f, 21.5f));
				pWallRim->GetTransform()->SetRotation(Vec3(0.f, 90.0f, 0.f));
				
				AddGameObject(pWallRim);

			}

			//2층 계단 벽 왼쪽- Cube2
			{
				PhysicsInfo info;
				info.eActorType = ActorType::Static;
				info.eGeometryType = GeometryType::Box;
				info.size = Vec3(0.7f, 3.f, 16.f);

				Ground* pCube2 = Factory::CreateObjectHasPhysical<Ground>(Vec3(1.3f, 2.f, -20.f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Cube2.fbx");

				pCube2->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
				pCube2->GetTransform()->SetRotation(Vec3(28.f, -90.f, 0.f));
				pCube2->GetTransform()->SetPositionExcludingColliders(Vec3(1.1f, -0.5f, 12.1f));
				pCube2->GetTransform()->SetRotationExcludingColliders(Vec3(0.f, 90.f, -28.f));
				AddGameObject(pCube2);
			}

			//2층 계단 벽 오른쪽 - Cube2
			{
				PhysicsInfo info;
				info.eActorType = ActorType::Static;
				info.eGeometryType = GeometryType::Box;
				info.size = Vec3(0.7f, 3.f, 16.f);

				Ground* pCube2 = Factory::CreateObjectHasPhysical<Ground>(Vec3(1.3f, 2.f, -25.f), info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Cube2.fbx");

				pCube2->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
				pCube2->GetTransform()->SetRotation(Vec3(28.f, -90.f, 0.f));
				pCube2->GetTransform()->SetPositionExcludingColliders(Vec3(1.1f, -0.5f, 12.1f));
				pCube2->GetTransform()->SetRotationExcludingColliders(Vec3(0.f, 90.f, -28.f));
				AddGameObject(pCube2);
			}

			{
				//2층 난간 아래 가로줄 - WallRim
				DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(3.8f, -1.9f, -6.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

				pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 27.5f));
				pWallRim->GetTransform()->SetRotation(Vec3(0.f, 90.0f, 0.f));
				
				AddGameObject(pWallRim);

			}
			{
				//2층 난간 위 가로줄 - WallRim
				DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(3.8f, -0.4f, -6.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

				pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 27.5f));
				pWallRim->GetTransform()->SetRotation(Vec3(0.f, 90.0f, 0.f));
				
				AddGameObject(pWallRim);

			}


			// 2층 계단 아랫벽 - Cube3
			{
				DecoObject* pCube3 = Factory::CreateObject<DecoObject>(Vec3(3.f, 0.5f, -20.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Cube3.fbx");

				pCube3->GetTransform()->SetScale(Vec3(13.f, 13.f, 13.f));
				pCube3->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pCube3);
			}

			{
				//2층 맨앞 기둥
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(0.2f, 2.7f, -6.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(19.f, 16.f, 19.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);


			}

			{
				//2층 중간 기둥
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(0.2f, 2.7f, -13.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(19.f, 16.f, 19.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);

			}

			{
				//2층 계단 기둥
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(1.1f, 2.5f, -20.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(17.f, 17.f, 17.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);
			}

			{
				//2층 계단 앞 기둥
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-11.8f, -0.7f, -20.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(15.f, 4.0f, 15.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);
			}

			{
				//2층 계단 앞 벽쪽 기둥
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-11.8f, -0.7f, -24.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(15.f, 4.0f, 15.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);

			}

			{
				//2-3층 계단 벽쪽 기둥
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(1.1f, 9.8f, -25.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(17.f, 17.f, 17.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);
			}

			{
				//2층 맨오른쪽 큰기둥
				DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-27.6f, 6.2f, -25.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

				pColumnFull->GetTransform()->SetScale(Vec3(30.f, 30.f, 30.f));
				pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
				AddGameObject(pColumnFull);
			}

			{
				//2층 난간 막대기 - BannisterStick
				for (float i = 0; i < 12; i++)
				{
					DecoObject* pBannisterStick = Factory::CreateObject<DecoObject>(Vec3(7.5f - (i * 1.5f), -1.f, -6.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\BannisterStick.fbx");

					pBannisterStick->GetTransform()->SetScale(Vec3(2.f, 1.3f, 2.f));
					pBannisterStick->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));

					AddGameObject(pBannisterStick);

				}
			}

			{
				//벽에 붙은 그림 - AssortedPaintings
				DecoObject* pAssortedPaintings = Factory::CreateObject<DecoObject>(Vec3(-4.3f, 6.4f, -12.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\AssortedPaintings.fbx");

				pAssortedPaintings->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
				pAssortedPaintings->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
				
				AddGameObject(pAssortedPaintings);
			}

			//2층 테이블 1 -CofeeTableWithCloth
			{
				PhysicsInfo Info;
				Info.eActorType = ActorType::Static;
				Info.eGeometryType = GeometryType::Box;
				Info.size = Vec3(4.5f, 2.f, 6.5f);

				WallObject* pCofeeTableWithCloth = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-0.1f, -0.7f, -9.6f), Info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CofeeTableWithCloth.fbx");

				pCofeeTableWithCloth->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));
				pCofeeTableWithCloth->GetTransform()->SetRotation(Vec3(0.0f, -90.f, 0.f));
				
				AddGameObject(pCofeeTableWithCloth);
			}

			//2층 러그 - Rug_Mark
			{
				DecoObject* pRug_Mark = Factory::CreateObject<DecoObject>(Vec3(-9.2f, -1.8f, -13.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\Rug_Mark.fbx");

				pRug_Mark->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));
				pRug_Mark->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
				
				AddGameObject(pRug_Mark);
			}

			//2층 왕의자 - fancyChairSit
			{
				PhysicsInfo Info;
				Info.eActorType = ActorType::Static;
				Info.eGeometryType = GeometryType::Box;
				Info.size = Vec3(2.f, 1.f, 2.f);

				WallObject* pfancyChairSit = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-0.1f, -1.1f, -14.0f), Info, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\fancyChairSit.fbx");

				pfancyChairSit->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
				pfancyChairSit->GetTransform()->SetRotation(Vec3(0.0f, 0.f, 0.f));
				pfancyChairSit->GetTransform()->SetRotationExcludingColliders(Vec3(0.0f, 0.f, 0.f));
				pfancyChairSit->GetTransform()->SetPositionExcludingColliders(Vec3(.0f, 3.6f, 11.f));
				
				AddGameObject(pfancyChairSit);
			}

		}
#pragma endregion




#pragma region "3층"
		// 3층 바닥 콜라이더
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(5.5f, 0.1f, 50.f);

			Ground* pWallObject = Factory::CreateObjectHasPhysical<Ground>(Vec3(11.f, 4.9f, 0.f), info, L"Forward", L"");
			AddGameObject(pWallObject);
		}

		// 3층 바닥 - floorextension_nocollider
		{
			Ground* pfloorextension_nocollider = Factory::CreateObject<Ground>(Vec3(11.5f, 5.f, 169.8f), L"Forward", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\floorextension_nocollider.fbx");

			pfloorextension_nocollider->GetTransform()->SetScale(Vec3(20.f, 10.f, 400.f));
			pfloorextension_nocollider->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
			pfloorextension_nocollider->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(164, 164, 145));
			AddGameObject(pfloorextension_nocollider);
		}

		{
			//3층 벽쪽 커튼 1 - CurtainHorizontal
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(1.8f, 12.5f, 18.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			
			AddGameObject(pCurtainHorizontal);
		}

		{
			//3층 벽쪽 커튼 2 - CurtainHorizontal
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(1.8f, 12.5f, 9.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			
			AddGameObject(pCurtainHorizontal);
		}

		{
			//3층 벽쪽 커튼 3 - CurtainHorizontal
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(1.8f, 12.5f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));

			AddGameObject(pCurtainHorizontal);
		}


		{
			//3층 벽쪽 커튼 4 - CurtainHorizontal
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(1.8f, 12.5f, -11.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			
			AddGameObject(pCurtainHorizontal);
		}

		{
			//3층 벽쪽 커튼 5 - CurtainHorizontal
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(1.8f, 12.5f, -20.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));

			AddGameObject(pCurtainHorizontal);
		}

		{
			//3층 벽쪽 커튼 6 - CurtainHorizontal
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(2.1f, 12.5f, -12.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pCurtainHorizontal);
		}

		{
			//3층 벽쪽 커튼 7 - CurtainHorizontal
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(-7.1f, 12.5f, -12.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\CurtainHorizontal.fbx");

			pCurtainHorizontal->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
			pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pCurtainHorizontal);
		}





		{
			//3층 ㄱ자 벽쪽 기둥
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(6.3f, 9.8f, -25.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

			pColumnFull->GetTransform()->SetScale(Vec3(17.f, 17.f, 17.f));
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			AddGameObject(pColumnFull);
		}


		{
			//3층 중간 벽쪽 기둥
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(6.3f, 9.8f, -6.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

			pColumnFull->GetTransform()->SetScale(Vec3(17.f, 17.f, 17.f));
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			AddGameObject(pColumnFull);
		}


		{
			//3층 난간 맨왼쪽 기둥
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(1.4f, 6.2f, 23.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

			pColumnFull->GetTransform()->SetScale(Vec3(16.5f, 4.5f, 16.5f));
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			AddGameObject(pColumnFull);

		}

		
		{
			//3층 난간 맨왼쪽 두번째 기둥
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(1.3f, 6.2f, 18.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

			pColumnFull->GetTransform()->SetScale(Vec3(16.5f, 4.5f, 16.5f));
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));

			AddGameObject(pColumnFull);
		}

		{
			//3층 난간 맨왼쪽 세번째 기둥
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(1.3f, 6.2f, 13.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\ColumnFull.fbx");

			pColumnFull->GetTransform()->SetScale(Vec3(16.5f, 4.5f, 16.5f));
			pColumnFull->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			AddGameObject(pColumnFull);
		}

		{
			//3층 난간 긴 막대기 아래 가로줄 - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(9.1f, 5.1f, 4.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 49.5f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pWallRim);
			
		}

		{
			//3층 난간 긴 막대기 위 가로줄 
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(9.1f, 6.5f, 4.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 49.5f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pWallRim);
			
		}

		{
			//3층 난간 긴 막대기 반대편 가로줄 - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(14.1f, 5.1f, 10.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 72.f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			
			AddGameObject(pWallRim);
		}

		{
			//3층 난간 긴 막대기 반대편 천장 가로줄 - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(14.3f, 14.2f, 12.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 20.f, 73.f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
		

			AddGameObject(pWallRim);
		}

		{
			//3층 난간 긴 천장 세로줄 - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(-5.7f, 14.2f, -25.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 20.f, 40.f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			

			AddGameObject(pWallRim);
		}

		{
			//3층 난간 짧은 막대기 아래 가로줄 - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(9.1f, 5.1f, 21.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 6.5f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pWallRim);

		}

		{
			//3층 난간 짧은 막대기 위 가로줄 - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(9.1f, 6.5f, 21.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 6.5f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));

			AddGameObject(pWallRim);

		}

		{
			//3층 난간 짧은 막대기 세로 /  아래 가로줄 - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(10.8f, 5.1f, 23.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 6.5f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));
			AddGameObject(pWallRim);

		}

		{
			//3층 난간 짧은 막대기 세로 / 위 가로줄 - WallRim
			DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(10.8f, 6.5f, 23.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\WallRim.fbx");

			pWallRim->GetTransform()->SetScale(Vec3(29.5f, 11.f, 6.5f));
			pWallRim->GetTransform()->SetRotation(Vec3(0.f, -90.0f, 0.f));

			AddGameObject(pWallRim);

		}

		{
			//난간 막대기 - BannisterStick
			DecoObject* pBannisterStick = Factory::CreateObject<DecoObject>(Vec3(9.f, 5.8f, 21.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\BannisterStick.fbx");

			pBannisterStick->GetTransform()->SetScale(Vec3(2.f, 1.3f, 2.f));
			pBannisterStick->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pBannisterStick);
		}

		{
			//난간 막대기 - BannisterStick
			DecoObject* pBannisterStick = Factory::CreateObject<DecoObject>(Vec3(9.f, 5.8f, 20.01f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\BannisterStick.fbx");

			pBannisterStick->GetTransform()->SetScale(Vec3(2.f, 1.3f, 2.f));
			pBannisterStick->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
			AddGameObject(pBannisterStick);
		}

		{
			//난간 막대기 - BannisterStick
			for (float i = 0; i < 9; i++)
			{
				DecoObject* pBannisterStick = Factory::CreateObject<DecoObject>(Vec3(9.f, 5.8f, 11.7f-(i*2)), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\BannisterStick.fbx");
				
				pBannisterStick->GetTransform()->SetScale(Vec3(2.f, 1.3f, 2.f));
				pBannisterStick->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
				AddGameObject(pBannisterStick);

			}
		}

		{
			//난간 막대기 - BannisterStick
			for (float i = 0; i < 3; i++)
			{
				DecoObject* pBannisterStick = Factory::CreateObject<DecoObject>(Vec3(9.f, 5.8f, -7.7f - (i * 2)), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\BannisterStick.fbx");

				pBannisterStick->GetTransform()->SetScale(Vec3(2.f, 1.3f, 2.f));
				pBannisterStick->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
				AddGameObject(pBannisterStick);

			}
		}

		{
			//난간 막대기 - BannisterStick
			for (float i = 0; i < 3; i++)
			{
				DecoObject* pBannisterStick = Factory::CreateObject<DecoObject>(Vec3(9.f, 5.8f, -14.7f - (i * 2)), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\DiningColliderCheckMap\\BannisterStick.fbx");

				pBannisterStick->GetTransform()->SetScale(Vec3(2.f, 1.3f, 2.f));
				pBannisterStick->GetTransform()->SetRotation(Vec3(0.f, 0.0f, 0.f));
				AddGameObject(pBannisterStick);

			}
		}


		


#pragma endregion






		
		

		









		//Player
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Kinematic;
			physicsInfo.eGeometryType = GeometryType::Capsule;

			physicsInfo.size = Vec3(0.8f, 0.5f, 0.8f);

			Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 8.f, 0.f), physicsInfo, L"Deferred", LARGE_RESOURCE(L"Player\\Crow_Fix.fbx"));
			//Player* pPlayer = Factory::CreateObjectHasPhysical<Player>(Vec3(0.f, 8.f, 0.f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Player\\Crow_Fix.fbx");
			PlayerMoveScript* pPlayerSc = pPlayer->AddComponent(new PlayerMoveScript);
			pPlayer->AddComponent(new PaperBurnScript);
			pPlayer->GetTransform()->SetScale(Vec3(20.f, 20.f, 20.f));
			pPlayer->GetTransform()->SetRotation(Vec3(0.f, 0.f, 90.f));
			pPlayer->GetTransform()->SetRotationExcludingColliders(Vec3(0.f, 90.f, -90.f));
			pPlayer->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -0.6f, 0.f));

			pPlayer->GetRigidBody()->ApplyGravity();
			pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_X, true);
			pPlayer->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_Z, true);


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
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Unknown);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Ground);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Monster);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::DecoObject);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::WallObject);
		GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Player);
	}
}
