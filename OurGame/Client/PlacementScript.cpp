#include "pch.h"
#include "PlacementScript.h"
#include "Input.h"
#include "Transform.h"
#include "GameObject.h"
#include "Engine.h"

bool PlacementScript::mbExists = false;
PlacementScript::PlacementScript()
	: meTransformType(TransformType::Rotation)
	, mUnit(1.f)
{
	AssertEx(false == mbExists, L"PlacementScript::PlacementScript() - 이미 PlacementScript를 적용받은 객체가 존재");
	mbExists = true;
}

Component* PlacementScript::Clone(GameObject* _pGameObject)
{
	return _pGameObject->AddComponent(new PlacementScript);
}

void PlacementScript::FixedUpdate()
{
	if (IS_DOWN(KeyType::N_1))
		meTransformType = TransformType::Scale;
	
	if (IS_DOWN(KeyType::N_2))
		meTransformType = TransformType::Rotation;
	
	if (IS_DOWN(KeyType::N_3))
		meTransformType = TransformType::Position;

	if (IS_DOWN(KeyType::SQUARE_BKT_L))
		mUnit *= 0.1f;

	if (IS_DOWN(KeyType::SQUARE_BKT_R))
		mUnit *= 10.f;
	
	switch (meTransformType)
	{
	case TransformType::Position:
		EditPosition();
		break;
	case TransformType::Scale:
		EditScale();
		break;
	case TransformType::Rotation:
		EditRotation();
		break;
	}

	ShowTransform();
}

void PlacementScript::EditPosition()
{
	Vec3 target_pos = GetTransform()->GetPosition();

	float offset = 0.1f * mUnit;
	if (IS_PRESS(KeyType::LCTRL))
		offset *= 10.f;

	if (IS_DOWN(KeyType::UP))
		target_pos.z += offset;
	if (IS_DOWN(KeyType::DOWN))
		target_pos.z -= offset;
	if (IS_DOWN(KeyType::LEFT))
		target_pos.x -= offset;
	if (IS_DOWN(KeyType::RIGHT))
		target_pos.x += offset;
	if (IS_DOWN(KeyType::Z))
		target_pos.y += offset;
	if (IS_DOWN(KeyType::X))
		target_pos.y -= offset;
	
	GetTransform()->SetPosition(target_pos);
}

void PlacementScript::EditScale()
{
	Vec3 target_scale = GetTransform()->GetScale();
	float offset = 0.1f * mUnit;
	if (IS_PRESS(KeyType::LCTRL))
		offset *= 10.f;

	if (IS_DOWN(KeyType::UP))
		target_scale.z += offset;
	if (IS_DOWN(KeyType::DOWN))
		target_scale.z -= offset;
	if (IS_DOWN(KeyType::LEFT))
		target_scale.x -= offset;
	if (IS_DOWN(KeyType::RIGHT))
		target_scale.x += offset;
	if (IS_DOWN(KeyType::Z))
		target_scale.y += offset;
	if (IS_DOWN(KeyType::X))
		target_scale.y -= offset;

	GetTransform()->SetScale(target_scale);
}

void PlacementScript::EditRotation()
{
	Vec3 target_rotation = GetTransform()->GetRotation();

	float offset = 1.f * mUnit;
	if (IS_PRESS(KeyType::LCTRL))
		offset *= 10.f;
	
	Axis eAxis = Axis::AXIS_MAX;
	if (IS_DOWN(KeyType::UP))
	{
		eAxis = AXIS_Z;
	}

	if (IS_DOWN(KeyType::DOWN))
	{
		eAxis = AXIS_Z;
		offset = -offset;
	}

	if (IS_DOWN(KeyType::LEFT))
	{
		eAxis = AXIS_X;
	}
	if (IS_DOWN(KeyType::RIGHT))
	{
		eAxis = AXIS_X;
		offset = -offset;
	}
	if (IS_DOWN(KeyType::Z))
	{
		eAxis = AXIS_Y;
	}
	if (IS_DOWN(KeyType::X))
	{
		eAxis = AXIS_Y;
		offset = -offset;
	}

	GetTransform()->AddRotation(eAxis, offset);
}

void PlacementScript::ShowTransform()
{
	Transform* pTransform = GetTransform();

	Vec3 transform = {};
	wstring transformName = {};
	switch (meTransformType)
	{
	case TransformType::Position:
		transform = pTransform->GetPosition();
		transformName = L"POSITION";
		break;
	case TransformType::Scale:
		transform = pTransform->GetScale();
		transformName = L"SCALE";
		break;
	case TransformType::Rotation:
		transform = pTransform->GetRotation();
		transformName = L"ROTATION";
		break;
	}

	wstring strTransform = {};
	strTransform += L"x = " + std::to_wstring(transform.x) + L"\n";
	strTransform += L"y = " + std::to_wstring(transform.y) + L"\n";
	strTransform += L"z = " + std::to_wstring(transform.z) + L"\n";

	wstring strUnit = L"UNIT : " + std::to_wstring(mUnit);

	UINT32 color = 0xff0000ff;
	switch (meTransformType)
	{
	case TransformType::Position:
		color = 0xff0000ff;
		break;
	case TransformType::Scale:
		color = 0xffff0000;
		break;
	case TransformType::Rotation:
		color = 0xff00ff00;
		break;
	}
	
	/*
	* 지금 구현한 폰트는 임시로 사용하는 코드이기 때문에 사용하지 말아주세용
	* 삭제될 수도 있습니다.
	*/
	FONT->DrawString(transformName, 30.f, Vec3(50.f, 890.f, 1.f), FONT_WEIGHT::ULTRA_BOLD, color, FONT_ALIGN::LEFT);
	FONT->DrawString(strTransform, 20.f, Vec3(50.f, 850.f, 1.f), FONT_WEIGHT::ULTRA_BOLD, 0xff7f7f7f, FONT_ALIGN::LEFT);
	FONT->DrawString(strUnit, 15.f, Vec3(50.f, 750.f, 1.f), FONT_WEIGHT::ULTRA_BOLD, color, FONT_ALIGN::LEFT);
}


