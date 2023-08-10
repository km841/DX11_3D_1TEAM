#pragma once
#include "Component.h"

namespace hm
{
	class RigidBody :
		public Component
	{
	public:
		RigidBody();
		virtual ~RigidBody();

		virtual void Initialize();
		virtual void FinalUpdate();
		virtual void Destroy();

		virtual Component* Clone(GameObject* _pGameObject);

		void SetPhysical(const PhysicsInfo& _physicsInfo = PhysicsInfo());
		bool IsAppliedPhysics();

		PxActor* GetActor() { return mpActor; }

		template<typename T>
		inline T* GetActor() const
		{
			T* pActor = mpActor->is<T>();
			assert(pActor);
			return pActor;
		}

		void AddActorToScene();

		PxRigidDynamic* GetDynamicActor() { return GetActor<PxRigidDynamic>(); }
		PxRigidStatic* GetStaticActor() { return GetActor<PxRigidStatic>(); }
		PxTransform GetPhysicsTransform();
		void	    SetPhysicsTransform(PxTransform _transform);

		ActorType GetActorType() { return mPhysicsInfo.eActorType; }
		GeometryType GetGeometryType() { return mPhysicsInfo.eGeometryType; }
		Vec3 GetGeometrySize() { return mPhysicsInfo.size * 2.f; }
		const PxFilterData& GetFilterData() { return mPhysicsInfo.filterData; }
		void SetOtherLayerInFilterData(LayerType _eOtherLayer) { mPhysicsInfo.filterData.word1 |= 1 << static_cast<int>(_eOtherLayer); }

		void SetVelocity(const Vec3& _velocity);
		void SetVelocity(Axis _eAxis, float _velocity);
		void AddVelocity(const Vec3& _velocity);
		void AddVelocity(Axis _eAxis, float _velocity);
		void AddGravity();

		void SetMaxVelocity(float _maxVelocity);
		void CheckMaxVelocity();

		void ApplyGravity();
		void RemoveGravity();

		void SetLinearDamping(float _damping);
		void SetSimulationShapeFlag(bool _bFlag);
		void SetTriggerShapeFlag(bool _bFlag);

		void SetActorInSceneFlag(bool _bFlag);
		bool IsActorInScene() { return mbIsActorInScene; }

	private:
		void CreateBoxGeometry();
		void CreateCapsuleGeometry();
		void CreatePlaneGeometry();
		void CreateSphereGeometry();

	private:
		void CreateGeometry();
		void CreateShape();
		void CreateActor();
		void CreateMaterial();
		void InitializeActor();

	private:
		bool mbAppliedPhysics;
		bool mbAppliedGravity;
		bool mbIsActorInScene;
		PhysicsInfo mPhysicsInfo;

		PxActor* mpActor;
		PxShape* mpShape;
		PxMaterial* mpMaterial;

		Vec3 mVelocity;
		float mMaxVelocity;
	};
}


