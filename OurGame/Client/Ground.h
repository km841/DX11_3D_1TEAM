#pragma once
#include "GameObject.h"

namespace hm
{
	class Ground :
		public GameObject
	{
	public:
		Ground();
		virtual ~Ground();
		Ground* Clone()
		{
			Ground* pGround = GameObject::Clone<Ground>();
			return pGround;
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


