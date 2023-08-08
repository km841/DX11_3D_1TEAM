#include "pch.h"
#include "TitleScene.h"
#include "Input.h"
#include "EventManager.h"
#include "SceneChangeEvent.h"
#include "SceneManager.h"

namespace hm
{
	TitleScene::TitleScene()
		: Scene(SceneType::Title)
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		Scene::Initialize();
	}

	void TitleScene::Update()
	{
		Scene::Update();
		if (IS_DOWN(KeyType::P))
		{
			GET_SINGLE(EventManager)->PushEvent(new SceneChangeEvent(SceneType::Test));
		}
	}

	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void TitleScene::FinalUpdate()
	{
		Scene::FinalUpdate();
	}

	void TitleScene::Render()
	{
		Scene::Render();
	}

	void TitleScene::Destroy()
	{
		Scene::Destroy();
	}

	void TitleScene::Enter()
	{
	}

	void TitleScene::Exit()
	{
	}
}

