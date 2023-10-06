#include "pch.h"
#include "Grimace_ProjectTile.h"
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
#include "Mirror_ProjectTile.h"

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


Grimace_ProjectTile::Grimace_ProjectTile()
{
	mHP = 1.f;
	mSpeed = 8.f;
	mAttackDamage = 1;
}

Grimace_ProjectTile::~Grimace_ProjectTile()
{
}

void Grimace_ProjectTile::Initialize()
{
	Monster_ProjectTile::Initialize();
}

void Grimace_ProjectTile::Update()
{
	Monster_ProjectTile::Update();
}

void Grimace_ProjectTile::FixedUpdate()
{
	if(isbool == false)
		FollowPos(); //몬스터가 플레이어 따라가는 함수
	Monster_ProjectTile::FixedUpdate();
}

void Grimace_ProjectTile::FinalUpdate()
{
	Monster_ProjectTile::FinalUpdate();
}

void Grimace_ProjectTile::Render()
{
	Monster_ProjectTile::Render();
}

void Grimace_ProjectTile::Destroy()
{
	Monster_ProjectTile::Destroy();
}

void Grimace_ProjectTile::OnCollisionEnter(Collider* _pOtherCollider)
{
	
}

void Grimace_ProjectTile::OnCollisionStay(Collider* _pOtherCollider)
{
}

void Grimace_ProjectTile::OnCollisionExit(Collider* _pOtherCollider)
{
}

void Grimace_ProjectTile::OnTriggerEnter(Collider* _pOtherCollider)
{
	if (LayerType::Player == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		SceneType eSceneType = GET_SINGLE(SceneManager)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->PushDeleteGameObjectEvent(eSceneType, this);
	}
	if (LayerType::PlayerCol == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		isbool = true;
		Mirror();
	}
	
}

void Grimace_ProjectTile::OnTriggerStay(Collider* _pOtherCollider)
{

}

void Grimace_ProjectTile::OnTriggerExit(Collider* _pOtherCollider)
{
}

void Grimace_ProjectTile::FollowPos()
{
	Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
	Vec3 myPos = GetTransform()->GetPosition();
	Vec3 myRot = GetTransform()->GetRotation();
	Vec3 scale = GetRigidBody()->GetGeometrySize();

	Vec3 dir = playerPos - myPos;

	dir.Normalize();
	Vec3 Ve = dir * mSpeed;

	GetRigidBody()->SetVelocity(Ve); //따라오게 만드는 코드
}

void Grimace_ProjectTile::Mirror()
{
	

	Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
	Vec3 myPos = GetTransform()->GetPosition();
	Vec3 myRot = GetTransform()->GetRotation();
	Vec3 scale = GetRigidBody()->GetGeometrySize();

	Vec3 dir = playerPos - myPos;

	dir.Normalize();
	Vec3 Ve = dir * mSpeed;



	PhysicsInfo physicsInfo;
	physicsInfo.eActorType = ActorType::Kinematic;
	physicsInfo.eGeometryType = GeometryType::Box;
	physicsInfo.size = Vec3(0.3f, 4.3f, 0.3f);

	Mirror_ProjectTile* pProjectTile = Factory::CreateObjectHasPhysical<Mirror_ProjectTile>(myPos, physicsInfo, L"Deferred_CullNone", L"..\\Resources\\FBX\\Monster\\_DROP_SOUL50.fbx");
	pProjectTile->GetTransform()->SetScale(Vec3(0.5f, 0.5f, 0.5f));
	pProjectTile->GetTransform()->SetPosition(GetTransform()->GetPosition());
	pProjectTile->GetTransform()->SetRotation(Vec3(0.f, 0.f, 0.f));

	pProjectTile->GetMeshRenderer()->GetMaterial()->SetBloom(true, 0);
	pProjectTile->GetMeshRenderer()->GetMaterial()->SetBloomPower(3.f, 0);
	pProjectTile->GetMeshRenderer()->GetMaterial()->SetBloomColor(Vec4(0.f, 1.f, 0.f, 1.f));

	pProjectTile->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_X, false);
	pProjectTile->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_Z, false);
	pProjectTile->GetRigidBody()->SetVelocity(-Ve);
	pProjectTile->Initialize();

	GET_SINGLE(SceneManager)->GetActiveScene()->AddGameObject(pProjectTile);

	MapType type = GET_SINGLE(SceneManager)->GetActiveScene()->GetSceneType();
	GET_SINGLE(EventManager)->PushDeleteGameObjectEvent(type, static_cast<GameObject*>(this));
	
}

void Grimace_ProjectTile::FollowRot()
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
