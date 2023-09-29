#pragma once
#include "GameObject.h"
namespace hm
{
	class Interface : 
		public GameObject
	{
	public:
		Interface();
		virtual ~Interface();

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();
		virtual void Destroy();

		virtual void Enable();
		virtual void Disable();

		Interface* GetChild(const wstring& _name);
		void UpdateChild();

	protected:
		std::map<int, Interface*> mChildren;

	};
}


