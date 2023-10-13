#pragma once

#include "MonoBehavior.h"

namespace yj
{
	class ManaIconScript : public MonoBehavior
	{
	public:

		ManaIconScript();
		virtual ~ManaIconScript();

		virtual void Initialize();
		virtual void Update();
		virtual Component* Clone(GameObject* _pGameObject) override;
		void Apear();
		void Decrease();
		void SetBigIcon() { isBigger = true; }

		enum Sequence
		{
			Begin,
			ApearSeq,
			DisapearSeq,
			Standby,
			End
		};
		Sequence mSequence;


	private:
		bool isBigger;
		
		float mSpeed;

		float mSize[2];
	};
}