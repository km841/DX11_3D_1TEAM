#include "pch.h"
#include "Collider.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "Resources.h"
#include "Transform.h"
#include "SceneManager.h"
#include "Engine.h"
#include "Camera.h"


namespace hm
{
	Collider::Collider()
		: Component(ComponentType::Collider)
		, mCollisionCount(0)
	{
		mpMesh = GET_SINGLE(Resources)->LoadBoundingCubeMesh();
		mpMaterial = GET_SINGLE(Resources)->Get<Material>(L"Collider")->Clone();
	}

	Collider::~Collider()
	{
	}

	void Collider::Initialize()
	{
		AssertEx(IsPhysicsObject(), L"Collider::Initialize() - 충돌을 사용하기 위해서는 RigidBody->SetPhysical()가 선행되어야 함.");
	}

	void Collider::Update()
	{
	}

	void Collider::FinalUpdate()
	{
		mpMaterial->SetVec3(0, 0 < mCollisionCount ? Vec3(1.f, 0.f, 0.f) : Vec3(0.f, 1.f, 0.f));
	}

	void Collider::Render()
	{
		Camera* pMainCamera = GET_SINGLE(SceneManager)->GetActiveScene()->GetMainCamera();

		PxTransform transform = GetRigidBody()->GetPhysicsTransform();
		Matrix matWorld =
			Matrix::CreateScale(GetRigidBody()->GetGeometrySize()) *
			Matrix::CreateFromQuaternion(transform.q) *
			Matrix::CreateTranslation(transform.p);

		TransformParams transformParams = {};
		transformParams.matWorld = matWorld;
		transformParams.matView = pMainCamera->GetViewMatrix();
		transformParams.matProjection = pMainCamera->GetProjectionMatrix();
		transformParams.matWV = matWorld * transformParams.matView;
		transformParams.matWVP = matWorld * transformParams.matView * transformParams.matProjection;
		transformParams.matWVPInv = transformParams.matWVP.Invert();
		CONST_BUFFER(ConstantBufferType::Transform)->PushData(&transformParams, sizeof(transformParams));

		mpMaterial->PushGraphicData();

		CONST_BUFFER(ConstantBufferType::Transform)->Mapping();
		CONST_BUFFER(ConstantBufferType::Material)->Mapping();
		mpMesh->Render();
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
	}
}

