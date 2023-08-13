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

	public:
		void ApplyForceInLayerAtLocation(LayerType _eLayerType, const Vec3& _location, const Vec3& _volume, const Vec3& _force);
		void ApplyForceInLayerFromDot(LayerType _eLayerType, const Vec3& _location, const Vec3& _force);

	private:
		std::array<std::bitset<LAYER_TYPE_COUNT>, LAYER_TYPE_COUNT> mArrColGroup;
	};
}


