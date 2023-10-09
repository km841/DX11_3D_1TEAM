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

    void SetAniRatio(float _AniRatio) { AniRatio = _AniRatio ;}
    void SetInit(Vec3 _EndScale, float _StartRatio, float _magn = 1) 
    {
        EndScale = _EndScale; StartRatio = _StartRatio; magn = _magn;
    }

    void SetOffSetPos(Vec3 _Pos) { OffSetPos = _Pos; }
private:
    Vec3 OffSetPos;

    Vec3 EndScale;
    float StartRatio;
    float magn = 1;

    float AniRatio;
};

