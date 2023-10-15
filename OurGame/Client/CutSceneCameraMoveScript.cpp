#include "pch.h"
#include "CutSceneCameraMoveScript.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "EventSystem.h"
#include "TextBox.h"
#include "Player.h"
#include "Input.h"
#include "Timer.h"
#include "RenderManager.h"
#include "AudioSound.h"

namespace jh
{
	CutSceneCameraMoveScript::CutSceneCameraMoveScript() :
		mWidePos(Vec3(-17.14f, -0.83f, 1.58f)),
		mWideRot(Vec3(22.18f, 135.49f, 0.f)),
		mClosePos(Vec3(-12.34f, -5.735f, -9.34f)),
		mCloseRot(Vec3(3.62f, 98.78f, 0.f)),
		mDoorStartPos(Vec3(-3.69f, 19.75f, 9.34f)),
		mDoorEndPos(Vec3(0.745f, 17.13f, 4.68f)),
		mBossStartPos(Vec3(2.45f, -5.89f, 1.47f)),
		mBossStartRot(Vec3(-9.77f, 133.65f, 0.f)),
		mBossEndPos(Vec3(3.57f, -5.62f, 0.4f)),
		mBossNameStartPos(Vec3(0.62f, -2.27f, 3.48f)),
		mBossNameStartRot(Vec3(-3.33f, 134.36f, 0.f)),
		mBossNameStartPos2(Vec3(-2.55f, -5.82f, 5.74f)),
		mBossNameStartRot2(Vec3(-6.6f, 132.82f, 0.f)),
		mBossNameEndPos(Vec3(-1.35f, -2.43f, 5.42f)),
		mBossNameEndPos2(Vec3(-6.53f, -6.4f, 8.85f)),
		mbIsAIState(false),
		mMainSequenceNum(-1),
		mBossSequenceNum(0),
		mbAddWhite(false),
		mbIsBGMStart(false)
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
			if (0 == mMainSequenceNum)
				MainOfficeMove();
			if (1 == mMainSequenceNum)
				MainOfficeMove2();
			if (2 == mMainSequenceNum)
				MainOfficeMove3();
			if (3 == mMainSequenceNum)
				MainOfficeMove4();
			if (4 == mMainSequenceNum)
				MainOfficeMove5();
			break;
		case hm::SceneType::BossMap:
			if(0 == mBossSequenceNum)
				BossMapMove();
			if (1 == mBossSequenceNum)
				BossMapMove2();
			if (2 == mBossSequenceNum)
				BossMapMove3();
			break;
		}

		// 확인용 코드
		if (IS_DOWN(KeyType::U))
			SetBossSequence(1);
		if (IS_DOWN(KeyType::I))
			SetBossSequence(2);

		if (EVENTSYSTEM->CheckEventOn("DoorApearCamMoveEvent"))
		{
			EVENTSYSTEM->EventOn("DoorApearEvent");
			SetMainSequence(2);
		}
		if (EVENTSYSTEM->CheckEventOn("ChandlerZoomEvent"))
		{
			SetMainSequence(1);
			TEXTBOX->SetWriteTexts(11, 13, "ChandlerZoomOutEvent");
			TEXTBOX->Apear();
			SetMainSequence(5); // <- 번호 바꿔 줘야함!
		}
		if (EVENTSYSTEM->CheckEventOn("ChandlerZoomOutEvent"))
		{
			TEXTBOX->SetWriteTexts(13, 17,"SpeechEndEvent");
			TEXTBOX->Apear();
			SetDeskPos();
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
			SetMainSequence(-1);	// 반복 금지용
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
			SetMainSequence(-1);	// 반복 금지용
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
			SetMainSequence(3);	// MainOfficeMove4로 이동
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
			SetMainSequence(4);	// MainOfficeMove5로 이동
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
			SetMainSequence(-1);	// 반복 금지용
		}
	}

	void CutSceneCameraMoveScript::SetDeskPos()
	{
		SetMainSequence(-1);
		GetGameObject()->GetTransform()->SetPosition(mWidePos);
		GetGameObject()->GetTransform()->SetRotation(mWideRot);
	}

	void CutSceneCameraMoveScript::BossMapMove()
	{
		mBossMapTimer.SetEndTime(7.f);

		if (false == mBossMapTimer.GetIsRun())
			mBossMapTimer.Start();

		mBossMapTimer.Update();

		float progress = mBossMapTimer.GetProgress();

		Vec3 pos = Lerp(mBossStartPos, mBossEndPos, progress);
		GetGameObject()->GetTransform()->SetPosition(pos);
		GetGameObject()->GetTransform()->SetRotation(mBossStartRot);

		if (true == mBossMapTimer.IsFinished())
		{
			mBossMapTimer.Stop();
			SetBossSequence(-1);	// 반복 금지용
		}
	}

	void CutSceneCameraMoveScript::BossMapMove2()
	{
		GetGameObject()->GetTransform()->SetPosition(Vec3(9.83f, 2.48f, -14.38f));
		GetGameObject()->GetTransform()->SetRotation(Vec3(28.4f, 24.31f, 0.f));
	}

	void CutSceneCameraMoveScript::BossMapMove3()
	{
		// 화면 하얗게
		if (false == mbAddWhite)
		{
			mbAddWhite = true;
			{
				ScreenEffectInfo* info = new ScreenEffectInfo;
				info->eEffectType = ScreenEffectType::WhiteOut;
				info->endTime = 2.f;

				GET_SINGLE(RenderManager)->AddScreenEffect(info);
			}
			{
				ScreenEffectInfo* info = new ScreenEffectInfo;
				info->eEffectType = ScreenEffectType::WhiteIn;
				info->endTime = 2.f;

				GET_SINGLE(RenderManager)->AddScreenEffect(info);
			}
		}

		mBossMapTimer2.SetEndTime(14.f);

		if (false == mBossMapTimer2.GetIsRun())
			mBossMapTimer2.Start();

		mBossMapTimer2.Update();

		float progress = mBossMapTimer2.GetProgress();

		if (0.1f < progress)
		{
			mbIsBGMStart = true;
		}
		if (0.14f <= progress && progress <= 0.45f)
		{
			Vec3 pos = Lerp(mBossNameStartPos, mBossNameEndPos, progress);
			GetGameObject()->GetTransform()->SetPosition(pos);
			GetGameObject()->GetTransform()->SetRotation(mBossNameStartRot);
		}
		else if (0.45f < progress)
		{
			// 여기서 보스 이름 텍스트 출력

			Vec3 pos = Lerp(mBossNameStartPos2, mBossNameEndPos2, progress);
			GetGameObject()->GetTransform()->SetPosition(pos);
			GetGameObject()->GetTransform()->SetRotation(mBossNameStartRot2);
		}

		if (true == mBossMapTimer2.IsFinished())
		{
			mBossMapTimer2.Stop();
			SetBossSequence(-1);	// 반복 금지용
		}
	}
}
