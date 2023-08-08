#pragma once
#include "GameObject.h"
namespace hm
{
	class CollisionManager
	{
		DECLARE_SINGLE(CollisionManager);
	public:
		
		void Update();
		void SetCollisionGroup(LayerType _eLayerType_1, LayerType _eLayerType_2);
		std::bitset<LAYER_TYPE_COUNT> GetCollisionGroup(LayerType _eLayerType);

	private:
		std::array<std::bitset<LAYER_TYPE_COUNT>, LAYER_TYPE_COUNT> mArrColGroup;
	};
}


