#include "pch.h"
#include "Monster.h"

namespace hm
{
	Monster::Monster()
		: GameObject(LayerType::Monster)
	{
	}

	Monster::~Monster()
	{
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

