#pragma once

namespace hm
{
	enum class EventType
	{
		ChangeScene,
		DeleteGameObjectEvent,
		DeleteGameObjectsEvent,
		RemoveGameObjectEvent,
		RemoveGameObjectsEvent,
		ChangeMaterialEvent,
	};

	enum class LayerType
	{
		Unknown,
		Player,
		Grandma_Boss,
		Monster,
		Npc,
		Effect,
		Ground,
		Obstacle,
		DecoObject,
		WallObject,
		UI,
		End,
	};

	enum
	{
		LAYER_TYPE_COUNT = static_cast<int>(LayerType::End),
	};

	enum class GroundMaterial
	{
		Marble, // �븮�� �ٴ�
		Wood,   // ���� �ٴ�
	};

	enum class ObjectType
	{
		GameObject,
		Component,
		Material,
		Mesh,
		Shader,
		Texture,
		Sound,
		MeshData,
		End,
	};

	enum
	{
		OBJECT_TYPE_COUNT = static_cast<int>(ObjectType::End),
	};

	enum class SceneType
	{
		Test,
		Title,
		Hall,
		Dungeon,
		Boss,
		Ending,

		MainOfficeMap,
		CorridorRightMap,
		DiningColliderCheckMap,
		EntranceHallMap,
		GrandmaBossMap,
		HallColliderCheckMap,
		LeftSecretFightMap,
		LeftSecretTrialMap,
		Right2Map,
		RightMap,
		RightSecretPassageMap,

		Monster_Player_Test,
		PhysicsTest,

		End,
	};

	using MapType = SceneType;

	enum
	{
		SCENE_TYPE_COUNT = static_cast<int>(SceneType::End),
	};

	enum class RegisterCBV
	{
		b0,
		b1,
		b2,
		b3,
		b4,


		End,
	};

	enum class RegisterSRV
	{
		t0,
		t1,
		t2,
		t3,
		t4,
		t5,
		t6,
		t7,
		t8,
		t9,
		t10,
		t11,
		t12,
		t13,
		t14,
		t15,

		End,
	};

	enum class RegisterUAV
	{
		u0,
		u1,
		u2,
		u3,
		u4,

		End,
	};

	enum
	{
		CBV_REGISTER_COUNT = RegisterCBV::End,
		SRV_REGISTER_COUNT = RegisterSRV::End,
		UAV_REGISTER_COUNT = RegisterUAV::End,
	};

	enum class ConstantBufferType
	{
		Transform,
		Material,
		Light,
		Bloom,
		End,
	};

	enum
	{
		CONSTANT_BUFFER_TYPE_COUNT = static_cast<int>(ConstantBufferType::End),
	};

	enum Axis
	{
		AXIS_X,
		AXIS_Y,
		AXIS_Z,
		AXIS_MAX
	};

	enum class ActorType
	{
		Static,
		Dynamic,
		Kinematic,
		Character,
	};

	enum class GeometryType
	{
		Sphere,
		Box,
		Capsule,
		Plane,
		Mesh,
	};

	enum class ModelType
	{
		StaticModel,
		DynamicModel,
	};

	enum class ScreenEffectType
	{
		None,
		FadeIn,
		FadeOut,
	};

	enum
	{
		SCREEN_EFFECT_GROUP_COUNT = 2,
	};

	enum class BehaviorResult
	{
		Success,
		Running,
		Failure,
	};
}

