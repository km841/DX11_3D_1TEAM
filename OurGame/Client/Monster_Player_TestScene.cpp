#include "pch.h"
#include "Monster_Player_TestScene.h"
#include "Engine.h"

/* Resource */
#include "MeshData.h"
#include "Material.h"
#include "Mesh.h"
#include "Video.h"

/* Manager */
#include "PrefabManager.h"
#include "EventManager.h"
#include "Factory.h"
#include "CollisionManager.h"
#include "Input.h"
#include "SceneManager.h"
#include "Resources.h"
#include "RenderManager.h"

/* GameObject */
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "DecoObject.h"
#include "WallObject.h"
#include "Npc.h"
#include "Monster.h"
#include "Grandma.h"
#include "Bat.h"
#include "SwordHeavyEffect.h"
#include "Mage.h"
#include "Lurker.h"
#include "HeadRoller.h"
#include "Grimace.h"
#include "LORD_BOSS.h"
#include "LORD_BOSS_ROLL.h"
#include "Cow.h"

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Animator.h"
#include "Mirror.h"

/* Script */
#include "PlayerMoveScript.h"
#include "PlacementScript.h"
#include "TestAnimationScript.h"
#include "PaperBurnScript.h"
#include "OwnerFollowScript.h"
#include "PlayerSlashScript.h"
#include "BonFireScript.h"

/* Event */
#include "SceneChangeEvent.h"


namespace hm {

