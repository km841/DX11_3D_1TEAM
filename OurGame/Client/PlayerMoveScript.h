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

    void SimpleFunc() { MessageBoxA(NULL, "Callback", "Test", MB_OK); }
    void AutoStepping(float _height);
private:
    void CheckPenetration(RigidBody* _rigidBody, LayerType _eLayertype);
    

    float mMoveSpeed;
};

