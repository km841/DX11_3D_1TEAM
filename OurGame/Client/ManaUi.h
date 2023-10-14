#pragma once
#include "GameObject.h"
#include "Interface.h"

#include "Player.h"
#include "MonoBehavior.h"

namespace yj
{
	class ManaUi : public MonoBehavior
	{
	public:
		ManaUi();
		virtual ~ManaUi();

		virtual Component* Clone(GameObject* _pGameObject);
		virtual void Initialize();
		virtual void Update();
		static ManaUi* spManaUi;
		static ManaUi* GetMpUI();
	public:
		void AddManaUI();

		void AddMana();
		void DecreaseMana();
		void UiOn();
		void UiOff();



	private:
		Interface* mpMpSlots[5];
		Interface* mpMpIns[5];

		std::vector<Interface*> OnOffList;

		int mCurrManaAmount;
	};
}