#pragma once
#include "GameObject.h"
namespace hm
{
	class WallObject :
		public GameObject
	{
	public:
		WallObject();
		virtual ~WallObject();
		WallObject* Clone()
		{
			WallObject* pWallObject = GameObject::Clone<WallObject>();
			return pWallObject;
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

