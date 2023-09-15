#pragma once
#include "Effect.h"

class SwordHeavyEffect :
    public Effect
{
public:
	SwordHeavyEffect();
	virtual ~SwordHeavyEffect();
	SwordHeavyEffect* Clone()
	{
		SwordHeavyEffect* pEffect = GameObject::Clone<SwordHeavyEffect>();
		return pEffect;
	}

public:
	virtual void Initialize();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void FinalUpdate();
	virtual void Render();
	virtual void Destroy();

	virtual void PushBloomData();

private:

};

