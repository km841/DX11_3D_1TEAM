#pragma once

#include "Interface.h"
namespace yj
{
	class HeadText :public Interface
	{
	private:

		HeadText();
		virtual ~HeadText();

		HeadText* Clone()
		{
			HeadText* _pHeadText = GameObject::Clone<HeadText>();
			return _pHeadText;
		}
		virtual void Initialize();
		virtual void Update();
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

	public:
		void AddTextInArray(wstring& _addText) { mWriteTextArray.push_back(_addText); }
		void Apear();
		void Disapear();

	private:

		void SetHeadText(int num);

	private:
		float mExpandLimitSize;
		float mInitSize;
		float mCurrSize;
		float mIncreaseSize;

		std::vector<wstring> mWriteTextArray;
		wstring mCurrWriteText;

	};
}
