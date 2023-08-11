#include "pch.h"
#include "Ground.h"

namespace hm
{
	Ground::Ground()
		: GameObject(LayerType::Ground)
	{
	}

	Ground::~Ground()
	{
	}

	void Ground::Initialize()
	{
		GameObject::Initialize();
	}

	void Ground::Update()
	{
		GameObject::Update();
	}

	void Ground::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Ground::FinalUpdate()
	{
		GameObject::FinalUpdate();
	}

	void Ground::Render()
	{
		GameObject::Render();
	}

	void Ground::Destroy()
	{
		GameObject::Destroy();
	}

}
