#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "MonoBehavior.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Engine.h"
#include "Resources.h"
#include "AI.h"
#include "UIText.h"
#include "Mirror.h"
#include "AudioSound.h"
#include "CollisionManager.h"
#include "SceneManager.h"

namespace hm
{
	GameObject::GameObject(LayerType _eLayerType)
		: Object(ObjectType::GameObject)
		, meLayerType(_eLayerType)
		, mComponents{}
		, mbDontDestroy(false)
		, mbEnable(true)
		, mbCheckFrustum(true)
		, mbShadow(true)
		, mbReflect(true)
		, mbMotionBlur(false)
	{
	}

	GameObject::GameObject(GameObject* _pOther)
		: Object(_pOther->meObjectType)
	{
	}

	GameObject::~GameObject()
	{
		if (true == IsPhysicsObject())
			gpEngine->GetPhysics()->RemoveActor(this);

		for (int i = 0; i < FIXED_COMPONENT_COUNT; ++i)
		{
			SAFE_DELETE(mComponents[i]);
		}

		for (size_t i = 0; i < mScripts.size(); ++i)
		{
			SAFE_DELETE(mScripts[i]);
		}

		mScripts.clear();
	}

	void GameObject::Initialize()
	{
		for (Component* pComponent : mComponents)
		{
			if (nullptr != pComponent)
				pComponent->Initialize();
		}

		for (MonoBehavior* pScript : mScripts)
		{
			if (nullptr != pScript)
				pScript->Initialize();
		}

	}
	void GameObject::Update()
	{
		for (Component* pComponent : mComponents)
		{
			if (nullptr != pComponent)
				pComponent->Update();
		}

		for (MonoBehavior* pScript : mScripts)
		{
			if (nullptr != pScript)
				pScript->Update();
		}
	}
	void GameObject::FixedUpdate()
	{
		for (Component* pComponent : mComponents)
		{
			if (nullptr != pComponent)
				pComponent->FixedUpdate();
		}

		for (MonoBehavior* pScript : mScripts)
		{
			if (nullptr != pScript)
				pScript->FixedUpdate();
		}
	}
	void GameObject::FinalUpdate()
	{
		for (Component* pComponent : mComponents)
		{
			if (nullptr != pComponent)
				pComponent->FinalUpdate();
		}

		for (MonoBehavior* pScript : mScripts)
		{
			if (nullptr != pScript)
				pScript->FinalUpdate();
		}
	}
	void GameObject::Render()
	{
		for (Component* pComponent : mComponents)
		{
			if (nullptr != pComponent)
				pComponent->Render();
		}

		for (MonoBehavior* pScript : mScripts)
		{
			if (nullptr != pScript)
				pScript->Render();
		}
	}
	void GameObject::Destroy()
	{
		for (Component* pComponent : mComponents)
		{
			if (nullptr != pComponent)
				pComponent->Destroy();
		}

		for (MonoBehavior* pScript : mScripts)
		{
			if (nullptr != pScript)
				pScript->Destroy();
		}
	}


	Component* GameObject::GetFixedComponent(ComponentType _eComponentType)
	{
		this;
		int index = static_cast<int>(_eComponentType);
		AssertEx(FIXED_COMPONENT_COUNT > index, L"GameObject::GetFixedComponent() - 잘못된 컴포넌트 타입 전달");
		return mComponents[index];
	}
	Transform* GameObject::GetTransform()
	{
		return static_cast<Transform*>(GetFixedComponent(ComponentType::Transform));
	}
	Camera* GameObject::GetCamera()
	{
		return static_cast<Camera*>(GetFixedComponent(ComponentType::Camera));
	}
	MeshRenderer* GameObject::GetMeshRenderer()
	{
		return static_cast<MeshRenderer*>(GetFixedComponent(ComponentType::MeshRenderer));
	}
	Light* GameObject::GetLight()
	{
		return static_cast<Light*>(GetFixedComponent(ComponentType::Light));
	}
	ParticleSystem* GameObject::GetParticleSystem()
	{
		return static_cast<ParticleSystem*>(GetFixedComponent(ComponentType::ParticleSystem));
	}
	Collider* GameObject::GetCollider()
	{
		return static_cast<Collider*>(GetFixedComponent(ComponentType::Collider));
	}
	RigidBody* GameObject::GetRigidBody()
	{
		return static_cast<RigidBody*>(GetFixedComponent(ComponentType::RigidBody));
	}
	Animator* GameObject::GetAnimator()
	{
		return static_cast<Animator*>(GetFixedComponent(ComponentType::Animator));
	}

	UIText* GameObject::GetUIText()
	{
		return static_cast<UIText*>(GetFixedComponent(ComponentType::UIText));
	}

	AI* GameObject::GetAI()
	{
		return static_cast<AI*>(GetFixedComponent(ComponentType::Ai));
	}

	Mirror* GameObject::GetMirror()
	{
		return static_cast<Mirror*>(GetFixedComponent(ComponentType::Mirror));
	}

	AudioSound* GameObject::GetAudioSound()
	{
		return static_cast<AudioSound*>(GetFixedComponent(ComponentType::AudioSound));
	}

	void GameObject::Enable()
	{
		mbEnable = true;
		if (true == IsPhysicsObject())
		{
			GetRigidBody()->SetSimulationShapeFlag(mbEnable);
		}
	}

	void GameObject::Disable()
	{
		mbEnable = false;
		if (true == IsPhysicsObject())
		{
			GetRigidBody()->SetSimulationShapeFlag(mbEnable);

			ActorType eActorType = GetRigidBody()->GetActorType();
			if (ActorType::Kinematic == eActorType)
			{
				GET_SINGLE(CollisionManager)->ClearAllCollisionForObject(this);
			}
		}
	}

	void GameObject::SetDontDestroyObject(const wstring& _name)
	{
		mbDontDestroy = true;
		mName = _name;
	}
	bool GameObject::IsPhysicsObject()
	{
		RigidBody* pRigidBody = GetRigidBody();
		if (nullptr == pRigidBody)
			return false;

		return pRigidBody->IsAppliedPhysics();
	}

	void GameObject::SetShader(const wstring& _shaderName)
	{
		shared_ptr<Shader> pShader = GET_SINGLE(Resources)->Get<Shader>(_shaderName);
		AssertEx(nullptr != GetMeshRenderer(), L"GameObject::SetShader() - 그려지지 않는 물체에 대한 셰이더 세팅");
		AssertEx(nullptr != GetMeshRenderer()->GetMaterial(), L"GameObject::SetShader() - 재질이 존재하지 않는 물체에 대한 셰이더 세팅");
		
		GetMeshRenderer()->GetMaterial()->SetShader(pShader);
	}
	bool GameObject::IsRaysCollide(const Vec3& _origin, const Vec3& _dir, LayerType _eLayerType, float _length)
	{
		AssertEx(IsPhysicsObject(), L"GameObject::IsRaysCollide - this가 물리적 객체가 아님");
		const auto& gameObjects = GET_SINGLE(SceneManager)->GetActiveScene()->GetGameObjects(_eLayerType);
		Vec3 normDir = _dir;
		normDir.Normalize();
		for (int i = 0; i < gameObjects.size(); ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (gameObjects[i]->GetCollider())
				{
					if (GetCollider()->Raycast(_origin, normDir, gameObjects[i]->GetCollider(), _length))
					{
						return true;
					}
				}
			}
		}

		return false;
	}
}

