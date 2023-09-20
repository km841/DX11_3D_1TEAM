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
		mHotkeyStates.resize(KEY_TYPE_COUNT, KeyState::None);

		mTimer.Start();
		mTimer.SetEndTime(0.2f);
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

		HotKeyUpdate();
	}
	void Input::HotKeyUpdate()
	{
		if (true == mTimer.IsFinished())
		{
			for (int i = 0; i < KEY_TYPE_COUNT; ++i)
			{
				mHotkeyStates[i] = KeyState::None;
			}
			mTimer.Stop();
			mTimer.Start();
		}
		

		bool bIsPressedHotKey = false;
		// UP_LEFT
		if (GetButtonPress(KeyType::UP) && GetButtonPress(KeyType::LEFT))
		{
			mHotkeyStates[static_cast<int>(HotKeyType::UP_LEFT)] = KeyState::Press;
			bIsPressedHotKey = true;
			mTimer.Stop();
			mTimer.Start();
		}

		if (GetButtonUp(KeyType::UP) && GetButtonNone(KeyType::LEFT) || 
			GetButtonNone(KeyType::UP) && GetButtonUp(KeyType::LEFT))
		{
			if (mHotkeyStates[static_cast<int>(HotKeyType::UP_LEFT)] == KeyState::Press)
				mHotkeyStates[static_cast<int>(HotKeyType::UP_LEFT)] = KeyState::Up;
		}

		// UP_RIGHT
		if (GetButtonPress(KeyType::UP) && GetButtonPress(KeyType::RIGHT))
		{
			mHotkeyStates[static_cast<int>(HotKeyType::UP_RIGHT)] = KeyState::Press;
			bIsPressedHotKey = true;
			mTimer.Stop();
			mTimer.Start();
		}

		if (GetButtonUp(KeyType::UP) && GetButtonNone(KeyType::RIGHT) ||
			GetButtonNone(KeyType::UP) && GetButtonUp(KeyType::RIGHT))
		{
			if (mHotkeyStates[static_cast<int>(HotKeyType::UP_RIGHT)] == KeyState::Press)
				mHotkeyStates[static_cast<int>(HotKeyType::UP_RIGHT)] = KeyState::Up;
		}

		// DOWN_LEFT
		if (GetButtonPress(KeyType::DOWN) && GetButtonPress(KeyType::LEFT))
		{
			mHotkeyStates[static_cast<int>(HotKeyType::DOWN_LEFT)] = KeyState::Press;
			bIsPressedHotKey = true;
			mTimer.Stop();
			mTimer.Start();
		}

		if (GetButtonUp(KeyType::DOWN) && GetButtonNone(KeyType::LEFT) ||
			GetButtonNone(KeyType::DOWN) && GetButtonUp(KeyType::LEFT))
		{
			if (mHotkeyStates[static_cast<int>(HotKeyType::DOWN_LEFT)] == KeyState::Press)
				mHotkeyStates[static_cast<int>(HotKeyType::DOWN_LEFT)] = KeyState::Up;
		}

		// DOWN_RIGHT
		if (GetButtonPress(KeyType::DOWN) && GetButtonPress(KeyType::RIGHT))
		{
			mHotkeyStates[static_cast<int>(HotKeyType::DOWN_RIGHT)] = KeyState::Press;
			bIsPressedHotKey = true;
			mTimer.Stop();
			mTimer.Start();
		}

		if (GetButtonUp(KeyType::DOWN) && GetButtonNone(KeyType::RIGHT) ||
			GetButtonNone(KeyType::DOWN) && GetButtonUp(KeyType::RIGHT))
		{
			if (mHotkeyStates[static_cast<int>(HotKeyType::DOWN_RIGHT)] == KeyState::Press)
				mHotkeyStates[static_cast<int>(HotKeyType::DOWN_RIGHT)] = KeyState::Up;
		}

		// WA
		if (GetButtonPress(KeyType::W) && GetButtonPress(KeyType::A))
		{
			mHotkeyStates[static_cast<int>(HotKeyType::WA)] = KeyState::Press;
			bIsPressedHotKey = true;
		}

		if (GetButtonUp(KeyType::W) && GetButtonNone(KeyType::A) ||
			GetButtonNone(KeyType::W) && GetButtonUp(KeyType::A))
		{
			if (mHotkeyStates[static_cast<int>(HotKeyType::WA)] == KeyState::Press)
				mHotkeyStates[static_cast<int>(HotKeyType::WA)] = KeyState::Up;
		}

		// WD
		if (GetButtonPress(KeyType::W) && GetButtonPress(KeyType::D))
		{
			mHotkeyStates[static_cast<int>(HotKeyType::WD)] = KeyState::Press;
			bIsPressedHotKey = true;
		}

		if (GetButtonUp(KeyType::W) && GetButtonNone(KeyType::D) ||
			GetButtonNone(KeyType::W) && GetButtonUp(KeyType::D))
		{
			if (mHotkeyStates[static_cast<int>(HotKeyType::WD)] == KeyState::Press)
				mHotkeyStates[static_cast<int>(HotKeyType::WD)] = KeyState::Up;
		}

		// AS
		if (GetButtonPress(KeyType::S) && GetButtonPress(KeyType::A))
		{
			mHotkeyStates[static_cast<int>(HotKeyType::AS)] = KeyState::Press;
			bIsPressedHotKey = true;
		}

		if (GetButtonUp(KeyType::S) && GetButtonNone(KeyType::A) ||
			GetButtonNone(KeyType::S) && GetButtonUp(KeyType::A))
		{
			if (mHotkeyStates[static_cast<int>(HotKeyType::AS)] == KeyState::Press)
				mHotkeyStates[static_cast<int>(HotKeyType::AS)] = KeyState::Up;
		}

		// SD
		if (GetButtonPress(KeyType::S) && GetButtonPress(KeyType::D))
		{
			mHotkeyStates[static_cast<int>(HotKeyType::SD)] = KeyState::Press;
			bIsPressedHotKey = true;
		}

		if (GetButtonUp(KeyType::S) && GetButtonNone(KeyType::D) ||
			GetButtonNone(KeyType::S) && GetButtonUp(KeyType::D))
		{
			if (mHotkeyStates[static_cast<int>(HotKeyType::SD)] == KeyState::Press)
				mHotkeyStates[static_cast<int>(HotKeyType::SD)] = KeyState::Up;
		}

		if (false == bIsPressedHotKey)
		{
			mTimer.Update();
		}
	}
}