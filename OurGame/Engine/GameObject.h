#pragma once
#include "Object.h"
#include "Component.h"
#include "MonoBehavior.h"

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
	class Animator;
	class UIText;
	class AI;
	class Mirror;
	class AudioSound;

	class GameObject :
		public Object
	{
	public:
		GameObject(LayerType _eLayerType);
		GameObject(GameObject* _pOther);
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();
		virtual void Destroy();

		template<typename T, typename ... Types>
		T* Clone(Types ... _args)
		{
			T* pObject = new T(_args...);
			for (int i = 0; i < FIXED_COMPONENT_COUNT; ++i)
			{
				if (nullptr != mComponents[i])
					mComponents[i]->Clone(pObject);
			}

			for (int i = 0; i < mScripts.size(); ++i)
			{
				mScripts[i]->Clone(pObject);
			}

			pObject->meObjectType = meObjectType;
			pObject->mbCheckFrustum = mbCheckFrustum;
			pObject->mbEnable = mbEnable;
			pObject->mbDontDestroy = mbDontDestroy;
			// GameObject가 가지는 변수가 많아지면 여기 추가해줘야 함

			return pObject;
		}

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
		Animator* GetAnimator();
		UIText* GetUIText();
		AI* GetAI();
		Mirror* GetMirror();
		AudioSound* GetAudioSound();
		GameObject* GetGameObject() { return this; }

		LayerType GetLayerType() { return meLayerType; }

		/* DontDestroyObject는 게임에 독립적으로 존재해야 하므로 구별하기 위한 이름을 필수적으로 부여한다. */
		void SetDontDestroyObject(const wstring& _name);
		bool IsDontDestroy() { return mbDontDestroy; }

		virtual void Enable();
		virtual void Disable();
		bool IsEnable() { return mbEnable; }

		/* Frustum Culling을 적용받을 것인지를 세팅 */
		void SetFrustumCheckFlag(bool _bFlag) { mbCheckFrustum = _bFlag; }
		bool IsFrustumCheck() { return mbCheckFrustum; }

		/* 물리적 객체인지를 검사하는 함수 */
		bool IsPhysicsObject();

		void SetShader(const wstring& _shaderName);

		void DrawShadow(bool _bFlag) { mbShadow = _bFlag; }
		bool IsDrawShadow() { return mbShadow; }

		bool IsReflect() { return mbReflect; }
		void SetReflect(bool _bFlag) { mbReflect = _bFlag; }

		void SetMotionBlur(bool _bFlag) { mbMotionBlur = _bFlag; }
		bool IsMotionBlur() { return mbMotionBlur; }

		const std::vector<MonoBehavior*>& GetScripts() { return mScripts; }

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


		/* 
		* 타입을 템플릿 매개변수로 넘기면 타입에 맞는 스크립트를 찾아서 반환하는 함수
		*/
		template<typename T>
		T* GetScript()
		{
			for (auto pScript : mScripts)
			{
				T* pPtr = dynamic_cast<T*>(pScript);
				if (nullptr != pPtr)
					return pPtr;
			}

			return nullptr;
		}

		virtual void OnCollisionEnter(Collider* pOtherCollider) {}
		virtual void OnCollisionStay(Collider* pOtherCollider) {}
		virtual void OnCollisionExit(Collider* pOtherCollider) {}

		virtual void OnTriggerEnter(Collider* pOtherCollider) {}
		virtual void OnTriggerStay(Collider* pOtherCollider) {}
		virtual void OnTriggerExit(Collider* pOtherCollider) {}

		bool IsRaysCollide(const Vec3& _origin, const Vec3& _dir, LayerType _eLayerType, float _length);

	private:
		LayerType                                     meLayerType;
		std::array<Component*, FIXED_COMPONENT_COUNT> mComponents;
		std::vector<MonoBehavior*>					  mScripts;
		
	protected:
		bool mbDontDestroy;
		bool mbEnable;
		bool mbCheckFrustum;
		bool mbShadow;
		bool mbReflect;
		bool mbMotionBlur;
	};
}


