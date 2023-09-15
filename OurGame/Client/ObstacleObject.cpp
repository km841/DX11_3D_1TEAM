#include "pch.h"
#include "ObstacleObject.h"

namespace hm
{
	ObstacleObject::ObstacleObject()
		: GameObject(LayerType::Obstacle)
	{
	}
	ObstacleObject::~ObstacleObject()
	{
	}
	void ObstacleObject::Initialize()
	{
		GameObject::Initialize();
	}
	void ObstacleObject::Update()
	{
		GameObject::Update();
	}

	void ObstacleObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void ObstacleObject::FinalUpdate()
	{
		GameObject::FinalUpdate();
	}

	void ObstacleObject::Render()
	{
		GameObject::Render();
	}

	void ObstacleObject::Destroy()
	{
		GameObject::Destroy();
	}
}
