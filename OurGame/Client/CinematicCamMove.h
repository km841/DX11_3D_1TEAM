#pragma once

#include "MonoBehavior.h"
#include "GameObject.h"
#include "Camera.h"

namespace yj
{

	class CinematicCamMove : public MonoBehavior
	{
	public:
		CinematicCamMove();
		virtual ~CinematicCamMove() = default;

		virtual void Initialize();
		virtual Component* Clone(GameObject* _pGameObject);

		void CamEventTrigger(int _event_num);

	public:
		virtual void Update();


		void MoveTo(Vec3 _dot_a, Vec3 _dot_b);
		void RotateTo();
		Vec3 mObjectivePos;

	private:
		GameObject* pCamera;
		bool isEventOn;
		int mPlayedNum = 0;
	};
}