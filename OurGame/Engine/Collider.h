#pragma once
#include "Component.h"
#include "RigidBody.h"

namespace hm
{
    class Mesh;
    class Material;

    class Collider :
        public Component
    {
    public:
        Collider();
        virtual ~Collider();

    public:
        virtual void Initialize() override;
        virtual void Update() override;
        virtual void FinalUpdate() override;
        virtual void Render() override;

        virtual Component* Clone(GameObject* _pGameObject);

    public:
        bool Raycast(const Vec3& _origin, const Vec3& _dir, Collider* _pOther, float _maxDist);
        bool Overlap(Collider* _pOther);
        const PxRaycastHit& GetRayHitInfo() { return mRaycastHit; }

    private:
        template<typename T>
        bool Raycast(T _geom, const Vec3& _origin, const Vec3& _dir, Collider* _pOther, float _maxDist)
        {
            PxTransform otherTr = _pOther->GetRigidBody()->GetPhysicsTransform();
            bool bResult = PxGeometryQuery::raycast(
                _origin,
                _dir,
                _geom, otherTr,
                _maxDist,
                PxHitFlag::ePOSITION | PxHitFlag::eDEFAULT,
                5,
                &mRaycastHit);

            return bResult;
        }

        template<typename T>
        bool Overlap(T _geom, Collider* _pOther)
        {
            PxTransform otherTr = _pOther->GetRigidBody()->GetPhysicsTransform();
            PxTransform myTr = GetRigidBody()->GetPhysicsTransform();
            T myGeom = *GetRigidBody()->GetGeometry<T>();
            bool bResult = PxGeometryQuery::overlap(_geom, otherTr, myGeom, myTr);
            return bResult;
        }

    public:
        void OnCollisionEnter(Collider* _pOtherCollider);
        void OnCollisionStay(Collider* _pOtherCollider);
        void OnCollisionExit(Collider* _pOtherCollider);

        void OnTriggerEnter(Collider* _pOtherCollider);
        void OnTriggerStay(Collider* _pOtherCollider);
        void OnTriggerExit(Collider* _pOtherCollider);

        bool IsCollision() { return mCollisionCount; }
        void ClearCollisionCount() { mCollisionCount = 0; }
        bool IsPenetrate();
        
        bool CheckIsCollisionObject(LayerType _layerType) {
            if (mCollisionCount == 0)
            {
                return false;
            }
            for (int i = 0; i < collLayerTypeList.size(); i++)
            {
                if (collLayerTypeList[i] == _layerType)
                {
                    return true;
                }
            }
            return false;
        }

	private:
        shared_ptr<Mesh> mpMesh;
        shared_ptr<Material> mpMaterial;

        int mCollisionCount;
        PxRaycastHit mRaycastHit;
        PxOverlapBuffer mOverlapBuffer;
        
        LayerType myLayerType;
        std::vector<LayerType> collLayerTypeList;
	};
}


