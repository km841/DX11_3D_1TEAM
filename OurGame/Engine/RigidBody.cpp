#include "pch.h"
#include "RigidBody.h"
#include "Engine.h"
#include "Transform.h"
#include "GameObject.h"
#include "CollisionManager.h"

namespace hm
{
	RigidBody::RigidBody()
		: Component(ComponentType::RigidBody)
		, mbAppliedPhysics(false)
		, mbAppliedGravity(false)
		, mMaxVelocity(10.f)
		, mpActor(nullptr)
		, mpMaterial(nullptr)
		, mpShape(nullptr)
		, mbIsActorInScene(false)
	{
	}
	RigidBody::~RigidBody()
	{
		SAFE_DELETE(mPhysicsInfo.pGeometries);
	}
	void RigidBody::Initialize()
	{
		if (true == mbAppliedPhysics &&
			false == mbIsActorInScene &&
			nullptr != mpActor)
			gpEngine->GetPhysics()->AddActor(mpGameObject);
	}

	void RigidBody::FinalUpdate()
	{
		if (false == mbAppliedGravity)
			AddGravity();

		if (true == mbAppliedPhysics && ActorType::Static == mPhysicsInfo.eActorType)
			return;
		
		else
			GetTransform()->Move(mVelocity);
	}

	void RigidBody::Destroy()
	{
		if (true == mbAppliedPhysics)
		{
			PxRigidActor* pActor = mpActor->is<PxRigidActor>();
			pActor->userData = nullptr;
		}
	}

	Component* RigidBody::Clone(GameObject* _pGameObject)
	{
		RigidBody* pRigidBody = _pGameObject->AddComponent(new RigidBody);

		if (true == mbAppliedPhysics)
		{
			PhysicsInfo info = {};
			info.size = GetGeometrySize();
			info.eActorType = mPhysicsInfo.eActorType;
			info.eGeometryType = mPhysicsInfo.eGeometryType;
			info.massProperties = mPhysicsInfo.massProperties;
			
			pRigidBody->SetPhysical(info);
		}

		pRigidBody->SetVelocity(mVelocity);
		pRigidBody->SetMaxVelocity(mMaxVelocity);

		return pRigidBody;
	}

	void RigidBody::SetPhysical(const PhysicsInfo& _physicsInfo)
	{
		mPhysicsInfo = _physicsInfo;

		CreateMaterial();
		CreateGeometry();
		CreateActor();
		CreateShape();

		mbAppliedPhysics = true;
		InitializeActor();
	}

	bool RigidBody::IsAppliedPhysics()
	{
		return mbAppliedPhysics;
	}

	void RigidBody::AddActorToScene()
	{
		AssertEx(mbAppliedPhysics, L"RigidBody::AddActorToScene() - 물리가 들어가지 않은 오브젝트에 대한 AddActorToScene 호출");
		AssertEx(mpActor, L"RigidBody::AddActorToScene() - mpActor가 생성되지 않음");

		gpEngine->GetPhysics()->AddActor(mpGameObject);
		mbIsActorInScene = true;
	}

	PxTransform RigidBody::GetPhysicsTransform()
	{
		AssertEx(mbAppliedPhysics, L"RigidBody::GetPhysicsTransform() - 물리가 들어가지 않은 오브젝트에 대한 GetPhysicsTransform 호출");
		return GetActor<PxRigidActor>()->getGlobalPose();
	}

	void RigidBody::SetPhysicsTransform(PxTransform _transform)
	{
		_transform.p.z = -_transform.p.z;
		AssertEx(mbAppliedPhysics, L"RigidBody::SetPhysicsTransform() - 물리가 들어가지 않은 오브젝트에 대한 SetPhysicsTransform 호출");
		GetActor<PxRigidActor>()->setGlobalPose(_transform);
		
	}

	void RigidBody::SetVelocity(const Vec3& _velocity)
	{
		if (true == mbAppliedPhysics)
		{
			AssertEx(ActorType::Dynamic == mPhysicsInfo.eActorType, L"RigidBody::SetVelocity() - Dynamic Actor가 아닌 물체에 대한 SetVelocity() 호출 시도");
			GetDynamicActor()->setLinearVelocity(_velocity);
		}
		else
		{
			mVelocity = _velocity;
		}

		CheckMaxVelocity();
	}

	void RigidBody::SetVelocity(Axis _eAxis, float _velocity)
	{
		if (true == mbAppliedPhysics)
		{
			AssertEx(ActorType::Dynamic == mPhysicsInfo.eActorType, L"RigidBody::SetVelocity() - Dynamic Actor가 아닌 물체에 대한 SetVelocity() 호출 시도");
			Vec3 velocity = GetDynamicActor()->getLinearVelocity();
			switch (_eAxis)
			{
			case hm::AXIS_X:
				velocity.x = _velocity;
				break;
			case hm::AXIS_Y:
				velocity.y = _velocity;
				break;
			case hm::AXIS_Z:
				velocity.z = _velocity;
				break;
			}
			GetDynamicActor()->setLinearVelocity(velocity);

			mVelocity = velocity;
		}
		else
		{
			switch (_eAxis)
			{
			case hm::AXIS_X:
				mVelocity.x = _velocity;
				break;
			case hm::AXIS_Y:
				mVelocity.y = _velocity;
				break;
			case hm::AXIS_Z:
				mVelocity.z = _velocity;
				break;
			}
		}
		
		CheckMaxVelocity();
	}

