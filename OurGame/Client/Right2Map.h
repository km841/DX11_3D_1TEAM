#pragma once
#include "Map.h"

namespace hm
{
	class Right2Map :
		public Map
	{
	public:
		Right2Map();
		virtual ~Right2Map();

	public:
		virtual void Initialize();
		virtual void Start();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();

		virtual void Enter();
		virtual void Exit();

	public:

		void InitObjectAdd();
		void InitCollidertAdd();
		
	private:
		class SlashGlareScript* mpTestScript;
	};
}


