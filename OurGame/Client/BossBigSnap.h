#pragma once
#include "GameObject.h"
namespace hm
{
	class BossBigSnap :
		public GameObject
	{
	public:
		BossBigSnap();
		virtual ~BossBigSnap();
		BossBigSnap* Clone()
		{
			BossBigSnap* pBigSnap = GameObject::Clone<BossBigSnap>();
			return pBigSnap;
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


