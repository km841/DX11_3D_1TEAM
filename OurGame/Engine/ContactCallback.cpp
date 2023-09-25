#include "pch.h"
#include "ContactCallback.h"
#include "GameObject.h"
#include "Collider.h"

namespace hm
{
    void ContactCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pPairs, PxU32 iNbPairs)
    {
        for (PxU32 i = 0; i < iNbPairs; i++)
        {
            const PxContactPair& cp = pPairs[i];

            if (cp.events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
            {
                if (pairHeader.actors[0]->userData && pairHeader.actors[1]->userData)
                {
                    GameObject* pContact = static_cast<GameObject*>(pairHeader.actors[0]->userData);
                    GameObject* pOther = static_cast<GameObject*>(pairHeader.actors[1]->userData);

                    if (nullptr != pContact && nullptr != pOther)
                    {
                        if (pContact->GetCollider())
                            pContact->GetCollider()->OnCollisionEnter(pOther->GetCollider());

                        if (pOther->GetCollider())
                            pOther->GetCollider()->OnCollisionEnter(pContact->GetCollider());
                    }
                }
            }

            else if (cp.events & PxPairFlag::eNOTIFY_TOUCH_PERSISTS)
            {
                if (pairHeader.actors[0]->userData && pairHeader.actors[1]->userData)
                {
                    GameObject* pContact = static_cast<GameObject*>(pairHeader.actors[0]->userData);
                    GameObject* pOther = static_cast<GameObject*>(pairHeader.actors[1]->userData);

                    if (nullptr != pContact && nullptr != pOther)
                    {
                        if (pContact->GetCollider())
                            pContact->GetCollider()->OnCollisionStay(pOther->GetCollider());

                        if (pOther->GetCollider())
                            pOther->GetCollider()->OnCollisionStay(pContact->GetCollider());
                    }
                }
            }

            else if (cp.events & PxPairFlag::eNOTIFY_TOUCH_LOST)
            {
                if (pairHeader.actors[0]->userData && pairHeader.actors[1]->userData)
                {
                    GameObject* pContact = static_cast<GameObject*>(pairHeader.actors[0]->userData);
                    GameObject* pOther = static_cast<GameObject*>(pairHeader.actors[1]->userData);

                    if (nullptr != pContact && nullptr != pOther)
                    {
                        if (pContact->GetCollider())
                            pContact->GetCollider()->OnCollisionExit(pOther->GetCollider());

                        if (pOther->GetCollider())
                            pOther->GetCollider()->OnCollisionExit(pContact->GetCollider());
                    }
                }
            }
        }
    }

    void ContactCallback::onTrigger(PxTriggerPair* pairs, PxU32 count)
    {
        for (PxU32 i = 0; i < count; i++)
        {
            const PxTriggerPair& pair = pairs[i];

            if (pair.status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
            {
                if (pair.triggerActor && pair.otherActor)
                {
                    GameObject* pTrigger = static_cast<GameObject*>(pair.triggerActor->userData);
                    GameObject* pOther = static_cast<GameObject*>(pair.otherActor->userData);

                    if (nullptr != pTrigger && nullptr != pOther)
                    {
                        if (pTrigger->GetCollider())
                            pTrigger->GetCollider()->OnTriggerEnter(pOther->GetCollider());

                        if (pOther->GetCollider())
                            pOther->GetCollider()->OnTriggerEnter(pTrigger->GetCollider());
                    }
                }
            }

            if (pair.status & PxPairFlag::eNOTIFY_TOUCH_LOST)
            {
                if (pair.triggerActor && pair.otherActor)
                {
                    GameObject* pTrigger = static_cast<GameObject*>(pair.triggerActor->userData);
                    GameObject* pOther = static_cast<GameObject*>(pair.otherActor->userData);

                    if (nullptr != pTrigger && nullptr != pOther)
                    {
                        if (pTrigger->GetCollider())
                            pTrigger->GetCollider()->OnTriggerExit(pOther->GetCollider());

                        if (pOther->GetCollider())
                            pOther->GetCollider()->OnTriggerExit(pTrigger->GetCollider());
                    }

                }
            }
        }
    }

    PxControllerBehaviorFlags ContactCallback::getBehaviorFlags(const PxShape& shape, const PxActor& actor)
    {
        //return PxControllerBehaviorFlag::eCCT_CAN_RIDE_ON_OBJECT | PxControllerBehaviorFlag::eCCT_SLIDE;
        return PxControllerBehaviorFlags(0);
    }

    void ContactCallback::onShapeHit(const PxControllerShapeHit& hit)
    {
        defaultCCTInteraction(hit);
    }

    PX_INLINE void addForceAtPosInternal(PxRigidBody& body, const PxVec3& force, const PxVec3& pos, PxForceMode::Enum mode, bool wakeup)
    {
        /*	if(mode == PxForceMode::eACCELERATION || mode == PxForceMode::eVELOCITY_CHANGE)
            {
                Ps::getFoundation().error(PxErrorCode::eINVALID_PARAMETER, __FILE__, __LINE__,
                    "PxRigidBodyExt::addForce methods do not support eACCELERATION or eVELOCITY_CHANGE modes");
                return;
            }*/

        const PxTransform globalPose = body.getGlobalPose();
        const PxVec3 centerOfMass = globalPose.transform(body.getCMassLocalPose().p);

        const PxVec3 torque = (pos - centerOfMass).cross(force);
        body.addForce(force, mode, wakeup);
        body.addTorque(torque, mode, wakeup);
    }

    static void addForceAtLocalPos(PxRigidBody& body, const PxVec3& force, const PxVec3& pos, PxForceMode::Enum mode, bool wakeup = true)
    {
        //transform pos to world space
        const PxVec3 globalForcePos = body.getGlobalPose().transform(pos);

        addForceAtPosInternal(body, force, globalForcePos, mode, wakeup);
    }

    void ContactCallback::defaultCCTInteraction(const PxControllerShapeHit& hit)
    {
        PxRigidDynamic* actor = hit.shape->getActor()->is<PxRigidDynamic>();
        if (actor)
        {
            if (actor->getRigidBodyFlags() & PxRigidBodyFlag::eKINEMATIC)
                return;

            if (0)
            {
                const PxVec3 p = actor->getGlobalPose().p + hit.dir * 10.0f;

                PxShape* shape;
                actor->getShapes(&shape, 1);
                PxRaycastHit newHit;
                PxU32 n = PxShapeExt::raycast(*shape, *shape->getActor(), p, -hit.dir, 20.0f, PxHitFlag::ePOSITION, 1, &newHit);
                if (n)
                {
                    // We only allow horizontal pushes. Vertical pushes when we stand on dynamic objects creates
                    // useless stress on the solver. It would be possible to enable/disable vertical pushes on
                    // particular objects, if the gameplay requires it.
                    const PxVec3 upVector = hit.controller->getUpDirection();
                    const PxF32 dp = hit.dir.dot(upVector);
                    //		shdfnd::printFormatted("%f\n", fabsf(dp));
                    if (fabsf(dp) < 1e-3f)
                        //		if(hit.dir.y==0.0f)
                    {
                        const PxTransform globalPose = actor->getGlobalPose();
                        const PxVec3 localPos = globalPose.transformInv(newHit.position);
                        ::addForceAtLocalPos(*actor, hit.dir * hit.length * 1000.0f, localPos, PxForceMode::eACCELERATION);
                    }
                }
            }

            // We only allow horizontal pushes. Vertical pushes when we stand on dynamic objects creates
            // useless stress on the solver. It would be possible to enable/disable vertical pushes on
            // particular objects, if the gameplay requires it.
            const PxVec3 upVector = hit.controller->getUpDirection();
            const PxF32 dp = hit.dir.dot(upVector);
            //		shdfnd::printFormatted("%f\n", fabsf(dp));
            if (fabsf(dp) < 1e-3f)
                //		if(hit.dir.y==0.0f)
            {
                const PxTransform globalPose = actor->getGlobalPose();
                const PxVec3 localPos = globalPose.transformInv(toVec3(hit.worldPos));
                ::addForceAtLocalPos(*actor, hit.dir * hit.length * 1000.0f, localPos, PxForceMode::eACCELERATION);
            }
        }
    }

    PxQueryHitType::Enum ContactCallback::preFilter(const PxFilterData& filterData, const PxShape* shape, const PxRigidActor* actor, PxHitFlags& queryFlags)
    {
        return PxQueryHitType::eBLOCK;
    }

    PxQueryHitType::Enum ContactCallback::postFilter(const PxFilterData& filterData, const PxQueryHit& hit)
    {
        return PxQueryHitType::eBLOCK;
    }
}