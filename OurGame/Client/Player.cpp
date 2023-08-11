#include "pch.h"
#include "Player.h"

Player::Player()
	: GameObject(LayerType::Player)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	GameObject::Initialize();
}

void Player::Update()
{
	GameObject::Update();
}

void Player::FixedUpdate()
{
	GameObject::FixedUpdate();
}

void Player::FinalUpdate()
{
	GameObject::FinalUpdate();
}

void Player::Render()
{
	GameObject::Render();
}

void Player::Destroy()
{
	GameObject::Destroy();
}
