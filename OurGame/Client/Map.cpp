#include "pch.h"
#include "Map.h"
#include "PlacementScript.h"

namespace hm
{
	Map::Map(MapType _eMapType)
		: Scene(_eMapType)
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
	void Map::SetGizmoTarget(GameObject* _pTarget)
	{
		TOOL->SetGameObject(_pTarget);
		_pTarget->AddComponent(new PlacementScript);
	}
}

