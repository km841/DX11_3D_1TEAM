#include "pch.h"
#include "Npc.h"

Npc::Npc()
	: GameObject(LayerType::Npc)
{
}

Npc::~Npc()
{
}

void Npc::Initialize()
{
	GameObject::Initialize();
}

void Npc::Update()
{
	GameObject::Update();
}

void Npc::FixedUpdate()
{
	GameObject::FixedUpdate();
}

void Npc::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void Npc::Render()
{
	GameObject::Render();
}

void Npc::Destroy()
{
	GameObject::Destroy();
}
