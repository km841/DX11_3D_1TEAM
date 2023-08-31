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

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
/* Script */
#include "PaperBurnScript.h"
#include "CameraMoveScript.h"

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

	void RightMap::Update()
	{
		Map::Update();
		if (Target != nullptr)
		{
			if (IS_UP(KeyType::LEFT))
			{
				Vec3 target_pos = Vec3(Target->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x -= 0.1f, target_pos.y, target_pos.z);
				Target->GetTransform()->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::UP))
			{
				Vec3 target_pos = Vec3(Target->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y, target_pos.z += 0.1f);
				Target->GetTransform()->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::DOWN))
			{
				Vec3 target_pos = Vec3(Target->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y, target_pos.z -= 0.1f);
				Target->GetTransform()->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::RIGHT))
			{
				Vec3 target_pos = Vec3(Target->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x += 0.1f, target_pos.y, target_pos.z);
				Target->GetTransform()->GetTransform()->SetPosition(fixed_pos);
			}
			if (IS_UP(KeyType::Z))
			{
				Vec3 target_pos = Vec3(Target->GetTransform()->GetPosition());
				Vec3 fixed_pos = Vec3(target_pos.x, target_pos.y += 0.1f, target_pos.z);
				Target->GetTransform()->GetTransform()->SetPosition(fixed_pos);
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
				Target->GetTransform()->GetTransform()->SetRotation(fixed_rot);
			}
			if (IS_UP(KeyType::Q))
			{
				Vec3 target_rot = Vec3(Target->GetTransform()->GetRotation());
				Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y -= 10.0f, target_rot.z);
				Target->GetTransform()->GetTransform()->SetRotation(fixed_rot);
			}

			if (IS_UP(KeyType::R))
			{
				Vec3 target_rot = Vec3(Target->GetTransform()->GetRotation());
				Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y += 1.0f, target_rot.z);
				Target->GetTransform()->GetTransform()->SetRotation(fixed_rot);
			}
			if (IS_UP(KeyType::T))
			{
				Vec3 target_rot = Vec3(Target->GetTransform()->GetRotation());
				Vec3 fixed_rot = Vec3(target_rot.x, target_rot.y -= 1.0f, target_rot.z);
				Target->GetTransform()->GetTransform()->SetRotation(fixed_rot);
			}

			if (IS_UP(KeyType::O))
			{
				Vec3 target_scale = Vec3(Target->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x += 0.5f, target_scale.y += 0.5f, target_scale.z += 0.5f);
				Target->GetTransform()->GetTransform()->SetScale(fixed_scale);
			}
			if (IS_UP(KeyType::P))
			{
				Vec3 target_scale = Vec3(Target->GetTransform()->GetScale());
				Vec3 fixed_scale = Vec3(target_scale.x -= 0.5f, target_scale.y -= 0.5f, target_scale.z -= 0.5f);
				Target->GetTransform()->GetTransform()->SetScale(fixed_scale);
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
			gpEngine->SetSwapChainRTVClearColor(Vec4(100.f, 100.f, 100.f, 255.f));


			{

				Player* pPlayer = Factory::CreateObject<Player>(Vec3(0.f, 0.f, 0.f), L"Deferred", L"..\\Resources\\FBX\\Player\\Crow2.fbx");
				pPlayer->GetTransform()->SetScale(Vec3(2.0f, 2.0f, 2.0f));

				AddGameObject(pPlayer);
			}
		{

			Ground* pGround = Factory::CreateObject<Ground>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\RightChairRoomFloor.fbx");
			pGround->GetTransform()->SetPosition(Vec3(0.0f,0.2f,0.0f));
			pGround->GetTransform()->SetScale(Vec3(20,20,20));

			AddGameObject(pGround);
		}

		{
			DecoObject* pWallFrame = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\Right.fbx");
			pWallFrame->GetTransform()->SetPosition(Vec3(0.0f, 3.0f, 0.0f));
			pWallFrame->GetTransform()->SetScale(Vec3(20, 20, 20));

			AddGameObject(pWallFrame);
		}		
		{
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetPosition(Vec3(-8.4f, 3.1f, -18.0f));
			pColumnFull->GetTransform()->SetRotation(Vec3(0.0f, -180.0f, 0.0f));
			pColumnFull->GetTransform()->SetScale(Vec3(18.5f, 18.5f, 18.5f));

			AddGameObject(pColumnFull);
		}

		std::vector<GameObject*> mColumnFullver2List;
		for (int i = 0; i < 2; i++)
		{
			DecoObject* pColumnFullVer2 = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\ColumnFullVer2.fbx");
			
			AddGameObject(pColumnFullVer2);
			mColumnFullver2List.push_back(pColumnFullVer2);
		}	

		mColumnFullver2List[0]->GetTransform()->SetPosition(Vec3(7.3f, 3.6f, -12.0f));
		mColumnFullver2List[0]->GetTransform()->SetRotation(Vec3(0.0f, -180.0f, 0.0f));
		mColumnFullver2List[0]->GetTransform()->SetScale(Vec3(7.0f, 7.0f, 7.0f));
		mColumnFullver2List[1]->GetTransform()->SetPosition(Vec3(7.4f, 3.5f, 0.1f));
		mColumnFullver2List[1]->GetTransform()->SetRotation(Vec3(0.0f, -180.0f, 0.0f));
		mColumnFullver2List[1]->GetTransform()->SetScale(Vec3(7.0f, 7.0f, 7.0f));


		{
			DecoObject* pDoorFrameBig = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\DoorFrameBig.fbx");

			AddGameObject(pDoorFrameBig);

			pDoorFrameBig->GetTransform()->SetPosition(Vec3(7.4f, 2.1f, -9.6f));
			pDoorFrameBig->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 0.0f));
			pDoorFrameBig->GetTransform()->SetScale(Vec3(14.5f, 14.5f, 14.5f));
		}

		{
			DecoObject* pCeilingBeamLow = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\CeilingBeamLow.fbx");

			AddGameObject(pCeilingBeamLow);

			pCeilingBeamLow->GetTransform()->SetPosition(Vec3(-0.6, 5.9f, -9.2f));
			pCeilingBeamLow->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 0.0f));
			pCeilingBeamLow->GetTransform()->SetScale(Vec3(16.0f, 16.0f, 16.0f));
		}


		std::vector<GameObject*> mCurtainHorizontalList;
		for (int i = 0; i < 4; i++)
		{
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\CurtainHorizontal.fbx");

			AddGameObject(pCurtainHorizontal);
			mCurtainHorizontalList.push_back(pCurtainHorizontal);
		}

		mCurtainHorizontalList[0]-> GetTransform()->SetPosition(Vec3(6.7, 4.7f, 2.8f));
		mCurtainHorizontalList[0]-> GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mCurtainHorizontalList[0]-> GetTransform()->SetScale(Vec3(12.0f, 12.0f, 12.0f));

		mCurtainHorizontalList[1]->GetTransform()->SetPosition(Vec3(6.6f, 4.7f, -3.3f));
		mCurtainHorizontalList[1]->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
		mCurtainHorizontalList[1]->GetTransform()->SetScale(Vec3(12.0f, 12.0f, 12.0f));

		mCurtainHorizontalList[2]->GetTransform()->SetPosition(Vec3(6.9f, 4.4f, -8.8f));
		mCurtainHorizontalList[2]->GetTransform()->SetRotation(Vec3(0.0f, 88.0f, 0.0f));
		mCurtainHorizontalList[2]->GetTransform()->SetScale(Vec3(12.0f, 12.0f, 12.0f));


		{
			DecoObject* pFireplace = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\Fireplace.fbx");

			AddGameObject(pFireplace);

			pFireplace->GetTransform()->SetPosition(Vec3(-0.6f, 2.9f, 1.93715096e-07f));
			pFireplace->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			pFireplace->GetTransform()->SetScale(Vec3(19.0f, 19.0f, 19.0f));
		}

		std::vector<GameObject*> mTwoTierShelf_BottomList;
		for (int i = 0; i < 2; i++)
		{
			DecoObject* pTwoTierShelf_Bottom = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\TwoTierShelf_Bottom.fbx");

			AddGameObject(pTwoTierShelf_Bottom);
			mTwoTierShelf_BottomList.push_back(pTwoTierShelf_Bottom);
		
		}
		mTwoTierShelf_BottomList[0]->GetTransform()->SetPosition(Vec3(6.8f, 1.1f, -7.6f));
		mTwoTierShelf_BottomList[0]->GetTransform()->SetRotation(Vec3(0.0f, -90.0f, 0.0f));
		mTwoTierShelf_BottomList[0]->GetTransform()->SetScale(Vec3(3.0f, 3.0f, 3.0f));
		
		mTwoTierShelf_BottomList[1]->GetTransform()->SetPosition(Vec3(4.7f, 1.1f, -8.5f));
		mTwoTierShelf_BottomList[1]->GetTransform()->SetRotation(Vec3(0.0f, -180.0f, 0.0f));
		mTwoTierShelf_BottomList[1]->GetTransform()->SetScale(Vec3(3.0f, 3.0f, 3.0f));


