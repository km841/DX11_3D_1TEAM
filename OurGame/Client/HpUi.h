#pragma once
#include "GameObject.h"
#include "Interface.h"

#include "Player.h"
#include "MonoBehavior.h"

namespace yj
{
	class HpUi : public MonoBehavior
	{
	public:
		HpUi();
		virtual ~HpUi();

		virtual Component* Clone(GameObject* _pGameObject);
		virtual void Initialize();
		virtual void Update();

		static HpUi* spHpUi;
		static HpUi* GetHpUI();
	public:
		void AddHpUI();
	private:

		void HpRestore();

		void HpDecrease();
		void HpBarShake();
		
		int GetPlayerHp();

	private:
		
		Interface* mpHpFrame[4];
		Interface* mpHpIn[4];
		Interface* mpEmty[4];

		Vec2 mInitSize;
		Vec2 mMaxSize;
		int mShakeState = -1;
		float mShakeSpeed;
	};
}
