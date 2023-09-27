#include "pch.h"
#include "LadderCollider.h"

LadderCollider::LadderCollider()
	: GameObject(LayerType::Ladder)
{
}

LadderCollider::~LadderCollider()
{
}

void LadderCollider::Initialize()
{
	GameObject::Initialize();
}

void LadderCollider::Update()
{
	GameObject::Update();
}

void LadderCollider::FixedUpdate()
{
	GameObject::FixedUpdate();
}

void LadderCollider::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void LadderCollider::Render()
{
	GameObject::Render();
}

void LadderCollider::Destroy()
{
	GameObject::Destroy();

}
