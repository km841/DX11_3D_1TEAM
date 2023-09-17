#pragma once
#include "MonoBehavior.h"
class SwordScript :
    public MonoBehavior
{
public:
    SwordScript();
    virtual ~SwordScript() = default;

    virtual void Initialize() override ;
    virtual void FixedUpdate() override;

    virtual Component* Clone(GameObject* _pGameObject);


};

