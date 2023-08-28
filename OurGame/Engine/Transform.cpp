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
		, mbUpdateByMat(false)
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
			if (true == mbUpdateByMat)
			{
				GetRigidBody()->SetPhysicsTransform(PxTransform(mPosition, EulerToQuaternion(mRotation)));

				if (nullptr != mpParent)
					mMatWorld *= mpParent->GetWorldMatrix();
				
				return;
			}

			PxTransform transform = GetRigidBody()->GetPhysicsTransform();
			PxQuat relativeX(mRelativeRotation.x * XM_PI / 180.f, Vec3(1.f, 0.f, 0.f));
			PxQuat relativeY(mRelativeRotation.y * XM_PI / 180.f, Vec3(0.f, 1.f, 0.f));
			PxQuat relativeZ(mRelativeRotation.z * XM_PI / 180.f, Vec3(0.f, 0.f, 1.f));

			Matrix matScale = Matrix::CreateScale(mScale);
			Matrix matRotation = Matrix::CreateFromQuaternion(relativeZ) *
				Matrix::CreateFromQuaternion(relativeX) *
				Matrix::CreateFromQuaternion(relativeY);
			//Z*Y*X ÇÏ´Ï±î Áü¹ú¶ô °É·Ç´Ù.

			matRotation *= Matrix::CreateFromQuaternion(transform.q);
			Matrix matTranslation = Matrix::CreateTranslation(Vec3(transform.p) + mRelativePosition);

			mMatWorld = matScale * matRotation * matTranslation;
		}

		else
		{
			if (true == mbUpdateByMat)
			{
				if (nullptr != mpParent)
					mMatWorld *= mpParent->GetWorldMatrix();
				
				return;
			}

			Matrix matScale = Matrix::CreateScale(mScale);
			Vec4 rotateQuat = XMQuaternionRotationRollPitchYaw(
				mRotation.x * XM_PI / 180.f, 
				mRotation.y * XM_PI / 180.f, 
				mRotation.z * XM_PI / 180.f);
	
			Matrix matRotation = XMMatrixRotationQuaternion(rotateQuat.Convert());
			Matrix matTranslation = Matrix::CreateTranslation(mPosition);

			mMatLocal = matScale * matRotation * matTranslation;
			mMatWorld = mMatLocal;
		}

		if (nullptr != mpParent)
		{
			mMatWorld *= mpParent->GetWorldMatrix();
		}
	}

	Component* Transform::Clone(GameObject* _pGameObject)
	{
		Transform* pTransform = _pGameObject->AddComponent(new Transform);

		pTransform->mMatLocal = mMatLocal;
		pTransform->mMatWorld = mMatWorld;
		pTransform->mPosition = mPosition;
		pTransform->mRotation = mRotation;
		pTransform->mScale = mScale;
		pTransform->mRelativeRotation = mRelativeRotation;
		pTransform->mRelativePosition = mRelativePosition;
		pTransform->mpParent = mpParent;

		return pTransform;
	}

	void Transform::SetRotation(const Vec3& _rotation)
	{
		if (true == IsPhysicsObject())
		{
			RigidBody* pRigidBody = GetRigidBody();
			PxTransform transform = pRigidBody->GetPhysicsTransform();

			transform.q = EulerToQuaternion(_rotation);
			pRigidBody->SetPhysicsTransform(transform);
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

	void Transform::SetRotationExcludingColliders(const Vec3& _rotation)
	{
		mRelativeRotation = _rotation;
	}

	void Transform::SetRotationExcludingColliders(Axis _eAxis, float _degree)
	{
		switch (_eAxis)
		{
		case hm::AXIS_X:
			mRelativeRotation.x = _degree;
			break;
		case hm::AXIS_Y:
			mRelativeRotation.y = _degree;
			break;
		case hm::AXIS_Z:
			mRelativeRotation.z = _degree;
			break;
		}
	}

	void Transform::SetPosition(const Vec3& _position)
	{
		if (true == IsPhysicsObject())
		{
			RigidBody* pRigidBody = GetRigidBody();
			PxTransform transform = pRigidBody->GetActor<PxRigidActor>()->getGlobalPose();
			transform.p = _position;
			pRigidBody->GetActor<PxRigidActor>()->setGlobalPose(transform);
		}
		else
		{
			mPosition = _position;
		}
	}

	void Transform::SetPosition(Axis _eAxis, float _position)
	{
		if (true == IsPhysicsObject())
		{
			RigidBody* pRigidBody = GetRigidBody();
			PxTransform transform = pRigidBody->GetDynamicActor()->getGlobalPose();

			switch (_eAxis)
			{
			case hm::AXIS_X:
				transform.p.x = _position;
				break;
			case hm::AXIS_Y:
				transform.p.y = _position;
				break;
			case hm::AXIS_Z:
				transform.p.z = _position;
				break;
			}

			pRigidBody->GetDynamicActor()->setGlobalPose(transform);
		}

		switch (_eAxis)
		{
		case hm::AXIS_X:
			mPosition.x = _position;
			break;
		case hm::AXIS_Y:
			mPosition.y = _position;
			break;
		case hm::AXIS_Z:
			mPosition.z = _position;
			break;
		}
	}

	void Transform::SetScaleFromTool(const Vec3& _scale)
	{
		mMatWorld._11 = _scale.x;
		mMatWorld._22 = _scale.y;
		mMatWorld._33 = _scale.z;

		DecomposeWorld();

		mScale = _scale;
	}

	void Transform::SetRotationFromTool(const Vec3& _rotation)
	{
	}

	void Transform::SetPositionFromTool(const Vec3& _position)
	{
	}

	void Transform::SetPositionExcludingColliders(const Vec3& _position)
	{
		mRelativePosition = _position;
	}

	void Transform::SetPositionExcludingColliders(Axis _eAxis, float _position)
	{
		switch (_eAxis)
		{
		case hm::AXIS_X:
			mRelativePosition.x = _position;
			break;
		case hm::AXIS_Y:
			mRelativePosition.y = _position;
			break;
		case hm::AXIS_Z:
			mRelativePosition.z = _position;
			break;
		}
	}

	void Transform::SetWorldMatrix(const Matrix& _matrix)
	{
		mbUpdateByMat = true;
		mMatWorld = _matrix;
		DecomposeWorld();
	}

	void Transform::DecomposeWorld()
	{
		XMVECTOR vScale;
		XMVECTOR vRotQ;
		XMVECTOR vPos;
		XMMatrixDecompose(&vScale, &vRotQ, &vPos, mMatWorld);


		mScale = vScale;
		mPosition = vPos;

		// Quaternion to Euler Angle
		// ÃâÃ³ http://www.littlecandle.co.kr/bbs/board.php?bo_table=codingnote&wr_id=174&page=2
		float w, x, y, z;
		w = vRotQ.m128_f32[3];
		x = vRotQ.m128_f32[0];
		y = vRotQ.m128_f32[1];
		z = vRotQ.m128_f32[2];

		float sqW = w * w;
		float sqX = x * x;
		float sqY = y * y;
		float sqZ = z * z;
		float unit = sqX + sqY + sqZ + sqW;
		float test = x * w - y * z;
		Vec3 v;

		if (test > 0.4955f * unit)
		{
			v.y = 2.f * atan2f(y, x);
			v.x = XM_PI / 2.f;
			v.z = 0;
			v = v * (180.f / XM_PI);
		}
		else if (test < -0.4995f * unit)
		{
			v.x = -2.f * atan2f(y, x);
			v.x = -XM_PI / 2.f;
			v.z = 0;
			v = v * (180.f / XM_PI);
		}
		else
		{
			Vec4 Quat(w, z, x, y);
			v.x = (float)asinf(2.f * (Quat.x * Quat.z - Quat.w * Quat.y)); // Pitch
			v.y = (float)atan2(2.f * Quat.x * Quat.w + 2.f * Quat.y * Quat.z, 1.f - 2.f * (Quat.z * Quat.z + Quat.w * Quat.w)); // Yaw
			v.z = (float)atan2(2.f * Quat.x * Quat.y + 2.f * Quat.z * Quat.w, 1.f - 2.f * (Quat.y * Quat.y + Quat.z * Quat.z)); // Roll
			v = v * (180.f / XM_PI);
		}

		mRotation = NormalizeAngles(v);
	}

	float Transform::NormalizeAngle(float _angle)
	{
		while (_angle > 360)
			_angle -= 360;
		while (_angle < 0)
			_angle += 360;
		return _angle;
	}

	Vec3 Transform::NormalizeAngles(Vec3 _angles)
	{
		_angles.x = NormalizeAngle(_angles.x);
		_angles.y = NormalizeAngle(_angles.y);
		_angles.z = NormalizeAngle(_angles.z);
		return _angles;
	}

	Vec3 Transform::QuaternionToEuler(float _x, float _y, float _z, float _w)
	{
		float w = _w, x = _x, y = _y, z = _z;

		float sqW = w * w;
		float sqX = x * x;
		float sqY = y * y;
		float sqZ = z * z;
		float unit = sqX + sqY + sqZ + sqW;
		float test = x * w - y * z;
		Vec3 v;

		if (test > 0.4955f * unit)
		{
			v.y = 2.f * atan2f(y, x);
			v.x = XM_PI / 2.f;
			v.z = 0;
			v = v * (180.f / XM_PI);
		}
		else if (test < -0.4995f * unit)
		{
			v.x = -2.f * atan2f(y, x);
			v.x = -XM_PI / 2.f;
			v.z = 0;
			v = v * (180.f / XM_PI);
		}
		else
		{
			Vec4 Quat(w, z, x, y);
			v.x = (float)asinf(2.f * (Quat.x * Quat.z - Quat.w * Quat.y)); // Pitch
			v.y = (float)atan2(2.f * Quat.x * Quat.w + 2.f * Quat.y * Quat.z, 1.f - 2.f * (Quat.z * Quat.z + Quat.w * Quat.w)); // Yaw
			v.z = (float)atan2(2.f * Quat.x * Quat.y + 2.f * Quat.z * Quat.w, 1.f - 2.f * (Quat.y * Quat.y + Quat.z * Quat.z)); // Roll
			v = v * (180.f / XM_PI);
		}

		NormalizeAngles(v);
		return v;
	}

	PxQuat Transform::EulerToQuaternion(Vec3 _euler)
	{
		Vec4 rotateQuat = XMQuaternionRotationRollPitchYaw(
			_euler.x * XM_PI / 180.f,
			_euler.y * XM_PI / 180.f,
			_euler.z * XM_PI / 180.f);

		return { rotateQuat.x, rotateQuat.y, rotateQuat.z, rotateQuat.w };
	}

	Vec3 Transform::GetWorldPosition()
	{
		Vec3 position = mPosition;

		if (nullptr != mpParent)
			position += mpParent->GetWorldPosition();

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
				AssertEx(false, L"Transform::Move() - Static Actor¿¡ ´ëÇÑ Move È£Ãâ");
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