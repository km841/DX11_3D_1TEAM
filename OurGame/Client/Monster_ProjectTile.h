#pragma once
#include "GameObject.h"
namespace hm
{
	class Monster_ProjectTile :
		public GameObject
	{
	public:
		Monster_ProjectTile();
		virtual ~Monster_ProjectTile();
		Monster_ProjectTile* Clone()
		{
			Monster_ProjectTile* pMonster_projecttile = GameObject::Clone<Monster_ProjectTile>();
			return pMonster_projecttile;
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