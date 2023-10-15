#include "pch.h"
#include "CutSceneCameraMoveScript.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "EventSystem.h"
#include "TextBox.h"
#include "Player.h"
#include "Input.h"
#include "Timer.h"

namespace jh
{
	CutSceneCameraMoveScript::CutSceneCameraMoveScript() :
		mWidePos(Vec3(-17.14f, -0.83f, 1.58f)),
		mWideRot(Vec3(22.18f, 135.49f, 0.f)),
		mClosePos(Vec3(-12.34f, -5.735f, -9.34f)),
		mCloseRot(Vec3(3.62f, 98.78f, 0.f)),
		mDoorStartPos(Vec3(-3.69f, 19.75f, 9.34f)),
		mDoorEndPos(Vec3(0.745f, 17.13f, 4.68f)),
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
			if (2 == mSequenceNum)
				MainOfficeMove3();
			if (3 == mSequenceNum)
				MainOfficeMove4();
			if (4 == mSequenceNum)
				MainOfficeMove5();
			break;
		}

		if (IS_DOWN(KeyType::U))
			SetSequence(1);
		if (IS_DOWN(KeyType::I))
			SetSequence(2);
		if (EVENTSYSTEM->CheckEventOn("DoorApearCamMoveEvent"))
		{
			EVENTSYSTEM->EventOn("DoorApearEvent");
			SetSequence(2);
		}
		if (EVENTSYSTEM->CheckEventOn("ChandlerZoomEvent"))
		{
			SetSequence(1);
			TEXTBOX->SetWriteTexts(11, 13, "ChandlerZoomOutEvent");
			TEXTBOX->Apear();
			SetSequence(5); // <- 번호 바꿔 줘야함!
		}
		if (EVENTSYSTEM->CheckEventOn("ChandlerZoomOutEvent"))
		{
			TEXTBOX->SetWriteTexts(13, 16,"SpeechEndEvent");
			TEXTBOX->Apear();
			SetSequence(5);
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
			TEXTBOX->SetWriteTexts(3, 9, "DoorApearCamMoveEvent");
			TEXTBOX->Apear();
			mMainOfficeTimer.Stop();
			SetSequence(-1);	// 반복 금지용
		}
	}

	void CutSceneCameraMoveScript::MainOfficeMove2()
	{
		mMainOfficeTimer2.SetEndTime(5.f);

		if (false == mMainOfficeTimer2.GetIsRun())
			mMainOfficeTimer2.Start();

		mMainOfficeTimer2.Update();

		float progress = mMainOfficeTimer2.GetProgress();

		Vec3 endPos = Vec3(-10.2f, -5.87f, -9.67f);
		Vec3 endRot = Vec3(3.62f, 98.78f, 0.f);

		Vec3 pos = Lerp(mClosePos, endPos, progress);
		GetGameObject()->GetTransform()->SetPosition(pos);
		Vec3 rot = Lerp(mCloseRot, endRot, progress);
		GetGameObject()->GetTransform()->SetRotation(rot);

		if (true == mMainOfficeTimer2.IsFinished())
		{
			mMainOfficeTimer2.Stop();
			SetSequence(-1);	// 반복 금지용
			
		}
	}

	void CutSceneCameraMoveScript::MainOfficeMove3()
	{
		mMainOfficeTimer3.SetEndTime(2.5f);

		if (false == mMainOfficeTimer3.GetIsRun())
			mMainOfficeTimer3.Start();

		mMainOfficeTimer3.Update();

		float progress = mMainOfficeTimer3.GetProgress();
		
		mDoorStartRot = mWideRot;
		mDoorStartRot.y = 137.4f;

		Vec3 pos = Lerp(mWidePos, mDoorStartPos, progress);
		GetGameObject()->GetTransform()->SetPosition(pos);
		Vec3 rot = Lerp(mWideRot, mDoorStartRot, progress);
		GetGameObject()->GetTransform()->SetRotation(rot);

		if (true == mMainOfficeTimer3.IsFinished())
		{
			mMainOfficeTimer3.Stop();
			SetSequence(3);	// MainOfficeMove4로 이동
		}
	}

	void CutSceneCameraMoveScript::MainOfficeMove4()
	{
		mMainOfficeTimer4.SetEndTime(4.f);

		if (false == mMainOfficeTimer4.GetIsRun())
			mMainOfficeTimer4.Start();

		mMainOfficeTimer4.Update();

		float progress = mMainOfficeTimer4.GetProgress();

		Vec3 pos = Lerp(mDoorStartPos, mDoorEndPos, progress);
		GetGameObject()->GetTransform()->SetPosition(pos);
		//Vec3 rot = Lerp(mDoorStartRot, mDoorEndRot, progress);
		//GetGameObject()->GetTransform()->SetRotation(rot);

		if (true == mMainOfficeTimer4.IsFinished())
		{
			mMainOfficeTimer4.Stop();
			SetSequence(4);	// MainOfficeMove5로 이동
			TEXTBOX->SetWriteTexts(10, 10, "ChandlerZoomEvent");
			TEXTBOX->Apear();
		}
	}

	void CutSceneCameraMoveScript::MainOfficeMove5()
	{
		mMainOfficeTimer5.SetEndTime(1.f);

		if (false == mMainOfficeTimer5.GetIsRun())
			mMainOfficeTimer5.Start();

		mMainOfficeTimer5.Update();

		float progress = mMainOfficeTimer5.GetProgress();

		Vec3 pos = Lerp(mDoorEndPos, mWidePos, progress);
		GetGameObject()->GetTransform()->SetPosition(pos);
		Vec3 rot = Lerp(mDoorStartRot, mWideRot, progress);
		GetGameObject()->GetTransform()->SetRotation(rot);

		if (true == mMainOfficeTimer5.IsFinished())
		{
			mMainOfficeTimer5.Stop();
			SetSequence(-1);	// 반복 금지용
		}
	}
}
