#pragma once
#include "GameObject.h"

namespace hm
{
	class CameraHolder :
		public GameObject
	{
	public:
		CameraHolder();
		virtual ~CameraHolder();
		CameraHolder* Clone()
		{
			CameraHolder* pHolder = GameObject::Clone<CameraHolder>();
			return pHolder;
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


