#pragma once
#include "Component.h"

namespace hm
{
	class BehaviorNode;
	class AI :
		public Component
	{
	public:
		AI();
		virtual ~AI();
		virtual Component* Clone(GameObject* _pGameObject);

	public:
		virtual void Update();

	public:
		BehaviorNode* GetRootNode()						{ return mpRoot; }
		void		  SetRootNode(BehaviorNode* _pRoot) { mpRoot = _pRoot; }

	private:
		BehaviorNode* mpRoot;
		bool mbInit;
	};
}


