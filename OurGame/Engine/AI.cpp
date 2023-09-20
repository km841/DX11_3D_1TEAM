#include "pch.h"
#include "AI.h"
#include "BehaviorNode.h"
#include "GameObject.h"

namespace hm
{
	AI::AI()
		: Component(ComponentType::Ai)
		, mpRoot(nullptr)
		, mbInit(false)
	{
	}
	AI::~AI()
	{
		mpRoot->Release();
	}

	Component* AI::Clone(GameObject* _pGameObject)
	{
		AI* pAI = _pGameObject->AddComponent(new AI);
		pAI->mpRoot = mpRoot;

		return pAI;
	}
	void AI::Update()
	{
		if (nullptr != mpRoot)
		{
			if (false == mbInit)
			{
				mbInit = true;
				mpRoot->SetRoot(mpRoot);
				mpRoot->SetAI(this);
			}

			mpRoot->Run();
		}
	}
}