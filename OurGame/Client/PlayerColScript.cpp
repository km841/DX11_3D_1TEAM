#include "pch.h"
#include "PlayerColScript.h"
#include "GameObject.h"
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
#include "WallObject.h"
#include "Npc.h"
#include "Monster.h"
#include "Grandma.h"

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
#include "SwordHeavyEffect.h"
#include "PlayerSlashScript.h"
#include "OwnerFollowScript.h"
#include "AttackState.h"

/* Event */
#include "SceneChangeEvent.h"
PlayerColScript::PlayerColScript()
{
}

void PlayerColScript::Initialize()
{
}

void PlayerColScript::FixedUpdate()
{
	Player* pPlayer = Player::GetPlayer();


	Transform* pTr = GetTransform();
	DirectionEvasion eDir = pPlayer->GetDirectioninfo();
	OwnerFollowScript* pOFSc = GetGameObject()->GetScript<OwnerFollowScript>();
	{
		Vec3 Pos = ConvertDir(eDir);
		Pos.Normalize();
		pOFSc->SetOffset(Pos * 1.2f);
	}
	

	if (eDir == DirectionEvasion::FORWARD)
	{
		pTr->SetRotation(AXIS_Y, 180);
	}
	if (eDir == DirectionEvasion::BACKWARD)
	{
		pTr->SetRotation(AXIS_Y, 0);
	}
	if (eDir == DirectionEvasion::LEFT)
	{
		pTr->SetRotation(AXIS_Y, 90);
	}
	if (eDir == DirectionEvasion::RIGHT)
	{
		pTr->SetRotation(AXIS_Y, 270);
	}
	if (eDir == DirectionEvasion::TOPLEFT)
	{
		pTr->SetRotation(AXIS_Y, 135);
	}
	if (eDir == DirectionEvasion::TOPRIGHT)
	{
		pTr->SetRotation(AXIS_Y, 225);
	}
	if (eDir == DirectionEvasion::BOTTOMLEFT)
	{
		pTr->SetRotation(AXIS_Y, 45);
	}
	if (eDir == DirectionEvasion::BOTTOMRIGHT)
	{
		pTr->SetRotation(AXIS_Y, 315);
	}
}

Component* PlayerColScript::Clone(GameObject* _pGameObject)
{
    return _pGameObject->AddComponent(new PlayerColScript);

}
