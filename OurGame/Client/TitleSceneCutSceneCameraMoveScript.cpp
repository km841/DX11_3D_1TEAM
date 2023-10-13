#include "pch.h"
#include "TitleSceneCutSceneCameraMoveScript.h"
#include "GameObject.h"
#include "Transform.h"

namespace jh
{
	TitleSceneCutSceneCameraMoveScript::TitleSceneCutSceneCameraMoveScript() :
		mLeftPos(Vec3::Zero),
		mLeftRot(Vec3::Zero),
		mRightPos(Vec3::Zero),
		mRightRot(Vec3::Zero),
		mbIsRightSide(false)
	{
	}

	Component* TitleSceneCutSceneCameraMoveScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new TitleSceneCutSceneCameraMoveScript);
	}

	void TitleSceneCutSceneCameraMoveScript::FixedUpdate()
	{
		mTimer.SetEndTime(5.f);

		if (false == mTimer.GetIsRun())
			mTimer.Start();

		mTimer.Update();

		float progress = mTimer.GetProgress();

		if (false == mbIsRightSide)
		{
			Vec3 pos = Lerp(mLeftPos, mRightPos, progress);
			GetGameObject()->GetTransform()->SetPosition(pos);
			Vec3 rot = Lerp(mLeftRot, mRightRot, progress);
			GetGameObject()->GetTransform()->SetRotation(rot);
		}
		else
		{
			Vec3 pos = Lerp(mRightPos, mLeftPos, progress);
			GetGameObject()->GetTransform()->SetPosition(pos);
			Vec3 rot = Lerp(mRightRot, mLeftRot, progress);
			GetGameObject()->GetTransform()->SetRotation(rot);
		}

		if (true == mTimer.IsFinished())
		{
			mTimer.Stop();
			mbIsRightSide = !mbIsRightSide;
		}
	}

	void TitleSceneCutSceneCameraMoveScript::SetLeft(Vec3 _leftPos, Vec3 _leftRot)
	{
		mLeftPos = _leftPos;
		mLeftRot = _leftRot;
	}

	void TitleSceneCutSceneCameraMoveScript::SetRight(Vec3 _rightPos, Vec3 _rightRot)
	{
		mRightPos = _rightPos;
		mRightRot = _rightRot;
	}
}