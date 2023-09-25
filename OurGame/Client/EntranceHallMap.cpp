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

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "UIText.h"

/* Script */
#include "PaperBurnScript.h"
#include "CameraMoveScript.h"
#include "PlayerMoveScript.h"
#include "PlayerSlashScript.h"
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
}

void EntranceHallMap::Update()
{
	Map::Update();
	if (mTarget != nullptr)
		{
			if (IS_UP(KeyType::LEFT))
			{
				Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x -= 0.1f, target_pos.y, target_pos.z);
				mTarget->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::RIGHT))
			{
				Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x += 0.1f, target_pos.y, target_pos.z);
				mTarget->GetTransform()->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::UP))
			{
				Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y, target_pos.z += 0.1f);
				mTarget->GetTransform()->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::DOWN))
			{
				Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y, target_pos.z -= 0.1f);
				mTarget->GetTransform()->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::Z))
			{
				Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y += 0.1f, target_pos.z);
				mTarget->GetTransform()->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::X))
			{
				Vec3 target_pos = Vec3(mTarget->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y -= 0.1f, target_pos.z);
				mTarget->GetTransform()->SetPosition(fixed_pos);

			}
			if (IS_UP(KeyType::R)) //회전
			{
				Vec3 target_rot = Vec3(mTarget->GetTransform()->GetRotation());
				Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y += 10.0f, target_rot.z);
				mTarget->GetTransform()->GetTransform()->SetRotation(fixed_rot);
			}
			if (IS_UP(KeyType::T)) //회전
			{
				Vec3 target_rot = Vec3(mTarget->GetTransform()->GetRotation());
				Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y -= 10.0f, target_rot.z);
				mTarget->GetTransform()->GetTransform()->SetRotation(fixed_rot);
			}

			if (IS_UP(KeyType::Y)) //회전
			{
				Vec3 target_rot = Vec3(mTarget->GetTransform()->GetRotation());
				Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y += 1.0f, target_rot.z);
				mTarget->GetTransform()->GetTransform()->SetRotation(fixed_rot);
			}
			if (IS_UP(KeyType::U)) //회전
			{
				Vec3 target_rot = Vec3(mTarget->GetTransform()->GetRotation());
				Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y -= 1.0f, target_rot.z);
				mTarget->GetTransform()->GetTransform()->SetRotation(fixed_rot);
			}

			if (IS_UP(KeyType::O)) //스케일 - 전체적 키우기
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x += 0.5f, target_scale.y += 0.5f, target_scale.z += 0.5f);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}
			if (IS_UP(KeyType::P)) //스케일 - 전체적 줄이기
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x -= 0.5f, target_scale.y -= 0.5f, target_scale.z -= 0.5f);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}

			if (IS_UP(KeyType::K)) //스케일 - y축제외 키우기
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x += 0.5f, target_scale.y, target_scale.z += 0.5f);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}
			if (IS_UP(KeyType::L)) //스케일 - y축 제외 줄이기
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x -= 0.5f, target_scale.y, target_scale.z -= 0.5f);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}
			if (IS_UP(KeyType::N)) //스케일 -y축만 키우기
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x, target_scale.y += 0.5, target_scale.z);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}
			if (IS_UP(KeyType::M)) //스케일 -y축만 줄이기
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x, target_scale.y -= 0.5, target_scale.z);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}

			if (IS_UP(KeyType::H)) //스케일 - x축만 키우기
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x +=0.5, target_scale.y, target_scale.z);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}
			if (IS_UP(KeyType::J)) //스케일 -x축만 줄이기
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x -=0.5, target_scale.y, target_scale.z);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}

			if (IS_UP(KeyType::F)) //스케일 -z축만 키우기
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x, target_scale.y, target_scale.z += 0.5);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}
			if (IS_UP(KeyType::G)) //스케일 -z축만 줄이기
			{
				Vec3 target_scale = Vec3(mTarget->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x, target_scale.y, target_scale.z -= 0.5);
				mTarget->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}

			if (IS_UP(KeyType::ENTER))
			{
				Vec3 a = mTarget->GetTransform()->GetPosition();
				Vec3 b = mTarget->GetTransform()->GetRotation();
				Vec3 c = mTarget->GetTransform()->GetScale();
				int d = 0;


			}
		}
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

	//배경맵 하얀색으로 만들어주는 코드
	//gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));

	InitObjectAdd();
	InitColliderAdd();
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
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Unknown);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Ground);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Monster);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::DecoObject);
	GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::WallObject);
	//GET_SINGLE(EventManager)->PushDeleteGameObjectsEvent(meSceneType, LayerType::Player);
}

