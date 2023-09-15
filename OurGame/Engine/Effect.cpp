#include "pch.h"
#include "Effect.h"

namespace hm
{
	Effect::Effect()
		: GameObject(LayerType::Effect)
	{
	}

	Effect::~Effect()
	{
	}

	void Effect::Initialize()
	{
		GameObject::Initialize();
	}

	void Effect::Update()
	{
		GameObject::Update();
	}

	void Effect::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Effect::FinalUpdate()
	{
		GameObject::FinalUpdate();
	}

	void Effect::Render()
	{
		GameObject::Render();
	}

	void Effect::Destroy()
	{
		GameObject::Destroy();
	}

}
