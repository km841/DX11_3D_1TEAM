#include "pch.h"
#include "Ladder.h"

namespace yj
{

	Ladder::Ladder(GameObject* _EnterPoint, GameObject* _ExitPoint, GameObject* _EnterCol, GameObject* _ExitCol)
		:GameObject(LayerType::Ladder)
	{
		pEnterPoint = _EnterPoint;
		pExitPoint = _EnterPoint;
		pEnterCol = _EnterCol;
		pExitCol = _ExitCol;
		pEnterPoint->SetName(L"LadderEnterPoint");
		pExitPoint->SetName(L"LadderExitPoint");
	}
	Ladder::~Ladder()
	{

	}
}