#include "pch.h"
#include "CameraMoveScript.h"
#include "Transform.h"
#include "Input.h"
#include "Timer.h"
#include "GameObject.h"


namespace hm
{
	CameraMoveScript::CameraMoveScript()
		: mSpeed(10.f)
	{
	}
	void CameraMoveScript::FixedUpdate()
	{
		Vec3 pos = GetGameObject()->GetTransform()->GetPosition();

		if (IS_PRESS(KeyType::W))
			pos += GetGameObject()->GetTransform()->GetLook() * mSpeed * DELTA_TIME;

		if (IS_PRESS(KeyType::S))
			pos -= GetGameObject()->GetTransform()->GetLook() * mSpeed * DELTA_TIME;

		if (IS_PRESS(KeyType::A))
			pos -= GetGameObject()->GetTransform()->GetRight() * mSpeed * DELTA_TIME;

		if (IS_PRESS(KeyType::D))
			pos += GetGameObject()->GetTransform()->GetRight() * mSpeed * DELTA_TIME;

		GetGameObject()->GetTransform()->SetPosition(pos);

		if (IS_PRESS(KeyType::LBUTTON))
		{
			POINT prevPos = GET_SINGLE(Input)->GetPrevMousePos();
			POINT curPos = GET_SINGLE(Input)->GetMousePos();
			float rotateX = static_cast<float>(curPos.y - prevPos.y);
			float rotateY = static_cast<float>(curPos.x - prevPos.x);

			GetGameObject()->GetTransform()->AddRotation(AXIS_X, rotateX * 50.f * DELTA_TIME);
			GetGameObject()->GetTransform()->AddRotation(AXIS_Y, rotateY * 50.f * DELTA_TIME);
		}
	}
	Component* CameraMoveScript::Clone(GameObject* _pGameObject)
	{
		return _pGameObject->AddComponent(new CameraMoveScript);
	}
}

