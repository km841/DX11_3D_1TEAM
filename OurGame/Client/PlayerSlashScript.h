#pragma once
#include "MonoBehavior.h"
class PlayerSlashScript :
    public MonoBehavior
{
public:
    PlayerSlashScript();
    virtual ~PlayerSlashScript() = default;

    virtual void FixedUpdate() override;
    virtual Component* Clone(GameObject* _pGameObject);

private:
    float mElapsedTime;
};

