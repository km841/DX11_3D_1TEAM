#include "pch.h"
#include "Transform.h"
#include "GameObject.h"
#include "Camera.h"
#include "Engine.h"
#include "RigidBody.h"
#include "Timer.h"

namespace hm
{
	Transform::Transform()
		: Component(ComponentType::Transform)
		, mpParent(nullptr)
		, mScale(Vec3(1.f, 1.f, 1.f))
	{
	}
	Transform::~Transform()
	{
	}
	void Transform::Initialize()
	{
	}
	void Transform::FinalUpdate()
	{
		if (true == IsPhysicsObject())
		{
			PxTransform transform = GetRigidBody()->GetPhysicsTransform();

			mRotation = Vec3(
				transform.q.x * 180.f / XM_PI, 
				transform.q.y * 180.f / XM_PI, 
				transform.q.z * 180.f / XM_PI);
			mPosition = transform.p;

			Matrix matScale = Matrix::CreateScale(mScale);
			Matrix matRotation = Matrix::CreateFromQuaternion(transform.q);
			Matrix matTranslation = Matrix::CreateTranslation(transform.p);

			mMatWorld = matScale * matRotation * matTranslation;
		}

		else
		{
			Matrix matScale = Matrix::CreateScale(mScale);

			Matrix matRotation = Matrix::CreateRotationX(mRotation.x * XM_PI / 180.f);
			matRotation *= Matrix::CreateRotationY(mRotation.y * XM_PI / 180.f);
			matRotation *= Matrix::CreateRotationZ(mRotation.z * XM_PI / 180.f);

			Matrix matTranslation = Matrix::CreateTranslation(mPosition);

			mMatLocal = matScale * matRotation * matTranslation;
			mMatWorld = mMatLocal;
		}

		if (nullptr != mpParent)
		{
			mMatWorld *= mpParent->GetWorldMatrix();
		}
	}

	void Transform::SetRotation(const Vec3& _rotation)
	{
		if (true == IsPhysicsObject())
		{
			RigidBody* pRigidBody = GetRigidBody();
			PxTransform transform = pRigidBody->GetPhysicsTransform();

			PxQuat rotateX(_rotation.x * XM_PI / 180.f, Vec3(1.f, 0.f, 0.f));
			PxQuat rotateY(_rotation.y * XM_PI / 180.f, Vec3(0.f, 1.f, 0.f));
			PxQuat rotateZ(_rotation.z * XM_PI / 180.f, Vec3(0.f, 0.f, 1.f));

			pRigidBody->SetPhysicsTransform(PxTransform(transform.p, rotateZ * rotateY * rotateX));
		}

		mRotation = _rotation; 
	}

	void Transform::SetRotation(Axis _eAxis, float _degree)
	{
		if (true == IsPhysicsObject())
		{
			RigidBody* pRigidBody = GetRigidBody();
			PxTransform transform = pRigidBody->GetPhysicsTransform();
			Vec3 rotVec = {};
			switch (_eAxis)
			{
			case hm::AXIS_X:
				rotVec.x = 1.f;
				break;
			case hm::AXIS_Y:
				rotVec.y = 1.f;
				break;
			case hm::AXIS_Z:
				rotVec.z = 1.f;
				break;
			}
			PxQuat q(_degree * XM_PI / 180.f, rotVec);
			pRigidBody->SetPhysicsTransform(PxTransform(transform.p, q));
		}

		switch (_eAxis)
		{
		case hm::AXIS_X:
			mRotation.x = _degree;
			break;
		case hm::AXIS_Y:
			mRotation.y = _degree;
			break;
		case hm::AXIS_Z:
			mRotation.z = _degree;
			break;
		}
	}

	void Transform::SetPosition(const Vec3& _position)
	{
		if (true == IsPhysicsObject())
		{
			RigidBody* pRigidBody = GetRigidBody();
			PxTransform transform = pRigidBody->GetDynamicActor()->getGlobalPose();
			transform.p = _position;
			pRigidBody->GetDynamicActor()->setGlobalPose(transform);
		}
		else
		{
			mPosition = _position;
		}
	}

	Vec3 Transform::GetWorldPosition()
	{
		Vec3 position = mPosition;

		if (nullptr != mpParent)
			position += mpParent->GetWorldPosition();
		
		//if (true == IsPhysicsObject())
		//	position.z = -position.z;

		return position;
	}

	const Vec3& Transform::GetPosition()
	{
		return mPosition;
	}

	const Vec3& Transform::GetRotation()
	{
		return mRotation;
	}

	const Vec3& Transform::GetScale()
	{
		return mScale;
	}

	void Transform::AddRotation(Axis _eAxis, float _degree)
	{
		if (true == IsPhysicsObject())
		{
			RigidBody* pRigidBody = GetRigidBody();
			PxTransform transform = pRigidBody->GetPhysicsTransform();
			Vec3 rotVec = {};
			switch (_eAxis)
			{
			case hm::AXIS_X:
				rotVec.x = 1.f;
				break;
			case hm::AXIS_Y:
				rotVec.y = 1.f;
				break;
			case hm::AXIS_Z:
				rotVec.z = 1.f;
				break;
			}
			PxQuat q = transform.q;
			PxQuat rotQ(_degree * XM_PI / 180.f, rotVec);
			pRigidBody->SetPhysicsTransform(PxTransform(transform.p, q * rotQ));
		}


		switch (_eAxis)
		{
		case AXIS_X:
			mRotation.x += _degree;
			break;
		case AXIS_Y:
			mRotation.y += _degree;
			break;
		case AXIS_Z:
			mRotation.z += _degree;
			break;
		}
	}
	void Transform::Move(const Vec3& _velocity)
	{
		if (true == IsPhysicsObject())
		{
			RigidBody* pRigidBody = GetRigidBody();
			PxTransform transform = pRigidBody->GetPhysicsTransform();
			transform.p += _velocity * DELTA_TIME;

			ActorType eActorType = pRigidBody->GetActorType();

			if (ActorType::Kinematic == eActorType)
				pRigidBody->GetDynamicActor()->setKinematicTarget(transform);
			else if (ActorType::Dynamic == eActorType)
				pRigidBody->GetDynamicActor()->setGlobalPose(transform);
			else
				AssertEx(false, L"Transform::Move() - Static Actor에 대한 Move 호출");
		}
		
		else
		{
			mPosition += _velocity * DELTA_TIME;
		}
	}

	void Transform::PushData(Camera* _pCamera)
	{
		TransformParams transformParams = {};

		transformParams.matWorld = mMatWorld;
		transformParams.matView = _pCamera->GetViewMatrix();
		transformParams.matProjection = _pCamera->GetProjectionMatrix();
		transformParams.matWV = mMatWorld * transformParams.matView;
		transformParams.matWVP = mMatWorld * transformParams.matView * transformParams.matProjection;
		transformParams.matWVPInv = transformParams.matWVP.Invert();

		CONST_BUFFER(ConstantBufferType::Transform)->PushData(&transformParams, sizeof(transformParams));
	}
}