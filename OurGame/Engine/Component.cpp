#include "pch.h"
#include "Component.h"
#include "Transform.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "MonoBehavior.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Animator.h"
#include "GameObject.h"
#include "AI.h"
#include "UIText.h"

namespace hm
{
	Component::Component(ComponentType _eType)
		: Object(ObjectType::Component)
		, meComponentType(_eType)
		, mpGameObject(nullptr)
	{
	}

	Component::~Component()
	{
	}
	Transform* Component::GetTransform()
	{
		return mpGameObject->GetTransform();
	}
	Camera* Component::GetCamera()
	{
		return mpGameObject->GetCamera();
	}
	MeshRenderer* Component::GetMeshRenderer()
	{
		return mpGameObject->GetMeshRenderer();
	}
	Light* Component::GetLight()
	{
		return mpGameObject->GetLight();
	}
	ParticleSystem* Component::GetParticleSystem()
	{
		return mpGameObject->GetParticleSystem();
	}
	Collider* Component::GetCollider()
	{
		return mpGameObject->GetCollider();
	}
	RigidBody* Component::GetRigidBody()
	{
		return mpGameObject->GetRigidBody();
	}
	Animator* Component::GetAnimator()
	{
		return mpGameObject->GetAnimator();
	}
	AI* Component::GetAI()
	{
		return mpGameObject->GetAI();
	}
	UIText* Component::GetUIText()
	{
		return mpGameObject->GetUIText();
	}
	bool Component::IsPhysicsObject()
	{
		return mpGameObject->IsPhysicsObject();
	}
}

