#pragma once
#include "GameObject.h"

namespace hm
{
	class UI :
		public GameObject
	{
	public:
		UI();
		virtual ~UI();

		virtual UI* Clone()
		{
			UI* pUI = GameObject::Clone<UI>();
			return pUI;
		}

		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();
		virtual void Destroy();
	};

}

