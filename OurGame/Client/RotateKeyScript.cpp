#include "pch.h"
#include "RotateKeyScript.h"
#include "Timer.h"
#include "Transform.h"
#include "GameObject.h"

RotateKeyScript::RotateKeyScript()
	: mAccTime(0.f)
	, mSpeed(20000.f)
	, mPeriod(6.f)
{
}

RotateKeyScript::~RotateKeyScript()
{
}

Component* RotateKeyScript::Clone(GameObject* _pGameObject)
{
	return _pGameObject->AddComponent(new RotateKeyScript);
}

void RotateKeyScript::FixedUpdate()
{
	mAccTime += DELTA_TIME;
	GetTransform()->SetRotation(AXIS_Y, mSpeed * sinf(mAccTime * XM_2PI) * DELTA_TIME );
}
