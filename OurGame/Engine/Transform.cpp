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
		, mbUpdateByRotMat(false)
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
			mPosition = transform.p;
			PxQuat relativeX(mRelativeRotation.x * XM_PI / 180.f, Vec3(1.f, 0.f, 0.f));
			PxQuat relativeY(mRelativeRotation.y * XM_PI / 180.f, Vec3(0.f, 1.f, 0.f));
			PxQuat relativeZ(mRelativeRotation.z * XM_PI / 180.f, Vec3(0.f, 0.f, 1.f));

			Matrix matScale = Matrix::CreateScale(mScale);
			Matrix matRotation = Matrix::CreateFromQuaternion(relativeZ) *
				Matrix::CreateFromQuaternion(relativeX) *
				Matrix::CreateFromQuaternion(relativeY);
			//Z*Y*X 하니까 짐벌락 걸렷다.

			matRotation *= Matrix::CreateFromQuaternion(transform.q);
			Matrix matTranslation = Matrix::CreateTranslation(Vec3(transform.p) + mRelativePosition);

			mMatOldWorld = mMatWorld;
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

			if (true == mbUpdateByRotMat)
			{
				Matrix matRotation = Matrix::CreateRotationX(mRotation.x);
				matRotation *= Matrix::CreateRotationZ(mRotation.z);
				matRotation *= Matrix::CreateRotationY(mRotation.y);

				mMatLocal = matScale * matRotation * matTranslation;
			}
			
			else
				mMatLocal = matScale * matRotation * matTranslation;

			mMatOldWorld = mMatWorld;
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
		pTransform->mMatOldWorld = mMatOldWorld;
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
			mPosition = _position;
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
		// 출처 http://www.littlecandle.co.kr/bbs/board.php?bo_table=codingnote&wr_id=174&page=2
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

	void Transform::DecomposeWorld(Matrix _worldMat, Vec3& _scale, Vec3& _rotation, Vec3& _position)
	{
		XMVECTOR vScale;
		XMVECTOR vRotQ;
		XMVECTOR vPos;
		XMMatrixDecompose(&vScale, &vRotQ, &vPos, _worldMat);


		_scale = vScale;
		_position = vPos;

		// Quaternion to Euler Angle
		// 출처 http://www.littlecandle.co.kr/bbs/board.php?bo_table=codingnote&wr_id=174&page=2
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

		_rotation = v;
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

	Vec3 Transform::GetRotation()
	{
		/*if (true == IsPhysicsObject())
		{
			AssertEx(IsPhysicsObject(), L"Transform::GetPhysicsRotation() - 물리적 오브젝트만 사용할 수 있는 함수");
			PxQuat q = GetRigidBody()->GetPhysicsTransform().q;
			return QuaternionToEuler(q.x, q.y, q.z, q.w);
		}*/
		return mRotation;
	}

	Vec3 Transform::GetPhysicsRotation()
	{
		if (true == IsPhysicsObject())
		{
			AssertEx(IsPhysicsObject(), L"Transform::GetPhysicsRotation() - 물리적 오브젝트만 사용할 수 있는 함수");
			PxQuat q = GetRigidBody()->GetPhysicsTransform().q;
			return QuaternionToEuler(q.x, q.y, q.z, q.w);
		}
		else
		{
			return Vec3(-1.f, -1.f, -1.f);
		}
	}

	const Vec3& Transform::GetScale()
	{
		return mScale;
	}


	void Transform::LookAt(const Vec3& _look)
	{
		Vec3 front = _look;
		front.Normalize();

		Vec3 right = Vec3::Up.Cross(_look);
		if (right == Vec3::Zero)
			right = Vec3::Forward.Cross(_look);

		right.Normalize();

		Vec3 up = front.Cross(right);
		up.Normalize();

		Matrix matrix = XMMatrixIdentity();
		matrix.Right(right);
		matrix.Up(up);
		matrix.Backward(front);

		mRotation = DecomposeRotationMatrix(matrix);
		mbUpdateByRotMat = true;
	}

	void Transform::SmoothRotateTo(const Vec3& _targetLook)
	{
		// 현재 회전값
		Vec3 currentLook = GetLook();
		currentLook.Normalize();

		// 목표 회전값
		Vec3 targetLookNormalized = _targetLook;
		targetLookNormalized.Normalize();

		// 보간된 회전값 계산
		Vec3 interpolatedLook = currentLook + (targetLookNormalized - currentLook) * 0.1f;
		interpolatedLook.Normalize();

		Vec3 right = Vec3::Up.Cross(interpolatedLook);
		if (right == Vec3::Zero)
			right = Vec3::Forward.Cross(interpolatedLook);

		right.Normalize();

		Vec3 up = interpolatedLook.Cross(right);
		up.Normalize();

		Matrix matrix = XMMatrixIdentity();
		matrix.Right(right);
		matrix.Up(up);
		matrix.Backward(interpolatedLook);

		mRotation = DecomposeRotationMatrix(matrix);
		mbUpdateByRotMat = true;
	}

	bool Transform::CloseEnough(const float& _a, const float& _b, const float& _epsilon)
	{
		return (_epsilon > std::abs(_a - _b));
	}

	Vec3 Transform::DecomposeRotationMatrix(const Matrix& _rotation)
	{
		Vec4 v[4];
		XMStoreFloat4(&v[0], _rotation.Right());
		XMStoreFloat4(&v[1], _rotation.Up());
		XMStoreFloat4(&v[2], _rotation.Backward());
		XMStoreFloat4(&v[3], _rotation.Translation());

		Vec3 ret;
		if (CloseEnough(v[0].z, -1.0f))
		{
			float x = 0;
			float y = XM_PI / 2;
			float z = x + atan2(v[1].x, v[2].x);
			ret = Vec3{ x, y, z };
		}
		else if (CloseEnough(v[0].z, 1.0f))
		{
			float x = 0;
			float y = -XM_PI / 2;
			float z = -x + atan2(-v[1].x, -v[2].x);
			ret = Vec3{ x, y, z };
		}
		else
		{
			float y1 = -asin(v[0].z);
			float y2 = XM_PI - y1;

			float x1 = atan2f(v[1].z / cos(y1), v[2].z / cos(y1));
			float x2 = atan2f(v[1].z / cos(y2), v[2].z / cos(y2));

			float z1 = atan2f(v[0].y / cos(y1), v[0].x / cos(y1));
			float z2 = atan2f(v[0].y / cos(y2), v[0].x / cos(y2));

			if ((std::abs(x1) + std::abs(y1) + std::abs(z1)) <= (std::abs(x2) + std::abs(y2) + std::abs(z2)))
			{
				ret = Vec3{ x1, y1, z1 };
			}
			else
			{
				ret = Vec3{ x2, y2, z2 };
			}
		}

		return ret;
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

			if ((ActorType::Kinematic == eActorType) || (ActorType::Character == eActorType))
				pRigidBody->GetDynamicActor()->setKinematicTarget(transform);
			else if (ActorType::Dynamic == eActorType)
				pRigidBody->GetDynamicActor()->setGlobalPose(transform);
			else
				AssertEx(false, L"Transform::Move() - Static Actor에 대한 Move 호출");


			const Vec3& graphicV = pRigidBody->GetGraphicVelocity();
			mRelativePosition += graphicV * DELTA_TIME;
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
		transformParams.matViewInv = transformParams.matView.Invert();
		transformParams.matWVPInv = transformParams.matWVP.Invert();
		transformParams.matOldWorld = mMatOldWorld;
		transformParams.matOldView = _pCamera->GetOldViewMatrix();

		CONST_BUFFER(ConstantBufferType::Transform)->PushData(&transformParams, sizeof(transformParams));
	}
}