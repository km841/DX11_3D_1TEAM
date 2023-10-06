#pragma once

#include "GameObject.h"

namespace yj
{

	class SoulDoor : public GameObject
	{
	public:

		SoulDoor(GameObject* _frameObj,GameObject* _doorObj ,GameObject* _EntranceCol, MapType _MapType, int _SpawnPoint);
		virtual ~SoulDoor();

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		

	public:

		void Drop();
		void Open();

		bool GetIsMove() { return isMove; }
		void SetMove() { state = DoorMoveUp;	mFlowSpeed = 3.0f; isMove = true; }
		bool GetIsRot() { return isRot; }
		void SetRot() { isRot = true; }
		void ChangeScene();

	public:

		enum State
		{
			Standby = 1,
			DoorApear,
			DoorMoveUp,
			DoorMoveDown,
			DoorCloseStandby,
			DoorOpen,
			End
		};
		State state;
	
	private:

		GameObject* pDoorObj;
		GameObject* pBackUVObj;
		GameObject* pEntranceColObj;
		
		Vec3 mApearPos;
		Vec3 mBargePos;

		MapType mMapType;

		float mFlowSpeed;
		float mDropSpeed = 30.0f;
		float mLimitDropSpeed;                                                 
		float mRotSpeed;

		bool isMove = false;
		bool isRot;		

		float mDeceleration = 3.0f;

		float mUpLimit;
		float mDownLimit = 5.1f;
		float mRotLimit;

		int mSpawnPoint = -1;

		int mOpenSequnce = -1;
		int mSequence;
		int mStartNum = -1;
	};
}