#include "pch.h"
#include "TriggerObject.h"
#include "Collider.h"
#include "SceneManager.h"
#include "Camera.h"
#include "FocusingScript.h"
#include "CutSceneCameraMoveScript.h"
#include "EventSystem.h"
#include "TextBox.h"

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
		/*
		영진님) MainOffice에서 플레이어와 충돌 시 여기로 들어옵니다.
		pScript->CutSceneStart()에서 bool변수 값을 바꿔주면
		CutSceneCameraMoveScript의 FixedUpdate에서 MainOfficeMove함수(실제 카메라가 이동하는 함수)를 호출합니다.
		*/

		if (LayerType::Player == _pOther->GetGameObject()->GetLayerType() &&
			SceneType::MainOfficeMap == ACTIVE_SCENE->GetSceneType())
		{
			EVENTSYSTEM->EventOn("OfficeArriveEvent");
			
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
