#include "pch.h"
#include "StartButtonScript.h"
#include "Interface.h"
#include "EventManager.h"
#include "RenderManager.h"

namespace hm
{
	StartButtonScript::StartButtonScript(const wstring& _name, MapType _eMapType)
		: meMapType(_eMapType)
		, mName(_name)
	{
		mTimer.SetEndTime(0.5f);
	}

	void StartButtonScript::FixedUpdate()
	{
		if (mTimer.GetIsRun())
		{
			mTimer.Update();
			float ratio = mTimer.GetProgress();
			Interface* pInterface = static_cast<Interface*>(GetGameObject());

			pInterface->SetText(mName, 40.f - ratio * 40.f, false);
			pInterface->SetTextColor(Vec4(1.f, 1.f, 1.f, 1.f - ratio));
		}

		if (mTimer.IsFinished())
		{
			Interface* pInterface = static_cast<Interface*>(GetGameObject());
			pInterface->SetText(L"", 1, false);
			mTimer.Stop();
			GET_SINGLE(EventManager)->PushSceneChangeEvent(meMapType);
		}
	}

	Component* StartButtonScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new StartButtonScript(mName, meMapType));
	}

	void StartButtonScript::Start()
	{
		mTimer.Start();
	}
}

