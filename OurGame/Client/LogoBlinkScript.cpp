#include "pch.h"
#include "LogoBlinkScript.h"
#include "GameObject.h"
#include "Interface.h"
#include "Timer.h"

namespace hm
{
	LogoBlinkScript::LogoBlinkScript()
		: mRatio(0.7f)
		, mSign(1)
	{
	}

	void LogoBlinkScript::FixedUpdate()
	{
		Interface* pInterface = static_cast<Interface*>(GetGameObject());
		
		if (mRatio < 0.5f || mRatio > 1.f)
			mSign = -mSign;

		mRatio += mSign * DELTA_TIME;
		pInterface->SetAlpha(mRatio);
	}

	Component* LogoBlinkScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new LogoBlinkScript);
	}
}

