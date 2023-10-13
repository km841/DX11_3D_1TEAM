#pragma once
#include "MonoBehavior.h"
#include "TimerObject.h"

namespace jh
{
	class TitleSceneCutSceneCameraMoveScript : public MonoBehavior
	{
	public:
		TitleSceneCutSceneCameraMoveScript();
		virtual ~TitleSceneCutSceneCameraMoveScript() = default;
		virtual Component* Clone(GameObject* _pGameObject);

	public:
		virtual void FixedUpdate() override;

		void SetLeft(Vec3 _leftPos, Vec3 _leftRot);
		void SetRight(Vec3 _rightPos, Vec3 _rightRot);

	private:
		Vec3 mLeftPos;
		Vec3 mRightPos;
		Vec3 mLeftRot;
		Vec3 mRightRot;

		TimerObject mTimer;
		bool mbIsRightSide;
	};
}
