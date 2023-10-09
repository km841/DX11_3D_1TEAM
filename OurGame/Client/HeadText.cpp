#include "pch.h"
#include "HeadText.h"
#include "Player.h"
#include "Timer.h"
#include "UIText.h"

namespace yj
{
	HeadText::HeadText()
	{

	}
	HeadText::~HeadText()
	{
	
	}

	void HeadText::Initialize()
	{
		mWriteTextArray.push_back(L"항아리 저택");
		mWriteTextArray.push_back(L"E 입장");
		mWriteTextArray.push_back(L"E 대화하기");
	}

	void HeadText::Update()
	{
		//GetTransform()->SetPosition();
		//GetTransform()->SetPosition();
		//플레이어 위를 따라다니게 넘버에 따라서 머리 바로위 그리고 더 위 하나
		//맵 표시와 키 입력 표시
		Vec3 mPlayerPos = PLAYER->GetTransform()->GetPosition();
		Vec3 mFixedPos = mPlayerPos + Vec3(0.0f, 0.5f, 0.0f);
		GetTransform()->SetPosition(mFixedPos);


		UIText* pUIText = GetUIText();
		pUIText = GetUIText();

		if (ApearAct)
		{
			while (mCurrSize < mExpandLimitSize)
			{
				mCurrSize += mIncreaseSize * DELTA_TIME;
				pUIText->SetSize(mCurrSize);
			}
			if (mCurrSize >= mExpandLimitSize)
			{
				pUIText->SetSize(mExpandLimitSize);
				mActState = StandbyAct;
			}
		}
		if (StandbyAct)
		{
			//
		}
		if (DisapearAct)
		{
			while (mCurrSize > mExpandLimitSize)
			{
				mCurrSize -= mIncreaseSize * DELTA_TIME;
				pUIText->SetSize(mCurrSize);
			}
			if (mCurrSize < 0.2f)
			{
				pUIText->SetSize(0.2f);
				Disable();
				mActState = End;
			}
		}
	}
	void HeadText::SetHeadText(int num)
	{
		SetText(mWriteTextArray[num], 25.f, true);
	}
	void HeadText::Apear()
	{
		this->GetGameObject()->Enable();
		mActState = ApearAct;
	}
	void HeadText::Disapear()
	{
		mActState = DisapearAct;
	}
}