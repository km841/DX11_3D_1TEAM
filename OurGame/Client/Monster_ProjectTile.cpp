#include "pch.h"
#include "Monster_ProjectTile.h"

hm::Monster_ProjectTile::Monster_ProjectTile()
	: GameObject(LayerType::Monster_ProjectTile)
{
}

hm::Monster_ProjectTile::~Monster_ProjectTile()
{
}

void hm::Monster_ProjectTile::Initialize()
{
	GameObject::Initialize();
}

void hm::Monster_ProjectTile::Update()
{
	GameObject::Update();
}

void hm::Monster_ProjectTile::FixedUpdate()
{
	GameObject::FixedUpdate();
}

void hm::Monster_ProjectTile::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void hm::Monster_ProjectTile::Render()
{
	GameObject::Render();
}

void hm::Monster_ProjectTile::Destroy()
{
	GameObject::Destroy();
}
