#pragma once
#include "MonoBehavior.h"
class RotateKeyScript :
    public MonoBehavior
{
public:
    RotateKeyScript();
    virtual ~RotateKeyScript();
    virtual Component* Clone(GameObject* _pGameObject);

public:
    virtual void FixedUpdate() override;

private:
    float mAccTime;
    float mSpeed;
    float mPeriod;
    int mSign;

};

