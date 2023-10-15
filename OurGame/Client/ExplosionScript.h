#pragma once
#include "MonoBehavior.h"
#include "TimerObject.h"

namespace hm
{
    class GameObject;
	class ExplosionScript :
		public MonoBehavior
	{
    public:
        ExplosionScript(GameObject* _pBoss);
        virtual ~ExplosionScript() = default;

        virtual void Initialize() override;
        virtual void FixedUpdate() override;

        virtual Component* Clone(GameObject* _pGameObject);

    private:
        float mAccTime;
        TimerObject mBigTimer;
        TimerObject mDeathTimer;
       

        GameObject* mpBoss;

	};
}


