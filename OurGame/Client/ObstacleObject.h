#pragma once
#include "GameObject.h"

namespace hm
{
	class ObstacleObject :
		public GameObject
	{
	public:
		ObstacleObject();
		virtual ~ObstacleObject();
		ObstacleObject* Clone()
		{
			ObstacleObject* pObstacleObject = GameObject::Clone<ObstacleObject>();
			return pObstacleObject;
		}

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();
		virtual void Destroy();
	};
}