void EntranceHallMap::InitObjectAdd()
{
#pragma region "어드민"
#pragma endregion

	//DecoObject == 콜라이더 없는 오브젝트
	//WallObject == 콜라이더 있는 오브젝트

	//Forward == 빛 계산이 없는 명령어
	//Deferred == 빛 계산이 있는 명령어

	//->GetTransform()->SetPositionExcludingColliders == 콜라이더를 제외하고 오브젝트만 [이동] 시키는 함수
	//->GetTransform()->SetRotationExcludingColliders == 콜라이더를 제외하고 오브젝트만 [회전] 시키는 함수

	//Deferred_CullNone == 머테리얼 카메라 시점 짤림 없애는 버전 _원본 그대로

	//shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"ObjectTexture", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\EntranceHall.fbm\\grandmaWallPaperTexture.png");
	//Object->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture); == 텍스쳐 번호 설정

	//Object->AddComponent(new PlacementScript); == 키보드로 움직이는 오브젝트 이동 스크립트
	//SetGizmoTarget(Object); == 유니티 방식으로 마우스로 움직이는 오브젝트 이동 함수


	//전체적인 가이드 라인 - EntranceHall
	{
		DecoObject* pEntranceHall = Factory::CreateObject<DecoObject>(Vec3(0.0f, 0.0f, 0.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\EntranceHall.fbx");
		pEntranceHall->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));

		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"EntranceHallTexture", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\EntranceHall.fbm\\grandmaWallPaperTexture.png");
		pEntranceHall->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture); // 텍스쳐 강제로 적용시키는법

		pEntranceHall->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.03f, 0.03f));

		AddGameObject(pEntranceHall);
	}

	//바닥 - EntranceHallFloor
	{
		DecoObject* pEntranceHallFloor = Factory::CreateObject<DecoObject>(Vec3(0.1f, -9.7f, 4.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\EntranceHallFloor.fbx");
		pEntranceHallFloor->GetTransform()->SetScale(Vec3(58.5f, 1.f, 58.5f));

		pEntranceHallFloor->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.05f, 0.05f));

		AddGameObject(pEntranceHallFloor);
	}

	//바닥 프레임 - wallPanel_Merged
	{
		DecoObject* pwallPanel_Merged = Factory::CreateObject<DecoObject>(Vec3(-0.4f, -10.6f, 4.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\wallPanel_Merged.fbx");
		pwallPanel_Merged->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pwallPanel_Merged->GetTransform()->SetScale(Vec3(41.4f, 41.4f, 41.4f));

		AddGameObject(pwallPanel_Merged);
	}

#pragma region "기둥"
	{
		//첫번째 기둥 - ColumnFull
		DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(11.7f, 0.85f, 24.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\ColumnFull.fbx");
		pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pColumnFull->GetTransform()->SetScale(Vec3(30.f, 21.f, 30.f));

		AddGameObject(pColumnFull);
	}
	{
		//두번째 기둥 - ColumnFull
		DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(11.7f, 0.85f, -14.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\ColumnFull.fbx");
		pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pColumnFull->GetTransform()->SetScale(Vec3(30.f, 21.f, 30.f));

		AddGameObject(pColumnFull);
	}

	{
		//세번째 기둥 - ColumnFull
		DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-11.3f, 0.85f, -14.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\ColumnFull.fbx");
		pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pColumnFull->GetTransform()->SetScale(Vec3(30.f, 21.f, 30.f));

		AddGameObject(pColumnFull);
	}
#pragma endregion

#pragma region "가로줄"
	//가로줄 - bannisterTop
	{
		DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(12.4f, 9.8f, 5.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\bannisterTop.fbx");
		pbannisterTop->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pbannisterTop->GetTransform()->SetScale(Vec3(40.f, 130.f, 40.f));


		AddGameObject(pbannisterTop);
	}

	//가로줄 - bannisterTop
	{
		DecoObject* pbannisterTop = Factory::CreateObject<DecoObject>(Vec3(0.4f, 9.8f, -14.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\bannisterTop.fbx");
		pbannisterTop->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pbannisterTop->GetTransform()->SetScale(Vec3(25.f, 130.f, 40.f));


		AddGameObject(pbannisterTop);
	}
#pragma endregion

#pragma region "벽패널"
	//벽패널 1 - WallPanel	
	{
		DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(11.8f, -6.6f, 17.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\WallPanel.fbx");
		pWallPanel->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pWallPanel->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));

		AddGameObject(pWallPanel);
	}

	//벽패널 2 - WallPanel	
	{
		DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(11.8f, -6.6f, 7.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\WallPanel.fbx");
		pWallPanel->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pWallPanel->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));

		AddGameObject(pWallPanel);
	}

	//벽패널 3 - WallPanel	
	{
		DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(11.8f, -6.6f, -2.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\WallPanel.fbx");
		pWallPanel->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pWallPanel->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));

		AddGameObject(pWallPanel);
	}

	//벽패널 4 - WallPanel	
	{
		DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(11.8f, -6.6f, -12.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\WallPanel.fbx");
		pWallPanel->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pWallPanel->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));

		AddGameObject(pWallPanel);
	}

	//벽패널 세로칸 - WallPanel_shot
	{
		DecoObject* pWallPanel_shot = Factory::CreateObject<DecoObject>(Vec3(9.3f, -8.5f, -15.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\WallPanel_shot.fbx");
		pWallPanel_shot->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pWallPanel_shot->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));

		AddGameObject(pWallPanel_shot);
	}

	//벽패널 세로칸 2  - WallPanel_shot
	{
		DecoObject* pWallPanel_shot = Factory::CreateObject<DecoObject>(Vec3(-7.3f, -8.5f, -15.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\WallPanel_shot.fbx");
		pWallPanel_shot->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pWallPanel_shot->GetTransform()->SetScale(Vec3(6.f, 10.f, 10.f));

		AddGameObject(pWallPanel_shot);
	}

	//벽패널 문 테두리 - DoorFrameBig
	{
		DecoObject* pDoorFrameBig = Factory::CreateObject<DecoObject>(Vec3(0.f, -3.9f, -14.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\DoorFrameBig.fbx");
		pDoorFrameBig->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pDoorFrameBig->GetTransform()->SetScale(Vec3(14.f, 14.f, 14.f));

		AddGameObject(pDoorFrameBig);
	}
#pragma endregion

	//커튼 - CurtainHorizontal
	{
		DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(0.f, 6.4f, -13.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\CurtainHorizontal.fbx");
		pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pCurtainHorizontal->GetTransform()->SetScale(Vec3(22.f, 22.f, 22.f));


		AddGameObject(pCurtainHorizontal);
	}

	//보라색 문 - jarDoor
	{
		pJarRDoor = Factory::CreateObject<DecoObject>(Vec3(0.f, -3.6f, -15.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\jarDoor.fbx");
		pJarRDoor->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pJarRDoor->GetTransform()->SetScale(Vec3(14.f, 14.f, 14.f));
		AddGameObject(pJarRDoor);
		pJarRDoor->GetMeshRenderer()->SetSubsetRenderFlag(1, false);
		pJarRDoor->GetMeshRenderer()->SetSubsetRenderFlag(2, false);
		pJarRDoor->GetMeshRenderer()->SetSubsetRenderFlag(3, false);
		pJarRDoor->GetMeshRenderer()->SetSubsetRenderFlag(0, false);
	}

	{
		pJarLDoor = Factory::CreateObject<DecoObject>(Vec3(0.f, -3.6f, -15.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\jarDoor.fbx");
		pJarLDoor->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pJarLDoor->GetTransform()->SetScale(Vec3(14.f, 14.f, 14.f));
		AddGameObject(pJarLDoor);
		pJarLDoor->GetMeshRenderer()->SetSubsetRenderFlag(4, false);
		pJarLDoor->GetMeshRenderer()->SetSubsetRenderFlag(5, false);
		pJarLDoor->GetMeshRenderer()->SetSubsetRenderFlag(6, false);
		pJarLDoor->GetMeshRenderer()->SetSubsetRenderFlag(7, false);
	}


	//탁자 - MiddleShelf
	{
		DecoObject* pMiddleShelf = Factory::CreateObject<DecoObject>(Vec3(8.6f, -7.2f, 5.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\MiddleShelf.fbx");
		pMiddleShelf->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pMiddleShelf->GetTransform()->SetScale(Vec3(13.f, 13.f, 13.f));

		AddGameObject(pMiddleShelf);
	}

	//탁자위 꽃 화분 - MansionPlantPot
	{
		DecoObject* pMansionPlantPot = Factory::CreateObject<DecoObject>(Vec3(8.6f, -2.4f, 9.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\MansionPlantPot.fbx");
		pMansionPlantPot->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pMansionPlantPot->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));

		AddGameObject(pMansionPlantPot);
	}

	//탁자위 작은 화분들 1 - MansionSpicePot_small
	{
		DecoObject* pMansionSpicePot_small = Factory::CreateObject<DecoObject>(Vec3(7.9f, -3.9f, 3.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\MansionSpicePot_small.fbx");
		pMansionSpicePot_small->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pMansionSpicePot_small->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));

		AddGameObject(pMansionSpicePot_small);
	}

	//탁자위 작은 화분들 2 - MansionSpicePot_small
	{
		DecoObject* pMansionSpicePot_small = Factory::CreateObject<DecoObject>(Vec3(9.0f, -3.9f, 1.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\MansionSpicePot_small.fbx");
		pMansionSpicePot_small->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pMansionSpicePot_small->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));

		AddGameObject(pMansionSpicePot_small);
	}

	//의자 - Chair
	{
		DecoObject* pChair = Factory::CreateObject<DecoObject>(Vec3(6.3f, -5.1f, 21.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\Chair.fbx");
		pChair->GetTransform()->SetRotation(Vec3(0.f, 75.f, 0.f));
		pChair->GetTransform()->SetScale(Vec3(9.f, 9.f, 9.f));

		AddGameObject(pChair);
	}

	//그림액자 1 - paintingFrame
	{
		DecoObject* pPaintingFrame = Factory::CreateObject<DecoObject>(Vec3(12.f, 3.2f, 15.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\paintingFrame.fbx");
		pPaintingFrame->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pPaintingFrame->GetTransform()->SetScale(Vec3(12.f, 12.f, 12.f));

		AddGameObject(pPaintingFrame);
	}

	//그림액자 2 - paintingFrame2
	{
		DecoObject* pPaintingFrame2 = Factory::CreateObject<DecoObject>(Vec3(12.f, 3.1f, 4.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\paintingFrame2.fbx");
		pPaintingFrame2->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pPaintingFrame2->GetTransform()->SetScale(Vec3(6.f, 6.f, 6.f));

		AddGameObject(pPaintingFrame2);
	}

	//그림액자 3 - paintingFrame4
	{
		DecoObject* pPaintingFrame4 = Factory::CreateObject<DecoObject>(Vec3(11.9f, 3.1f, -7.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\paintingFrame4.fbx");
		pPaintingFrame4->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pPaintingFrame4->GetTransform()->SetScale(Vec3(12.f, 12.f, 12.f));

		AddGameObject(pPaintingFrame4);
	}

	

	////////////yj
	{

		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(10.35f, 13.0f,1.0f);

		DecoObject* pDoorCollider = Factory::CreateObjectHasPhysical<DecoObject>(Vec3(-0.1f,-3.2f,-15.0f), physicsInfo, L"Deferred", L"");
		AddGameObject(pDoorCollider);

		yj::JarDoor* pJarDoor = Factory::CreateObject<yj::JarDoor>(Vec3::Zero, L"Deferred", L"", false, 2, pJarLDoor, pJarRDoor, pDoorCollider);
		AddGameObject(pJarDoor);

		//키+파란색 항아리 - POT_Key
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(3.192, 3.8f, 2.28f);

			pPot1 = Factory::CreateObjectHasPhysical<yj::KeyPot>(Vec3(7.1f, -7.7f, -12.1f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\POT_Key.fbx");
			pPot1->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			pPot1->GetTransform()->SetScale(Vec3(4.f, 4.f, 4.f));
			pPot1->SetReceiver(pJarDoor);
			AddGameObject(pPot1);
		}

		//키+파란색 항아리 두번째 - POT_Key
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(3.192, 3.8f, 2.28f);

			yj::KeyPot* pPot2 = Factory::CreateObjectHasPhysical<yj::KeyPot>(Vec3(-7.1f, -7.7f, -12.1f), physicsInfo, L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_EntranceHallMap\\POT_Key.fbx");
			pPot2->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			pPot2->GetTransform()->SetScale(Vec3(4.f, 4.f, 4.f));
			pPot2->SetReceiver(pJarDoor);
			AddGameObject(pPot2);
		}

		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(9.2, 3.8f, 8.75f);

			yj::TeleportZone* pTelZone = Factory::CreateObjectHasPhysical<yj::TeleportZone>(Vec3(0.1f, -7.7f, -21.6f), physicsInfo, L"Deferred", L"",false,MapType::Right2Map);
			AddGameObject(pTelZone);
			SetGizmoTarget(pTelZone);
		}

	}
}

void EntranceHallMap::InitColliderAdd()
{
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(49.0f, 0.98f, 78.4f);

		Ground* pGroundCol = Factory::CreateObjectHasPhysical<Ground>(Vec3(-6.1f, -10.1f, -0.5f), physicsInfo, L"Deferred", L"");
		AddGameObject(pGroundCol);
	}

	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(0.98f, 49.74f, 78.4f);

		WallObject* pLWallCol = Factory::CreateObjectHasPhysical<WallObject>(Vec3(11.7f, -10.1f, -0.5f), physicsInfo, L"Deferred", L"");
		AddGameObject(pLWallCol);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(0.98f, 49.74f, 78.4f);

		WallObject* pRWallCol = Factory::CreateObjectHasPhysical<WallObject>(Vec3(11.7f, -10.1f, -0.5f), physicsInfo, L"Deferred", L"");
		AddGameObject(pRWallCol);
	}
}