#include "pch.h"
#include "Input.h"
#include "Engine.h"

namespace hm
{
	Input::Input()
		: mHwnd(NULL)
	{

	}

	Input::~Input()
	{

	}

	void Input::Initialize()
	{
		mHwnd = gpEngine->GetHwnd();
		mStates.resize(KEY_TYPE_COUNT, KeyState::None);
	}
	void Input::Update()
	{
		HWND hwnd = GetActiveWindow();

		if (mHwnd != hwnd)
		{
			for (int i = 0; i < KEY_TYPE_COUNT; ++i)
				mStates[i] = KeyState::None;

			return;
		}
		else
		{
			mPrevMousePos = mMousePos;
			GetCursorPos(&mMousePos);
			ScreenToClient(gpEngine->GetHwnd(), &mMousePos);
		}

		BYTE asciiKeys[KEY_TYPE_COUNT] = {};
		if (false == GetKeyboardState(asciiKeys))
			return;

		for (int i = 0; i < KEY_TYPE_COUNT; ++i)
		{
			if (asciiKeys[i] & 0x80)
			{
				KeyState& eState = mStates[i];

				if (KeyState::Press == eState || KeyState::Down == eState)
					eState = KeyState::Press;
				else
					eState = KeyState::Down;
			}

			else
			{
				KeyState& eState = mStates[i];

				if (KeyState::Press == eState || KeyState::Down == eState)
					eState = KeyState::Up;
				else
					eState = KeyState::None;
			}
		}
	}
}