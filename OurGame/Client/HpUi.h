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

		static HpUi* GetHpUI();
		static HpUi* spHpUi;
	public:
		void AddHpUI();
		void UiOff();
		void UiOn();
		void HpDecrease();

	private:

		void HpRestore();

		void HpBarShake();

		int GetPlayerHp();
		void ShakeOn() { isShake = true; mShakeState = 0; }
		void ShakeOff() { isShake = false; mShakeState = -1; }

	private:

		Interface* mpHpFrame[4];
		Interface* mpHpIn[4];
		Interface* mpEmty[4];
		Interface* pHpContainerFrame;

		Vec2 mInitSize;
		Vec2 mMaxSize;
		int mShakeState = -1;
		float mShakeSpeed;
		bool isShake;
	};

}