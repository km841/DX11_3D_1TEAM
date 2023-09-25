#pragma once

namespace hm
{
	class ContactCallback :
		public PxSimulationEventCallback,
		public PxControllerBehaviorCallback,
		public PxUserControllerHitReport,
		public PxQueryFilterCallback
	{
	public:
		virtual void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs) override;
		virtual void onConstraintBreak(PxConstraintInfo* constraints, PxU32 count) override {}
		virtual void onWake(PxActor** actors, PxU32 count) override {}
		virtual void onSleep(PxActor** actors, PxU32 count) override {}
		virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) override;
		virtual void onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count) override {}

		// Implements PxControllerBehaviorCallback
		virtual PxControllerBehaviorFlags getBehaviorFlags(const PxShape& shape, const PxActor& actor) override;
		virtual PxControllerBehaviorFlags getBehaviorFlags(const PxController& controller) override { return PxControllerBehaviorFlags(); };
		virtual PxControllerBehaviorFlags getBehaviorFlags(const PxObstacle& obstacle) override { return PxControllerBehaviorFlags(); };

		// Implements PxUserControllerHitReport
		virtual void onShapeHit(const PxControllerShapeHit& hit);
		virtual void onControllerHit(const PxControllersHit& hit) {};
		virtual void onObstacleHit(const PxControllerObstacleHit& hit) {};

		void defaultCCTInteraction(const PxControllerShapeHit& hit);

		// Implements PxQueryFilterCallback
		virtual PxQueryHitType::Enum			preFilter(const PxFilterData& filterData, const PxShape* shape, const PxRigidActor* actor, PxHitFlags& queryFlags);
		virtual	PxQueryHitType::Enum			postFilter(const PxFilterData& filterData, const PxQueryHit& hit);
	};


}
