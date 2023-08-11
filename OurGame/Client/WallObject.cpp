#include "pch.h"
#include "WallObject.h"

namespace hm
{
	WallObject::WallObject()
		: GameObject(LayerType::WallObject)
	{
	}
	WallObject::~WallObject()
	{
	}
	void WallObject::Initialize()
	{
		GameObject::Initialize();
	}
	void WallObject::Update()
	{
		GameObject::Update();
	}

	void WallObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void WallObject::FinalUpdate()
	{
		GameObject::FinalUpdate();
	}

	void WallObject::Render()
	{
		GameObject::Render();
	}

	void WallObject::Destroy()
	{
		GameObject::Destroy();
	}
}