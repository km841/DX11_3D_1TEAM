#include "pch.h"
#include "RightMap.h"
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
#include "TeleportZone.h"
#include "SpikeDoor.h"

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
#include "Animator.h"
#include "Fireplace.h"
#include "Mirror.h"

/* Script */
#include "PaperBurnScript.h"
#include "CameraMoveScript.h"
#include "BonFireScript.h"
#include "OwnerFollowScript.h"
#include "PlayerMoveOverMapScript.h"

/* Event */
#include "SceneChangeEvent.h"

namespace yj
{
	RightMap::RightMap()
		: Map(MapType::RightMap)
	{
	}

	RightMap::~RightMap()
	{
	}

	void RightMap::Initialize()
	{
		Map::Initialize();
	}

	void RightMap::Start()
	{
		Map::Start();

		mpMainCamera->GetTransform()->SetPosition(Vec3(0.7f, 26.35f, 8.6f));
		mpMainCamera->GetTransform()->SetRotation(Vec3(54.2f, 137.f, 0.f));

		OwnerFollowScript* pFollowScript = spPlayerHolder->GetScript<OwnerFollowScript>();
		pFollowScript->SetOffset(Vec3(-10.3f, 25.f, 14.f));

		PLAYER->GetKeyInfo().SetLeftKey(KeyType::RIGHT);
		PLAYER->GetKeyInfo().SetForwardKey(KeyType::DOWN);

		if (PLAYER != nullptr)
		{
			mSpawnPoint = PLAYER->GetScript<yj::PlayerMoveOverMapScript>()->GetMoveOverNum();
			switch (mSpawnPoint)
			{
			case 4:
				PLAYER->GetTransform()->SetPosition(Vec3(14.6f, 4.6f,-7.0f));
				break;
			case 5:
				//PLAYER->GetTransform()->SetPosition(Vec3(-17.0f, 1.6f,-2.1f));
				//PLAYER->GetTransform()->SetRotation(Vec3());
				break;
			}
		}
	}

