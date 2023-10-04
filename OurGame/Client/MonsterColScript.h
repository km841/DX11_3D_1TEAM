#pragma once
#include "MonoBehavior.h"
class MonsterColScript :
    public MonoBehavior
{
public:
    MonsterColScript();
    virtual ~MonsterColScript() = default;

    virtual void Initialize() override;
    virtual void FixedUpdate() override;


    virtual Component* Clone(GameObject* _pGameObject);

};

