#include "pch.h"
#include "LeftSecretFightMap.h"
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
#include "TeleportZone.h"
#include "Ground.h"
#include "WallObject.h"
#include "DecoObject.h"
#include "Monster.h"
#include "SpawnDoor.h"
#include "LORD_BOSS.h"
#include "LORD_BOSS_ROLL.h"
#include "Bat.h"
#include "Mage.h"
#include "Lurker.h"
#include "HeadRoller.h"
#include "Grimace.h"
/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "UIText.h"
#include "Animator.h"
#include "Mirror.h"

/* Script */
#include "PaperBurnScript.h"
#include "CameraMoveScript.h"
#include "PlayerMoveScript.h"
#include "PlayerSlashScript.h"
#include "PlacementScript.h"
#include "TestAnimationScript.h"
#include "PlayerMoveOverMapScript.h"
#include "HeadText.h"

/* Event */
#include "SceneChangeEvent.h"


LeftSecretFightMap::LeftSecretFightMap()
	: Map(MapType::LeftSecretFightMap)
{
}

LeftSecretFightMap::~LeftSecretFightMap()
{
}

void LeftSecretFightMap::Initialize()
{
	Map::Initialize();
}

void LeftSecretFightMap::Start()
{
	Map::Start();

	mpMainCamera->GetTransform()->SetPosition(Vec3(-27.2f, 29.3f, 27.2f));
	mpMainCamera->GetTransform()->SetRotation(Vec3(56.f, -225.3f, 0.f));

	PLAYER->GetKeyInfo().SetLeftKey(KeyType::RIGHT);
	PLAYER->GetKeyInfo().SetForwardKey(KeyType::DOWN);

	if (PLAYER != nullptr)
	{
		mSpawnPoint = PLAYER->GetScript<yj::PlayerMoveOverMapScript>()->GetMoveOverNum();
		switch (mSpawnPoint)
		{
		case 2:
			PLAYER->GetTransform()->SetPosition(Vec3(-10.8f, -7.5f, 23.6f));
			break;
		}
	}
}

void LeftSecretFightMap::Update()
{
	Map::Update();

	if (IS_DOWN(KeyType::L))
	{
		// 초록거미
		{
			SpawnDoor<Lurker>* pLurker = Factory::SpawnMonster<Lurker>(Vec3(4.5f, -5.5f, 1.5f), Vec3(-90.f, -90.f, 180.f));
			pLurker->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			AddGameObject(pLurker);
		}

		// 마법사
		{
			SpawnDoor<Mage>* pMage = Factory::SpawnMonster<Mage>(Vec3(-15.5f, -5.5f, 17.f), Vec3(-90.f, 90.f, 180.f));
			pMage->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
			AddGameObject(pMage);
		}
		 
		//콩벌레
		{
			SpawnDoor<HeadRoller>* pRoller = Factory::SpawnMonster<HeadRoller>(Vec3(4.5f, -5.5f, 17.f), Vec3(180.f, -90.f, 180.f));
			pRoller->GetTransform()->SetRotation(Vec3(0.f, -90.f, 0.f));
			AddGameObject(pRoller);
		}


		// 박쥐
		{
			SpawnDoor<Bat>* pBat = Factory::SpawnMonster<Bat>(Vec3(-15.5f, -5.5f, 1.5f), Vec3(-90.f, 90.f, 180.f));
			pBat->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
			AddGameObject(pBat);
		}
	}
}

void LeftSecretFightMap::FixedUpdate()
{
	Map::FixedUpdate();
}

void LeftSecretFightMap::FinalUpdate()
{
	Map::FinalUpdate();
}

void LeftSecretFightMap::Render()
{
	Map::Render();
}

