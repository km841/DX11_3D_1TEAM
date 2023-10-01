#include "pch.h"
#include "MageColScript.h"
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

MageColScript::MageColScript()
{
}

void MageColScript::Initialize()
{
}

void MageColScript::FixedUpdate()
{
	Vec3 playerPos = PLAYER->GetTransform()->GetPosition();
	Vec3 myPos = GetTransform()->GetPosition();
	Vec3 myRot = GetTransform()->GetRotation();
	Vec3 scale = GetRigidBody()->GetGeometrySize();

	Vec3 dir = playerPos - myPos;
	Vec3 Num = scale * dir;
	float offset = max(max(fabs(scale.x), fabs(scale.y)), fabs(scale.z));

	dir.Normalize();
	//dir.y = 0;

	Vec3 Ve = dir * 2;

	GetRigidBody()->SetVelocity(Ve); //따라오게 만드는 코드
}

Component* MageColScript::Clone(GameObject* _pGameObject)
{
    return _pGameObject->AddComponent(new MageColScript);

}
