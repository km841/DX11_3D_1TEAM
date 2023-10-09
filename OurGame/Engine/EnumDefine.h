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
		PlayerCol,
		ArrowCol,
		Grandma_Boss,  //이거 더미 목록
		Monster,
		MonsterCol,
		MonsterSlowCol,
		MonsterHeavyCol,
		Monster_ProjectTile,
		Item,
		Ladder,
		Npc,
		Effect,
		Ground,
		Obstacle,
		DungeonObject,
		DecoObject,
		WallObject,
		Portal,
		Mirror,
		PotCell,
		Interface,
		End,
	};

	enum
	{
		LAYER_TYPE_COUNT = static_cast<int>(LayerType::End),
	};

	enum class GroundMaterial
	{
		Marble, // 대리석 바닥
		Wood,   // 나무 바닥
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
		Video,
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
		b5,
		b6,
		b7,
		b8,

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
		Noise,
		Distortion,
		Reflect,
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
		Convex,
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
		Hold,
		WhiteIn,
		WhiteOut,
		CameraShake,
		ChromaticAbberation, // 색수차
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

	enum class NaviMeshCellType
	{
		None,
		Open,
		Close,
	};

	enum class KeyType
	{
		UP = VK_UP,
		DOWN = VK_DOWN,
		LEFT = VK_LEFT,
		RIGHT = VK_RIGHT,

		Q = 'Q', W = 'W', E = 'E', R = 'R', T = 'T', Y = 'Y', U = 'U', I = 'I', O = 'O', P = 'P',
		A = 'A', S = 'S', D = 'D', F = 'F', G = 'G', H = 'H', J = 'J', K = 'K', L = 'L',
		Z = 'Z', X = 'X', C = 'C', V = 'V', B = 'B', N = 'N', M = 'M',

		NUM_0 = VK_NUMPAD0, NUM_1 = VK_NUMPAD1, NUM_2 = VK_NUMPAD2,
		NUM_3 = VK_NUMPAD3, NUM_4 = VK_NUMPAD4, NUM_5 = VK_NUMPAD5,
		NUM_6 = VK_NUMPAD6, NUM_7 = VK_NUMPAD7, NUM_8 = VK_NUMPAD8,
		NUM_9 = VK_NUMPAD9,

		N_0 = '0', N_1 = '1', N_2 = '2', N_3 = '3', N_4 = '4', N_5 = '5',
		N_6 = '6', N_7 = '7', N_8 = '8', N_9 = '9',

		ENTER = VK_RETURN,
		SPACE = VK_SPACE,
		TAB = VK_TAB,
		LCTRL = VK_LCONTROL,
		ALT = VK_MENU,
		SHIFT_L = VK_LSHIFT,

		LBUTTON = MK_LBUTTON,
		RBUTTON = MK_RBUTTON,

		SQUARE_BKT_L = VK_OEM_4,
		SQUARE_BKT_R = VK_OEM_6,
	};
}

