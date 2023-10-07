#pragma once
#include "Component.h"

namespace hm
{
	class Camera;
	class Transform :
		public Component
	{
	public:
		Transform();
		virtual ~Transform();

	public:
		virtual void  Initialize() override;

		/* 월드 행렬을 업데이트한다 */
		virtual void  FinalUpdate() override;

		virtual Component* Clone(GameObject* _pGameObject) override;

		void  SetScale(const Vec3& _scale) { mScale = _scale; }
		void  SetRotation(const Vec3& _rotation);
		void  SetRotation(Axis _eAxis, float _degree);
		void  SetPosition(const Vec3& _position);
		void  SetPosition(Axis _eAxis, float _position);

		/* 콜라이더를 제외하고 오브젝트만 회전시키는 함수 */
		void  SetRotationExcludingColliders(const Vec3& _rotation);
		void  SetRotationExcludingColliders(Axis _eAxis, float _degree);

		/* 콜라이더를 제외하고 오브젝트만 이동시키는 함수 */
		void  SetPositionExcludingColliders(const Vec3& _position);
		void  SetPositionExcludingColliders(Axis _eAxis, float _position);

		void SetWorldMatrix(const Matrix& _matrix);
		void SetUpdateByMat(bool _bFlag) { mbUpdateByMat = _bFlag; }

		void DecomposeWorld();
		static void DecomposeWorld(Matrix _worldMat, Vec3& _scale, Vec3& _rotation, Vec3& _position);
		static float NormalizeAngle(float _angle);
		static Vec3 NormalizeAngles(Vec3 _angles);
		Vec3 QuaternionToEuler(float _x, float _y, float _z, float _w);
		PxQuat EulerToQuaternion(Vec3 _euler);

		float GetBoundingSphereRadius() { return max(max(mScale.x, mScale.y), mScale.z); }

		const Vec3& GetRelativePosition() { return mRelativePosition; }
		void SetRelativePosition(const Vec3& _position) { mRelativePosition = _position; }
		Vec3 GetWorldPosition();
		const Vec3& GetPosition();
		Vec3 GetRotation();
		Vec3 GetPhysicsRotation();
		const Vec3& GetScale();
		
		Vec3 GetRight() { return mMatWorld.Right(); }
		Vec3 GetUp() { return mMatWorld.Up(); }
		Vec3 GetLook() { return mMatWorld.Backward(); }

		void LookAt(const Vec3& _look);
		static bool CloseEnough(const float& _a, const float& _b, const float& _epsilon = std::numeric_limits<float>::epsilon());
		static Vec3 DecomposeRotationMatrix(const Matrix& _rotation);
		void AddRotation(Axis _eAxis, float _degree);

		void Move(const Vec3& _velocity);

		const Matrix& GetWorldMatrix() { return mMatWorld; }
		const Matrix& GetWorldMatrix() const { return mMatWorld; }

	public:
		void PushData(Camera* pCamera);

	private:
		Transform* mpParent;

		Vec3    mScale;
		Vec3    mRotation;
		Vec3    mRelativeRotation;
		Vec3    mPosition;
		Vec3    mRelativePosition;

		Matrix  mMatLocal;
		Matrix  mMatWorld;
		Matrix  mMatOldWorld;
		
		bool mbUpdateByMat;

	};

}

