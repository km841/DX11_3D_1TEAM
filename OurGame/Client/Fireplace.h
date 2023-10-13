#pragma once
#include "Light.h"

namespace hm
{
    class Fireplace :
        public Light
    {
    public:
        Fireplace();
        virtual ~Fireplace();

        virtual void FinalUpdate() override;
        void Render(Camera* _pCamera);

        virtual Component* Clone(GameObject* _pGameObject);
    };
}


