#include "pch.h"
#include "SlashGlareScript.h"
#include "GameObject.h"
#include "Timer.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Resources.h"
#include "Input.h"

namespace hm
{
	SlashGlareScript::SlashGlareScript()
		: meState(SlashGlareState::None)
	{
		mBeginTimer.SetEndTime(0.3f);
		mEndTimer.SetEndTime(0.3f);
	}

	void SlashGlareScript::FixedUpdate()
	{
		if (true == mBeginTimer.GetIsRun())
		{
			mBeginTimer.Update();

			if (mBeginTimer.IsFinished())
			{
				mEndTimer.Start();
				meState = SlashGlareState::End;
			}
		}

		if (true == mEndTimer.GetIsRun())
		{
			mEndTimer.Update();

			if (mEndTimer.IsFinished())
			{
				if (nullptr != mEndCallback)
					mEndCallback();

				meState = SlashGlareState::None;
				mEndTimer.Stop();
			}
		}

		shared_ptr<Texture> pTexture = GET_SINGLE(Resources)->Load<Texture>(L"SlashWhite", L"..\\Resources\\Texture\\White.png");
		GetMeshRenderer()->GetMaterial()->SetTextureAllSubset(0, pTexture);

		if (SlashGlareState::Begin == meState)
			GetMeshRenderer()->GetMaterial()->SetFloatAllSubset(0, mBeginTimer.GetProgress() * 3.f);
		else if (SlashGlareState::End == meState)
			GetMeshRenderer()->GetMaterial()->SetFloatAllSubset(0, mEndTimer.GetProgress() * 3.f);

		GetMeshRenderer()->GetMaterial()->SetIntAllSubset(2, static_cast<int>(meState));
	}

	Component* SlashGlareScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new SlashGlareScript);
	}
	void SlashGlareScript::Start()
	{
		meState = SlashGlareState::Begin;
		mBeginTimer.Stop();
		mBeginTimer.Start();
		mEndTimer.Stop();
	}
	void SlashGlareScript::SetEndCallback(std::function<void()> _function)
	{
		mEndCallback = _function;
	}
}

