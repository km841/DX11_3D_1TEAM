#pragma once
#include "MonoBehavior.h"
class MonsterBackswingColScript :
    public MonoBehavior
{
public:
    MonsterBackswingColScript();
    virtual ~MonsterBackswingColScript() = default;

    virtual void Initialize() override;
    virtual void FixedUpdate() override;



    virtual Component* Clone(GameObject* _pGameObject);


    void SetOffSetPos(Vec3 _Pos) { OffSetPos = _Pos; }
private:
    Vec3 OffSetPos;
   
};

