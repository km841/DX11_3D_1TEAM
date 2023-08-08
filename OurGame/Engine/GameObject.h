#pragma once
#include "Object.h"
#include "Component.h"

namespace hm
{
	class Component;
	class MonoBehavior;
	class Transform;
	class Camera;
	class MeshRenderer;
	class Light;
	class ParticleSystem;
	class Collider;
	class RigidBody;

	class GameObject :
		public Object
	{
	public:
		GameObject(LayerType _eLayerType);
		GameObject(std::vector<GameObject*> _gameObjects, LayerType _eLayerType);
		virtual ~GameObject();

		virtual void Initialize() const;
		virtual void Update() const;
		virtual void FixedUpdate() const;
		virtual void FinalUpdate() const;
		virtual void Render() const;
		virtual void Destroy() const;

		/* 전달받은 ComponentType을 통해 해당 인덱스에 맞는 컴포넌트를 반환하는 함수
		* _eComponentType : 가져올 컴포넌트의 타입
		*/
		Component* GetFixedComponent(ComponentType _eComponentType);
		Transform* GetTransform();
		Camera* GetCamera();
		MeshRenderer* GetMeshRenderer();
		Light* GetLight();
		ParticleSystem* GetParticleSystem();
		Collider* GetCollider();
		RigidBody* GetRigidBody();

		LayerType GetLayerType() { return meLayerType; }

		/* DontDestroyObject는 게임에 독립적으로 존재해야 하므로 구별하기 위한 이름을 필수적으로 부여한다. */
		void SetDontDestroyObject(const wstring& _name);
		bool IsDontDestroy() { return mbDontDestroy; }

		void Enable() { mbEnable = true; }
		void Disable() { mbEnable = false; }

		/* Frustum Culling을 적용받을 것인지를 세팅 */
		void SetFrustumCheckFlag(bool _bFlag) { mbCheckFrustum = _bFlag; }
		bool IsFrustumCheck() { return mbCheckFrustum; }

		/* 물리적 객체인지를 검사하는 함수 */
		bool IsPhysicsObject();

		/*
		* AddComponent(Component* _pComponent)
		* 게임 오브젝트에 컴포넌트를 추가하는 함수
		* 함수 내부에서 컴포넌트에 게임 오브젝트의 포인터를 전달한다.
		*/
		template<typename T>
		T* AddComponent(T* _pComponent = new T)
		{
			_pComponent->SetGameObject(this);
			int componentType = static_cast<int>(_pComponent->GetComponentType());

			if (FIXED_COMPONENT_COUNT > componentType)
			{
				mComponents[componentType] = _pComponent;
			}
			else
			{
				mScripts.push_back(reinterpret_cast<MonoBehavior*>(_pComponent));
			}

			return _pComponent;
		}

		virtual void OnCollisionEnter(Collider* pOtherCollider) {}
		virtual void OnCollisionStay(Collider* pOtherCollider) {}
		virtual void OnCollisionExit(Collider* pOtherCollider) {}

		virtual void OnTriggerEnter(Collider* pOtherCollider) {}
		virtual void OnTriggerStay(Collider* pOtherCollider) {}
		virtual void OnTriggerExit(Collider* pOtherCollider) {}

	private:
		LayerType                                     meLayerType;
		std::array<Component*, FIXED_COMPONENT_COUNT> mComponents;
		std::vector<MonoBehavior*>					  mScripts;
		
	protected:
		bool mbDontDestroy;
		bool mbEnable;
		bool mbCheckFrustum;
	};
}


