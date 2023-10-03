#include "pch.h"
#include "Collider.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "Resources.h"
#include "Transform.h"
#include "SceneManager.h"
#include "Engine.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "Mesh.h"


namespace hm
{
	Collider::Collider()
		: Component(ComponentType::Collider)
		, mCollisionCount(0)
	{
		
		mpMaterial = GET_SINGLE(Resources)->Get<Material>(L"Collider")->Clone();
	}

	Collider::~Collider()
	{
	}

	void Collider::Initialize()
	{
		AssertEx(IsPhysicsObject(), L"Collider::Initialize() - 충돌을 사용하기 위해서는 RigidBody->SetPhysical()가 선행되어야 함.");

		switch (GetRigidBody()->GetGeometryType())
		{
		case GeometryType::Box:
			mpMesh = GET_SINGLE(Resources)->LoadBoundingCubeMesh();
			break;
		case GeometryType::Capsule:
		{
			Vec3 geomSize = GetRigidBody()->GetGeometrySize();
			mpMesh = GET_SINGLE(Resources)->CreateCapsuleMesh(geomSize.x / 2.f, geomSize.y);
		}
		break;
		case GeometryType::Convex:
		case GeometryType::Mesh:
		{
			wstring name = GetMeshRenderer()->GetMesh()->GetName();
			mpMesh = GET_SINGLE(Resources)->Get<Mesh>(name + L"Col");
		}
		break;
		}
		myLayerType = this->GetGameObject()->GetLayerType();
	}

	void Collider::Update()
	{
	}

	void Collider::FinalUpdate()
	{
		mpMaterial->SetVec4(0, 0 < mCollisionCount ? Vec4(1.f, 0.f, 0.f, 1.f) : Vec4(0.f, 1.f, 0.f, 1.f));
	}

	void Collider::Render()
	{
		if (false == GetGameObject()->IsEnable())
			return;

		Camera* pMainCamera = GET_SINGLE(SceneManager)->GetActiveScene()->GetMainCamera();

		bool bIsCapsule = GeometryType::Capsule == GetRigidBody()->GetGeometryType();

		PxTransform transform = GetRigidBody()->GetPhysicsTransform();
		Matrix matWorld =
			Matrix::CreateScale(bIsCapsule ? Vec3(1.f, 1.f, 1.f) : GetRigidBody()->GetGeometrySize()) *
			Matrix::CreateFromQuaternion(transform.q) *
			Matrix::CreateTranslation(transform.p);

		TransformParams transformParams = {};
		transformParams.matWorld = matWorld;
		transformParams.matView = pMainCamera->GetViewMatrix();
		transformParams.matProjection = pMainCamera->GetProjectionMatrix();
		transformParams.matWV = matWorld * transformParams.matView;
		transformParams.matWVP = matWorld * transformParams.matView * transformParams.matProjection;
		transformParams.matViewInv = transformParams.matView.Invert();
		transformParams.matWVPInv = transformParams.matWVP.Invert();
		CONST_BUFFER(ConstantBufferType::Transform)->PushData(&transformParams, sizeof(transformParams));

		mpMaterial->PushGraphicData();

		CONST_BUFFER(ConstantBufferType::Transform)->Mapping();
		CONST_BUFFER(ConstantBufferType::Material)->Mapping();
		mpMesh->Render();
	}

	Component* Collider::Clone(GameObject* _pGameObject)
	{
		Collider* pCollider = _pGameObject->AddComponent(new Collider);

		pCollider->mpMesh = mpMesh;
		pCollider->mpMaterial = mpMaterial->Clone();

		pCollider->mCollisionCount = 0;
		pCollider->myLayerType = _pGameObject->GetLayerType();

		return pCollider;
	}

	bool Collider::Sweep(const PxVec3& _dir, float _maxDist, Collider* _pOther, PxSweepHit& _pHit)
	{
		GeometryType eGeometryType = GetRigidBody()->GetGeometryType();
		switch (eGeometryType)
		{
		case GeometryType::Sphere:
			return Sweep<PxSphereGeometry>(GetRigidBody()->GetGeometries()->sphereGeom, _dir, _maxDist, _pOther, _pHit);

		case GeometryType::Box:
			return Sweep<PxBoxGeometry>(GetRigidBody()->GetGeometries()->boxGeom, _dir, _maxDist, _pOther, _pHit);

		case GeometryType::Capsule:
			return Sweep<PxCapsuleGeometry>(GetRigidBody()->GetGeometries()->capsuleGeom, _dir, _maxDist, _pOther, _pHit);

		case GeometryType::Convex:
			return Sweep<PxConvexMeshGeometry>(GetRigidBody()->GetGeometries()->convexGeom, _dir, _maxDist, _pOther, _pHit);
		}
		return false;
	}

