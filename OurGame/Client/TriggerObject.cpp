#include "pch.h"
#include "TriggerObject.h"
#include "Collider.h"
#include "SceneManager.h"
#include "Camera.h"
#include "FocusingScript.h"
#include "CutSceneCameraMoveScript.h"

namespace jh
{
	TriggerObject::TriggerObject() :
		GameObject(LayerType::Trigger)
	{
	}

	TriggerObject::~TriggerObject()
	{
	}

	void TriggerObject::Initialize()
	{
		GameObject::Initialize();
	}

	void TriggerObject::Update()
	{
		GameObject::Update();
	}

	void TriggerObject::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void TriggerObject::Render()
	{
		GameObject::Render();
	}

	void TriggerObject::OnTriggerEnter(Collider* _pOther)
	{
		if (LayerType::Player == _pOther->GetGameObject()->GetLayerType() &&
			SceneType::MainOfficeMap == ACTIVE_SCENE->GetSceneType())
		{
			CUTSCENE_CAMERA->GetTransform()->SetPosition(MAIN_CAMERA->GetTransform()->GetPosition());
			CUTSCENE_CAMERA->GetTransform()->SetRotation(MAIN_CAMERA->GetTransform()->GetRotation());
			ACTIVE_SCENE->ChangeCameraMode();

			CutSceneCameraMoveScript* pScript = MAIN_CAMERA->GetScript<CutSceneCameraMoveScript>();
			pScript->SetStartPos(CUTSCENE_CAMERA->GetGameObject()->GetTransform()->GetPosition());
			pScript->SetStartRot(CUTSCENE_CAMERA->GetGameObject()->GetTransform()->GetRotation());
			pScript->CutSceneStart();
		}
	}

	void TriggerObject::OnTriggerStay(Collider* _pOther)
	{
	}

	void TriggerObject::OnTriggerExit(Collider* _pOther)
	{
	}
}
