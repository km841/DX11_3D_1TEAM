#include "pch.h"
#include "ExplosionScript.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Timer.h"

namespace hm
{
	ExplosionScript::ExplosionScript(GameObject* _pBoss)
		: mpBoss(_pBoss)
		, mAccTime(0.f)
	{
	}
	void ExplosionScript::Initialize()
	{
	}
	void ExplosionScript::FixedUpdate()
	{
		mAccTime += DELTA_TIME;
		GetMeshRenderer()->GetMaterial()->SetFloat(0, mAccTime);

	}
	Component* ExplosionScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new ExplosionScript(mpBoss));
	}
}