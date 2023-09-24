#pragma once
#include "MonoBehavior.h"
class BowScript :
    public MonoBehavior
{
public:
    BowScript();
    virtual ~BowScript() = default;

    virtual void Initialize() override;
    virtual void FixedUpdate() override;

    void SetPlayerState(PlayerState _eStateNum); // 플레이어 상태를 가져오는 함수
    virtual Component* Clone(GameObject* _pGameObject);


private:
    PlayerState mPlayerStateNum;
};

