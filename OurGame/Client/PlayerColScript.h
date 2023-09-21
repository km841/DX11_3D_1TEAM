#pragma once
#include "MonoBehavior.h"
class PlayerColScript :
    public MonoBehavior
{
public:
    PlayerColScript();
    virtual ~PlayerColScript() = default;

    virtual void Initialize() override;
    virtual void FixedUpdate() override;


    virtual Component* Clone(GameObject* _pGameObject);
};