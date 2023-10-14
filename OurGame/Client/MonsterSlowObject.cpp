#include "pch.h"
#include "MonsterSlowObject.h"
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
 /*State ¸ðÀ½*/
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
MonsterSlowObject::MonsterSlowObject()
	: GameObject(LayerType::MonsterSlowCol)
{
}

MonsterSlowObject::~MonsterSlowObject()
{
}

void MonsterSlowObject::Initialize()
{
	GameObject::Initialize();
}

void MonsterSlowObject::Update()
{
	GameObject::Update();
}

void MonsterSlowObject::FixedUpdate()
{
	GameObject::FixedUpdate();
}

void MonsterSlowObject::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void MonsterSlowObject::Render()
{
	GameObject::Render();
}

void MonsterSlowObject::Destroy()
{
	GameObject::Destroy();
}

void MonsterSlowObject::OnCollisionEnter(Collider* _pOtherCollider)
{
}

void MonsterSlowObject::OnCollisionStay(Collider* _pOtherCollider)
{
}

void MonsterSlowObject::OnCollisionExit(Collider* _pOtherCollider)
{
}

void MonsterSlowObject::OnTriggerEnter(Collider* _pOtherCollider)
{
}

void MonsterSlowObject::OnTriggerStay(Collider* _pOtherCollider)
{
}

void MonsterSlowObject::OnTriggerExit(Collider* _pOtherCollider)
{
}
