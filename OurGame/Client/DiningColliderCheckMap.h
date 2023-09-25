#pragma once
#include "Map.h"
namespace sy
{
	class DiningColliderCheckMap :
		public Map
	{
	public:
		DiningColliderCheckMap();
		virtual ~DiningColliderCheckMap();

	public:
		virtual void Initialize();
		virtual void Start();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();

	public:
		virtual void Enter();
		virtual void Exit();

	private:
		PxCapsuleController* mpCharacterController;
		PxControllerFilters filter;
	};
}

