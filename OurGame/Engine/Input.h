#pragma once
#include "TimerObject.h"
namespace hm
{


	enum class HotKeyType
	{
		UP_LEFT,
		UP_RIGHT,
		DOWN_LEFT,
		DOWN_RIGHT,
		
		WA,
		WD,
		AS,
		SD,
	};

	enum class KeyState
	{
		None,
		Press,
		Down,
		Up,
		End
	};

	enum
	{
		KEY_TYPE_COUNT = static_cast<int>(UINT8_MAX + 1),
		KEY_STATE_COUNT = static_cast<int>(KeyState::End),
	};


	class Input
	{
		DECLARE_SINGLE(Input);

	public:
		// 각 키의 상태를 초기화하는 함수
		void Initialize();
		// 각 키의 상태를 업데이트하는 함수
		void Update();
		void HotKeyUpdate();
		void ClearHotkey();
		// 키가 눌려있는지 체크하는 함수
		bool GetButtonPress(KeyType _eKey)     const { return KeyState::Press == GetState(_eKey); }
		// 키가 방금 눌렸는지 체크하는 함수
		bool GetButtonDown(KeyType _eKey)      const { return KeyState::Down == GetState(_eKey); }
		// 키가 방금 떼졌는지 함수
		bool GetButtonUp(KeyType _eKey)        const { return KeyState::Up == GetState(_eKey); }
		// 키가 눌려있지 않은지 함수
		bool GetButtonNone(KeyType _eKey)      const { return KeyState::None == GetState(_eKey); }
		// 현재 마우스 위치를 반환한다.
		const POINT& GetMousePos() const { return mMousePos; }
		const POINT& GetPrevMousePos() const { return mPrevMousePos; }

		bool GetHotKeyPress(HotKeyType _eKey) const { return KeyState::Press == mHotkeyStates[static_cast<int>(_eKey)]; }
		bool GetHotKeyUp(HotKeyType _eKey) const { return KeyState::Up == mHotkeyStates[static_cast<int>(_eKey)]; }



	private:
		// 특정 키의 상태를 반환하는 함수
		KeyState GetState(KeyType _eKeyType) const { return mStates[static_cast<int>(_eKeyType)]; }

	private:
		HWND				  mHwnd;
		std::vector<KeyState> mStates;
		std::vector<KeyState> mHotkeyStates;
		POINT				  mMousePos = {};
		POINT				  mPrevMousePos = {};
		TimerObject			  mTimer;
	};
}