	void RigidBody::AddVelocity(const Vec3& _velocity)
	{
		if (true == mbAppliedPhysics)
		{
			AssertEx(ActorType::Dynamic == mPhysicsInfo.eActorType, L"RigidBody::AddVelocity() - Dynamic Actor가 아닌 물체에 대한 SetVelocity() 호출 시도");
			Vec3 velocity = GetDynamicActor()->getLinearVelocity();
			velocity += _velocity;
			GetDynamicActor()->setLinearVelocity(velocity);
		}
		else
		{
			mVelocity = _velocity;
		}

		CheckMaxVelocity();
	}

	void RigidBody::AddVelocity(Axis _eAxis, float _velocity)
	{
		if (true == mbAppliedPhysics)
		{
			AssertEx(ActorType::Dynamic == mPhysicsInfo.eActorType, L"RigidBody::AddVelocity() - Dynamic Actor가 아닌 물체에 대한 SetVelocity() 호출 시도");
			Vec3 velocity = GetDynamicActor()->getLinearVelocity();
			switch (_eAxis)
			{
			case hm::AXIS_X:
				velocity.x += _velocity;
				break;
			case hm::AXIS_Y:
				velocity.y += _velocity;
				break;
			case hm::AXIS_Z:
				velocity.z += _velocity;
				break;
			}
			GetDynamicActor()->setLinearVelocity(velocity);
		}
		else
		{
			switch (_eAxis)
			{
			case hm::AXIS_X:
				mVelocity.x += _velocity;
				break;
			case hm::AXIS_Y:
				mVelocity.y += _velocity;
				break;
			case hm::AXIS_Z:
				mVelocity.z += _velocity;
				break;
			}
		}
		CheckMaxVelocity();
	}

	void RigidBody::AddGravity()
	{
		mVelocity += GLOBAL_GRAVITY;
	}

	void RigidBody::SetMaxVelocity(float _maxVelocity)
	{
		if (true == mbAppliedPhysics)
		{
			AssertEx(ActorType::Dynamic == mPhysicsInfo.eActorType, L"RigidBody::SetMaxVelocity() - Dynamic Actor가 아닌 물체에 대한 SetMaxVelocity() 호출 시도");
			GetDynamicActor()->setMaxLinearVelocity(_maxVelocity);
		}

		mMaxVelocity = _maxVelocity;
	}

	void RigidBody::CheckMaxVelocity()
	{
		mVelocity.x = mVelocity.x < 0.f ? max(mVelocity.x, -mMaxVelocity) : min(mVelocity.x, mMaxVelocity);
		mVelocity.y = mVelocity.y < 0.f ? max(mVelocity.y, -mMaxVelocity) : min(mVelocity.y, mMaxVelocity);
		mVelocity.z = mVelocity.z < 0.f ? max(mVelocity.z, -mMaxVelocity) : min(mVelocity.z, mMaxVelocity);
	}

	void RigidBody::ApplyGravity()
	{
		if (true == mbAppliedPhysics)
		{
			AssertEx(ActorType::Dynamic == mPhysicsInfo.eActorType, L"RigidBody::ApplyGravity() - Dynamic Actor가 아닌 물체에 대한 ApplyGravity() 호출 시도");
			GetDynamicActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);
		}

