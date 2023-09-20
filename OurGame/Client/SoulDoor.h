#pragma once

#include "GameObject.h"

namespace yj
{

	class SoulDoor : public GameObject
	{
	public:

		virtual void Update();
		void Drop();


	public:

		enum State
		{
			Standby = 1,
			Apear,
			MoveUp,
			MoveDown,
			CloseStandby,
			Open,
			End
		};
		State state;

	private:
		Vec3 mApearPos;
		Vec3 mBargePos;

		float mCurrSpeed;
		float mCurrAddSpeed = 0.0f;
		float mInitAddSpeed;
		float mDropSpeed;
		float mLimitSpeed;
		float mLimitDropSpeed;                                                 

		GameObject* pFrame;
		GameObject* pDoor;
		
		float mDeceleration;

		float mUpLimit;
		float mDownLimit;

		int mSequence;

	};
}