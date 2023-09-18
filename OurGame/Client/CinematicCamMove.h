#pragma once

#include "MonoBehavior.h"
#include "GameObject.h"
#include "Camera.h"

namespace yj
{

	class CinematicCamMove : public GameObject
	{
	public:
		CinematicCamMove();
		virtual ~CinematicCamMove() = default;
		virtual Component* Clone(GameObject* _pGameObject);

	public:
		virtual void Initialize();
		virtual void Update();
		void CamEventTrigger(int _event_num);


		void MoveTo(Vec3 _dot_a, Vec3 _dot_b);
		void RotateTo();
		Vec3 mObjectivePos;

		float Dot(Vec3 a, Vec3 b);

		float Mag(Vec3 a);

	private:
		GameObject* pCamera;
		bool isEventOn;
		int mPlayedNum = 0;
	};
}

