#include "pch.h"
#include "BowScript.h"
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
BowScript::BowScript()
{
}

void BowScript::Initialize()
{
}

void BowScript::FixedUpdate()
{
	Player* pPlayer = Player::GetPlayer(); // 플레이어*
	Animator* pAni = pPlayer->GetAnimator(); // 플레이어 애니메이션
	Transform* pPlyer_Tr = pPlayer->GetTransform(); //플레이어 트랜스폼
	DirectionEvasion eDir = pPlayer->GetDirectioninfo(); // 플레이어 8방향 상태 가져오는거
	mPlayerStateNum; //플레이어 상태FSM

	Transform* pTr = GetTransform(); // 활 트랜스폼
	GameObject* pObj = GetGameObject(); // 활 오브젝트

	Vec3 Pos = pPlyer_Tr->GetPosition(); //플레이어 Pos
	Vec3 Rot = pTr->GetRotation(); // 활 회전 Rot

	if (eDir == DirectionEvasion::BACKWARD) {
		Pos.x -= 0.10;
		Pos.z -= 0.37;
		Pos.y += 0.25f;
		pTr->SetPosition(Pos);
		pTr->SetRotation(Vec3(0.f, 270.f, 0.f));

	}
	if (eDir == DirectionEvasion::FORWARD) {
		Pos.x += 0.10;
		Pos.z += 0.37;
		Pos.y += 0.25f;
		pTr->SetPosition(Pos);
		pTr->SetRotation(Vec3(0.f, 90.f, 0.f));
	}
	if (eDir == DirectionEvasion::LEFT) {
		Pos.x -= 0.37;
		Pos.z += 0.10;
		Pos.y += 0.25f;

		pTr->SetPosition(Pos);
		pTr->SetRotation(Vec3(0.f, 0.f, 0.f));
	}
	if (eDir == DirectionEvasion::RIGHT) {
		Pos.x += 0.37;
		Pos.z -= 0.10;
		Pos.y += 0.25f;

		pTr->SetPosition(Pos);
		pTr->SetRotation(Vec3(0.f, 180.f, 0.f));
	}

	if (eDir == DirectionEvasion::TOPLEFT) {
		Pos.x -= 0.10;
		Pos.z += 0.37;
		Pos.y += 0.25f;

		pTr->SetPosition(Pos);
		pTr->SetRotation(Vec3(0.f, 45.f, 0.f));
	}

	if (eDir == DirectionEvasion::TOPRIGHT) {
		Pos.x += 0.37;
		Pos.z += 0.10;
		Pos.y += 0.25f;

		pTr->SetPosition(Pos);
		pTr->SetRotation(Vec3(0.f, 135.f, 0.f));
	}

	if (eDir == DirectionEvasion::BOTTOMLEFT) {
		Pos.x -= 0.37;
		Pos.z -= 0.10;
		Pos.y += 0.25f;

		pTr->SetPosition(Pos);
		pTr->SetRotation(Vec3(0.f, 315.f, 0.f));
	}

	if (eDir == DirectionEvasion::BOTTOMRIGHT) {
		Pos.x += 0.10;
		Pos.z -= 0.37;
		Pos.y += 0.25f;

		pTr->SetPosition(Pos);
		pTr->SetRotation(Vec3(0.f,225.f, 0.f));
	}
}

void BowScript::SetPlayerState(PlayerState _eStateNum)
{
}

Component* BowScript::Clone(GameObject* _pGameObject)
{
	return _pGameObject->AddComponent(new BowScript);
}
