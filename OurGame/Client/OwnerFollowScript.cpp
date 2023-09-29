#include "pch.h"
#include "OwnerFollowScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "SceneManager.h"

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
            LayerType eLayerType = GetGameObject()->GetLayerType();
            if (LayerType::Interface == eLayerType)
            {
                Vec3 fixedPos = mpOwner->GetTransform()->GetPosition();
                Camera* pCamera = GET_SINGLE(SceneManager)->GetActiveScene()->GetMainCamera();
                fixedPos = GET_SINGLE(SceneManager)->WorldToScreenPosition(fixedPos, pCamera);
                GetTransform()->SetPosition(fixedPos + mOffset);
            }
            else
            {
                Vec3 fixedPos = mpOwner->GetTransform()->GetPosition();
                GetTransform()->SetPosition(fixedPos + mOffset);
            }
        }


    }

    Component* OwnerFollowScript::Clone(GameObject* _pGameObject)
    {
        return _pGameObject->AddComponent(new OwnerFollowScript(mpOwner));
    }
}
