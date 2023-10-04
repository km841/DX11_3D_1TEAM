#include "pch.h"
#include "Monster.h"
#include "MonsterHitScript.h"
#include "RenderManager.h"

namespace hm
{
	Monster::Monster()
		: GameObject(LayerType::Monster)
	{
	}

	Monster::~Monster()
	{
	}

	void Monster::TakeDamage(float _float)
	{
		mHP -= _float;
		MonsterHitScript* pScript = GetScript<MonsterHitScript>();
		AssertEx(nullptr != pScript, L"Factory::CreateMonster() 함수로 몬스터를 생성된 몬스터가 아님");

		pScript->HitBegin();
		GET_SINGLE(RenderManager)->AddCameraShakeEffect(0.1f, 0.02f);
	}

	void Monster::Initialize()
	{
		GameObject::Initialize();
		SetBehaviorTree();
	}

	void Monster::Update()
	{
		GameObject::Update();
	}

	void Monster::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Monster::FinalUpdate()
	{
		GameObject::FinalUpdate();
	}

	void Monster::Render()
	{
		GameObject::Render();
	}

	void Monster::Destroy()
	{
		GameObject::Destroy();
	}
}

