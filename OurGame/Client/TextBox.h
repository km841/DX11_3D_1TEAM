
#include "Interface.h"
#include "GameObject.h"

using namespace hm;

namespace yj
{
	class TextBox :
		public Interface
	{
	public:

		TextBox();
		virtual ~TextBox();

		TextBox* Clone()
		{
			TextBox* _pTextBox = GameObject::Clone<TextBox>();
			return _pTextBox;
		}

	private:
		
		virtual void Initialize();
		virtual void Update();

	public:
		void AddTextInArray(wstring& _addText) { mWriteTextArray.push_back(_addText); }

		void Apear();
		void Disapear();

	private:


		void SetCurrWriteText(int _TextLineNum);
		void AddText(wstring _AddText) { mCurrWriteText + _AddText; }
		void WriteText();
		bool GetIsWriteDone() {
			if (mCurrTextLength == mCurrWriteText.length()) {
				return true;
			}
			else { return false; }
		}

		void ResetCurrWriteText() { mCurrWriteText = L""; }
		void ResetCurrTextLength() { mCurrTextLength = -1; }

		void SetTimerFlow() { isTimerFlow = true; }
		bool IsTimerReach() { if (mTimer >= mTimerLimit) { return true; } else { return false; } }
		void TimerReset() { mTimer = 0.0f; }
		void TimerStop() { isTimerFlow = false; }

	public:
		enum ActState
		{
			Start,
			ApearAct,
			StandbyAct,
			DisapearAct,
			End,
		};

		ActState mActState;

	private:
		
		Interface* pTextBox;

		float mExpandLimitSize;
		float mInitSize;
		float mCurrSize;
		float mIncreaseSize;

		std::vector<wstring> mWriteTextArray;
		wstring mCurrWriteText;
		wstring mSetWriteText;
		int mCurrTextLength = -1;

		bool isTextWriting;

		float mTimer = 0.0f;
		float mTimerLimit;
		bool isTimerFlow;
	};
}