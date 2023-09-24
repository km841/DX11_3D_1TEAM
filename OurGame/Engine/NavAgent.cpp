#include "pch.h"
#include "NavAgent.h"
#include "GameObject.h"
#include "Transform.h"

namespace hm
{
	NavAgent::NavAgent()
		: Component(ComponentType::NavAgent)
		, mMoveSpeed(0.f)
		, mRotationSpeed(360.f)
		, mbApplyNavMesh(true)
		, mbRotating(false)
	{
		mCurFaceDir = Vec3(0.f, 0.f, 1.f);
	}
	NavAgent::~NavAgent()
	{
	}
	Component* NavAgent::Clone(GameObject* _pGameObject)
	{
		NavAgent* pComp = new NavAgent;
		return _pGameObject->AddComponent(pComp);
	}
	void NavAgent::Initialize()
	{
	}
	void NavAgent::Update()
	{
		Vec3 currentFaceDir = Vec3(0.f, 0.f, -1.f);
		Vec3 rot = GetTransform()->GetRotation();

		Matrix rotMat;
		rotMat.Rotation(rot);

		currentFaceDir = currentFaceDir.TransformCoord(rotMat);

		if (false == mPathList.empty())
		{
			Vec3 targetPos = mPathList.back();
			Vec3 pos = GetTransform()->GetPosition();

			float dist = Vec3::Distance(targetPos, pos);

			Vec3 dir = targetPos - pos;
			dir.Normalize();

			GetTransform()->Move(dir * mMoveSpeed);
			if (dist <= 0.5f)
			{
				mPathList.pop_back();
			}

			float dot = Vec3(dir.x, 0.f, dir.z).Dot(Vec3(currentFaceDir.x, 0.f, currentFaceDir.z));
			float angle = Vec3(dir.x, 0.f, dir.z).Angle(Vec3(currentFaceDir.x, 0.f, currentFaceDir.z));

			if (fabs(angle) > 1.f)
			{
				float degree = acosf(dot) * 180.f /XM_PI;
				Vec3 crossResult = Vec3(dir.x, 0.f, dir.z).Cross(Vec3(currentFaceDir.x, 0.f, currentFaceDir.z));

				if (crossResult.y > 0.f)
				{
					GetTransform()->AddRotation(AXIS_Y, -mRotationSpeed);
				}
				else
				{
					GetTransform()->AddRotation(AXIS_Y, mRotationSpeed);
				}

				mbRotating = true;
			}
			else
			{
				if (false == isnan(angle))
				{
					GetTransform()->AddRotation(AXIS_Y, angle);
				}

				mbRotating = false;
			}
		}
	}
	bool NavAgent::Move(const Vec3& _endPos)
	{
		// 네비게이션 매니저 작성 후 작성 예정
		return false;
	}
	bool NavAgent::MoveOnNavMesh(const Vec3& _endPos)
	{
		// 네비게이션 매니저 작성 후 작성 예정
		return false;
	}
	bool NavAgent::MoveOnNavMesh(const Vec3& _dir, float _speed)
	{
		// 네비게이션 매니저 작성 후 작성 예정
		return false;
	}
	const Vec3& NavAgent::GetTargetPos()
	{
		if (false == mPathList.empty())
			return mPathList.back();

		return Vec3::Zero;
	}
}