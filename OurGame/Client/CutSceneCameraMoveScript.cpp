#include "pch.h"
#include "CutSceneCameraMoveScript.h"
#include "GameObject.h"
#include "SceneManager.h"

namespace jh
{
	CutSceneCameraMoveScript::CutSceneCameraMoveScript() :
		mWidePos(Vec3(-17.14f, -0.83f, 1.58f)),
		mWideRot(Vec3(22.18f, 135.49f, 0.f))
	{
	}

	Component* CutSceneCameraMoveScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new CutSceneCameraMoveScript);
	}

	void CutSceneCameraMoveScript::FixedUpdate()
	{
		SceneType type = ACTIVE_SCENE->GetSceneType();

		switch (type)
		{
		case hm::SceneType::Title:
			TitleMove();
			break;
		case hm::SceneType::MainOfficeMap:
			if(true == mbIsCutSceneStart)
				MainOfficeMove();
			break;
		}
	}

	void CutSceneCameraMoveScript::SetLeft(Vec3 _leftPos, Vec3 _leftRot)
	{
		mLeftPos = _leftPos;
		mLeftRot = _leftRot;
	}

	void CutSceneCameraMoveScript::SetRight(Vec3 _rightPos, Vec3 _rightRot)
	{
		mRightPos = _rightPos;
		mRightRot = _rightRot;
	}

	void CutSceneCameraMoveScript::TitleMove()
	{
		mTitleTimer.SetEndTime(5.f);

		if (false == mTitleTimer.GetIsRun())
			mTitleTimer.Start();

		mTitleTimer.Update();

		float progress = mTitleTimer.GetProgress();

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

		if (true == mTitleTimer.IsFinished())
		{
			mTitleTimer.Stop();
			mbIsRightSide = !mbIsRightSide;
		}
	}

	void CutSceneCameraMoveScript::MainOfficeMove()
	{
		mMainOfficeTimer.SetEndTime(3.f);

		if (false == mMainOfficeTimer.GetIsRun())
			mMainOfficeTimer.Start();

		mMainOfficeTimer.Update();

		float progress = mMainOfficeTimer.GetProgress();

		Vec3 pos = Lerp(mStartPos, mWidePos, progress);
		GetGameObject()->GetTransform()->SetPosition(pos);
		Vec3 rot = Lerp(mStartRot, mWideRot, progress);
		GetGameObject()->GetTransform()->SetRotation(rot);

		if (true == mMainOfficeTimer.IsFinished())
		{
			mMainOfficeTimer.Stop();
			mbIsCutSceneStart = false;
		}

		//GetGameObject()->GetTransform()->SetPosition(mStartPos);
		//GetGameObject()->GetTransform()->SetRotation(mStartRot);
	}
}
