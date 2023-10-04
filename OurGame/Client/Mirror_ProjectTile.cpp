#include "pch.h"
#include "Mirror_ProjectTile.h"
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

Mirror_ProjectTile::Mirror_ProjectTile()
	:GameObject(LayerType::PlayerCol)
{
	mHP = 1.f;
	mSpeed = 8.f;
	mAttackDamage = 1;
}

Mirror_ProjectTile::~Mirror_ProjectTile()
{
}

void Mirror_ProjectTile::Initialize()
{
	GameObject::Initialize();
}

void Mirror_ProjectTile::Update()
{
	GameObject::Update();
}

void Mirror_ProjectTile::FixedUpdate()
{
	//MirrorPos();
	GameObject::FixedUpdate();
}

void Mirror_ProjectTile::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void Mirror_ProjectTile::Render()
{
	GameObject::Render();
}

void Mirror_ProjectTile::Destroy()
{
	GameObject::Destroy();
}

void Mirror_ProjectTile::OnCollisionEnter(Collider* _pOtherCollider)
{
}

void Mirror_ProjectTile::OnCollisionStay(Collider* _pOtherCollider)
{
}

void Mirror_ProjectTile::OnCollisionExit(Collider* _pOtherCollider)
{
}

void Mirror_ProjectTile::OnTriggerEnter(Collider* _pOtherCollider)
{
	if (LayerType::Monster == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		SceneType eSceneType = GET_SINGLE(SceneManager)->GetActiveScene()->GetSceneType();
		GET_SINGLE(EventManager)->PushDeleteGameObjectEvent(eSceneType, this);
	}
}

void Mirror_ProjectTile::OnTriggerStay(Collider* _pOtherCollider)
{
}

void Mirror_ProjectTile::OnTriggerExit(Collider* _pOtherCollider)
{
}

void Mirror_ProjectTile::MirrorPos()
{
	Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
	Vec3 myPos = GetTransform()->GetPosition();
	Vec3 myRot = GetTransform()->GetRotation();
	Vec3 scale = GetRigidBody()->GetGeometrySize();

	Vec3 dir = playerPos - myPos;

	dir.Normalize();
	//dir.y = 0;
	Vec3 Ve = dir * mSpeed;

	GetRigidBody()->SetVelocity(-Ve); //따라오게 만드는 코드
	GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_X, false);
	GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_Z, false);
}
