#include "pch.h"
#include "ArrowScript.h"
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
ArrowScript::ArrowScript()
{
}

void ArrowScript::Initialize()
{
}

void ArrowScript::FixedUpdate()
{
	Player* pPlayer = Player::GetPlayer(); // 플레이어*
	Animator* pAni = pPlayer->GetAnimator(); // 플레이어 애니메이션
	Transform* pPlyer_Tr = pPlayer->GetTransform(); //플레이어 트랜스폼
	DirectionEvasion eDir = pPlayer->GetDirectioninfo(); // 플레이어 8방향 상태 가져오는거
	mPlayerStateNum; //플레이어 상태FSM

	Transform* pTr = GetTransform(); // 화살 트랜스폼
	GameObject* pObj = GetGameObject(); // 화살 오브젝트


}

void ArrowScript::SetPlayerState(PlayerState _eStateNum)
{
}

Component* ArrowScript::Clone(GameObject* _pGameObject)
{
	return _pGameObject->AddComponent(new ArrowScript);
}