		mbAppliedGravity = true;
	}

	void RigidBody::RemoveGravity()
	{
		if (true == mbAppliedPhysics)
		{
			AssertEx(ActorType::Dynamic == mPhysicsInfo.eActorType, L"RigidBody::RemoveGravity() - Dynamic Actor가 아닌 물체에 대한 RemoveGravity() 호출 시도");
			GetDynamicActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
		}

		mbAppliedGravity = false;
	}

	void RigidBody::SetLinearDamping(float _damping)
	{
		AssertEx(ActorType::Dynamic == mPhysicsInfo.eActorType, L"RigidBody::SetLinearDamping() - Dynamic Actor가 아닌 물체에 대한 SetLinearDamping() 호출 시도");
		GetActor<PxRigidDynamic>()->setLinearDamping(_damping);
	}

	void RigidBody::SetSimulationShapeFlag(bool _bFlag)
	{
		AssertEx(mbAppliedPhysics, L"RigidBody::SetSimulationShapeFlag() - 물리가 들어가지 않은 오브젝트에 대한 SetSimulationShapeFlag 호출");
		mpShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, _bFlag);
	}

	void RigidBody::SetTriggerShapeFlag(bool _bFlag)
	{
		AssertEx(mbAppliedPhysics, L"RigidBody::SetTriggerShapeFlag() - 물리가 들어가지 않은 오브젝트에 대한 SetTriggerShapeFlag 호출");
		mpShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, _bFlag);
	}

	void RigidBody::SetActorInSceneFlag(bool _bFlag)
	{
		mbIsActorInScene = _bFlag;
	}

	void RigidBody::CreateBoxGeometry()
	{
		mPhysicsInfo.pGeometries = new Geometries(mPhysicsInfo.eGeometryType, mPhysicsInfo.size);
	}

	void RigidBody::CreateCapsuleGeometry()
	{
		mPhysicsInfo.pGeometries = new Geometries(mPhysicsInfo.eGeometryType, mPhysicsInfo.size.x, mPhysicsInfo.size.y);
	}

	void RigidBody::CreatePlaneGeometry()
	{
		mPhysicsInfo.pGeometries = new Geometries(mPhysicsInfo.eGeometryType);
	}

	void RigidBody::CreateSphereGeometry()
	{
		mPhysicsInfo.pGeometries = new Geometries(mPhysicsInfo.eGeometryType, mPhysicsInfo.size.x);
	}

	void RigidBody::CreateGeometry()
	{
		mPhysicsInfo.size /= 2.f;
		switch (mPhysicsInfo.eGeometryType)
		{
		case GeometryType::Box:
			CreateBoxGeometry();
			break;

		case GeometryType::Capsule:
			CreateCapsuleGeometry();
			break;

		case GeometryType::Sphere:
			CreateSphereGeometry();
			break;

		case GeometryType::Plane:
			CreatePlaneGeometry();
			break;
		}

		AssertEx(mPhysicsInfo.pGeometries, L"RigidBody::CreateGeometry() - Geometry 생성 실패");
	}

	void RigidBody::CreateShape()
	{
		switch (mPhysicsInfo.eGeometryType)
		{
		case GeometryType::Box:
			mpShape = PxRigidActorExt::createExclusiveShape(*mpActor->is<PxRigidActor>(), mPhysicsInfo.pGeometries->boxGeom, *mpMaterial);
			break;
		case GeometryType::Capsule:
			mpShape = PxRigidActorExt::createExclusiveShape(*mpActor->is<PxRigidActor>(), mPhysicsInfo.pGeometries->capsuleGeom, *mpMaterial);
			break;
		case GeometryType::Sphere:
			mpShape = PxRigidActorExt::createExclusiveShape(*mpActor->is<PxRigidActor>(), mPhysicsInfo.pGeometries->sphereGeom, *mpMaterial);
			break;
		case GeometryType::Plane:
			mpShape = PxRigidActorExt::createExclusiveShape(*mpActor->is<PxRigidActor>(), mPhysicsInfo.pGeometries->planeGeom, *mpMaterial);
			break;
		}

		AssertEx(mpShape, L"RigidBody::CreateShape() - Shape 생성 실패");
	}


	void RigidBody::CreateActor()
	{
		switch (mPhysicsInfo.eActorType)
		{
		case ActorType::Dynamic:
			mpActor = PHYSICS->createRigidDynamic(PxTransform(GetTransform()->GetPosition()));
			break;

		case ActorType::Static:
			mpActor = PHYSICS->createRigidStatic(PxTransform(GetTransform()->GetPosition()));
			break;

		case ActorType::Kinematic:
			mpActor = PHYSICS->createRigidDynamic(PxTransform(GetTransform()->GetPosition()));
			mpActor->is<PxRigidDynamic>()->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
			break;
		}

		AssertEx(mpActor, L"RigidBody::CreateActor() - Actor 생성 실패");
	}

	void RigidBody::CreateMaterial()
	{
		mpMaterial = PHYSICS->createMaterial(
			mPhysicsInfo.massProperties.staticFriction,
			mPhysicsInfo.massProperties.dynamicFriction,
			mPhysicsInfo.massProperties.restitution);
	}

	void RigidBody::InitializeActor()
	{
		PxRigidActor* pActor = mpActor->is<PxRigidActor>();
		pActor->userData = mpGameObject;

		mPhysicsInfo.filterData.word0 = 1 << static_cast<int>(mpGameObject->GetLayerType());
		std::bitset<LAYER_TYPE_COUNT> collisionGroup = GET_SINGLE(CollisionManager)->GetCollisionGroup(mpGameObject->GetLayerType());

		for (int i = 0; i < LAYER_TYPE_COUNT; ++i)
		{
			if (true == collisionGroup[i])
				mPhysicsInfo.filterData.word1 |= 1 << i;
		}

		mpShape->setSimulationFilterData(mPhysicsInfo.filterData);
		PxVec3 myPos = GetTransform()->GetPosition();
		pActor->setGlobalPose(PxTransform(myPos));

		switch (mPhysicsInfo.eActorType)
		{
		case ActorType::Static:
			break;
		case ActorType::Dynamic:
			ApplyGravity();
			break;
		case ActorType::Kinematic:
			SetSimulationShapeFlag(false);
			SetTriggerShapeFlag(true);
			break;
		}
	}
}
