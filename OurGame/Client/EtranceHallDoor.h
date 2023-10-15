#pragma once
#include "GameObject.h"


namespace yj
{

	class EtranceHallDoor :public GameObject
	{

	public:
		EtranceHallDoor(GameObject* _leftDoor, GameObject* _rightDoor);
		virtual ~EtranceHallDoor();
		void Update();
		void AddKey() { mCurrKey += 1; }

		bool GetIsOpen() { return isOpen; }

	private:

		void Open();

		int mCurrKey = 0;
		int mRequireKey = 2;
		GameObject* mLeftDoor;
		GameObject* mRightDoor;
		bool isOpen;
	};
}