#pragma region "2Ãþ ¼±¹Ý ´Ù¸®"


		std::vector<GameObject*> mTwoTierShelf_LegList;
		for (int i = 0; i < 8; i++)
		{
			DecoObject* pTwoTierShelf_Leg = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\TwoTierShelf_Leg.fbx");

			AddGameObject(pTwoTierShelf_Leg);
			mTwoTierShelf_LegList.push_back(pTwoTierShelf_Leg);
		}

		mTwoTierShelf_LegList[0]->GetTransform()->SetPosition(Vec3(7.2f, 0.7f, -6.2f));
		mTwoTierShelf_LegList[0]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_LegList[0]->GetTransform()->SetScale(Vec3(0.295f, 0.495f, 0.295f));

		mTwoTierShelf_LegList[1]->GetTransform()->SetPosition(Vec3(6.4f, 0.7f, -6.2f));
		mTwoTierShelf_LegList[1]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_LegList[1]->GetTransform()->SetScale(Vec3(0.295f, 0.495f, 0.295f));

		mTwoTierShelf_LegList[2]->GetTransform()->SetPosition(Vec3(6.4f, 0.7f, -9.0f));
		mTwoTierShelf_LegList[2]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_LegList[2]->GetTransform()->SetScale(Vec3(0.295f, 0.495f, 0.295f));

		mTwoTierShelf_LegList[3]->GetTransform()->SetPosition(Vec3(7.2f, 0.7f, -9.0f));
		mTwoTierShelf_LegList[3]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_LegList[3]->GetTransform()->SetScale(Vec3(0.295f, 0.495f, 0.295f));

		mTwoTierShelf_LegList[4]->GetTransform()->SetPosition(Vec3(3.3f, 0.7f, -8.1f));
		mTwoTierShelf_LegList[4]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_LegList[4]->GetTransform()->SetScale(Vec3(0.295f, 0.495f, 0.295f));

		mTwoTierShelf_LegList[5]->GetTransform()->SetPosition(Vec3(3.3f, 0.7f, -8.9f));
		mTwoTierShelf_LegList[5]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_LegList[5]->GetTransform()->SetScale(Vec3(0.295f, 0.495f, 0.295f));

		mTwoTierShelf_LegList[6]->GetTransform()->SetPosition(Vec3(6.2f, 0.7f, -8.9f));
		mTwoTierShelf_LegList[6]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_LegList[6]->GetTransform()->SetScale(Vec3(0.295f, 0.495f, 0.295f));

		mTwoTierShelf_LegList[7]->GetTransform()->SetPosition(Vec3(6.2f, 0.7f, -8.1f));
		mTwoTierShelf_LegList[7]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_LegList[7]->GetTransform()->SetScale(Vec3(0.295f, 0.495f, 0.295f));
