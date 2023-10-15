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
		void MainOfficeMove();
		void MainOfficeMove2();

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

		int mSequenceNum;
		TimerObject mMainOfficeTimer;
		TimerObject mMainOfficeTimer2;
		bool mbIsAIState;
	};
}
