#include "pch.h"
#include "EndingScene.h"
#include "Engine.h"

/* Resource */
#include "MeshData.h"
#include "Material.h"
#include "Mesh.h"

/* Manager */
#include "PrefabManager.h"
#include "EventManager.h"
#include "Factory.h"
#include "CollisionManager.h"
#include "Input.h"
#include "SceneManager.h"
#include "Resources.h"
#include "RenderManager.h"

/* GameObject */
#include "GameObject.h"
#include "Player.h"
#include "Ground.h"
#include "DecoObject.h"
#include "UI.h"
#include "CameraHolder.h"
#include "Elevator.h"
#include "HpUi.h"
#include "ManaUi.h"
#include "Banker.h"

/* Interface */
#include "Interface.h"

/* Component */
#include "Collider.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "ParticleSystem.h"
#include "UIText.h"
#include "AudioSound.h"
#include "Mirror.h"
#include "Animator.h"

/* Script */
#include "PaperBurnScript.h"
#include "CameraMoveScript.h"
#include "CinematicCamMove.h"
#include "InterfaceAlphaScript.h"
#include "InterfaceButtonScript.h"
#include "StartButtonScript.h"
#include "LogoBlinkScript.h"
#include "PlayerMoveScript.h"
#include "PlayerMoveOverMapScript.h"
#include "FocusingScript.h"
#include "OwnerFollowScript.h"
#include "CutSceneCameraMoveScript.h"
#include "EndingLogoScript.h"
#include "EventSystem.h"

/* Event */
#include "SceneChangeEvent.h"

namespace hm
{
	EndingScene::EndingScene()
		: Map(MapType::Ending)
	{
	}

	EndingScene::~EndingScene()
	{
	}

	void EndingScene::Initialize()
	{
		Map::Initialize();
	}

	void EndingScene::Update()
	{
		Map::Update();
	}

	void EndingScene::FixedUpdate()
	{
		Map::FixedUpdate();
	}

	void EndingScene::FinalUpdate()
	{
		Map::FinalUpdate();
	}

	void EndingScene::Render()
	{
		Map::Render();
	}

	void EndingScene::Destroy()
	{
		Map::Destroy();
	}

	void EndingScene::Enter()
	{		// Title

		PLAYER->GetTransform()->SetPosition(Vec3(1000.f, 1000.f, 1000.f));
		{
			Interface* pLogoInterface = Factory::CreateInterface<Interface>(Vec3(0.f, 0.f, 0.f), Vec2(0.f, 0.f), L"..\\Resources\\Texture\\DD_Logo_Smooth_Dropshadow.png");
			pLogoInterface->AddComponent(new EndingLogoScript);
			pLogoInterface->AddComponent(new AudioSound);
			AddGameObject(pLogoInterface);
		}

		spPlayerHolder->GetAudioSound()->SetSound(L"EndingBGM", this, true, "..\\Resources\\Sound\\EndingBGM.mp3");
		spPlayerHolder->GetAudioSound()->Play(30);
	}

	void EndingScene::Exit()
	{
	}
}