void LeftSecretFightMap::Enter()
{
	//배경맵 하얀색으로 만들어주는 코드
	//gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));

	spPlayerHolder->GetAudioSound()->SetSound(L"GrimaceBGM", this, true, "..\\Resources\\Sound\\GrimaceBGM.mp3");
	spPlayerHolder->GetAudioSound()->Play();

	InitObjectAdd();
	InitColliderAdd();
	FuncObjectAdd();
#pragma region "어드민"
#pragma endregion

	// 그리마스
	{
		SpawnDoor<Grimace>* pGrimace = Factory::SpawnMonster<Grimace>(Vec3(-9.5f, -4.f, -2.8f),Vec3(180.f,180.f,0.f));
		pGrimace->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		AddGameObject(pGrimace);
	}

	// 샹들리에 라이트
	{
		GameObject* pGameObject = new GameObject(LayerType::Unknown);
		Transform* pTransform = pGameObject->AddComponent(new Transform);
		pTransform->SetPosition(Vec3(0.f, 30.f, 0.f));
		pTransform->SetRotation(Vec3(90.f, 0.f, 0.f));
		pTransform->SetScale(Vec3(100.f, 100.f, 100.f));
		Light* pLight = pGameObject->AddComponent(new Light);
		pLight->SetDiffuse(Vec3(0.7f, 0.7f, 0.7f));
		pLight->SetAmbient(Vec3(0.0f, 0.0f, 0.0f));
		pLight->SetLightRange(55.f);
		pLight->SetLightType(LightType::PointLight);
		AddGameObject(pGameObject);
	}


	//펭귄 뼈다귀 - skelecrow
	{
		DecoObject* pskelecrow = Factory::CreateObject<DecoObject>(Vec3(10.3f, -1.5f, -17.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\skelecrow.fbx");
		pskelecrow->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pskelecrow->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.5f));

		AddGameObject(pskelecrow);
	}
}

void LeftSecretFightMap::Exit()
{
	spPlayerHolder->GetAudioSound()->Stop();
}

