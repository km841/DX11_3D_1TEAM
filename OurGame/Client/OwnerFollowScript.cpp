#include "pch.h"
#include "OwnerFollowScript.h"
#include "GameObject.h"
#include "Transform.h"

namespace hm
{
    OwnerFollowScript::OwnerFollowScript(GameObject* _pOwner)
        : mpOwner(_pOwner)
    {
    }

    void OwnerFollowScript::FixedUpdate()
    {
        if (nullptr != mpOwner)
        {
            Vec3 fixedPos = mpOwner->GetTransform()->GetPosition();
            GetTransform()->SetPosition(fixedPos + mOffset);
        }
    }

    Component* OwnerFollowScript::Clone(GameObject* _pGameObject)
    {
        return _pGameObject->AddComponent(new OwnerFollowScript(mpOwner));
    }
}
