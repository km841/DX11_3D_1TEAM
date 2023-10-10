#pragma once
#include "GameObject.h"
#include "Interface.h"
namespace yj
{
	namespace yj
	{
		class HpUi : public Interface
		{
		public:
			HpUi();
			virtual ~HpUi();

			HpUi* Clone()
			{
				HpUi* _pHpUi = GameObject::Clone<HpUi>();
				return _pHpUi;
			}

		private:

			virtual void Initialize();
			virtual void Update();
		};
	}
}
