#pragma once

#include "Monobehavior.h"
#include "GameObject.h"

namespace yj
{
	class PlayerMoveOverMapScript : public MonoBehavior
	{
	public:
		PlayerMoveOverMapScript();
		~PlayerMoveOverMapScript() = default;

		virtual Component* Clone(class GameObject* _pGameObject);
	public:
		void SetMoveOverNum(int potal_num) { mMoveOverNum = potal_num; }
		int GetMoveOverNum() { return mMoveOverNum; }
	private:
		int mMoveOverNum = -1;
	};
}

