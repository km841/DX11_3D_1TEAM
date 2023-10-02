#include "pch.h"
#include "Mage_ProjectTile.h"
#include "Engine.h"
#include "AI.h"
#include "ChangeStateTask.h"
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
#include "Npc.h"
#include "Monster.h"
#include "SwordHeavyEffect.h"
#include "Ladder.h"
#include "LadderCollider.h"

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
#include "MageColScript.h"

/* Event */
#include "SceneChangeEvent.h"
#include "EventManager.h"
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


Mage_ProjectTile::Mage_ProjectTile()
{
	mHP = 1.f; 
	mSpeed = 2.f;
	mAttackDamage = 1;
}

Mage_ProjectTile::~Mage_ProjectTile()
{
}

void Mage_ProjectTile::Initialize()
{
	
	Monster_ProjectTile::Initialize();
}

void Mage_ProjectTile::Update()
{
	Monster_ProjectTile::Update();
}

void Mage_ProjectTile::FixedUpdate()
{
	FollowPos(); //몬스터가 플레이어 따라가는 함수

	
	Monster_ProjectTile::FixedUpdate();
}

void Mage_ProjectTile::FinalUpdate()
{
	Monster_ProjectTile::FinalUpdate();
}

void Mage_ProjectTile::Render()
{
	Monster_ProjectTile::Render();
}

void Mage_ProjectTile::Destroy()
{
	Monster_ProjectTile::Destroy();
}

void Mage_ProjectTile::OnCollisionEnter(Collider* _pOtherCollider)
{
}

void Mage_ProjectTile::OnCollisionStay(Collider* _pOtherCollider)
{
}

void Mage_ProjectTile::OnCollisionExit(Collider* _pOtherCollider)
{
}

void Mage_ProjectTile::OnTriggerEnter(Collider* _pOtherCollider)
{
	if (LayerType::Player == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		SceneType eSceneType = GET_SINGLE(SceneManager)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->PushDeleteGameObjectEvent(eSceneType, this);
	}
}

void Mage_ProjectTile::OnTriggerStay(Collider* _pOtherCollider)
{
}

void Mage_ProjectTile::OnTriggerExit(Collider* _pOtherCollider)
{
}

void Mage_ProjectTile::FollowPos()
{
	Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
	Vec3 myPos = GetTransform()->GetPosition();
	Vec3 myRot = GetTransform()->GetRotation();
	Vec3 scale = GetRigidBody()->GetGeometrySize();

	Vec3 dir = playerPos - myPos;

	dir.Normalize();
	//dir.y = 0;
	Vec3 Ve = dir * mSpeed;

	GetRigidBody()->SetVelocity(Ve); //따라오게 만드는 코드
}

void Mage_ProjectTile::FollowRot()
{
	Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
	Vec3 myPos = GetTransform()->GetPosition();
	Vec3 myRot = GetTransform()->GetRotation();
	Vec3 scale = GetRigidBody()->GetGeometrySize();
	Transform* pTr = GetTransform();


	Vec3 dir = playerPos - myPos;
	dir.Normalize();

	Vec3 rot = Vec3(0, 0, -1);
	double angleRadian = atan2(dir.x, dir.z) - atan2(rot.x, rot.z);
	float angleDegree = static_cast<float>(angleRadian) * 180.f / XM_PI;

	if (angleDegree < 0.f)
		angleDegree += 360.f;

	pTr->SetRotation(Vec3(-90.f, 0.f, angleDegree));
}