	void RightMap::Update()
	{
		Map::Update();
		if (Target != nullptr)
		{
			if (IS_UP(KeyType::LEFT))
			{
				Vec3 target_pos = Vec3(Target->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x -= 0.1f, target_pos.y, target_pos.z);
				Target->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::UP))
			{
				Vec3 target_pos = Vec3(Target->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y, target_pos.z += 0.1f);
				Target->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::DOWN))
			{
				Vec3 target_pos = Vec3(Target->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y, target_pos.z -= 0.1f);
				Target->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::RIGHT))
			{
				Vec3 target_pos = Vec3(Target->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x += 0.1f, target_pos.y, target_pos.z);
				Target->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::Z))
			{
				Vec3 target_pos = Vec3(Target->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y += 0.1f, target_pos.z);
				Target->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::X))
			{
				Vec3 target_pos = Vec3(Target->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y -= 0.1f, target_pos.z);
				Target->GetTransform()->SetPosition(fixed_pos);

			}
			if (IS_UP(KeyType::E))
			{
				Vec3 target_rot = Vec3(Target->GetTransform()->GetRotation());
				Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y += 10.0f, target_rot.z);
				Target->GetTransform()->SetRotation(fixed_rot);
			}
			if (IS_UP(KeyType::Q))
			{
				Vec3 target_rot = Vec3(Target->GetTransform()->GetRotation());
				Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y -= 10.0f, target_rot.z);
				Target->GetTransform()->SetRotation(fixed_rot);
			}

			if (IS_UP(KeyType::R))
			{
				Vec3 target_rot = Vec3(Target->GetTransform()->GetRotation());
				Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y += 1.0f, target_rot.z);
				Target->GetTransform()->SetRotation(fixed_rot);
			}
			if (IS_UP(KeyType::T))
			{
				Vec3 target_rot = Vec3(Target->GetTransform()->GetRotation());
				Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y -= 1.0f, target_rot.z);
				Target->GetTransform()->SetRotation(fixed_rot);
			}

			if (IS_UP(KeyType::O))
			{
				Vec3 target_scale = Vec3(Target->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x += 0.5f, target_scale.y += 0.5f, target_scale.z += 0.5f);
				Target->GetTransform()->SetScale(fixed_scale);
			}
			if (IS_UP(KeyType::P))
			{
				Vec3 target_scale = Vec3(Target->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x -= 0.5f, target_scale.y -= 0.5f, target_scale.z -= 0.5f);
				Target->GetTransform()->SetScale(fixed_scale);
			}
			if (IS_UP(KeyType::ENTER))
			{
				Vec3 a = Target->GetTransform()->GetPosition();
				Vec3 b = Target->GetTransform()->GetRotation();
				Vec3 c = Target->GetTransform()->GetScale();
				int d = 0;
			}
		}
	}

	void RightMap::FixedUpdate()
	{
		Map::FixedUpdate();
	}

	void RightMap::FinalUpdate()
	{
		Map::FinalUpdate();
	}

	void RightMap::Render()
	{
		Map::Render();
	}

	void RightMap::Enter()
	{
		

		gpEngine->SetSwapChainRTVClearColor(Vec4(0.f, 0.f, 0.f, 0.f));
		////마법사
		//{
		//	SpawnDoor<Mage>* pMage = Factory::SpawnMonster<Mage>(Vec3(-10.f,8.f, -10.f),Vec3(-90.f,0.f,-90.f));
		//	AddGameObject(pMage);
		//}

		//마법사
		{
			Mage* pMage = Factory::CreateMage(Vec3(-10.f, 5.f, -10.f), Vec3(-90.f, 0.f, -90.f));
			AddGameObject(pMage);
		}

		//마법사
		{
			Mage* pMage = Factory::CreateMage(Vec3(10.f, 5.f, 0.f), Vec3(-90.f, 0.f, -90.f));
			AddGameObject(pMage);
		}

		//콩벌레
		{
			HeadRoller* pHeadRoller = Factory::CreateHeadRoller(Vec3(-10.f, 5.f, 0.f), Vec3(0.f, -45.f, 0.f));
			AddGameObject(pHeadRoller);
		}


			InitObjectAdd();
			InitColliderAdd();
			FuncObjectAdd();
			
	}

	void RightMap::Exit()
	{
	}
	void RightMap::InitObjectAdd()
	{
		{

			Ground* pGround = Factory::CreateObject<Ground>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\RightChairRoomFloor.fbx");
			pGround->GetTransform()->SetPosition(Vec3(0.0f, 0.2f, 0.0f));
			pGround->GetTransform()->SetScale(Vec3(20, 20, 20));

			AddGameObject(pGround);
		}

		{

			Ground* pGround = Factory::CreateObject<Ground>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\RightChairRoomFloor.fbx");
			pGround->GetTransform()->SetPosition(Vec3(0.0f, 0.4f, 0.0f));
			pGround->GetTransform()->SetScale(Vec3(40.0f, 40.0f, 40.0f));

			AddGameObject(pGround);
		}

		// 미러
		{
			GameObject* pMirror = Factory::CreateObject<GameObject>(Vec3(0.0f, 0.87f, 0.0f), L"Forward", L"", false, LayerType::Mirror);

			pMirror->GetTransform()->SetScale(Vec3(15.f, 15.f, 15.f));
			pMirror->AddComponent(new Mirror);
			pMirror->GetMeshRenderer()->SetMesh(GET_SINGLE(Resources)->LoadRectMesh());
			pMirror->GetTransform()->SetRotation(Vec3(90.f, 0.f, 0.f));

			AddGameObject(pMirror);
		}

		{
			DecoObject* pWallFrame = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\Right.fbx");
			pWallFrame->GetTransform()->SetPosition(Vec3(0.0f, 6.0f, 0.0f));
			pWallFrame->GetTransform()->SetScale(Vec3(40.0f, 40.0f, 40.0f));

			AddGameObject(pWallFrame);
		}
		{
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetPosition(Vec3(-16.8f, 6.2f, -36.0f));
			pColumnFull->GetTransform()->SetRotation(Vec3(0.0f, -180.0f, 0.0f));
			pColumnFull->GetTransform()->SetScale(Vec3(37.0f, 37.0f, 37.0f));

			AddGameObject(pColumnFull);
		}

		std::vector<GameObject*> mColumnFullver2List;
		for (int i = 0; i < 2; i++)
		{
			DecoObject* pColumnFullVer2 = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\ColumnFullVer2.fbx");

			AddGameObject(pColumnFullVer2);
			mColumnFullver2List.push_back(pColumnFullVer2);
		}

		mColumnFullver2List[0]->GetTransform()->SetPosition(Vec3(14.6f, 7.2f, -24.0f));
		mColumnFullver2List[0]->GetTransform()->SetRotation(Vec3(0.0f, -180.0f, 0.0f));
		mColumnFullver2List[0]->GetTransform()->SetScale(Vec3(14.0f, 14.0f, 14.0f));
		mColumnFullver2List[1]->GetTransform()->SetPosition(Vec3(14.8f, 7.0f, 0.2f));
		mColumnFullver2List[1]->GetTransform()->SetRotation(Vec3(0.0f, -180.0f, 0.0f));
		mColumnFullver2List[1]->GetTransform()->SetScale(Vec3(14.0f, 14.0f, 14.0f));

		// 샹들리에 라이트
		{
			GameObject* pGameObject = new GameObject(LayerType::Unknown);
			Transform* pTransform = pGameObject->AddComponent(new Transform);
			pTransform->SetPosition(Vec3(-1.3f, 11.f, -16.1f));
			pTransform->SetRotation(Vec3(71.9f, 0.f, 0.f));
			pTransform->SetScale(Vec3(100.f, 100.f, 100.f));
			Fireplace* pLight = pGameObject->AddComponent(new Fireplace);
			pLight->SetDiffuse(Vec3(1.0f, 0.3f, 0.3f));
			pLight->SetAmbient(Vec3(0.0f, 0.0f, 0.0f));
			pLight->SetLightRange(70.f);
			pLight->SetLightType(LightType::PointLight);
			AddGameObject(pGameObject);
		}

		{
			DecoObject* pBonFire = Factory::CreateObject<DecoObject>(Vec3(-1.3f, 4.9f, -18.1f), L"Fireplace", L"");
			pBonFire->GetMeshRenderer()->SetMaterial(pBonFire->GetMeshRenderer()->GetMaterial()->Clone());
			pBonFire->GetMeshRenderer()->GetMaterial()->SetSamplerType(SamplerType::WrapClamp);
			pBonFire->GetTransform()->SetScale(Vec3(2.8f, 3.f, 2.f));
			pBonFire->AddComponent(new BonFireScript);
			AddGameObject(pBonFire);
		}

		//{
		//	DecoObject* pDoorFrameBig = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\DoorFrameBig.fbx");

		//	AddGameObject(pDoorFrameBig);

		//	pDoorFrameBig->GetTransform()->SetPosition(Vec3(14.8f, 4.2f, -19.2f));
		//	pDoorFrameBig->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 0.0f));
		//	pDoorFrameBig->GetTransform()->SetScale(Vec3(29.0f, 29.0f, 29.0f));
		//}

		//{
		//	DecoObject* pCeilingBeamLow = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\CeilingBeamLow.fbx");

		//	AddGameObject(pCeilingBeamLow);

		//	pCeilingBeamLow->GetTransform()->SetPosition(Vec3(-1.2f, 11.8f, -18.4f));
		//	pCeilingBeamLow->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 0.0f));
		//	pCeilingBeamLow->GetTransform()->SetScale(Vec3(32.0f, 32.0f, 32.0f));
		//}


		std::vector<GameObject*> mCurtainHorizontalList;
		for (int i = 0; i < 4; i++)
		{
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\CurtainHorizontal.fbx");

			AddGameObject(pCurtainHorizontal);
			mCurtainHorizontalList.push_back(pCurtainHorizontal);
		}

		mCurtainHorizontalList[0]->GetTransform()->SetPosition(Vec3(13.4f, 9.4f, 5.6f));
		mCurtainHorizontalList[0]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mCurtainHorizontalList[0]->GetTransform()->SetScale(Vec3(24.0f, 24.0f, 24.0f));

		mCurtainHorizontalList[1]->GetTransform()->SetPosition(Vec3(13.2f, 9.4f, -6.6f));
		mCurtainHorizontalList[1]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mCurtainHorizontalList[1]->GetTransform()->SetScale(Vec3(24.0f, 24.0f, 24.0f));

		mCurtainHorizontalList[2]->GetTransform()->SetPosition(Vec3(13.8f, 8.8f, -17.6f));
		mCurtainHorizontalList[2]->GetTransform()->SetRotation(Vec3(0.0f, 88.f, 0.0f));
		mCurtainHorizontalList[2]->GetTransform()->SetScale(Vec3(24.0f, 24.0f, 24.0f));

		mCurtainHorizontalList[3]->GetTransform()->SetPosition(Vec3(-5.0f, 8.8f, -17.6f));
		mCurtainHorizontalList[3]->GetTransform()->SetRotation(Vec3(0.0f, 88.f, 0.0f));
		mCurtainHorizontalList[3]->GetTransform()->SetScale(Vec3(24.0f, 24.0f, 24.0f));

		std::vector<GameObject*> mCurtainVerticalList;
		for (int i = 0; i < 4; i++)
		{
			DecoObject* pCurtainVertical = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\CurtainVertical.fbx");

			AddGameObject(pCurtainVertical);
			mCurtainVerticalList.push_back(pCurtainVertical);
		}

		mCurtainVerticalList[0]->GetTransform()->SetPosition(Vec3(13.4f, 5.2f, 10.3f));
		mCurtainVerticalList[0]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mCurtainVerticalList[0]->GetTransform()->SetScale(Vec3(24.0f, 24.0f, 24.0f));

		mCurtainVerticalList[1]->GetTransform()->SetPosition(Vec3(-0.1f, 4.7f, -17.6f));
		mCurtainVerticalList[1]->GetTransform()->SetRotation(Vec3(0.0f, 90.0f, 0.0f));
		mCurtainVerticalList[1]->GetTransform()->SetScale(Vec3(9.6f, 24.0f, 24.0f));

		{
			DecoObject* pFireplace = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\Fireplace.fbx");

			AddGameObject(pFireplace);

			pFireplace->GetTransform()->SetPosition(Vec3(-1.2f, 5.8f, 3.87430192e-07f));
			pFireplace->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			pFireplace->GetTransform()->SetScale(Vec3(38.0f, 38.0f, 38.0f));
		}

		std::vector<GameObject*> mTwoTierShelf_BottomList;
		for (int i = 0; i < 2; i++)
		{
			DecoObject* pTwoTierShelf_Bottom = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\TwoTierShelf_Bottom.fbx");

			AddGameObject(pTwoTierShelf_Bottom);
			mTwoTierShelf_BottomList.push_back(pTwoTierShelf_Bottom);

		}
		mTwoTierShelf_BottomList[0]->GetTransform()->SetPosition(Vec3(13.6f, 2.2f, -15.2f));
		mTwoTierShelf_BottomList[0]->GetTransform()->SetRotation(Vec3(0.0f, -90.0f, 0.0f));
		mTwoTierShelf_BottomList[0]->GetTransform()->SetScale(Vec3(6.0f, 6.0f, 6.0f));

		mTwoTierShelf_BottomList[1]->GetTransform()->SetPosition(Vec3(9.4f, 2.2f, -17.0f));
		mTwoTierShelf_BottomList[1]->GetTransform()->SetRotation(Vec3(0.0f, -180.0f, 0.0f));
		mTwoTierShelf_BottomList[1]->GetTransform()->SetScale(Vec3(6.0f, 6.0f, 6.0f));


#pragma region "2Ãþ ¼±¹Ý ´Ù¸®"
		std::vector<GameObject*> mTwoTierShelf_LegList;
		for (int i = 0; i < 8; i++)
		{
			DecoObject* pTwoTierShelf_Leg = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\TwoTierShelf_Leg.fbx");

			AddGameObject(pTwoTierShelf_Leg);
			mTwoTierShelf_LegList.push_back(pTwoTierShelf_Leg);
		}

		mTwoTierShelf_LegList[0]->GetTransform()->SetPosition(Vec3(14.4f, 1.4f, -12.4f));
		mTwoTierShelf_LegList[0]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_LegList[0]->GetTransform()->SetScale(Vec3(0.59f, 0.99f, 0.59f));

		mTwoTierShelf_LegList[1]->GetTransform()->SetPosition(Vec3(12.8f, 1.4f, -12.4f));
		mTwoTierShelf_LegList[1]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_LegList[1]->GetTransform()->SetScale(Vec3(0.59f, 0.99f, 0.59f));

		mTwoTierShelf_LegList[2]->GetTransform()->SetPosition(Vec3(12.8f, 1.4f, -18.0f));
		mTwoTierShelf_LegList[2]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_LegList[2]->GetTransform()->SetScale(Vec3(0.59f, 0.99f, 0.59f));

		mTwoTierShelf_LegList[3]->GetTransform()->SetPosition(Vec3(14.4f, 1.4f, -18.0f));
		mTwoTierShelf_LegList[3]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_LegList[3]->GetTransform()->SetScale(Vec3(0.59f, 0.99f, 0.59f));

		mTwoTierShelf_LegList[4]->GetTransform()->SetPosition(Vec3(6.6f, 1.4f, -16.2f));
		mTwoTierShelf_LegList[4]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_LegList[4]->GetTransform()->SetScale(Vec3(0.59f, 0.99f, 0.59f));

		mTwoTierShelf_LegList[5]->GetTransform()->SetPosition(Vec3(6.6f, 1.4f, -17.8f));
		mTwoTierShelf_LegList[5]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_LegList[5]->GetTransform()->SetScale(Vec3(0.59f, 0.99f, 0.59f));

		mTwoTierShelf_LegList[6]->GetTransform()->SetPosition(Vec3(12.4f, 1.4f, -17.8f));
		mTwoTierShelf_LegList[6]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_LegList[6]->GetTransform()->SetScale(Vec3(0.59f, 0.99f, 0.59f));

		mTwoTierShelf_LegList[7]->GetTransform()->SetPosition(Vec3(12.4f, 1.4f, -16.2f));
		mTwoTierShelf_LegList[7]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_LegList[7]->GetTransform()->SetScale(Vec3(0.59f, 0.99f, 0.59f));
#pragma endregion


		std::vector<GameObject*> mTwoTierShelf_Middle_LegList;
		for (int i = 0; i < 8; i++)
		{
			DecoObject* pTwoTierShelf_Middle_Leg = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\TwoTierShelf_Middle_Leg.fbx");

			AddGameObject(pTwoTierShelf_Middle_Leg);
			mTwoTierShelf_Middle_LegList.push_back(pTwoTierShelf_Middle_Leg);
		}


		mTwoTierShelf_Middle_LegList[0]->GetTransform()->SetPosition(Vec3(12.8f, 3.5f, -12.4f));
		mTwoTierShelf_Middle_LegList[0]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_Middle_LegList[0]->GetTransform()->SetScale(Vec3(1.1f, 2.2f, 1.1f));

		mTwoTierShelf_Middle_LegList[1]->GetTransform()->SetPosition(Vec3(14.4f, 3.5f, -12.4f));
		mTwoTierShelf_Middle_LegList[1]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_Middle_LegList[1]->GetTransform()->SetScale(Vec3(1.1f, 2.2f, 1.1f));

		mTwoTierShelf_Middle_LegList[2]->GetTransform()->SetPosition(Vec3(14.4f, 3.5f, -18.0f));
		mTwoTierShelf_Middle_LegList[2]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_Middle_LegList[2]->GetTransform()->SetScale(Vec3(1.1f, 2.2f, 1.1f));

		mTwoTierShelf_Middle_LegList[3]->GetTransform()->SetPosition(Vec3(12.6f, 3.5f, -18.0f));
		mTwoTierShelf_Middle_LegList[3]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_Middle_LegList[3]->GetTransform()->SetScale(Vec3(1.1f, 2.2f, 1.1f));

		mTwoTierShelf_Middle_LegList[4]->GetTransform()->SetPosition(Vec3(12.0f, 3.5f, -17.8f));
		mTwoTierShelf_Middle_LegList[4]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_Middle_LegList[4]->GetTransform()->SetScale(Vec3(1.1f, 2.2f, 1.1f));

		mTwoTierShelf_Middle_LegList[5]->GetTransform()->SetPosition(Vec3(12.0f, 3.5f, -16.2f));
		mTwoTierShelf_Middle_LegList[5]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_Middle_LegList[5]->GetTransform()->SetScale(Vec3(1.1f, 2.2f, 1.1f));

		mTwoTierShelf_Middle_LegList[6]->GetTransform()->SetPosition(Vec3(6.6f, 3.5f, -16.2f));
		mTwoTierShelf_Middle_LegList[6]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_Middle_LegList[6]->GetTransform()->SetScale(Vec3(1.1f, 2.2f, 1.1f));

		mTwoTierShelf_Middle_LegList[7]->GetTransform()->SetPosition(Vec3(6.6f, 3.5f, -17.8f));
		mTwoTierShelf_Middle_LegList[7]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_Middle_LegList[7]->GetTransform()->SetScale(Vec3(1.1f, 2.2f, 1.1f));

		std::vector<GameObject*> mEmptyBoxList;

		for (int i = 0; i < 3; i++)
		{
			DecoObject* pEmptyBox = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\EmptyBox.fbx");

			AddGameObject(pEmptyBox);
			mEmptyBoxList.push_back(pEmptyBox);

		}
		mEmptyBoxList[0]->GetTransform()->SetPosition(Vec3(7.7f, 3.4f, -0.7f));
		mEmptyBoxList[0]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mEmptyBoxList[0]->GetTransform()->SetScale(Vec3(35.0f, 35.0f, 35.0f));

		mEmptyBoxList[1]->GetTransform()->SetPosition(Vec3(9.35f, 3.4f, -0.1f));
		mEmptyBoxList[1]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mEmptyBoxList[1]->GetTransform()->SetScale(Vec3(35.0f, 35.0f, 35.0f));

		mEmptyBoxList[2]->GetTransform()->SetPosition(Vec3(11.0f, 3.4f, -0.7f));
		mEmptyBoxList[2]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mEmptyBoxList[2]->GetTransform()->SetScale(Vec3(35.0f, 35.0f, 35.0f));


		std::vector<GameObject*> mTwoTierShelfTopList;
		for (int i = 0; i < 2; i++)
		{
			DecoObject* pTwoTierShelf_Top = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\TwoTierShelfTop.fbx");

			AddGameObject(pTwoTierShelf_Top);
			mTwoTierShelfTopList.push_back(pTwoTierShelf_Top);
		}
		mTwoTierShelfTopList[0]->GetTransform()->SetPosition(Vec3(9.3f, 4.5f, -17.0f));
		mTwoTierShelfTopList[0]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mTwoTierShelfTopList[0]->GetTransform()->SetScale(Vec3(5.8f, 6.5f, 6.5f));

		mTwoTierShelfTopList[1]->GetTransform()->SetPosition(Vec3(13.6f, 4.5f, -15.2f));
		mTwoTierShelfTopList[1]->GetTransform()->SetRotation(Vec3(0.0f, 90.0f, 0.0f));
		mTwoTierShelfTopList[1]->GetTransform()->SetScale(Vec3(5.8f, 6.5f, 6.5f));



		{
			DecoObject* pJewellery = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\Jewellery.fbx");

			AddGameObject(pJewellery);

			pJewellery->GetTransform()->SetPosition(Vec3(9.35f, 4.2f, -0.5f));
			pJewellery->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			pJewellery->GetTransform()->SetScale(Vec3(34.5f, 24.0f, 34.0f));
		}

		{
			DecoObject* pPOSSESSED_Chair = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\POSSESSED_Chair.fbx");

			AddGameObject(pPOSSESSED_Chair);

			pPOSSESSED_Chair->GetTransform()->SetPosition(Vec3(10.35f, 2.9f, -2.6f));
			pPOSSESSED_Chair->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			pPOSSESSED_Chair->GetTransform()->SetScale(Vec3(25.0f, 25.0f, 25.0f));

		}

		std::vector<GameObject*> mPOTHEALGenericVariantList;
		for (int i = 0; i < 3; i++)
		{
			DecoObject* pPOTHEALGenericVariant = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\POT_HEAL_Generic_Variant.fbx");

			AddGameObject(pPOTHEALGenericVariant);


			mPOTHEALGenericVariantList.push_back(pPOTHEALGenericVariant);
		}

		mPOTHEALGenericVariantList[0]->GetTransform()->SetPosition(Vec3(4.85f, 2.0f, -0.4f));
		mPOTHEALGenericVariantList[0]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mPOTHEALGenericVariantList[0]->GetTransform()->SetScale(Vec3(35.0f, 35.0f, 35.0f));

		mPOTHEALGenericVariantList[1]->GetTransform()->SetPosition(Vec3(12.35f, 2.0f, 23.0f));
		mPOTHEALGenericVariantList[1]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mPOTHEALGenericVariantList[1]->GetTransform()->SetScale(Vec3(35.0f, 35.0f, 35.0f));

		mPOTHEALGenericVariantList[2]->GetTransform()->SetPosition(Vec3(-16.48f, 2.0f, 23.0f));
		mPOTHEALGenericVariantList[2]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mPOTHEALGenericVariantList[2]->GetTransform()->SetScale(Vec3(35.0f, 35.0f, 35.0f));

		{
			DecoObject* pFancyChairSit = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\FancyChairSit.fbx");

			AddGameObject(pFancyChairSit);

			pFancyChairSit->GetTransform()->SetPosition(Vec3(-1.15f, 4.6f, 4.4f));
			pFancyChairSit->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			pFancyChairSit->GetTransform()->SetScale(Vec3(25.0f, 25.0f, 25.0f));

		}

		{
			DecoObject* pBook3 = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\Book3.fbx");

			AddGameObject(pBook3);

			pBook3->GetTransform()->SetPosition(Vec3(13.65f, 4.6f, 1.8f));
			pBook3->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			pBook3->GetTransform()->SetScale(Vec3(32.0f, 32.0f, 32.0f));

		}

		{
			DecoObject* pMansionPlantPot2 = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\MansionPlantPot2.fbx");

			AddGameObject(pMansionPlantPot2);

			pMansionPlantPot2->GetTransform()->SetPosition(Vec3(13.00f, 5.9f, -2.1f));
			pMansionPlantPot2->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			pMansionPlantPot2->GetTransform()->SetScale(Vec3(32.0f, 32.0f, 32.0f));

		}

		std::vector<GameObject*> mMansionSpicePotList;

		for (int i = 0; i < 2; i++)
		{
			DecoObject* pMansionSpicePot = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\MansionSpicePot.fbx");

			AddGameObject(pMansionSpicePot);
			mMansionSpicePotList.push_back(pMansionSpicePot);
		}
		mMansionSpicePotList[0]->GetTransform()->SetPosition(Vec3(10.5f, 5.1f, -4.6f));
		mMansionSpicePotList[0]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mMansionSpicePotList[0]->GetTransform()->SetScale(Vec3(25.0f, 25.0f, 25.0f));

		mMansionSpicePotList[1]->GetTransform()->SetPosition(Vec3(8.9f, 5.1f, -1.5f));
		mMansionSpicePotList[1]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mMansionSpicePotList[1]->GetTransform()->SetScale(Vec3(32.0f, 32.0f, 32.0f));


		{
			DecoObject* pScrolls6 = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\Scrolls_6.fbx");

			AddGameObject(pScrolls6);

			pScrolls6->GetTransform()->SetPosition(Vec3(13.5f, 3.1f, -3.2f));
			pScrolls6->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			pScrolls6->GetTransform()->SetScale(Vec3(25.0f, 25.0f, 25.0f));

		}

		{
			DecoObject* pSpike = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\SpikeDoor.fbx");

			AddGameObject(pSpike);

			pSpike->GetTransform()->SetPosition(Vec3(-17.5f, 2.8f, 6.9f));
			pSpike->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			pSpike->GetTransform()->SetScale(Vec3(22.0f, 22.0f, 22.0f));
			pSpikeDoor = pSpike;
		}
	}
	void RightMap::InitColliderAdd()
	{
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(47.24f, 1.07f, 24.44f);

			Ground* pGround = Factory::CreateObjectHasPhysical<Ground>(Vec3(-3.2f, 0.5f, -4.9f), physicsInfo, L"Forward", L"");

			AddGameObject(pGround);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(1.0f, 4.73f, 15.33f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-17.9f, 3.2f, -12.3f), physicsInfo, L"Forward", L"");

			AddGameObject(pWall);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(1.0f, 4.73f, 11.5f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(15.2f, 3.2f, 0.5f), physicsInfo, L"Forward", L"");

			AddGameObject(pWall);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(1.0f, 1.0f, 1.0f);

			WallObject* pSpawnPoint = Factory::CreateObjectHasPhysical<WallObject>(Vec3(15.2f, 3.2f, 0.5f), physicsInfo, L"Forward", L"");

			AddGameObject(pSpawnPoint);
			//SetGizmoTarget(pSpawnPoint);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(1.0f, 4.73f, 10.35f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(15.2f, 3.2f, -14.6f), physicsInfo, L"Forward", L"");

			AddGameObject(pWall);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(36.72f, 5.28f, 1.0f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-1.3f, 3.6f, -17.7f), physicsInfo, L"Forward", L"");

			AddGameObject(pWall);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(36.72f, 5.28f, 1.0f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-1.3f, 3.6f, 7.3f), physicsInfo, L"Forward", L"");

			AddGameObject(pWall);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(2.82f, 5.28f, 2.5f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-1.2f, 3.6f, -7.0f), physicsInfo, L"Forward", L"");

			AddGameObject(pWall);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(5.65f, 5.28f, 2.5f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(9.3f, 3.6f, -16.8f), physicsInfo, L"Forward", L"");

			AddGameObject(pWall);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(5.65f, 5.28f, 3.5f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(11.9f, 3.6f, -14.2f), physicsInfo, L"Forward", L"");

			AddGameObject(pWall);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(0.56f, 5.28f, 7.35f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-17.7f, 3.6f, 3.7f), physicsInfo, L"Forward", L"");

			AddGameObject(pWall);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(0.56f, 4.7f, 4.41f);

			WallObject* pSpikeCol = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-17.7f, 3.3f, -2.3f), physicsInfo, L"Forward", L"");

			AddGameObject(pSpikeCol);
			pSpikeDoorCol = pSpikeCol;
		}

		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(11.4f, 5.3f, 7.3f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-23.9f, 3.6f, 3.7f), physicsInfo, L"Forward", L"");

			AddGameObject(pWall);
		}

		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(11.4f, 5.3f, 15.3f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-23.9f, 3.6f, -12.4f), physicsInfo, L"Forward", L"");

			AddGameObject(pWall);
		}

		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(11.4f, 5.3f, 15.3f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-25.6f, 3.6f, -2.8f), physicsInfo, L"Forward", L"");

			AddGameObject(pWall);
		}

		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(38.4f, 5.3f, 15.3f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-1.5f, 3.6f, -25.7f), physicsInfo, L"Forward", L"");

			AddGameObject(pWall);
		}

		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(38.4f, 5.3f, 15.3f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(-2.2f, 3.6f, 15.4f), physicsInfo, L"Forward", L"");

			AddGameObject(pWall);
		}

		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(11.5f, 5.3f, 55.7f);

			WallObject* pWall = Factory::CreateObjectHasPhysical<WallObject>(Vec3(23.f, 3.6f, -5.f), physicsInfo, L"Forward", L"");

			AddGameObject(pWall);
		}

	}
	void RightMap::FuncObjectAdd()
	{
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(1.0, 3.8f, 3.5f);

			TeleportZone* pTelZone = Factory::CreateObjectHasPhysical<TeleportZone>(Vec3(-19.1f, 2.8f, -2.1f), physicsInfo, L"Deferred", L"", false, MapType::CorridorRightMap,5);
			AddGameObject(pTelZone);
		}
		{
			PhysicsInfo physicsInfo;
			physicsInfo.eActorType = ActorType::Static;
			physicsInfo.eGeometryType = GeometryType::Box;
			physicsInfo.size = Vec3(1.0, 3.8f, 3.5f);

			TeleportZone* pTelZone = Factory::CreateObjectHasPhysical<TeleportZone>(Vec3(16.8f, 2.8f, -7.3f), physicsInfo, L"Deferred", L"", false, MapType::Right2Map,1);
			AddGameObject(pTelZone);
		}
		{
			SpikeDoor* pDoor = Factory::CreateObject<yj::SpikeDoor>(Vec3(0.0f, 0.0f, 0.0f), L"Deferred", L"", false, pSpikeDoor, pSpikeDoorCol,2);
			AddGameObject(pDoor);
		}
	}
}