#pragma endregion


		std::vector<GameObject*> mTwoTierShelf_Middle_LegList;
		for (int i = 0; i < 8; i++)
		{
			DecoObject* pTwoTierShelf_Middle_Leg = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\TwoTierShelf_Middle_Leg.fbx");

			AddGameObject(pTwoTierShelf_Middle_Leg);
			mTwoTierShelf_Middle_LegList.push_back(pTwoTierShelf_Middle_Leg);
		}


		mTwoTierShelf_Middle_LegList[0]->GetTransform()->SetPosition(Vec3(6.4f, 1.6f, -6.2f));
		mTwoTierShelf_Middle_LegList[0]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_Middle_LegList[0]->GetTransform()->SetScale(Vec3(0.55f, 0.75f, 0.55f));

		mTwoTierShelf_Middle_LegList[1]->GetTransform()->SetPosition(Vec3(7.2f, 1.6f, -6.2f));
		mTwoTierShelf_Middle_LegList[1]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_Middle_LegList[1]->GetTransform()->SetScale(Vec3(0.55f, 0.75f, 0.55f));

		mTwoTierShelf_Middle_LegList[2]->GetTransform()->SetPosition(Vec3(7.2f, 1.6f, -9.0f));
		mTwoTierShelf_Middle_LegList[2]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_Middle_LegList[2]->GetTransform()->SetScale(Vec3(0.55f, 0.75f, 0.55f));
		
		mTwoTierShelf_Middle_LegList[3]->GetTransform()->SetPosition(Vec3(6.3f, 1.6f, -9.0f));
		mTwoTierShelf_Middle_LegList[3]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_Middle_LegList[3]->GetTransform()->SetScale(Vec3(0.55f, 0.75f, 0.55f));

		mTwoTierShelf_Middle_LegList[4]->GetTransform()->SetPosition(Vec3(6.0f, 1.6f, -8.9f));
		mTwoTierShelf_Middle_LegList[4]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_Middle_LegList[4]->GetTransform()->SetScale(Vec3(0.55f, 0.75f, 0.55f));

		mTwoTierShelf_Middle_LegList[5]->GetTransform()->SetPosition(Vec3(6.0f, 1.6f, -8.1f));
		mTwoTierShelf_Middle_LegList[5]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_Middle_LegList[5]->GetTransform()->SetScale(Vec3(0.55f, 0.75f, 0.55f));

		mTwoTierShelf_Middle_LegList[6]->GetTransform()->SetPosition(Vec3(3.3f, 1.6f, -8.1f));
		mTwoTierShelf_Middle_LegList[6]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_Middle_LegList[6]->GetTransform()->SetScale(Vec3(0.55f, 0.75f, 0.55f));

		mTwoTierShelf_Middle_LegList[7]->GetTransform()->SetPosition(Vec3(3.3f, 1.6f, -8.9f));
		mTwoTierShelf_Middle_LegList[7]->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 180.0f));
		mTwoTierShelf_Middle_LegList[7]->GetTransform()->SetScale(Vec3(0.55f, 0.75f, 0.55f));






		{
		/*	DecoObject* pFireHolder = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\Holder.fbx");

			AddGameObject(pFireHolder);

			pFireHolder->GetTransform()->SetPosition(Vec3(-0.6f, 2.9f, 1.93715096e-07f));
			pFireHolder->GetTransform()->SetRotation(Vec3(0.0f, 0.0f, 0.0f));
			pFireHolder->GetTransform()->SetScale(Vec3(19.0f, 19.0f, 19.0f));
			Target = pFireHolder;*/
		}
	}

	void RightMap::Exit()
	{
	}
}