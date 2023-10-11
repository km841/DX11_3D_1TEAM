#include "pch.h"
#include "HpUi.h"

#include "Timer.h"
#include "Factory.h"

#include "SceneManager.h"

yj::HpUi* yj::HpUi::spHpUi;

namespace yj
{
	HpUi::HpUi()
		:isShake(false),
		mShakeSpeed(5.0f),
		mMaxSize(0.5f)
	{
		spHpUi = this; //정적변수 선언
	}
	HpUi::~HpUi()
	{
	}

	
	Component* HpUi::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new HpUi);
	}

	void HpUi::Initialize()
	{
		AddHpUI();
	}
	void HpUi::Update()
	{
		if (isShake)
		{
			HpBarShake();
		}
	}
	void HpUi::AddHpUI()
	{
		Scene * mScene = SceneManager::GetInstance()->GetScene(SceneType::Title);
		
		for (int i = 0; i < 4; i++)
		{
			Interface* pHpEmty = Factory::CreateInterface<Interface>(Vec3::Zero, Vec2(33.f, 22.f), L"..\\Resources\\Texture\\hud_hp_bar.png");
			mScene->AddGameObject(pHpEmty);
			mpEmty[i] = pHpEmty;
			pHpEmty->SetDontDestroyObject(L"Emty");
		}
		mpEmty[0]->GetTransform()->SetPosition(Vec3(-500.0f, 400.0f, 1.0f));
		mpEmty[1]->GetTransform()->SetPosition(Vec3(-442.5f, 400.f, 1.0f));
		mpEmty[2]->GetTransform()->SetPosition(Vec3(-385.5f, 400.f, 1.0f));
		mpEmty[3]->GetTransform()->SetPosition(Vec3(-328.5f, 400.f, 1.0));
		
		for (int i = 0; i < 4; i++)
		{
			Interface* pHpIn = Factory::CreateInterface<Interface>(Vec3(-328.5f, 400.f, 1.0f), Vec2(33.f, 22.f), L"..\\Resources\\Texture\\HP_Blip_Thin.png");
			mScene->AddGameObject(pHpIn);
			mpHpIn[i] = pHpIn;
			mpHpIn[i]->SetDontDestroyObject(L"Side");
		}
		mpHpIn[0]->GetTransform()->SetPosition(Vec3(-500.0f, 400.0f, 1.0f));
		mpHpIn[1]->GetTransform()->SetPosition(Vec3(-442.5f, 400.f, 1.0f));
		mpHpIn[2]->GetTransform()->SetPosition(Vec3(-385.5f, 400.f, 1.0f));
		mpHpIn[3]->GetTransform()->SetPosition(Vec3(-328.5f, 400.f, 1.0));
		mpHpIn[3]->SetColor(Vec3::Color(181, 235, 84));
		mpHpIn[2]->SetColor(Vec3::Color(134, 176, 59));
		mpHpIn[1]->SetColor(Vec3::Color(134, 176, 59));
		mpHpIn[0]->SetColor(Vec3::Color(134, 176, 59));
	}
	void HpUi::HpRestore()
	{

	}
	void HpUi::HpDecrease()
	{
		switch (GetPlayerHp())
		{
		case 0:
			//사망임으로 동작 불필요
			break;
		case 1:
			mpHpIn[1]->Disable();
			mpEmty[1]->Disable();
			mpHpIn[0]->SetColor(Vec3::Color(238, 70, 75));
			ShakeOn();
			break;
		case 2:
			mpHpIn[2]->Disable();
			mpEmty[2]->Disable();
			mpHpIn[0]->SetColor(Vec3::Color(185, 235, 84));
			mpHpIn[1]->SetColor(Vec3::Color(185, 140, 84));
			break;
		case 3:
			mpHpIn[3]->Disable();
			mpEmty[3]->Disable();
			mpHpIn[2]->SetColor(Vec3::Color(181, 235, 84));
			break;
		}
		if (GetPlayerHp() > 1)
		{
			ShakeOff();
		}
	}

	void HpUi::HpBarShake()
	{
		Vec3 mHpInSize = mpHpIn[0]->GetTransform()->GetScale();;
		Vec3 mHpInFixedSize;
		
		if (mShakeState == 0)
		{
			mHpInFixedSize += Vec3(DELTA_TIME * mShakeSpeed, DELTA_TIME * mShakeSpeed, DELTA_TIME * mShakeSpeed);
			mpHpIn[0]->GetTransform()->SetScale(mHpInFixedSize);
		}
		else if (mShakeState == 1)
		{
			mHpInFixedSize += Vec3(DELTA_TIME * mShakeSpeed, DELTA_TIME * mShakeSpeed, DELTA_TIME * mShakeSpeed);
			mpHpIn[0]->GetTransform()->SetScale(mHpInFixedSize);
		}

	}

	void HpUi::UiOff()
	{
		for (int i = 0; i < 4; i++)
		{
			mpHpIn[i]->Disable();
			mpEmty[i]->Disable();
		}
	}
	void HpUi::UiOn()
	{
		for (int i = 0; i < 4; i++)
		{
			mpHpIn[i]->Enable();
			mpEmty[i]->Enable();
		}
	}

	int HpUi::GetPlayerHp()
	{
		return PLAYER->GetHp();
	}
	HpUi* HpUi::GetHpUI()
	{
		return spHpUi;
	}

}