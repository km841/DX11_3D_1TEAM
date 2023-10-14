#pragma once
#include "GameObject.h"

namespace hm
{
	class BossLaser :
		public GameObject
	{
	public:
		BossLaser();
		virtual ~BossLaser();
		BossLaser* Clone()
		{
			BossLaser* pBossLaser = GameObject::Clone<BossLaser>();
			return pBossLaser;
		}

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();
		virtual void Destroy();

	private:

	};
}


