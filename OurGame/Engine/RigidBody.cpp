#include "pch.h"
#include "RigidBody.h"
#include "Engine.h"
#include "Transform.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "Timer.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Resources.h"

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
		, mZeroAxisV{}
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
		if (true == mbAppliedGravity && 
		   (false == mbAppliedPhysics || 
			ActorType::Kinematic == mPhysicsInfo.eActorType))
		{
			AddGravity();
		}

		if (true == mbAppliedPhysics && ActorType::Static == mPhysicsInfo.eActorType)
			return;
		
		else
		{
			GetTransform()->Move(mVelocity);
		}


		bool bChangedFlag = false;
		for (int i = 0; i < AXIS_MAX; ++i)
		{
			if (true == mZeroAxisV[i])
			{
				float& axisValue = *(&mVelocity.x + i);
				axisValue = 0.f;
				bChangedFlag = true;
			}
		}

		if (true == bChangedFlag)
			SetVelocity(mVelocity);
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
			_pGameObject->GetTransform()->SetPosition(GetTransform()->GetPosition());
			_pGameObject->GetTransform()->SetRotation(GetTransform()->GetRotation());
			_pGameObject->GetTransform()->SetScale(GetTransform()->GetScale());
		}

		if (ActorType::Static != mPhysicsInfo.eActorType)
		{
			pRigidBody->SetVelocity(mVelocity);
			pRigidBody->SetMaxVelocity(mMaxVelocity);
		}

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
		//_transform.p.z = -_transform.p.z;
		AssertEx(mbAppliedPhysics, L"RigidBody::SetPhysicsTransform() - 물리가 들어가지 않은 오브젝트에 대한 SetPhysicsTransform 호출");
		GetActor<PxRigidActor>()->setGlobalPose(_transform);
		
	}

	void RigidBody::SetGeometrySize(const Vec3& _geomSize)
	{
		SAFE_DELETE(mPhysicsInfo.pGeometries);
		mPhysicsInfo.size = _geomSize;
		CreateGeometry();

		switch (mPhysicsInfo.eGeometryType)
		{
		case GeometryType::Box:
			mpShape->setGeometry(mPhysicsInfo.pGeometries->boxGeom);
			break;
		case GeometryType::Sphere:
			mpShape->setGeometry(mPhysicsInfo.pGeometries->sphereGeom);
			break;
		case GeometryType::Capsule:
			mpShape->setGeometry(mPhysicsInfo.pGeometries->capsuleGeom);
			break;
		}
	}

	void RigidBody::SetVelocity(const Vec3& _velocity)
	{
		if (true == mbAppliedPhysics)
		{
			AssertEx(ActorType::Static != mPhysicsInfo.eActorType, L"RigidBody::SetVelocity() - Dynamic Actor가 아닌 물체에 대한 SetVelocity() 호출 시도");
			GetDynamicActor()->setLinearVelocity(_velocity);
			mVelocity = _velocity;
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
			AssertEx(ActorType::Static != mPhysicsInfo.eActorType, L"RigidBody::SetVelocity() - Static Actor 물체에 대한 SetVelocity() 호출 시도");
			Vec3 velocity = ActorType::Kinematic == mPhysicsInfo.eActorType ? mVelocity : static_cast<Vec3>(GetDynamicActor()->getLinearVelocity());
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
			AssertEx(ActorType::Static != mPhysicsInfo.eActorType, L"RigidBody::AddVelocity() - Dynamic Actor가 아닌 물체에 대한 AddVelocity() 호출 시도");
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
			mVelocity = velocity;
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
		mVelocity += GLOBAL_GRAVITY * DELTA_TIME;
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
			AssertEx(ActorType::Static != mPhysicsInfo.eActorType, L"RigidBody::ApplyGravity() - Dynamic Actor가 아닌 물체에 대한 ApplyGravity() 호출 시도");
			GetDynamicActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);
		}

		mbAppliedGravity = true;
	}

	void RigidBody::RemoveGravity()
	{
		if (true == mbAppliedPhysics)
		{
			AssertEx(ActorType::Static != mPhysicsInfo.eActorType, L"RigidBody::RemoveGravity() - Dynamic Actor가 아닌 물체에 대한 RemoveGravity() 호출 시도");
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

	void RigidBody::AddForce(const Vec3& _force)
	{
		AssertEx(mbAppliedPhysics, L"RigidBody::AddForce() - 물리가 들어가지 않은 오브젝트에 대한 AddForce 호출");
		AssertEx(ActorType::Static != mPhysicsInfo.eActorType, L"RigidBody::AddForce() - Static 객체에 대해 힘 적용");

		/*PxRigidBodyExt::addForceAtPos(
			*GetDynamicActor(),
			_force,
			GetTransform()->GetPosition(),
			PxForceMode::eIMPULSE
		);*/

		GetDynamicActor()->addForce(_force, PxForceMode::eIMPULSE);
	}

	void RigidBody::AddTorque(const Vec3& _force)
	{
		AssertEx(mbAppliedPhysics, L"RigidBody::AddForce() - 물리가 들어가지 않은 오브젝트에 대한 AddForce 호출");
		AssertEx(ActorType::Static != mPhysicsInfo.eActorType, L"RigidBody::AddForce() - Static 객체에 대해 힘 적용");

		GetDynamicActor()->addTorque(_force, PxForceMode::eIMPULSE);
	}

	void RigidBody::AddForceAndTorque(const Vec3& _force)
	{
		AssertEx(mbAppliedPhysics, L"RigidBody::AddForce() - 물리가 들어가지 않은 오브젝트에 대한 AddForce 호출");
		AssertEx(ActorType::Static != mPhysicsInfo.eActorType, L"RigidBody::AddForce() - Static 객체에 대해 힘 적용");

		GetDynamicActor()->addForce(_force, PxForceMode::eIMPULSE);
		GetDynamicActor()->addTorque(_force, PxForceMode::eIMPULSE);
	}

	void RigidBody::RemoveAxisSpeedAtUpdate(Axis _eAxis, bool _bFlag)
	{
		mZeroAxisV[_eAxis] = _bFlag;
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

	void RigidBody::CreateMeshGeometry()
	{
		TriangleMeshInfo info = GetMeshRenderer()->GetMesh()->GetTriangleMeshInfo();
		
		wstring name = GetMeshRenderer()->GetMesh()->GetName();
		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->CreateTriangleMesh(name + L"Col", info);
		PxTriangleMesh* _pTriMesh = CreateTriangleMesh(info);

		mPhysicsInfo.pGeometries = new Geometries(mPhysicsInfo.eGeometryType, _pTriMesh, mPhysicsInfo.size * 2.f);
	}

	void RigidBody::CreateConvexGeometry()
	{
		TriangleMeshInfo info = GetMeshRenderer()->GetMesh()->GetTriangleMeshInfo();

		wstring name = GetMeshRenderer()->GetMesh()->GetName();
		shared_ptr<Mesh> pMesh = GET_SINGLE(Resources)->CreateTriangleMesh(name + L"Col", info);
		PxConvexMesh* _pConvexMesh = CreateConvexMesh(info);

		mPhysicsInfo.pGeometries = new Geometries(mPhysicsInfo.eGeometryType, _pConvexMesh, mPhysicsInfo.size * 2.f);
	}

	PxTriangleMesh* RigidBody::CreateTriangleMesh(const TriangleMeshInfo& _meshInfo)
	{
		const std::vector<PxVec3>& vertices = _meshInfo.vertices;
		const std::vector<int>& indices = _meshInfo.indices;

		PxTriangleMeshDesc meshDesc;
		meshDesc.points.count = static_cast<PxU32>(vertices.size());
		meshDesc.points.stride = sizeof(PxVec3);
		meshDesc.points.data = &vertices[0];

		meshDesc.triangles.count = static_cast<PxU32>(indices.size() / 3);
		meshDesc.triangles.stride = sizeof(PxU32) * 3;
		meshDesc.triangles.data = &indices[0];

		PxDefaultMemoryOutputStream stream;
		bool bRes = gpEngine->GetPhysics()->GetCooking()->cookTriangleMesh(meshDesc, stream);
		AssertEx(bRes, L"RigidBody::CreateTriangleMesh() - 메쉬콜라이더 생성 실패");

		PxTriangleMesh* _pMesh = gpEngine->GetPhysics()->GetCooking()->createTriangleMesh(meshDesc, PHYSICS->getPhysicsInsertionCallback());
		return _pMesh;
	}

	PxConvexMesh* RigidBody::CreateConvexMesh(const TriangleMeshInfo& _meshInfo)
	{
		const std::vector<PxVec3>& vertices = _meshInfo.vertices;

		PxConvexMeshDesc meshDesc;
		meshDesc.points.count = static_cast<PxU32>(vertices.size());
		meshDesc.points.stride = sizeof(PxVec3);
		meshDesc.points.data = &vertices[0];
		meshDesc.flags = PxConvexFlag::eCOMPUTE_CONVEX;

		PxDefaultMemoryOutputStream stream;
		bool bRes = gpEngine->GetPhysics()->GetCooking()->cookConvexMesh(meshDesc, stream);
		AssertEx(bRes, L"RigidBody::CreateTriangleMesh() - 메쉬콜라이더 생성 실패");

		PxConvexMesh* _pMesh = gpEngine->GetPhysics()->GetCooking()->createConvexMesh(meshDesc, PHYSICS->getPhysicsInsertionCallback());
		return _pMesh;
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

		case GeometryType::Mesh:
			CreateMeshGeometry();
			break;

		case GeometryType::Convex:
			CreateConvexGeometry();
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
		case GeometryType::Mesh:
			mpShape = PxRigidActorExt::createExclusiveShape(*mpActor->is<PxRigidActor>(), mPhysicsInfo.pGeometries->triangleGeom, *mpMaterial);
			break;
		case GeometryType::Convex:
			mpShape = PxRigidActorExt::createExclusiveShape(*mpActor->is<PxRigidActor>(), mPhysicsInfo.pGeometries->convexGeom, *mpMaterial);
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
