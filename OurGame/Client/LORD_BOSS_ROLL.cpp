#include "pch.h"
#include "LORD_BOSS_ROLL.h"
#include "AI.h"

#include "ChangeStateCondition.h"
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


LORD_BOSS_ROLL::LORD_BOSS_ROLL()
{
	mMaxHP = 50.f;
	mHP = mMaxHP; // 피통
	Health = (mHP / mMaxHP) * 100;

	mAttackDamage = 1; // 공격력
}

LORD_BOSS_ROLL::~LORD_BOSS_ROLL()
{
}

void LORD_BOSS_ROLL::SetBehaviorTree()
{
}

void LORD_BOSS_ROLL::Initialize()
{
	Monster::Initialize();

	Animator* pAnimator = GetAnimator();
	pAnimator->SetLoop(1, true);
}

void LORD_BOSS_ROLL::Update()
{
	Monster::Update();
}

void LORD_BOSS_ROLL::FixedUpdate()
{
	Monster::FixedUpdate();
}

void LORD_BOSS_ROLL::FinalUpdate()
{
	Monster::FinalUpdate();
}

void LORD_BOSS_ROLL::Render()
{
	Monster::Render();
}

void LORD_BOSS_ROLL::Destroy()
{
	Monster::Destroy();
}

void LORD_BOSS_ROLL::OnCollisionEnter(Collider* _pOtherCollider)
{

}

void LORD_BOSS_ROLL::OnCollisionStay(Collider* _pOtherCollider)
{
}

void LORD_BOSS_ROLL::OnCollisionExit(Collider* _pOtherCollider)
{
}

void LORD_BOSS_ROLL::OnTriggerEnter(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		if (mGroundCount == 0)
		{
			GetRigidBody()->RemoveGravity();
			GetRigidBody()->SetVelocity(Vec3::Zero);
		}

		mGroundCount++;
	}
}

void LORD_BOSS_ROLL::OnTriggerStay(Collider* _pOtherCollider)
{
}

void LORD_BOSS_ROLL::OnTriggerExit(Collider* _pOtherCollider)
{
	if (LayerType::Ground == _pOtherCollider->GetGameObject()->GetLayerType())
	{
		--mGroundCount;

		if (0 == mGroundCount)
			GetRigidBody()->ApplyGravity();
	}
}
