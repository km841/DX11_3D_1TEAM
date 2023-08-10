#pragma once
#include "Component.h"

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

        void OnCollisionEnter(Collider* _pOtherCollider);
        void OnCollisionStay(Collider* _pOtherCollider);
        void OnCollisionExit(Collider* _pOtherCollider);

        void OnTriggerEnter(Collider* _pOtherCollider);
        void OnTriggerStay(Collider* _pOtherCollider);
        void OnTriggerExit(Collider* _pOtherCollider);

        bool IsCollision() { return mCollisionCount; }
        void ClearCollisionCount() { mCollisionCount = 0; }

	private:
        shared_ptr<Mesh> mpMesh;
        shared_ptr<Material> mpMaterial;

        int mCollisionCount;

	};
}


