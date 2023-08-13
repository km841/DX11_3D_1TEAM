#pragma once
#include "MonoBehavior.h"
class PlayerMoveScript :
    public MonoBehavior
{
public:
    PlayerMoveScript();
    ~PlayerMoveScript() = default;

    virtual void FixedUpdate() override;
    virtual Component* Clone(GameObject* _pGameObject) override;

private:
    float mMoveSpeed;
};

