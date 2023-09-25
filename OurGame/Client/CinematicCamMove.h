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
		virtual Component* Clone(GameObject* _pGameObject);
		virtual void Initialize();
		virtual void Update();

	public:
		void CamEventTrigger(int _event_num);

		void MoveTo(Vec3 _dot_a, Vec3 _dot_b);
		void RotateTo();

		float Dot(Vec3 a, Vec3 b);
		float Mag(Vec3 a);

		void SetFollowPlayer() { isPlayerFollow = true; }
		void DeFollowPlayer() { isPlayerFollow = false; }
		
	public:
		Vec3 mObjectivePos;
			
	private:
		GameObject* pCamera;
		bool isEventOn;
		int mPlayedNum = 0;
		bool isPlayerFollow = true;
	};
}

