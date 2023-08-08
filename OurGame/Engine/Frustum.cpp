#include "pch.h"
#include "Frustum.h"
#include "Camera.h"

namespace hm
{
	void Frustum::FinalUpdate(Camera* _pCamera)
	{
		Matrix matViewInv = _pCamera->GetViewMatrix().Invert();
		Matrix matProjectionInv = _pCamera->GetProjectionMatrix().Invert();
		Matrix matInv = matProjectionInv * matViewInv;

		std::vector<Vec3> worldPos =
		{
			::XMVector3TransformCoord(Vec3(-1.f, 1.f, 0.f), matInv),
			::XMVector3TransformCoord(Vec3(1.f, 1.f, 0.f), matInv),
			::XMVector3TransformCoord(Vec3(1.f, -1.f, 0.f), matInv),
			::XMVector3TransformCoord(Vec3(-1.f, -1.f, 0.f), matInv),
			::XMVector3TransformCoord(Vec3(-1.f, 1.f, 1.f), matInv),
			::XMVector3TransformCoord(Vec3(1.f, 1.f, 1.f), matInv),
			::XMVector3TransformCoord(Vec3(1.f, -1.f, 1.f), matInv),
			::XMVector3TransformCoord(Vec3(-1.f, -1.f, 1.f), matInv)
		};

		mPlanes[PlaneFront] = ::XMPlaneFromPoints(worldPos[0], worldPos[1], worldPos[2]); // CW
		mPlanes[PlaneBack] = ::XMPlaneFromPoints(worldPos[4], worldPos[7], worldPos[5]); // CCW
		mPlanes[PlaneUp] = ::XMPlaneFromPoints(worldPos[4], worldPos[5], worldPos[1]); // CW
		mPlanes[PlaneDown] = ::XMPlaneFromPoints(worldPos[7], worldPos[3], worldPos[6]); // CCW
		mPlanes[PlaneLeft] = ::XMPlaneFromPoints(worldPos[4], worldPos[0], worldPos[7]); // CW
		mPlanes[PlaneRight] = ::XMPlaneFromPoints(worldPos[5], worldPos[6], worldPos[1]); // CCW
	}

	bool Frustum::ContainsSphere(const Vec3& _pos, float _radius)
	{
		for (const Vec4& plane : mPlanes)
		{
			// n = (a, b, c)
			Vec3 normal = Vec3(plane.x, plane.y, plane.z);

			// ax + by + cz + d > radius
			if (normal.Dot(_pos) + plane.w > _radius)
				return false;
		}

		return true;
	}
}

