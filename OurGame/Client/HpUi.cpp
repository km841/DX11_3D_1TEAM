#include "pch.h"
#include "HpUi.h"

#include "Timer.h"
#include "Factory.h"

#include "SceneManager.h"

yj::HpUi* yj::HpUi::spHpUi;

namespace yj
{
	HpUi::HpUi()
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

	}
	void HpUi::AddHpUI()
	{
		Scene * mScene = SceneManager::GetInstance()->GetScene(SceneType::Title);
		
		for (int i = 0; i < 4; i++)
		{
			Interface* pHpFrame = Factory::CreateInterface<Interface>(Vec3::Zero, Vec2(33.f, 22.f), L"..\\Resources\\Texture\\hud_hp_bar.png");
			mScene->AddGameObject(pHpFrame);
			mpHpFrame[i] = pHpFrame;
		}
		mpHpFrame[0]->GetTransform()->SetPosition(Vec3(-500.0f,400.0f,1.0f));
		mpHpFrame[1]->GetTransform()->SetPosition(Vec3(-442.5f, 400.f, 1.0f));
		mpHpFrame[2]->GetTransform()->SetPosition(Vec3(-385.5f, 400.f, 1.0f));
		mpHpFrame[3]->GetTransform()->SetPosition(Vec3(-328.5f, 400.f, 1.0));

		for (int i = 0; i < 4; i++)
		{
			Interface* pHpEmty = Factory::CreateInterface<Interface>(Vec3::Zero, Vec2(33.f, 22.f), L"..\\Resources\\Texture\\hud_hp_bar.png");
			mScene->AddGameObject(pHpEmty);
			mpEmty[i] = pHpEmty;
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
		}
		mpHpIn[0]->GetTransform()->SetPosition(Vec3(-500.0f, 400.0f, 1.0f));
		mpHpIn[1]->GetTransform()->SetPosition(Vec3(-442.5f, 400.f, 1.0f));
		mpHpIn[2]->GetTransform()->SetPosition(Vec3(-385.5f, 400.f, 1.0f));
		mpHpIn[3]->GetTransform()->SetPosition(Vec3(-328.5f, 400.f, 1.0));

	}
	void HpUi::HpRestore()
	{

	}
	void HpUi::HpDecrease()
	{
		//switch (GetPlayerHp())
		//{
		//case 0:
		//	//사망임으로 동작 불필요
		//	break;
		//case 1:
		//	mpHpIn[1]->Disable();
		//	mpEmty[1]->Disable();

		//	break;
		//case 2:
		//	mpHpIn[2]->Disable();
		//	mpEmty[2]->Disable();
		//	break;
		//case 3:
		//	mpHpIn[3]->Disable();
		//	mpEmty[3]->Disable();
		//	break;
		//}


		////줄어듦
		////3면 4칸 in과 frame disable
		////3면 4칸 in과 frame disable
		////3면의 색상 4칸과 동일화

		//// 2면 3칸 in과 frame 삭제
		//// 2면 1면 주광빛
		//// 
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
	int HpUi::GetPlayerHp()
	{
		return PLAYER->GetHp();
	}
	
}