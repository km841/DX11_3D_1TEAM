#include "pch.h"
#include "Map.h"

namespace hm
{
	Map::Map(SceneType _eSceneType)
		: Scene(_eSceneType)
	{
	}

	Map::~Map()
	{
	}
	void Map::Initialize()
	{
		Scene::Initialize();
	}
	void Map::Update()
	{
		Scene::Update();
	}
	void Map::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void Map::FinalUpdate()
	{
		Scene::FinalUpdate();
	}
	void Map::Render()
	{
		Scene::Render();
	}
	void Map::Enter()
	{
	}
	void Map::Exit()
	{
	}
}

