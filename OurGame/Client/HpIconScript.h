#pragma once

#include "MonoBehavior.h"

namespace yj
{
	class HpIconScript : public MonoBehavior
	{
	public:

		HpIconScript();
		virtual ~HpIconScript();

		virtual void Initialize();
		virtual void Update();
		virtual Component* Clone(GameObject* _pGameObject) override;
		
		void SetColorRed();
		void SetColorGreen();
		void SetColorOrange();

	private:


	};
}