void LeftSecretFightMap::InitObjectAdd()
{
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


	//전체적인 가이드 라인 - Room_Walls
	{
		DecoObject* pRoom_Walls = Factory::CreateObject<DecoObject>(Vec3(0.0f, 0.0f, 0.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\Room_Walls.fbx");
		pRoom_Walls->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));

		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"EntranceHallTexture", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\Room_Walls.fbm\\grandmaWallPaperTexture.png");
		pRoom_Walls->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture); // 텍스쳐 강제로 적용시키는법

		pRoom_Walls->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.03f, 0.03f));

		AddGameObject(pRoom_Walls);
	}

	// 1층 바닥 - Grimace_Decay_Floor
	{
		DecoObject* pGrimace_Decay_Floor = Factory::CreateObject<DecoObject>(Vec3(-4.8f, -9.f, 9.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\Grimace_Decay_Floor.fbx");
		pGrimace_Decay_Floor->GetTransform()->SetScale(Vec3(39.f, 40.f, 38.f));

		//shared_ptr<Texture> pTexture2 = GET_SINGLE(Resources)->Load<Texture>(L"Grimace_Decay_FloorTexture", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\Grimace_Decay_Floor.fbm\\floormark_tiling_broken.png");
		//pGrimace_Decay_Floor->GetMeshRenderer()->GetMaterial()->SetTexture(0, pTexture2 ,1); // 텍스쳐 강제로 적용시키는법

		pGrimace_Decay_Floor->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.01f, 0.01f), 1);

		AddGameObject(pGrimace_Decay_Floor);
	}

	// 미러
	{
		GameObject* pMirror = Factory::CreateObject<GameObject>(Vec3(-4.8f, -8.3f, 9.8f), L"Forward", L"", false, LayerType::Mirror);

		pMirror->GetTransform()->SetScale(Vec3(25.f, 25.f, 25.f));
		pMirror->AddComponent(new Mirror);
		pMirror->GetMeshRenderer()->SetMesh(GET_SINGLE(Resources)->LoadRectMesh());
		pMirror->GetTransform()->SetRotation(Vec3(90.f, 0.f, 0.f));

		AddGameObject(pMirror);

	}

	// 2층 바닥 - Floor
	{
		DecoObject* pFloor = Factory::CreateObject<DecoObject>(Vec3(10.44f, -2.3f, 0.0f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\Floor.fbx");
		pFloor->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));

		pFloor->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.03f, 0.03f));

		AddGameObject(pFloor);
	}

	//2층 안보이는 벽 - Wall
	{
		DecoObject* pWall = Factory::CreateObject<DecoObject>(Vec3(5.54f, 1.14f, -17.41f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\Wall.fbx");
		pWall->GetTransform()->SetScale(Vec3(17.f, 17.f, 17.f));

		pWall->GetMeshRenderer()->GetMaterial()->SetUVTiling(Vec2(0.03f, 0.03f));

		AddGameObject(pWall);
	}

#pragma region "가로줄"
	//가로줄 1 - WallRim
	{
		DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(-20.3f, -8.45f, 7.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\WallRim.fbx");
		pWallRim->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pWallRim->GetTransform()->SetScale(Vec3(33.5f, 30.f, 30.f));



		AddGameObject(pWallRim);
	}

	//가로줄 2 - WallRim
	{
		DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(-17.06f, -8.45f, 24.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\WallRim.fbx");
		pWallRim->GetTransform()->SetRotation(Vec3(180.f, 0.f, 0.f));
		pWallRim->GetTransform()->SetScale(Vec3(7.f, 30.f, 30.f));

		AddGameObject(pWallRim);
	}

	//가로줄 3 - WallRim
	{
		DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(1.2f, -8.45f, 24.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\WallRim.fbx");
		pWallRim->GetTransform()->SetRotation(Vec3(180.f, 0.f, 0.f));
		pWallRim->GetTransform()->SetScale(Vec3(18.5f, 30.f, 30.f));



		AddGameObject(pWallRim);
	}

	//가로줄 4 - WallRim
	{
		DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(15.4f, -2.3f, 24.81f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\WallRim.fbx");
		pWallRim->GetTransform()->SetRotation(Vec3(180.f, 0.f, 0.f));
		pWallRim->GetTransform()->SetScale(Vec3(10.f, 30.f, 30.f));

		AddGameObject(pWallRim);
	}

	//가로줄 5 - WallRim
	{
		DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(20.5f, 8.6f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\WallRim.fbx");
		pWallRim->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pWallRim->GetTransform()->SetScale(Vec3(49.f, 30.f, 30.f));

		AddGameObject(pWallRim);
	}

	//가로줄 6 - WallRim
	{
		DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(10.5f, 8.6f, -25.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\WallRim.fbx");
		pWallRim->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pWallRim->GetTransform()->SetScale(Vec3(20.f, 30.f, 30.f));

		AddGameObject(pWallRim);
	}

	//가로줄 7 - WallRim
	{
		DecoObject* pWallRim = Factory::CreateObject<DecoObject>(Vec3(-10.f, 4.7f, -8.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\WallRim.fbx");
		pWallRim->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pWallRim->GetTransform()->SetScale(Vec3(20.f, 30.f, 30.f));

		AddGameObject(pWallRim);
	}
#pragma endregion




#pragma region "난간"
	//난간 1 - CeilingBeamLow
	{
		DecoObject* pCeilingBeamLow = Factory::CreateObject<DecoObject>(Vec3(10.4f, -1.62f, 17.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\CeilingBeamLow.fbx");
		pCeilingBeamLow->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pCeilingBeamLow->GetTransform()->SetScale(Vec3(14.f, 8.f, 8.f));

		AddGameObject(pCeilingBeamLow);
	}
	//난간 2 - CeilingBeamLow
	{
		DecoObject* pCeilingBeamLow = Factory::CreateObject<DecoObject>(Vec3(10.4f, -1.62f, -2.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\CeilingBeamLow.fbx");
		pCeilingBeamLow->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pCeilingBeamLow->GetTransform()->SetScale(Vec3(12.5f, 8.f, 8.f));


		AddGameObject(pCeilingBeamLow);
	}

	//난간 3 - CeilingBeamLow
	{
		DecoObject* pCeilingBeamLow = Factory::CreateObject<DecoObject>(Vec3(5.3f, -1.62f, -8.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\CeilingBeamLow.fbx");
		pCeilingBeamLow->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pCeilingBeamLow->GetTransform()->SetScale(Vec3(9.f, 8.f, 8.f));

		AddGameObject(pCeilingBeamLow);
	}

	//난간 4 - CeilingBeamLow
	{
		DecoObject* pCeilingBeamLow = Factory::CreateObject<DecoObject>(Vec3(0.4f, 5.38f, -17.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\CeilingBeamLow.fbx");
		pCeilingBeamLow->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pCeilingBeamLow->GetTransform()->SetScale(Vec3(15.5f, 8.f, 8.f));

		AddGameObject(pCeilingBeamLow);
	}
#pragma endregion


	//난간 사이 기둥1 - BannisterStickX5
	{
		DecoObject* pBannisterStickX5 = Factory::CreateObject<DecoObject>(Vec3(5.4f, -1.6f, -8.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\BannisterStickX5.fbx");
		pBannisterStickX5->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pBannisterStickX5->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));


		AddGameObject(pBannisterStickX5);
	}

	//난간 사이 기둥2 - BannisterStickX5
	{
		DecoObject* pBannisterStickX5 = Factory::CreateObject<DecoObject>(Vec3(10.4f, -1.6f, -2.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\BannisterStickX5.fbx");
		pBannisterStickX5->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pBannisterStickX5->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));


		AddGameObject(pBannisterStickX5);
	}

	//난간 사이 기둥3 - BannisterStickX5
	{
		DecoObject* pBannisterStickX5 = Factory::CreateObject<DecoObject>(Vec3(10.4f, -1.6f, 17.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\BannisterStickX5.fbx");
		pBannisterStickX5->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pBannisterStickX5->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));


		AddGameObject(pBannisterStickX5);
	}






#pragma region "기둥들 모음"
	//기둥1
	{
		DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(-19.93f, -1.69f, -8.95f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\ColumnFull.fbx");
		pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pColumnFull->GetTransform()->SetScale(Vec3(10.f, 14.f, 10.f));

		AddGameObject(pColumnFull);
	}

	//기둥2
	{
		DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(0.47f, -0.99f, -8.95f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\ColumnFull.fbx");
		pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pColumnFull->GetTransform()->SetScale(Vec3(10.f, 15.f, 10.f));


		AddGameObject(pColumnFull);
	}

	//기둥3
	{
		DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(20.47f, 3.61f, -24.95f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\ColumnFull.fbx");
		pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pColumnFull->GetTransform()->SetScale(Vec3(10.f, 12.f, 10.f));


		AddGameObject(pColumnFull);
	}

	//기둥4
	{
		DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(0.47f, 3.61f, -25.05f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\ColumnFull.fbx");
		pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pColumnFull->GetTransform()->SetScale(Vec3(10.f, 12.f, 10.f));


		AddGameObject(pColumnFull);
	}

	//기둥4
	{
		DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(20.47f, 3.61f, 24.85f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\ColumnFull.fbx");
		pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pColumnFull->GetTransform()->SetScale(Vec3(10.f, 12.f, 10.f));


		AddGameObject(pColumnFull);
	}

	//기둥5
	{
		DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(10.47f, -3.69f, 24.85f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\ColumnFull.fbx");
		pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pColumnFull->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));


		AddGameObject(pColumnFull);
	}

	//기둥6
	{
		DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(10.47f, -3.69f, 10.55f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\ColumnFull.fbx");
		pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pColumnFull->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));


		AddGameObject(pColumnFull);
	}

	//기둥7
	{
		DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(10.47f, -3.69f, 4.55f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\ColumnFull.fbx");
		pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pColumnFull->GetTransform()->SetScale(Vec3(10.f, 10.f, 10.f));


		AddGameObject(pColumnFull);
	}

	//기둥8
	{
		DecoObject* pColumnFull = Factory::CreateObject<DecoObject>(Vec3(10.47f, -1.09f, -8.95f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\ColumnFull.fbx");
		pColumnFull->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pColumnFull->GetTransform()->SetScale(Vec3(10.f, 3.f, 10.f));


		AddGameObject(pColumnFull);
	}
#pragma endregion

#pragma region "벽패널"
	//벽패널1 - WallPanel
	{
		DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(20.3f, -0.1f, 18.3f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\WallPanel.fbx");
		pWallPanel->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pWallPanel->GetTransform()->SetScale(Vec3(12.f, 12.f, 12.f));

		AddGameObject(pWallPanel);
	}

	//벽패널2 - WallPanel
	{
		DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(20.3f, -0.1f, 6.4f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\WallPanel.fbx");
		pWallPanel->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pWallPanel->GetTransform()->SetScale(Vec3(12.f, 12.f, 12.f));


		AddGameObject(pWallPanel);
	}

	//벽패널3 - WallPanel
	{
		DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(20.3f, -0.1f, -5.5f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\WallPanel.fbx");
		pWallPanel->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pWallPanel->GetTransform()->SetScale(Vec3(12.f, 12.f, 12.f));


		AddGameObject(pWallPanel);
	}

	//벽패널4 - WallPanel
	{
		DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(20.3f, -0.1f, -17.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\WallPanel.fbx");
		pWallPanel->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pWallPanel->GetTransform()->SetScale(Vec3(13.f, 12.f, 12.f));


		AddGameObject(pWallPanel);
	}

	//벽패널5 - WallPanel
	{
		DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(18.8f, -0.1f, -24.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\WallPanel.fbx");
		pWallPanel->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pWallPanel->GetTransform()->SetScale(Vec3(12.f, 12.f, 12.f));


		AddGameObject(pWallPanel);
	}

	//벽패널6 - WallPanel
	{
		DecoObject* pWallPanel = Factory::CreateObject<DecoObject>(Vec3(6.9f, -0.1f, -24.7f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\WallPanel.fbx");
		pWallPanel->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pWallPanel->GetTransform()->SetScale(Vec3(12.f, 12.f, 12.f));


		AddGameObject(pWallPanel);
	}
#pragma endregion

#pragma region "커튼 가로줄 모음"
	//커튼 가로줄1 - CurtainHorizontal
	{
		DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(10.6f, 6.3f, -24.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\CurtainHorizontal.fbx");
		pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pCurtainHorizontal->GetTransform()->SetScale(Vec3(19.f, 15.f, 15.f));


		AddGameObject(pCurtainHorizontal);
	}

	//커튼 가로줄2 - CurtainHorizontal
	{
		DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(19.5f, 6.3f, -14.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\CurtainHorizontal.fbx");
		pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pCurtainHorizontal->GetTransform()->SetScale(Vec3(19.f, 15.f, 15.f));


		AddGameObject(pCurtainHorizontal);
	}

	//커튼 가로줄3 - CurtainHorizontal
	{
		DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(19.5f, 6.3f, 4.f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\CurtainHorizontal.fbx");
		pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pCurtainHorizontal->GetTransform()->SetScale(Vec3(19.f, 15.f, 15.f));

		AddGameObject(pCurtainHorizontal);
	}

	//커튼 가로줄4 - CurtainHorizontal
	{
		DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(19.5f, 6.3f, 19.3f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\CurtainHorizontal.fbx");
		pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pCurtainHorizontal->GetTransform()->SetScale(Vec3(12.f, 15.f, 15.f));


		AddGameObject(pCurtainHorizontal);
	}

	//커튼 가로줄5 - CurtainHorizontal
	{
		DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>(Vec3(-9.9f, 2.3f, -7.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\CurtainHorizontal.fbx");
		pCurtainHorizontal->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pCurtainHorizontal->GetTransform()->SetScale(Vec3(19.f, 15.f, 15.f));

		AddGameObject(pCurtainHorizontal);
	}
#pragma endregion


#pragma region "커튼 세로줄 모음"
	//커튼 세로줄 1 - CurtainVertical1
	{
		DecoObject* pCurtainVertical1 = Factory::CreateObject<DecoObject>(Vec3(11.f, 1.8f, -23.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\CurtainVertical1.fbx");
		pCurtainVertical1->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pCurtainVertical1->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));


		AddGameObject(pCurtainVertical1);
	}

	//커튼 세로줄 2 - CurtainVertical1
	{
		DecoObject* pCurtainVertical1 = Factory::CreateObject<DecoObject>(Vec3(-5.f, -2.7f, -8.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\CurtainVertical1.fbx");
		pCurtainVertical1->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pCurtainVertical1->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));


		AddGameObject(pCurtainVertical1);
	}

	//커튼 세로줄 3 - CurtainVertical1
	{
		DecoObject* pCurtainVertical1 = Factory::CreateObject<DecoObject>(Vec3(-15.f, -2.7f, -8.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\CurtainVertical1.fbx");
		pCurtainVertical1->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pCurtainVertical1->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));


		AddGameObject(pCurtainVertical1);
	}

	//커튼 세로줄 4 - CurtainVertical1
	{
		DecoObject* pCurtainVertical1 = Factory::CreateObject<DecoObject>(Vec3(19.9f, 1.8f, -14.9f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\CurtainVertical1.fbx");
		pCurtainVertical1->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pCurtainVertical1->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));


		AddGameObject(pCurtainVertical1);
	}

	//커튼 세로줄 5 - CurtainVertical1
	{
		DecoObject* pCurtainVertical1 = Factory::CreateObject<DecoObject>(Vec3(19.9f, 1.8f, 4.1f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\CurtainVertical1.fbx");
		pCurtainVertical1->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pCurtainVertical1->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));


		AddGameObject(pCurtainVertical1);
	}

	//커튼 세로줄 6 - CurtainVertical1
	{
		DecoObject* pCurtainVertical1 = Factory::CreateObject<DecoObject>(Vec3(19.9f, 1.8f, 19.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\CurtainVertical1.fbx");
		pCurtainVertical1->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pCurtainVertical1->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));

		AddGameObject(pCurtainVertical1);
	}
#pragma endregion




	//그림 액자 - paintingFrame3 
	{
		DecoObject* pPaintingFrame3 = Factory::CreateObject<DecoObject>(Vec3(-9.8f, -3.6f, -8.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\paintingFrame3.fbx");
		pPaintingFrame3->GetTransform()->SetRotation(Vec3(0.f, 180.f, 0.f));
		pPaintingFrame3->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));

		AddGameObject(pPaintingFrame3);
	}


	//스파이크 문 - SpikeDoor_avatest
	{
		DecoObject* pSpikeDoor_avatest = Factory::CreateObject<DecoObject>(Vec3(-10.8f, -6.5f, 24.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\SpikeDoor_avatest.fbx");
		pSpikeDoor_avatest->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pSpikeDoor_avatest->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));

		AddGameObject(pSpikeDoor_avatest);
	}

	//사다리 - Ladder
	{
		DecoObject* pLadder = Factory::CreateObject<DecoObject>(Vec3(10.3f, -5.8f, 7.6f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\Ladder.fbx");
		pLadder->GetTransform()->SetRotation(Vec3(0.f, 90.f, 0.f));
		pLadder->GetTransform()->SetScale(Vec3(7.f, 7.f, 7.f));


		AddGameObject(pLadder);
	}
	//항아리 1 - POT_HEAL_Generic_Variant
	{
		DecoObject* pPOT_HEAL_Generic_Variant = Factory::CreateObject<DecoObject>(Vec3(15.4f, -1.1f, 21.8f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\POT_HEAL_Generic_Variant.fbx");
		pPOT_HEAL_Generic_Variant->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pPOT_HEAL_Generic_Variant->GetTransform()->SetScale(Vec3(2.5f, 2.5f, 2.5f));

		AddGameObject(pPOT_HEAL_Generic_Variant);
	}

	//항아리 2 - POT_HEAL_Generic_Variant
	{
		DecoObject* pPOT_HEAL_Generic_Variant = Factory::CreateObject<DecoObject>(Vec3(17.4f, -1.1f, -21.2f), L"Deferred", L"..\\Resources\\FBX\\Map\\Dungeon\\R_LeftSecret_FightMap\\POT_HEAL_Generic_Variant.fbx");
		pPOT_HEAL_Generic_Variant->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
		pPOT_HEAL_Generic_Variant->GetTransform()->SetScale(Vec3(2.5f, 2.5f, 2.5f));

		AddGameObject(pPOT_HEAL_Generic_Variant);
	}
}

void LeftSecretFightMap::InitColliderAdd()
{
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(31.85f, 1.f, 40.84f);

		Ground* pGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(-5.f, -8.6f, 9.3f), physicsInfo, L"Forward",L"");

		AddGameObject(pGround);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(11.7f, 8.68f, 51.5f);

		Ground* pGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(15.8f, -6.2f, 0.6f), physicsInfo, L"Forward", L"");

		AddGameObject(pGround);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(23.16f, 11.8f, 18.54f);

		WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-10.6f, -2.7f, -17.6f), physicsInfo, L"Forward", L"");

		AddGameObject(pWall);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(30.1158f, 11.8f, 1.85f);

		WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(7.1f, -3.2f, 25.9f), physicsInfo, L"Forward", L"");

		AddGameObject(pWall);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(1.44f, 7.08f, 55.14f);

		WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(21.2f, 1.0f, -1.6f), physicsInfo, L"Forward", L"");

		AddGameObject(pWall);

	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(9.71f, 7.08f, 16.54f);

		Ground* pGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(5.1f, -5.4f, -17.0f), physicsInfo, L"Forward", L"");

		AddGameObject(pGround);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(22.54f, 5.61f, 1.0f);

		WallObject* pGround = Factory::CreateObjectHasPhysical<WallObject>(Vec3(11.3f, 1.1f, -24.9f), physicsInfo, L"Forward", L"");

		AddGameObject(pGround);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(6.84f, 10.0f, 1.5f);

		WallObject* pGround = Factory::CreateObjectHasPhysical<WallObject>(Vec3(17.1f, -4.0f, 25.7f), physicsInfo, L"Forward", L"");

		AddGameObject(pGround);
	}
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(0.56f, 6.5f, 33.85f);

		WallObject* pGround = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-20.7f, -5.2f, 8.1f), physicsInfo, L"Forward", L"");

		AddGameObject(pGround);
	}
}

void LeftSecretFightMap::FuncObjectAdd()
{
	{
		PhysicsInfo physicsInfo;
		physicsInfo.eActorType = ActorType::Static;
		physicsInfo.eGeometryType = GeometryType::Box;
		physicsInfo.size = Vec3(5.52, 3.8f, 2.18f);

		yj::TeleportZone* pTelZone = Factory::CreateObjectHasPhysical<yj::TeleportZone>(Vec3(-11.0f, -7.7f, 27.7f), physicsInfo, L"Forward", L"", false, MapType::LeftSecretTrialMap, 2);
		AddGameObject(pTelZone);
	}

	{
		GameObject* pClimbUpTextBox = Factory::CreateObject<GameObject>(Vec3::One, L"Forward", L"", false, LayerType::InterativeCol);
		pClimbUpTextBox->GetMeshRenderer()->GetMaterial()->SetTexture(0, GET_SINGLE(Resources)->Load<Texture>(L"Texture3D", L"..\\Resources\\Texture\\PopUpClimbUppng.png"));
		pClimbUpTextBox->GetMeshRenderer()->SetMesh(GET_SINGLE(Resources)->LoadRectMesh());
		pClimbUpTextBox->GetTransform()->SetPosition(Vec3(9.3f, -5.8f, 7.9f));
		pClimbUpTextBox->GetTransform()->SetRotation(Vec3(0.0f, 90.0f, 0.0f));
		pClimbUpTextBox->GetTransform()->SetScale(Vec3(2.0f, 1.0f, 1.0f));
		AddGameObject(pClimbUpTextBox);
		yj::HeadText* pClimbUpTextScript = pClimbUpTextBox->AddComponent<yj::HeadText>();
		pClimbUpTextScript->SetDectetorPos(Vec3(8.9f, -6.8f, 7.5f));
	}
	{
		/*GameObject* pClimbDownTextBox = Factory::CreateObject<GameObject>(Vec3::One, L"Forward", L"", false, LayerType::InterativeCol);
		pClimbDownTextBox->GetMeshRenderer()->GetMaterial()->SetTexture(0, GET_SINGLE(Resources)->Load<Texture>(L"Texture3D", L"..\\Resources\\Texture\\PopUpClimbDown.png"));
		pClimbDownTextBox->GetMeshRenderer()->SetMesh(GET_SINGLE(Resources)->LoadRectMesh());
		pClimbDownTextBox->GetTransform()->SetPosition(Vec3(10.1f, -0.1f, 7.9f));
		pClimbDownTextBox->GetTransform()->SetRotation(Vec3(0.0f, 90.0f, 0.0f));
		pClimbDownTextBox->GetTransform()->SetScale(Vec3(2.0f, 1.0f, 1.0f));
		AddGameObject(pClimbDownTextBox);
		yj::HeadText* pClimbDownTextScript = pClimbDownTextBox->AddComponent<yj::HeadText>();
		pClimbDownTextScript->SetDectetorPos(Vec3(11.3f, -0.8f, 7.5f));*/
	}
}
