#include "pch.h"
#include "CutSceneCameraMoveScript.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "EventSystem.h"
#include "TextBox.h"
#include "Player.h"

namespace jh
{
	CutSceneCameraMoveScript::CutSceneCameraMoveScript() :
		mWidePos(Vec3(-17.14f, -0.83f, 1.58f)),
		mWideRot(Vec3(22.18f, 135.49f, 0.f)),
		mbIsAIState(false),
		mSequenceNum(-1)
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
			if (0 == mSequenceNum)
				MainOfficeMove();
			if (1 == mSequenceNum)
				MainOfficeMove2();
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
		PLAYER->SetCutScenePos(Vec3(-8.68f, -8.24f, -9.44f));
		if (false == mbIsAIState)
		{
			mbIsAIState = true;
			PLAYER->StateChange(PlayerState::AIMoveState);
		}

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
			//플레이어 움직임 금지
			TEXTBOX->SetWriteTexts(3, 10, "DoorApearEvent");
			TEXTBOX->Apear();
			mMainOfficeTimer.Stop();
			SetSequence(1);
		}
	}
	void CutSceneCameraMoveScript::MainOfficeMove2()
	{
		mMainOfficeTimer2.SetEndTime(5.f);

		if (false == mMainOfficeTimer2.GetIsRun())
			mMainOfficeTimer2.Start();

		mMainOfficeTimer2.Update();

		float progress = mMainOfficeTimer2.GetProgress();

		Vec3 startPos = Vec3(-12.34f, -5.735f, -9.34f);
		Vec3 startRot = Vec3(3.62f, 98.78f, 0.f);
		Vec3 endPos = Vec3(-10.2f, -5.87f, -9.67f);
		Vec3 endRot = Vec3(3.62f, 98.78f, 0.f);

		Vec3 pos = Lerp(startPos, endPos, progress);
		GetGameObject()->GetTransform()->SetPosition(pos);
		Vec3 rot = Lerp(startRot, endRot, progress);
		GetGameObject()->GetTransform()->SetRotation(rot);
	}
}
