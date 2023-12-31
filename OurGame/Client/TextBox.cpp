#include "pch.h"
#include "TextBox.h"
#include "UIText.h"
#include "Timer.h"
#include "Input.h"
#include "EventSystem.h"

yj::TextBox* yj::TextBox::spTextBox;

namespace yj
{
	TextBox::TextBox()
	{
		spTextBox = this;
	}
	TextBox::~TextBox()
	{

	}

	void TextBox::Initialize()
	{
		mWriteTextArray.push_back(L"이제 영혼 수확 위원회 본부에 도착합니다.");
		mWriteTextArray.push_back(L"이번 역은 종점입니다...");

		mWriteTextArray.push_back(L"이런 이런 이런...");
		mWriteTextArray.push_back(L"드디어 얼굴을 비추시는 구만, 자네 몫 벌레는 없어...");
		mWriteTextArray.push_back(L"벌레는 일찍 일어나는 새가- 아니 됐다.");
		mWriteTextArray.push_back(L"어쨌든, 오늘 운 좋으시네... 수확해줘야 할 영혼이 하나 있어.");
		mWriteTextArray.push_back(L"그냥 평범한 영혼도 아니야. 대형 영혼이라고! 한 번 고민해봐...");
		mWriteTextArray.push_back(L"훈련은 잊지 않았길 바라. 발톱도 준비해둬. \n 대형 영혼을 수확하는 건 쉬운 일이 아니니까...");
		mWriteTextArray.push_back(L"지금 문을 내려주지.");


		mWriteTextArray.push_back(L"그 정도 크기의 영혼이라면 시간 좀 들여야 할 거야...");
		mWriteTextArray.push_back(L"그래도 명심해...");

		mWriteTextArray.push_back(L"네 방 문은 지정된 영혼을 가져오기 전까진 계속 열려있을 거야.");
		mWriteTextArray.push_back(L"문이 열려있는 동안은 필멸자로서 살아갈 거고, 나이도 먹을 거야. \n 그러니 서두르라고.");
		
		
		mWriteTextArray.push_back(L"영혼을 수확하면, 문에 동력을 넣게 되고, 그렇게 더 많은 영혼을 \n 수확할 수 있게 되고... 그렇게 순환하는 거야... 영원히 말이지...");
		mWriteTextArray.push_back(L"다 먹고살자고 하는 일이야.");
		mWriteTextArray.push_back(L"어쨌든, 들어가 봐. 그리고 조심하고.");
		mWriteTextArray.push_back(L"네가 죽으면 처리해야 할 서류가 산더미처럼 쌓일 테니까 말이야. \n 시간도 없는데 말이야.");

		mWriteTextArray.push_back(L"그대를 지켜보고 있었다. 젊은 까마귀여.");
		mWriteTextArray.push_back(L"이렇게까지 될 줄은 몰랐거늘... \n 하지만 결국 오고야 마는구나.");
		mWriteTextArray.push_back(L"우리가 만들어진 그 날 부터, 우리는 언제 우리가 죽을 지 듣게 된다.");
		mWriteTextArray.push_back(L"죽을 날을 정확히 알게 된다면, 그대는 어떻게 삶을 살아갈 것인가?");
		mWriteTextArray.push_back(L"그대의 존재 모든 것에 이미 끝이 예정되어 있다면 말이야.");
		mWriteTextArray.push_back(L"나는 그냥 죽음을 기다리고 있을 수만은 없다. \n 싸우지 않고선 받아들일 수 없다...");
		mWriteTextArray.push_back(L"내가 그러하듯, 너도 네 생명을 걸고 싸울 준비가 되었는지 \n 내가 시험해주마...");

	}


	void TextBox::Update()
	{
		if (mActState == ApearAct)
		{
			Vec3 mScale = this->GetTransform()->GetScale();

			if (this->GetTransform()->GetScale().x < 400)
			{
				Vec3 mFixedScale = mScale += Vec3(4.0f * DELTA_TIME* 500.0f, 1.0f * DELTA_TIME * 500.0f, 0.0f);
				this->GetTransform()->SetScale(mFixedScale);
			}
				
			if (mScale.x >= 400)
			{
				this->GetTransform()->SetScale(Vec3(400.0f,100.0f,0.0f));
				SetCurrWriteText(mLineStartNum);
				SetTimerFlow();
				isTextWriting = true;
				mActState = WriteTextAct;
			}
		}
		if (mActState == WriteTextAct)
		{
			if (isTextWriting)
			{
				if (!GetIsWriteDone())
				{
					if (IsTimerReach())
					{
						mAddedTextCount += 1;
						CurrWriteTextAdd(mAddedTextCount);
						WriteText();
						TimerReset();
					}
				}
				else
				{
					SetTimerStop();

					if (IS_DOWN(KeyType::F))
					{
						mAddedLineNum += 1;
						ResetTextLine();
						if (mLineStartNum + mAddedLineNum < mLineEndNum)
						{
							SetTimerFlow();
							SetCurrWriteText(mLineStartNum + mAddedLineNum);
						}
						else
						{
							Disapear();
						}
					}
				}
			}
		}
		if (mActState == DisapearAct)
		{
			Vec3 mScale = this->GetTransform()->GetScale();

			if (this->GetTransform()->GetScale().x > 10)
			{
				Vec3 mFixedScale = mScale -= Vec3(4.0f * DELTA_TIME * 500.0f, 1.0f * DELTA_TIME * 500.0f, 0.0f);
				this->GetTransform()->SetScale(mFixedScale);
			}

			if (mScale.x <= 10)
			{
				this->GetTransform()->SetScale(Vec3(40.0f, 10.0f, 0.0f));
				if (mCurrEvent != "")
				{
					EVENTSYSTEM->EventOn(mCurrEvent);
					mCurrEvent = "";
				}
				this->Disable();
				mActState = End;
			}
		}

		if (isTimerFlow)
		{
			mTimer += DELTA_TIME;
		}

	}
	void TextBox::Apear()
	{
		this->GetGameObject()->Enable();
		this->GetTransform()->SetScale(Vec3(40.0f,10.0f,1.0f));
		mAddedLineNum = 0;
		mActState = ApearAct;
	}
	void TextBox::SetCurrWriteText(int _TextLineNum)
	{
		mSetWriteText = mWriteTextArray[_TextLineNum];
		mCurrTextLength = mSetWriteText.length();
	}
	void TextBox::WriteText()
	{
		SetText(mCurrWriteText, 25.f, true);
	}

	void TextBox::CurrWriteTextAdd(int num)
	{
		wstring mAddText = wstring(1, mSetWriteText[num]);
		mCurrWriteText += mAddText;
	}
	
	
	void TextBox::Disapear()
	{
		SetText(L"", 25, false);
		
		mActState = DisapearAct;
	}

	TextBox* TextBox::GetTextBox()
	{
		return spTextBox;
	}

}