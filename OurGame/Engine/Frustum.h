#pragma once


namespace hm
{
	class Camera;
	enum PlaneType
	{
		PlaneFront,
		PlaneBack,
		PlaneUp,
		PlaneDown,
		PlaneLeft,
		PlaneRight,

		PlaneEnd
	};

	class Frustum
	{
	public:
		void FinalUpdate(Camera* _pCamera);
		bool ContainsSphere(const Vec3& _pos, float _radius);

	private:
		std::array<Vec4, PlaneEnd> mPlanes;
	};

}

