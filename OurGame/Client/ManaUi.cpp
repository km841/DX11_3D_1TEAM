#include "pch.h"
#include "ManaUi.h"

#include "SceneManager.h"
#include "Scene.h"

#include "Timer.h"
#include "Input.h"
#include "Factory.h"
#include "Player.h"

#include "ManaIconScript.h"

yj::ManaUi* yj::ManaUi::spManaUi;

namespace yj
{
	ManaUi::ManaUi()
	{
		spManaUi = this;
	}
	ManaUi::~ManaUi()
	{

	}

	Component* ManaUi::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new ManaUi);
	}

	void ManaUi::Initialize()
	{

	}

	void ManaUi::Update()
	{

	}

	void ManaUi::AddManaUI()
	{
		Scene* mScene = SceneManager::GetInstance()->GetScene(SceneType::Title);

		for (int i = 0; i < 5; i++)
		{
			Interface* pMpSlot = Factory::CreateInterface<Interface>(Vec3::Zero, Vec2(15.f, 18.0f), L"..\\Resources\\Texture\\hud_energy_empty.png");
			mScene->AddGameObject(pMpSlot);
			mpMpSlots[i] = pMpSlot;
			pMpSlot->SetDontDestroyObject(L"ManaSlot");
			OnOffList.push_back(pMpSlot);

		}
		mpMpSlots[0]->GetTransform()->SetPosition(Vec3(-663.0f, 357.0f, 1.0f));
		mpMpSlots[1]->GetTransform()->SetPosition(Vec3(-629.5f, 357.0f, 1.0f));
		mpMpSlots[2]->GetTransform()->SetPosition(Vec3(-596.0f, 357.0f, 1.0f));
		mpMpSlots[3]->GetTransform()->SetPosition(Vec3(-564.5f, 357.0f, 1.0));
		mpMpSlots[4]->GetTransform()->SetPosition(Vec3(-531.0f, 357.0f, 1.0));

		for (int i = 0; i < 5; i++)
		{
			Interface* pMpIn = Factory::CreateInterface<Interface>(Vec3::Zero, Vec2(12.f, 15.0f), L"..\\Resources\\Texture\\MP_Box.png");
			mScene->AddGameObject(pMpIn);
			mpMpIns[i] = pMpIn;
			pMpIn->SetDontDestroyObject(L"ManaIn");
			pMpIn->SetColor(Vec3::Color(255, 255, 255));
			//pMpIn->AddComponent<ManaIconScript>();
			OnOffList.push_back(pMpIn);

		}
	/*	mpMpIns[3]->GetScript<ManaIconScript>()->SetBigIcon();
		mpMpIns[4]->GetScript<ManaIconScript>()->SetBigIcon();*/

		mpMpIns[0]->GetTransform()->SetPosition(Vec3(-663.0f, 357.0f, 1.0f));
		mpMpIns[1]->GetTransform()->SetPosition(Vec3(-629.5f, 357.0f, 1.0f));
		mpMpIns[2]->GetTransform()->SetPosition(Vec3(-596.0f, 357.0f, 1.0f));
		mpMpIns[3]->GetTransform()->SetPosition(Vec3(-564.5f, 357.0f, 1.0));
		mpMpIns[4]->GetTransform()->SetPosition(Vec3(-531.0f, 357.0f, 1.0));

		{
			Interface* mIconFrame = Factory::CreateInterface<Interface>(Vec3(-733.0f, 377.0f, 1.0f), Vec2(57.f, 57.0f), L"..\\Resources\\Texture\\Ability_select_box_LightStroke.png");
			mScene->AddGameObject(mIconFrame);
			mIconFrame->SetDontDestroyObject(L"IconFrame");
			OnOffList.push_back(mIconFrame);

		}

		{
			Interface* mBowIcon = Factory::CreateInterface<Interface>(Vec3(-733.0f, 375.0f, 1.0f), Vec2(33.f, 33.0f), L"..\\Resources\\Texture\\Icon_Arrow.png");
			mScene->AddGameObject(mBowIcon);
			mBowIcon->SetDontDestroyObject(L"BowIcon");
			OnOffList.push_back(mBowIcon);
		}
		UiOff();
	}

	void ManaUi::UiOn()
	{
		for (int i = 0; i < OnOffList.size(); i++)
		{
			OnOffList[i]->Enable();
		}
	}
	void ManaUi::UiOff()
	{
		for (int i = 0; i < OnOffList.size(); i++)
		{
			OnOffList[i]->Disable();
		}
	}
	ManaUi* ManaUi::GetMpUI()
	{
		return spManaUi;
	}
	void ManaUi::AddMana()
	{
	/*	mCurrManaAmount += 1;
		mpMpSlots[mCurrManaAmount]->GetScript<ManaIconScript>()->Apear();*/
	}
	void ManaUi::DecreaseMana()
	{
		/*if (mCurrManaAmount > 0)
			mCurrManaAmount -= 0;
		mpMpSlots[mCurrManaAmount]->GetScript<ManaIconScript>()->Decrease();*/
	}
}