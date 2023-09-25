#pragma once

#include "GameObject.h"

namespace yj
{
	class Ladder : public GameObject
	{
	public:
		Ladder(GameObject* _EnterPoint, GameObject* _ExitPoint, GameObject* _EnterCol, GameObject* _ExitCol);
		virtual ~Ladder();
	public:

		GameObject*  GetEnterPoint() { return pEnterPoint; }
		GameObject*  GetExitPoint() { return pExitPoint; }
	private:
		GameObject* pEnterPoint;
		GameObject* pExitPoint;

		GameObject* pEnterCol;
		GameObject* pExitCol;

	};
}