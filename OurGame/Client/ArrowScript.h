#pragma once
#include "MonoBehavior.h"
#include "TimerObject.h"

class ArrowScript :
    public MonoBehavior
{
public:
    ArrowScript();
    virtual ~ArrowScript() = default;

    virtual void Initialize() override;
    virtual void FixedUpdate() override;

    void SetPlayerState(PlayerState _eStateNum); // 플레이어 상태를 가져오는 함수
    virtual Component* Clone(GameObject* _pGameObject);

public:
    bool GetArrowAtkCheck() { return ArrowAtkCheck; }
    void SetArrowAtkCheck(bool _ArrowAtkCheck) { ArrowAtkCheck = _ArrowAtkCheck; }

    bool GetIsBurn() { return ArrowAtkCheck; }
    void SetBurn() { isBurn = true; }   
    void BurnReset() { isBurn = false; }
    void SetmSpeed() { mSpeed = 40; }

    void SetDirPos(Vec3 _dir) { DirPos = _dir; }
private:
    PlayerState mPlayerStateNum;

    bool ArrowAtkCheck = false;
    Vec3 DirPos = Vec3::Zero;

    TimerObject timerObj;

    bool isBurn = false;

    int mSpeed;
};

