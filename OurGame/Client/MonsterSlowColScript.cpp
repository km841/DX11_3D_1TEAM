#include "pch.h"
#include "MonsterSlowColScript.h"
#include "GameObject.h"
#include "Engine.h"
#include "TimerObject.h"
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
#include "MonsterSlowObject.h"

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

MonsterSlowColScript::MonsterSlowColScript()
{
	timer.SetEndTime(0.2f);
	SumScale = 6.f;
	Count = 0;
}

void MonsterSlowColScript::Initialize()
{
	timer.Start();
}

void MonsterSlowColScript::FixedUpdate()
{
	timer.Update();

	Transform* pTr = GetTransform();
	RigidBody* pRb = GetRigidBody();
	Vec3 ColSize = pRb->GetGeometrySize();
	Vec3 TextureSize = pTr->GetScale();

	if (timer.IsFinished() && Count < 6) //지정된시간에 + 카운트 갯수만큼 스케일 키우기
	{
		timer.Stop();
		ColSize.x += (SumScale - Count);
		ColSize.z += (SumScale - Count);
		TextureSize.x += (SumScale - Count);
		TextureSize.z += (SumScale - Count);



		pRb->SetGeometrySize(ColSize);
		pTr->SetScale(TextureSize);
		timer.Start();
		Count++;
	}

	if (Count >= 6)
	{
		if (TextureSize.x > 15.f)
		{
			SceneType eSceneType = GET_SINGLE(SceneManager)->GetActiveScene()->GetSceneType();
			GET_SINGLE(EventManager)->PushDeleteGameObjectEvent(eSceneType, GetGameObject());
			return;
		}
		if (TextureSize.x > 14.f)
		{
			static_cast<MonsterSlowObject*>(GetGameObject())->SetColCheck(true);
		}
		ColSize.x += 0.2f;
		ColSize.z += 0.2f;
		TextureSize.x += 0.2f;
		TextureSize.z += 0.2f;



		pRb->SetGeometrySize(ColSize);
		pTr->SetScale(TextureSize);

	
	}
	else 
	{
		ColSize.x -= 0.3f;
		ColSize.z -= 0.3f;
		TextureSize.x -= 0.3f;
		TextureSize.z -= 0.3f;



		pRb->SetGeometrySize(ColSize);
		pTr->SetScale(TextureSize);

	}

}

Component* MonsterSlowColScript::Clone(GameObject* _pGameObject)
{
	return _pGameObject->AddComponent(new MonsterSlowColScript);
}
