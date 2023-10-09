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

    void SetOffSetPos(Vec3 _Pos) { OffSetPos = _Pos; }
private:
    Vec3 OffSetPos;
};

