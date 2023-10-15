#pragma once
#include "MonoBehavior.h"
#include "TimerObject.h"

namespace hm
{
	class LaserLockOnScript :
		public MonoBehavior
	{
    public:
        LaserLockOnScript(GameObject* _pBoss);
        virtual ~LaserLockOnScript() = default;

        virtual void Initialize() override;
        virtual void FixedUpdate() override;

        virtual Component* Clone(GameObject* _pGameObject);

    private:
        float mFlipWidth;

        std::queue<Vec3> mPlayerPath;
        TimerObject mDuration;

        GameObject* mpBoss;
	};
}


