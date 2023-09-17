#pragma once
#include "MonoBehavior.h"
class PlayerSlashScript :
    public MonoBehavior
{
    friend class SwordHeavyEffect;
public:
    PlayerSlashScript();
    virtual ~PlayerSlashScript() = default;

    virtual void FixedUpdate() override;
    virtual Component* Clone(GameObject* _pGameObject);

    void Attack() { mElapsedTime = 0.f; }
    void ChangeReverse();
    void ChangeReverse(bool _bool);

private:
    float mElapsedTime;
    bool mbEnable;
    float mEndTime;
    float mAttackSpeed;
    bool mbReverse;
};

