#pragma once
#include "Map.h"

namespace jh
{
    class PhysicsTestScene :
        public Map
    {
	public:
		PhysicsTestScene();
		virtual ~PhysicsTestScene();

	public:
		virtual void Initialize();
		virtual void Start();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void FinalUpdate();
		virtual void Render();

		virtual void Enter();
		virtual void Exit();

	private:
		void CreateCharacterController();

		PxCapsuleController* mpCharacterController;

		const PxFilterData* mFilterData;		// User-defined filter data for 'move' function
		PxQueryFilterCallback* mFilterCallback;	// User-defined filter data for 'move' function
		PxControllerFilterCallback* mCCTFilterCallback;	// User-defined filter data for 'move' function
    };
}