	Monster_Player_TestScene::Monster_Player_TestScene()
		: Map(MapType::Monster_Player_Test)
	{
	}
	Monster_Player_TestScene::~Monster_Player_TestScene()
	{
	}
	void Monster_Player_TestScene::Initialize()
	{
		Map::Initialize();
	}
	void Monster_Player_TestScene::Start()
	{
		Map::Start();
	}
	void Monster_Player_TestScene::Update()
	{
		Map::Update();
	}
	void Monster_Player_TestScene::FixedUpdate()
	{
		Map::FixedUpdate();
	}
	void Monster_Player_TestScene::FinalUpdate()
	{
		Map::FinalUpdate();
	}
	void Monster_Player_TestScene::Render()
	{
		Map::Render();
	}
	void Monster_Player_TestScene::Enter()
	{
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Monster_ProjectTile);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Monster);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::MonsterCol);

		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Monster, LayerType::Ground);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Monster, LayerType::PlayerCol);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Monster, LayerType::ArrowCol);

		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::PlayerCol, LayerType::Monster_ProjectTile);
		

		//GET_SINGLE(RenderManager)->AddFadeEffect(ScreenEffectType::FadeOut, 3.f, nullptr, nullptr, Vec4(1.f, 0.f, 0.f, 1.f) );
		//GET_SINGLE(RenderManager)->AddHoldEffect(3.f, nullptr, nullptr, Vec4(1.f, 0.f, 0.f, 1.f) );
		//GET_SINGLE(RenderManager)->AddFadeEffect(ScreenEffectType::FadeIn, 3.f, nullptr, nullptr, Vec4(1.f, 0.f, 0.f, 1.f) );
		//
		//shared_ptr<Video> pVideo = GET_SINGLE(Resources)->Load<Video>(L"Loding", L"..\\Resources\\Video\\Test.avi");
		//pVideo->Play();
		//배경맵 하얀색으로 만들어주는 코드
		gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));

		// 1층 바닥 - Floor
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(100.f, 1.1f, 100.f);

			Ground* pFloor = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, -8.5f, 6.6f), info, L"Forward", L"");

			pFloor->GetTransform()->SetScale(Vec3(50.f, 1.f, 50.f));
			pFloor->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
			pFloor->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(114, 114, 115));

			AddGameObject(pFloor);
			
		}

		PLAYER->GetTransform()->SetPosition(Vec3(0.f, -7.f, 0.f));

		//pLordOfDoor->GetMeshRenderer()->SetMaterial(pLordOfDoor->GetMeshRenderer()->GetMaterial()->Clone()); 복제품 만들때 노인스턴싱

		 //콩벌레
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(1.f, 2.0f, 1.f);

			HeadRoller* p_E_HEADROLLER = Factory::CreateMonster<HeadRoller>(Vec3(10.f, 0.f, 20.f), info, L"MonsterDeferred", L"..\\Resources\\FBX\\Monster\\_E_HEADROLLER.fbx");
			p_E_HEADROLLER->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));
			p_E_HEADROLLER->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));
			p_E_HEADROLLER->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -1.f, 0.f));



			//SetGizmoTarget(p_E_HEADROLLER);
			AddGameObject(p_E_HEADROLLER);
			//SetMeshTarget(p_E_HEADROLLER);
		}

		
		// 최종보스
		{

			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(2.f, 2.0f, 6.f);

			LORD_BOSS_ROLL* pLordOfDoorRoll = Factory::CreateMonster<LORD_BOSS_ROLL>(Vec3(8.f, 5.f, 0.f), info, L"MonsterDeferred", L"..\\Resources\\FBX\\Monster\\LordOfDoor_Roller.fbx");
			pLordOfDoorRoll->GetTransform()->SetScale(Vec3(60.f, 60.f, 60.f));
			pLordOfDoorRoll->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));
			pLordOfDoorRoll->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -3.f, 0.f));
			pLordOfDoorRoll->GetAnimator()->Play(1,true);
			pLordOfDoorRoll->Disable();

			LORD_BOSS* pLordOfDoor = Factory::CreateMonster<LORD_BOSS>(Vec3(5.f, -4.f, 0.f), info, L"MonsterDeferred", L"..\\Resources\\FBX\\Monster\\LordOfDoor.fbx");
			pLordOfDoor->GetTransform()->SetScale(Vec3(3.f, 3.f, 3.f));
			pLordOfDoor->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));
			pLordOfDoor->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -3.f, 0.f));

			pLordOfDoor->SetObject(pLordOfDoorRoll);
			pLordOfDoorRoll->SetLORD_BOSS(pLordOfDoor);
			

			AddGameObject(pLordOfDoorRoll);
			AddGameObject(pLordOfDoor);
			//SetMeshTarget(pLordOfDoor);
		
		}

		

		//// 보스가 소환하는 소
		//{
		//	PhysicsInfo info = {};
		//	info.eActorType = ActorType::Kinematic;
		//	info.eGeometryType = GeometryType::Box;
		//	info.size = Vec3(1.5f, 1.0f, 2.f);

		//	Cow* pBullKnocker = Factory::CreateMonster<Cow>(Vec3(10.f, 0.f, 0.f), info, L"MonsterDeferred", L"..\\Resources\\FBX\\Monster\\BullKnocker.fbx");
		//	pBullKnocker->GetTransform()->SetScale(Vec3(0.3f, 0.3f, 0.3f));
		//	pBullKnocker->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));
		//	pBullKnocker->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -1.f, 0.f));
		//	pBullKnocker->GetAnimator()->SetPlaySpeed(0, 4.f);
		//	pBullKnocker->GetAnimator()->SetPlaySpeed(1, 3.f);
		//	pBullKnocker->GetAnimator()->SetPlaySpeed(2, 2.f);
		//	//pBullKnocker->GetAnimator()->Play(0,true);
		//	//SetGizmoTarget(p_E_HEADROLLER);
		//	AddGameObject(pBullKnocker);
		//	//SetMeshTarget(pBullKnocker);
		//}

		// 초록거미
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(0.5f, 0.5f, 1.f);

			Lurker* p_E_LURKER = Factory::CreateMonster<Lurker>(Vec3(0.f, 0.f, 20.f), info, L"MonsterDeferred", L"..\\Resources\\FBX\\Monster\\_E_LURKER.fbx");
			p_E_LURKER->GetTransform()->SetScale(Vec3(0.5f, 0.5f, 0.5f));
			p_E_LURKER->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));
			p_E_LURKER->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -0.4f, 0.f));

			AddGameObject(p_E_LURKER);
			//SetMeshTarget(p_E_LURKER);
		}
		
	
		// 마법사
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(0.5f, 0.5f, 2.f);

			Mage* p_E_MAGE = Factory::CreateMonster<Mage>(Vec3(-10.f, 0.f, 20.f), info, L"MonsterDeferred", L"..\\Resources\\FBX\\Monster\\_E_MAGE.fbx");
			p_E_MAGE->GetTransform()->SetScale(Vec3(0.5f, 0.5f, 0.5f));
			p_E_MAGE->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));
			p_E_MAGE->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -1.f, 0.f));
		
			
			AddGameObject(p_E_MAGE);
			//SetMeshTarget(p_E_MAGE);
		}

		 //중간보스 내루미
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(2.f, 8.f, 2.f);

			Grimace* p_E_GRIMACE_KNIGHT = Factory::CreateMonster<Grimace>(Vec3(-16.f, 0.f, -15.f), info, L"MonsterDeferred", L"..\\Resources\\FBX\\Monster\\_E_GRIMACE_KNIGHT.fbx");
			p_E_GRIMACE_KNIGHT->GetTransform()->SetScale(Vec3(0.7f, 0.7f, 0.7f));
			p_E_GRIMACE_KNIGHT->GetTransform()->SetRotation(Vec3(180.f, 0.f, 0.f));
			p_E_GRIMACE_KNIGHT->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -4.f, 0.f));
			for (size_t i = 0; i < 13; i++)
			{
				p_E_GRIMACE_KNIGHT->GetAnimator()->SetPlaySpeed(i, 0.8f);
			}
			//SetGizmoTarget(p_E_GRIMACE_KNIGHT);
			AddGameObject(p_E_GRIMACE_KNIGHT);
			//SetMeshTarget(p_E_GRIMACE_KNIGHT);
		}

		// 박쥐
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(0.5f, 0.5f, 1.0f);

			Bat* p_E_BAT_White = Factory::CreateMonster<Bat>(Vec3(-20.f, 0.f, 20.f), info, L"MonsterDeferred", L"..\\Resources\\FBX\\Monster\\_E_BAT_White.fbx");
			p_E_BAT_White->GetTransform()->SetScale(Vec3(0.5f, 0.5f, 0.5f));
			p_E_BAT_White->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 360.f));
	
			AddGameObject(p_E_BAT_White);
			//SetGizmoTarget(p_E_BAT_White);
		}

		

		/*{
			DecoObject* pBonFire = Factory::CreateObject<DecoObject>(Vec3(11.1f, 7.4f, -16.5f), L"Fire", L"");
			pBonFire->GetMeshRenderer()->GetMaterial()->SetSamplerType(SamplerType::WrapClamp);
			pBonFire->GetTransform()->SetScale(Vec3(2.f, 2.f, 2.f));
			pBonFire->AddComponent(new BonFireScript);
			AddGameObject(pBonFire);
		}*/

		// 미러
		{
			GameObject* pMirror = Factory::CreateObject<GameObject>(Vec3(0.f, -8.7f, 0.f), L"Forward", L"", false, LayerType::Mirror);

			pMirror->GetTransform()->SetScale(Vec3(50.f, 50.f, 50.f));
			pMirror->AddComponent(new Mirror);
			pMirror->GetMeshRenderer()->SetMesh(GET_SINGLE(Resources)->LoadRectMesh());
			pMirror->GetTransform()->SetRotation(Vec3(90.f, 0.f, 0.f));

			AddGameObject(pMirror);
		}
	}
	void Monster_Player_TestScene::Exit()
	{
	}
}