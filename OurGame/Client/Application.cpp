#include "pch.h"
#include "Application.h"
#include "Engine.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "TestScene.h"

namespace hm
{
	void Application::Initialize(const WindowInfo& _windowInfo)
	{
		gpEngine->Initialize(_windowInfo);
	}

	void Application::Start()
	{
		GET_SINGLE(SceneManager)->AddScene(new TitleScene);
		GET_SINGLE(SceneManager)->AddScene(new TestScene);
		GET_SINGLE(SceneManager)->ActiveAndInitializeScene(SceneType::Test);
	}

	void Application::Update()
	{
		gpEngine->Update();
		gpEngine->Render();
	}

	void Application::Destroy()
	{
		gpEngine->Destroy();
	}
}

