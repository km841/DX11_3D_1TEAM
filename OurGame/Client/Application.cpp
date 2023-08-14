#include "pch.h"
#include "Application.h"
#include "Engine.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "TestScene.h"

#include "MainOfficeMap.h"
#include "CorridorRightMap.h"
#include "DiningColliderCheckMap.h"
#include "EntranceHallMap.h"
#include "GrandmaBossMap.h"
#include "HallColliderCheckMap.h"
#include "LeftSecretFightMap.h"
#include "LeftSecretTrialMap.h"
#include "Right2Map.h"
#include "RightMap.h"
#include "RightSecretPassageMap.h"

#include "PrefabManager.h"

namespace hm
{
	void Application::Initialize(const WindowInfo& _windowInfo)
	{
		gpEngine->Initialize(_windowInfo);
		GET_SINGLE(PrefabManager)->Initialize();
	}

	void Application::Start()
	{
		GET_SINGLE(SceneManager)->AddScene(new TitleScene);
		GET_SINGLE(SceneManager)->AddScene(new TestScene);

		GET_SINGLE(SceneManager)->AddMap(new CorridorRightMap);
		GET_SINGLE(SceneManager)->AddMap(new DiningColliderCheckMap);
		GET_SINGLE(SceneManager)->AddMap(new EntranceHallMap);
		GET_SINGLE(SceneManager)->AddMap(new GrandmaBossMap);
		GET_SINGLE(SceneManager)->AddMap(new jh::HallColliderCheckMap);
		GET_SINGLE(SceneManager)->AddMap(new LeftSecretFightMap);
		GET_SINGLE(SceneManager)->AddMap(new LeftSecretTrialMap);
		GET_SINGLE(SceneManager)->AddMap(new Right2Map);
		GET_SINGLE(SceneManager)->AddMap(new RightMap);
		GET_SINGLE(SceneManager)->AddMap(new RightSecretPassageMap);
		GET_SINGLE(SceneManager)->AddMap(new MainOfficeMap);

		GET_SINGLE(SceneManager)->ActiveAndInitializeScene(SceneType::Title);
	}

	void Application::Update()
	{
		gpEngine->Update();
		gpEngine->Render();
	}

	void Application::Destroy()
	{
		GET_SINGLE(PrefabManager)->ClearPrefab();
		gpEngine->Destroy();
	}
}