	bool Collider::Raycast(const Vec3& _origin, const Vec3& _dir, Collider* _pOther, float _maxDist)
	{
		GeometryType eGeometryType = _pOther->GetRigidBody()->GetGeometryType();
		switch (eGeometryType)
		{
		case GeometryType::Box:
			return Raycast<PxBoxGeometry>(_pOther->GetRigidBody()->GetGeometries()->boxGeom, _origin, _dir, _pOther, _maxDist);

		case GeometryType::Capsule:
			return Raycast<PxCapsuleGeometry>(_pOther->GetRigidBody()->GetGeometries()->capsuleGeom, _origin, _dir, _pOther, _maxDist);
	
		case GeometryType::Sphere:
			return Raycast<PxSphereGeometry>(_pOther->GetRigidBody()->GetGeometries()->sphereGeom, _origin, _dir, _pOther, _maxDist);

		case GeometryType::Mesh:
			return Raycast<PxTriangleMeshGeometry>(_pOther->GetRigidBody()->GetGeometries()->triangleGeom, _origin, _dir, _pOther, _maxDist);
		}
		return false;
	}

	bool Collider::Overlap(Collider* _pOther)
	{
		GeometryType eGeometryType = _pOther->GetRigidBody()->GetGeometryType();
		if (GeometryType::Mesh == eGeometryType || GeometryType::Mesh == GetRigidBody()->GetGeometryType())
			return false;

		switch (eGeometryType)
		{
		case GeometryType::Sphere:
			return Overlap<PxSphereGeometry>(_pOther->GetRigidBody()->GetGeometries()->sphereGeom, _pOther);

		case GeometryType::Box:
			return Overlap<PxBoxGeometry>(_pOther->GetRigidBody()->GetGeometries()->boxGeom, _pOther);

		case GeometryType::Capsule:
			return Overlap<PxCapsuleGeometry>(_pOther->GetRigidBody()->GetGeometries()->capsuleGeom, _pOther);

		case GeometryType::Mesh:
			return Overlap<PxTriangleMeshGeometry>(_pOther->GetRigidBody()->GetGeometries()->triangleGeom, _pOther);

		case GeometryType::Convex:
			return Overlap<PxConvexMeshGeometry>(_pOther->GetRigidBody()->GetGeometries()->convexGeom, _pOther);

		default:
			return false;

		}
		return false;
	}

	void Collider::OnCollisionEnter(Collider* _pOtherCollider)
	{
		mpGameObject->OnCollisionEnter(_pOtherCollider);
		mCollisionCount++;
	}

	void Collider::OnCollisionStay(Collider* _pOtherCollider)
	{
		mpGameObject->OnCollisionStay(_pOtherCollider);
	}

	void Collider::OnCollisionExit(Collider* _pOtherCollider)
	{
		mpGameObject->OnCollisionExit(_pOtherCollider);
		mCollisionCount--;

		if (0 > mCollisionCount)
			mCollisionCount = 0;
	}

	void Collider::OnTriggerEnter(Collider* _pOtherCollider)
	{
		mpGameObject->OnTriggerEnter(_pOtherCollider);
		mCollisionCount++;
		collLayerTypeList.push_back(_pOtherCollider->myLayerType);
	}

	void Collider::OnTriggerStay(Collider* _pOtherCollider)
	{
		mpGameObject->OnTriggerStay(_pOtherCollider);
	}

	void Collider::OnTriggerExit(Collider* _pOtherCollider)
	{
		mpGameObject->OnTriggerExit(_pOtherCollider);
		mCollisionCount--;

		if (0 > mCollisionCount)
			mCollisionCount = 0;

		for (int i = 0; i < collLayerTypeList.size(); i++)
		{
			if (collLayerTypeList[i] == _pOtherCollider->myLayerType)
			{
				collLayerTypeList.erase(collLayerTypeList.begin() + i);
				return;
			}
		}
	}

	bool Collider::IsPenetrate()
	{

		return false;
	}
}

