
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
		static TextBox* spTextBox;
		static TextBox* GetTextBox();
	private:
		
		virtual void Initialize();
		virtual void Update();

	public:
		void AddTextInArray(wstring& _addText) { mWriteTextArray.push_back(_addText); }

		void Apear();
		void Disapear();

		void SetWriteTexts(int _startNum, int _endNum) { mLineStartNum = _startNum; mLineEndNum = _endNum; }
	private:

		void SetCurrWriteText(int _TextLineNum);
		void WriteText();
		void CurrWriteTextAdd(int num);

		void ResetTextLine() { mCurrWriteText = L""; mCurrTextLength = -1; mAddedTextCount = -1; }

		void SetTimerFlow() { isTimerFlow = true; }
		bool IsTimerReach() { if (mTimer >= mTimerLimit) { return true; } else { return false; } }

		void TimerReset() { mTimer = 0.0f; }
		void SetTimerStop() { isTimerFlow = false; }

		bool GetIsWriteDone() {
			if (mCurrTextLength == mCurrWriteText.length()) {
				return true;
			}
			else { return false; }
		}
	public:
		enum ActState
		{
			Start,
			ApearAct,
			WriteTextAct,
			DisapearAct,
			End,
		};

		ActState mActState = Start;

	private:
		
		Interface* pTextBox;

		float mExpandLimitSize;
		float mInitSize;
		float mCurrSize;
		float mIncreaseSize;

		std::vector<wstring> mWriteTextArray;
		
		wstring mSetWriteText;
		wstring mCurrWriteText;

		int mLineStartNum;
		int mLineEndNum;
		int mAddedLineNum;

		int mCurrTextLength = -1;
		int mAddedTextCount = -1;

		bool isTextWriting;

		float mTimer = 0.0f;
		float mTimerLimit = 0.075f;
		bool isTimerFlow;

	};
}
