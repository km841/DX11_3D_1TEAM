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

			Ground* pGround = Factory::CreateObject<Ground>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\RightChairRoomFloor.fbx");
			pGround->GetTransform()->SetPosition(Vec3(0.0f,0.2f,0.0f));
			pGround->GetTransform()->SetScale(Vec3(30,30,30));

			AddGameObject(pGround);
		}

		{
			DecoObject* pWallFrame = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\Right.fbx");
			pWallFrame->GetTransform()->SetPosition(Vec3(0.0f, 4.3f, 0.0f));
			pWallFrame->GetTransform()->SetScale(Vec3(30, 30, 30));

			AddGameObject(pWallFrame);
		}		
		{
			DecoObject* pColumnFull = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\ColumnFull.fbx");
			pColumnFull->GetTransform()->SetPosition(Vec3(-12.8f, 4.4f, -27.6f));
			pColumnFull->GetTransform()->SetRotation(Vec3(0.0f,-180.0f,0.0f));
			pColumnFull->GetTransform()->SetScale(Vec3(28.5f, 28.5f, 28.5f));

			AddGameObject(pColumnFull);
		}


		std::vector<GameObject*> mColumnFullver2List;
		for (int i = 0; i < 2; i++)
		{
			DecoObject* pColumnFullVer2 = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\ColumnFullVer2.fbx");
			
			AddGameObject(pColumnFullVer2);
			mColumnFullver2List.push_back(pColumnFullVer2);
		}	

		mColumnFullver2List[0]->GetTransform()->SetPosition(Vec3(11.0f, 4.4f, -17.9f));
		mColumnFullver2List[0]->GetTransform()->SetRotation(Vec3(0.0f, -180.0f, 0.0f));
		mColumnFullver2List[0]->GetTransform()->SetScale(Vec3(10.0f, 10.0f, 10.0f));
		
		mColumnFullver2List[1]->GetTransform()->SetPosition(Vec3(11.0f, 4.4f, 0.3f));
		mColumnFullver2List[1]->GetTransform()->SetRotation(Vec3(0.0f, -180.0f, 0.0f));
		mColumnFullver2List[1]->GetTransform()->SetScale(Vec3(10.0f, 10.0f, 10.0f));


		{
			DecoObject* pDoorFrameBig = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\DoorFrameBig.fbx");

			AddGameObject(pDoorFrameBig);

			pDoorFrameBig->GetTransform()->SetPosition(Vec3(11.1f, 3.0f, -14.1f));
			pDoorFrameBig->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 0.0f));
			pDoorFrameBig->GetTransform()->SetScale(Vec3(21.0f, 21.0f, 21.0f));
			Target = pDoorFrameBig;

		}

		{
			DecoObject* pCeilingBeamLow = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\CeilingBeamLow.fbx");

			AddGameObject(pCeilingBeamLow);

			pCeilingBeamLow->GetTransform()->SetPosition(Vec3(-0.8, 7.7f, -13.5f));
			pCeilingBeamLow->GetTransform()->SetRotation(Vec3(0.0f, 180.0f, 0.0f));
			pCeilingBeamLow->GetTransform()->SetScale(Vec3(24.0f, 24.0f, 24.0f));
			Target = pCeilingBeamLow;
		}

		std::vector<GameObject*> mCurtainHorizontalList;
		for (int i = 0; i < 4; i++)
		{
			DecoObject* pCurtainHorizontal = Factory::CreateObject<DecoObject>((Vec3::Zero), L"Deferred", L"..\\Resources\\FBX\\Map\\R_Right\\CurtainHorizontal.fbx");

			AddGameObject(pCurtainHorizontal);
			mCurtainHorizontalList.push_back(pCurtainHorizontal);
		}

		mCurtainHorizontalList[0]-> GetTransform()->SetPosition(Vec3(9.9, 6.7f, 3.9f));
		mCurtainHorizontalList[0]-> GetTransform()->SetRotation(Vec3(0.0f, -3.0f, 0.0f));
		mCurtainHorizontalList[0]-> GetTransform()->SetScale(Vec3(17.0f, 17.0f, 17.0f));

		mCurtainHorizontalList[1]->GetTransform()->SetPosition(Vec3(10.4f, 6.7f, -5.1f));
		mCurtainHorizontalList[1]->GetTransform()->SetRotation(Vec3(0.0f, 2.0f, 0.0f));
		mCurtainHorizontalList[1]->GetTransform()->SetScale(Vec3(17.0f, 17.0f, 17.0f));

		mCurtainHorizontalList[2]->GetTransform()->SetPosition(Vec3(10.4f, 6.7f, -13.2f));
		mCurtainHorizontalList[2]->GetTransform()->SetRotation(Vec3(0.0f, 94.0f, 0.0f));
		mCurtainHorizontalList[2]->GetTransform()->SetScale(Vec3(17.0f, 17.0f, 17.0f));

		Target = mCurtainHorizontalList[2];
	}

	void RightMap::Exit()
	{
	}
}