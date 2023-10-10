#include "pch.h"
#include "Monster.h"
#include "MonsterHitScript.h"
#include "RenderManager.h"
#include "SwordGlareEffect.h"
#include "AI.h"
#include "Player.h"
#include "Transform.h"
#include "Animator.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Input.h"
#include "ChangeStateCondition.h"
#include "PaperBurnScript.h"
#include "EventManager.h"
#include "SceneManager.h"
#include "ChangeStateTask.h"
#include "Factory.h"
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
#include "RenderManager.h"

/* GameObject */
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "DecoObject.h"
#include "WallObject.h"
#include "Npc.h"
#include "Monster.h"
#include "SwordHeavyEffect.h"
#include "Ladder.h"
#include "LadderCollider.h"
#include "HeadRoller.h"
#include "Grimace_ProjectTile.h"

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
#include "PlayerSlashScript.h"
#include "OwnerFollowScript.h"
#include "SwordScript.h"
#include "PlayerColScript.h"
#include "BowScript.h"
#include "ArrowScript.h"
#include "MonsterColScript.h"
/* Event */
#include "SceneChangeEvent.h"
 /*State 모음*/
#include "State.h"
#include "PauseState.h"
#include "IdleState.h"
#include "MoveState.h"
#include "AttackState.h"
#include "MagicAttackState.h"
#include "EvasionState.h"
#include "FallState.h"
#include "HitStartState.h"
#include "HittingState.h"
#include "HitEndState.h"
#include "FallDownState.h"
#include "DeadState.h"
#include "ClimingDownState.h"
#include "ClimingEndState.h"
#include "ClimingUpState.h"
#include "BowState.h"
namespace hm
{
	Monster::Monster()
		: GameObject(LayerType::Monster)
	{
	}

	Monster::~Monster()
	{
	}

	void Monster::TakeDamage(float _float)
	{
		mHP -= _float;
		MonsterHitScript* pScript = GetScript<MonsterHitScript>();
		AssertEx(nullptr != pScript, L"Factory::CreateMonster() 함수로 몬스터를 생성된 몬스터가 아님");
		
		SwordGlareEffect::Create(GetTransform()->GetPosition());
		pScript->HitBegin();
		GET_SINGLE(RenderManager)->AddCameraShakeEffect(0.1f, 0.02f);
	}

	void Monster::Initialize()
	{
		GameObject::Initialize();
		SetBehaviorTree();
	}

	void Monster::Update()
	{
		//CheckPenetration(GetRigidBody(),LayerType::WallObject);
		//CheckPenetration(GetRigidBody(),LayerType::Ground);
		GameObject::Update();
	}

	void Monster::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Monster::FinalUpdate()
	{
		GameObject::FinalUpdate();
	}

	void Monster::Render()
	{
		GameObject::Render();
	}

	void Monster::Destroy()
	{
		GameObject::Destroy();
	}

	void Monster::CheckPenetration(RigidBody* _rigidBody, LayerType _eLayertype)
	{
		const auto& gameObjects = GET_SINGLE(SceneManager)->GetActiveScene()->GetGameObjects(_eLayertype);

		for (int i = 0; i < gameObjects.size(); ++i)
		{
			if (false == gameObjects[i]->IsEnable())
				continue;

			if (gameObjects[i]->GetCollider())
			{
				PxVec3 dir;
				float depth;
				PxCapsuleGeometry playerGeom = _rigidBody->GetGeometries()->capsuleGeom;
				PxTransform pxTr = _rigidBody->GetPhysicsTransform();
				Geometries* otherGeom = gameObjects[i]->GetRigidBody()->GetGeometries();
				PxTransform pxTr2 = gameObjects[i]->GetRigidBody()->GetPhysicsTransform();

				bool isPenetrating = false;
				switch (gameObjects[i]->GetRigidBody()->GetGeometryType())
				{
				case hm::GeometryType::Sphere:
					isPenetrating = PxGeometryQuery::computePenetration(dir, depth, playerGeom, pxTr, otherGeom->sphereGeom, pxTr2);
					break;
				case hm::GeometryType::Box:
					isPenetrating = PxGeometryQuery::computePenetration(dir, depth, playerGeom, pxTr, otherGeom->boxGeom, pxTr2);
					break;
				case hm::GeometryType::Capsule:
					isPenetrating = PxGeometryQuery::computePenetration(dir, depth, playerGeom, pxTr, otherGeom->capsuleGeom, pxTr2);
					break;
				case hm::GeometryType::Plane:
					isPenetrating = PxGeometryQuery::computePenetration(dir, depth, playerGeom, pxTr, otherGeom->planeGeom, pxTr2);
					break;
				case hm::GeometryType::Mesh:
					isPenetrating = PxGeometryQuery::computePenetration(dir, depth, playerGeom, pxTr, otherGeom->triangleGeom, pxTr2);
					break;
				}

				if (true == isPenetrating && depth > 0.05f)
				{
					Vec3 offset = dir * (depth - 0.025f);
					Vec3 fixedPos = PLAYER->GetTransform()->GetPosition();
					PLAYER->GetTransform()->SetPosition(fixedPos + offset);
				}
			}
		}
	}
}

