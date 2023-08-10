#include "pch.h"
#include "PrefabManager.h"
#include "GameObject.h"

namespace hm
{
	PrefabManager::PrefabManager()
	{
	}

	PrefabManager::~PrefabManager()
	{
	}

	void PrefabManager::ClearPrefab()
	{
		for (int i = 0; i < mPrefabMap.size(); ++i)
		{
			PrefabMap& prefabMap = mPrefabMap[i];

			for (auto& pair : prefabMap)
			{
				SAFE_DELETE(pair.second);
			}
		}

	}
}
