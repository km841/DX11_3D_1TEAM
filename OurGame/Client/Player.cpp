#include "pch.h"
#include "Player.h"
#include "Collider.h"
#include "RigidBody.h"

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

void Player::OnTriggerEnter(Collider* pOtherCollider)
{
	if (LayerType::Ground == pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->RemoveGravity();
		GetRigidBody()->SetVelocity(Vec3::Zero);
	}
}

void Player::OnTriggerStay(Collider* pOtherCollider)
{
}

void Player::OnTriggerExit(Collider* pOtherCollider)
{
	if (LayerType::Ground == pOtherCollider->GetGameObject()->GetLayerType())
	{
		GetRigidBody()->ApplyGravity();
	}
}
