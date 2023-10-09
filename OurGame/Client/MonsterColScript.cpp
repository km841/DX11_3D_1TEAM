#include "pch.h"
#include "MonsterColScript.h"
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

MonsterColScript::MonsterColScript()
	:OffSetPos(0.f,0.f,0.f)
{
}

void MonsterColScript::Initialize()
{
}

void MonsterColScript::FixedUpdate()
{
	Transform* pTr = GetTransform();
	Vec3 Pos = pTr->GetScale();

	float ratio = AniRatio;
	ratio -= StartRatio;
	ratio *= 10;
	ratio *= magn;
	if (ratio > 0.f && ratio<1.f)
	{
		Vec3 Scale = Lerp(Vec3(1.f, 1.f, 1.f), Vec3(EndScale), ratio);
		pTr->SetScale(Scale);
	}
	else
	{
		pTr->SetScale(Vec3(1.f, 1.f, 1.f));
	}

	
	OwnerFollowScript* pOFSc = GetGameObject()->GetScript<OwnerFollowScript>();
	pOFSc->SetOffset(OffSetPos);
	
}

Component* MonsterColScript::Clone(GameObject* _pGameObject)
{
	return _pGameObject->AddComponent(new MonsterColScript);
}
