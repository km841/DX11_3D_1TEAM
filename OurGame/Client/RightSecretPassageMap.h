#pragma once
#include "Map.h"

namespace jh
{
	class RightSecretPassageMap :
		public Map
	{
	public:
		RightSecretPassageMap();
		virtual ~RightSecretPassageMap();

	private:
		virtual void Initialize();
		virtual void Start();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();

		virtual void Enter();
		virtual void Exit();

	private:

	private:
		void InitObjectAdd();
		void InitColliderAdd();
		void FuncObjectAdd();

	};
}
