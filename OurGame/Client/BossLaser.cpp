#include "pch.h"
#include "BossLaser.h"

namespace hm
{
	BossLaser::BossLaser(GameObject* _pBoss)
		: GameObject(LayerType::MonsterCol)
		, mpBoss(_pBoss)
	{
	}

	BossLaser::~BossLaser()
	{
	}

	void BossLaser::Initialize()
	{
		GameObject::Initialize();
	}

	void BossLaser::Update()
	{
		GameObject::Update();
	}

	void BossLaser::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void BossLaser::FinalUpdate()
	{
		GameObject::FinalUpdate();
	}

	void BossLaser::Render()
	{
		GameObject::Render();
	}

	void BossLaser::Destroy()
	{
		GameObject::Destroy();
	}
}

