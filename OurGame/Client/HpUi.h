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
		void UiOff();
		void UiOn();

	private:

		void HpRestore();

		void HpDecrease();
		void HpBarShake();
		
		int GetPlayerHp();
		void ShakeOn() { isShake = true; mShakeState = 0; }
		void ShakeOff() { isShake = false; mShakeState = -1; }

	private:
		
		//Interface* mpHpFrame;
		Interface* mpHpIn[4];
		Interface* mpEmty[4];

		Vec2 mInitSize;
		Vec2 mMaxSize;
		int mShakeState = -1;
		float mShakeSpeed;
		bool isShake;
	};
}
