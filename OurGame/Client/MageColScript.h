#pragma once
#include "MonoBehavior.h"
class MageColScript :
    public MonoBehavior
{
public:
    MageColScript();
    virtual ~MageColScript() = default;

    virtual void Initialize() override;
    virtual void FixedUpdate() override;


    virtual Component* Clone(GameObject * _pGameObject);
};