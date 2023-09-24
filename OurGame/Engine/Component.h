#pragma once
#include "Object.h"

namespace hm
{
	class GameObject;
	class MonoBehavior;
	class Transform;
	class Camera;
	class MeshRenderer;
	class Light;
	class ParticleSystem;
	class Collider;
	class RigidBody;
	class Animator;
	class AI;

	enum class ComponentType
	{
		Light,
		Animator,
		Transform,
		DebugRenderer,
		MeshRenderer,
		RigidBody,
		Movement,
		Camera,
		Collider,
		NavAgent,
		Ai,
		ParticleSystem,
		SoundListener,
		SoundSource,
		UI,
		// ...
		MonoBehavior,
		End,
	};

	enum
	{
		FIXED_COMPONENT_COUNT = static_cast<int>(ComponentType::End) - 1,
	};

	class Component :
		public Object
	{
	public:
		Component(ComponentType _eType);
		virtual ~Component();

		virtual void Initialize() { }
		virtual void Start() { }
		virtual void Update() { }
		virtual void FixedUpdate() { }
		virtual void FinalUpdate() { }
		virtual void Render() { }
		virtual Component* Clone(GameObject* _pGameObject) = 0;

		ComponentType GetComponentType() const { return meComponentType; }
		GameObject* GetGameObject() { return mpGameObject; }

		Transform* GetTransform();
		Camera* GetCamera();
		MeshRenderer* GetMeshRenderer();
		Light* GetLight();
		ParticleSystem* GetParticleSystem();
		Collider* GetCollider();
		RigidBody* GetRigidBody();
		Animator* GetAnimator();
		AI* GetAI();

		bool IsPhysicsObject();

	private:
		friend class GameObject;
		void SetGameObject(GameObject* _pGameObject) { mpGameObject = _pGameObject; }

	protected:
		ComponentType meComponentType;
		GameObject* mpGameObject;
	};
}


