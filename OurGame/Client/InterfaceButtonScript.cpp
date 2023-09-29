#include "pch.h"
#include "InterfaceButtonScript.h"
#include "GameObject.h"
#include "Input.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Material.h"

namespace hm
{
	InterfaceButtonScript::InterfaceButtonScript()
		: mbClicked(false)
		, mbHovered(false)
	{
	}
	void InterfaceButtonScript::FixedUpdate()
	{
		POINT temp = GET_SINGLE(Input)->GetMousePos();
		Vec2 mousePos = Vec2(static_cast<float>(temp.x), static_cast<float>(RESOLUTION.y - temp.y));
		mousePos -= RESOLUTION / 2.f;

		Vec3 scale = GetTransform()->GetScale() * 2.f;
		Vec3 pos = GetTransform()->GetPosition();

		float left = pos.x - scale.x / 2.f;
		float right = pos.x + scale.x / 2.f;
		float top = pos.y + scale.y / 2.f;
		float bottom = pos.y - scale.y / 2.f;

		if (mousePos.x >= left && mousePos.x <= right &&
			mousePos.y >= bottom && mousePos.y <= top)
		{
			if (false == mbHovered)
			{
				mbHovered = true;
				if (nullptr != mHoveredCallback)
					mHoveredCallback();

				if (nullptr != mpHoveredTexture)
					GetMeshRenderer()->GetMaterial()->SetTexture(0, mpHoveredTexture);
				
			}

			if (IS_DOWN(KeyType::LBUTTON))
			{
				if (false == mbClicked)
				{
					mbClicked = true;
					if (nullptr != mClickedCallback)
						mClickedCallback();

					if (nullptr != mpClickedTexture)
						GetMeshRenderer()->GetMaterial()->SetTexture(0, mpClickedTexture);
				}
			}

			if (IS_UP(KeyType::LBUTTON))
			{
				mbClicked = false;

				if (nullptr != mpHoveredTexture)
					GetMeshRenderer()->GetMaterial()->SetTexture(0, mpHoveredTexture);
			}
		}
		else
		{
			mbHovered = false;

			if (nullptr != mpNonHoveredTexture)
				GetMeshRenderer()->GetMaterial()->SetTexture(0, mpNonHoveredTexture);


			if (IS_UP(KeyType::LBUTTON))
			{
				mbClicked = false;

				if (nullptr != mpNonHoveredTexture)
					GetMeshRenderer()->GetMaterial()->SetTexture(0, mpNonHoveredTexture);
			}
		}
		
	}
	Component* InterfaceButtonScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new InterfaceButtonScript);
	}
}