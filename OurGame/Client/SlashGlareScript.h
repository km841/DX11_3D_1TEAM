#pragma once
#include "MonoBehavior.h"
#include "TimerObject.h"

namespace hm
{
	enum class SlashGlareState
	{
		None,
		Begin,
		End,
	};
	class SlashGlareScript :
		public MonoBehavior
	{
	public:
		SlashGlareScript();
		~SlashGlareScript() = default;

		virtual void FixedUpdate() override;
		virtual Component* Clone(GameObject* _pGameObject) override;

		void Start();
		void SetEndCallback(std::function<void()> _function);


	private:
		SlashGlareState meState;

		TimerObject mBeginTimer;
		TimerObject mEndTimer;

		std::function<void()> mEndCallback;
	};
}


