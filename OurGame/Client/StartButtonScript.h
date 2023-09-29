#pragma once
#include "MonoBehavior.h"
#include "TimerObject.h"

namespace hm
{
	class StartButtonScript :
		public MonoBehavior
	{
	public:
		StartButtonScript(const wstring& _name, MapType _eMapType);
		~StartButtonScript() = default;

		virtual void FixedUpdate() override;
		virtual Component* Clone(GameObject* _pGameObject) override;

		void Start();

	private:
		TimerObject mTimer;
		MapType meMapType;
		wstring mName;

	};
}


