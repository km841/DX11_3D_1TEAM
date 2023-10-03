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

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Animator.h"

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
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Monster, LayerType::Ground);
		
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Monster, LayerType::PlayerCol);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Monster, LayerType::ArrowCol);
		GET_SINGLE(CollisionManager)->SetCollisionGroup(LayerType::Player, LayerType::Monster_ProjectTile);

		//GET_SINGLE(RenderManager)->AddFadeEffect(ScreenEffectType::FadeOut, 3.f, nullptr, nullptr, Vec4(1.f, 0.f, 0.f, 1.f) );
		//GET_SINGLE(RenderManager)->AddHoldEffect(3.f, nullptr, nullptr, Vec4(1.f, 0.f, 0.f, 1.f) );
		//GET_SINGLE(RenderManager)->AddFadeEffect(ScreenEffectType::FadeIn, 3.f, nullptr, nullptr, Vec4(1.f, 0.f, 0.f, 1.f) );
		//
		//shared_ptr<Video> pVideo = GET_SINGLE(Resources)->Load<Video>(L"Loding", L"..\\Resources\\Video\\Test.avi");
		//pVideo->Play();
		//���� �Ͼ������ ������ִ� �ڵ�
		gpEngine->SetSwapChainRTVClearColor(Vec4(255.f, 255.f, 255.f, 255.f));

		// 1�� �ٴ� - Floor
		{
			PhysicsInfo info;
			info.eActorType = ActorType::Static;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(50.f, 0.1f, 50.f);

			Ground* pFloor = Factory::CreateObjectHasPhysical<Ground>(Vec3(0.f, -8.5f, 6.6f), info, L"Forward", L"..\\Resources\\FBX\\Map\\Dungeon\\LeftSecretTrialMap\\RoughLowerFloor.fbx");

			pFloor->GetTransform()->SetScale(Vec3(50.f, 1.f, 50.f));
			pFloor->GetMeshRenderer()->GetMaterial()->SetTexture(0, nullptr);
			pFloor->GetMeshRenderer()->GetMaterial()->SetVec3(0, Vec3::Color(114, 114, 115));

			AddGameObject(pFloor);
			
		}

		PLAYER->GetTransform()->SetPosition(Vec3(0.f, -7.f, 0.f));



		 //�����
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

		// �ʷϰŹ�
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
		
	
		// ������
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

		 //�߰����� �����
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(3.f, 8.f, 3.f);

			Grimace* p_E_GRIMACE_KNIGHT = Factory::CreateMonster<Grimace>(Vec3(-5.f, 0.f, 0.f), info, L"MonsterDeferred", L"..\\Resources\\FBX\\Monster\\_E_GRIMACE_KNIGHT.fbx");
			p_E_GRIMACE_KNIGHT->GetTransform()->SetScale(Vec3(1.f, 1.f, 1.f));
			p_E_GRIMACE_KNIGHT->GetTransform()->SetRotation(Vec3(180.f, 0.f, 0.f));
			p_E_GRIMACE_KNIGHT->GetTransform()->SetPositionExcludingColliders(Vec3(0.f, -4.f, 0.f));

			//SetGizmoTarget(p_E_GRIMACE_KNIGHT);
			AddGameObject(p_E_GRIMACE_KNIGHT);
			SetMeshTarget(p_E_GRIMACE_KNIGHT);
		}

		// ����
		{
			PhysicsInfo info = {};
			info.eActorType = ActorType::Kinematic;
			info.eGeometryType = GeometryType::Box;
			info.size = Vec3(0.5f, 0.5f, 1.0f);

			Bat* p_E_BAT_White = Factory::CreateMonster<Bat>(Vec3(-20.f, 0.f, 20.f), info, L"MonsterDeferred", L"..\\Resources\\FBX\\Monster\\_E_BAT_White.fbx");
			p_E_BAT_White->GetTransform()->SetScale(Vec3(0.5f, 0.5f, 0.5f));
			p_E_BAT_White->GetTransform()->SetRotation(Vec3(-90.f, 0.f, 0.f));
	
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

		
	}
	void Monster_Player_TestScene::Exit()
	{
	}
}