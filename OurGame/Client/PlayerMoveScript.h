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
    void CheckPenetration(RigidBody* _rigidBody, LayerType _eLayertype);

    float mMoveSpeed;
};

