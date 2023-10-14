#pragma once
#include "MonoBehavior.h"

namespace hm
{
	class LaserLockOnScript :
		public MonoBehavior
	{
    public:
        LaserLockOnScript();
        virtual ~LaserLockOnScript() = default;

        virtual void Initialize() override;
        virtual void FixedUpdate() override;

        virtual Component* Clone(GameObject* _pGameObject);

    private:
        float mFlipWidth;
	};
}


