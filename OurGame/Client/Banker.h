#pragma once
#include "Npc.h"
namespace hm
{
    class Banker :
        public Npc
    {
	public:
		Banker();
		virtual ~Banker();
		Banker* Clone()
		{
			Banker* pNpc = GameObject::Clone<Banker>();
			return pNpc;
		}

	public:
		virtual void Initialize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();
		virtual void Destroy();
    };
}


