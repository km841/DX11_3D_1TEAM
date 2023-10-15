#pragma once
#include "MonoBehavior.h"
#include "TimerObject.h"

namespace jh
{
	class CutSceneCameraMoveScript : public MonoBehavior
	{
	public:
		CutSceneCameraMoveScript();
		virtual ~CutSceneCameraMoveScript() = default;
		virtual Component* Clone(GameObject* _pGameObject);

	public:
		virtual void FixedUpdate() override;

		/* Title Scene */
		void SetLeft(Vec3 _leftPos, Vec3 _leftRot);
		void SetRight(Vec3 _rightPos, Vec3 _rightRot);
		void TitleMove();

		/* MainOffice */
		void SetStartPos(Vec3 _pos) { mStartPos = _pos; }
		void SetStartRot(Vec3 _rot) { mStartRot = _rot; }
		void SetSequence(int _num) { mSequenceNum = _num; }

		void MainOfficeMove();	// 계단 앞~책상 앞
		void MainOfficeMove2();	// 까마귀 NPC 클로즈업
		void MainOfficeMove3();	// 책상 앞~문
		void MainOfficeMove4();	// 문 클로즈업
		void MainOfficeMove5();	// 문~책상 앞

		void SetDeskPos();

	private:
		/* Title Scene */
		Vec3 mLeftPos;
		Vec3 mRightPos;
		Vec3 mLeftRot;
		Vec3 mRightRot;

		bool mbIsRightSide;
		TimerObject mTitleTimer;

		/* MainOffice */
		Vec3 mStartPos;
		Vec3 mStartRot;

		Vec3 mWidePos;
		Vec3 mWideRot;

		Vec3 mClosePos;
		Vec3 mCloseRot;

		Vec3 mDoorStartPos;
		Vec3 mDoorStartRot;

		Vec3 mDoorEndPos;
		Vec3 mDoorEndRot;

		bool mbIsAIState;

		int mSequenceNum;

		TimerObject mMainOfficeTimer;
		TimerObject mMainOfficeTimer2;
		TimerObject mMainOfficeTimer3;
		TimerObject mMainOfficeTimer4;
		TimerObject mMainOfficeTimer5;
	};
}
