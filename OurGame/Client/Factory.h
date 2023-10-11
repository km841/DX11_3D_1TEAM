#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "Collider.h"
#include "Interface.h"
#include "AudioSound.h"

#include "InterfaceAlphaScript.h"
#include "InterfaceButtonScript.h"
#include "PaperBurnScript.h"
#include "MonsterCrackScript.h"
#include "MonsterHitScript.h"

#include "Grimace.h"
#include "Bat.h"
#include "HeadRoller.h"
#include "Mage.h"
#include "Lurker.h"
#include "SpawnDoor.h"


namespace hm
{
	class Factory
	{
	public:
		template<typename T, typename ... Types>
		static T* CreateObject(
			const Vec3& _pos,
			const wstring& _materialName = L"Deferred",
			const wstring& _fbxPath = L"",
			bool _bInvNormal = false,
			Types ... _args);

		template<typename T, typename ... Types>
		static T* CreateObjectHasPhysical(
			const Vec3& _pos,
			PhysicsInfo _physicsInfo = PhysicsInfo(),
			const wstring& _materialName = L"Deferred",
			const wstring& _fbxPath = L"",
			bool _bInvNormal = false,
			Types ... _args);

		template<typename T, typename ... Types>
		static T* CreateMonster(
			const Vec3& _pos,
			PhysicsInfo _physicsInfo = PhysicsInfo(),
			const wstring& _materialName = L"MonsterDeferred",
			const wstring& _fbxPath = L"",
			bool _bInvNormal = false,
			Types ... _args);


		template<typename T, typename ... Types>
		static T* CreateInterface(const Vec3& _pos, const Vec2& _scale, const wstring& _imgPath = L"", Types ... _args);

		template<typename T, typename ... Types>
		static T* CreateButtonInterface(const Vec3& _pos, const Vec2& _scale, const ButtonInfo& _info, const wstring& _imgPath = L"", Types ... _args);

		template<typename T, typename ... Types>
		static SpawnDoor<T>* SpawnMonster(const Vec3& _pos, const Vec3& _rotation = Vec3(90.f, 0.f, 0.f), Types ... _args);

		template<typename T, typename ... Types>
		static SpawnDoor<T>* CreateSpawnDoor(const Vec3& _pos, Types ... _args);

	public:
		static Grimace* CreateGrimace(const Vec3& _pos, const Vec3& _rotation = Vec3(-180.f, 0.f, 0.f));
		static Bat* CreateBat(const Vec3& _pos, const Vec3& _rotation = Vec3(-90.f, 0.f, 0.f));
		//static Mage* CreateMage(const Vec3& _pos, const Vec3& _rotation = Vec3(-90.f, 0.f, 0.f));
		//static Lurker* CreateLurker(const Vec3& _pos, const Vec3& _rotation = Vec3(-90.f, 0.f, 0.f));
		//static HeadRoller* CreateHeadRoller(const Vec3& _pos, const Vec3& _rotation = Vec3(0.f, 0.f, 0.f));
	
	

	private:
		template<typename T>
		static MonsterType GetMonsterType();

	};


	template<typename T, typename ...Types>
	inline T* Factory::CreateObject(const Vec3& _pos, const wstring& _materialName, const wstring& _fbxPath, bool _bInvNormal, Types ..._args)
	{
		T* pObject = new T(_args...);
		Transform* pTransform = pObject->AddComponent(new Transform);
		pTransform->SetPosition(_pos);

		RigidBody* pRigidBody = pObject->AddComponent(new RigidBody);
		MeshRenderer* pMeshRenderer = pObject->AddComponent(new MeshRenderer);
		if (false == _fbxPath.empty())
		{
			shared_ptr<MeshData> pMeshData = GET_SINGLE(Resources)->LoadFBX(_fbxPath, _materialName, _bInvNormal);
			AssertEx(nullptr != pMeshData, L"Factory::CreateObject() - FBX 파일 주소가 잘못되었음");
			pMeshRenderer->SetMeshData(pMeshData);
		}
		else
		{
			shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(_materialName);
			AssertEx(nullptr != pMaterial, L"Factory::CreateObject() - Material이 존재하지 않음");

			pMeshRenderer->SetMaterial(pMaterial->Clone());
			pMeshRenderer->SetMesh(GET_SINGLE(Resources)->LoadPointMesh());
		}

		return pObject;
	}

	template<typename T, typename ...Types>
	inline T* Factory::CreateObjectHasPhysical(const Vec3& _pos, PhysicsInfo _physicsInfo, const wstring& _materialName, const wstring& _fbxPath, bool _bInvNormal, Types ..._args)
	{
		T* pObject = CreateObject<T>(_pos, _materialName, _fbxPath, _bInvNormal, _args...);

		RigidBody* pRigidBody = pObject->GetRigidBody();
		pRigidBody->SetPhysical(_physicsInfo);
		pObject->AddComponent(new Collider);

		return pObject;
	}
	template<typename T, typename ...Types>
	inline T* Factory::CreateMonster(const Vec3& _pos, PhysicsInfo _physicsInfo, const wstring& _materialName, const wstring& _fbxPath, bool _bInvNormal, Types ..._args)
	{
		T* pObject = CreateObjectHasPhysical<T>(_pos, _physicsInfo, _materialName, _fbxPath, _bInvNormal, _args...);
		pObject->SetFrustumCheckFlag(false);
		pObject->AddComponent<PaperBurnScript>();
		pObject->AddComponent<MonsterCrackScript>();
		pObject->AddComponent<MonsterHitScript>();
		pObject->AddComponent<AudioSound>();
		pObject->GetRigidBody()->ApplyGravity();
		pObject->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_X, true);
		pObject->GetRigidBody()->RemoveAxisSpeedAtUpdate(AXIS_Z, true);

		return pObject;
	}
	template<typename T, typename ...Types>
	inline T* Factory::CreateInterface(const Vec3& _pos, const Vec2& _scale, const wstring& _imgPath, Types ..._args)
	{
		if constexpr (!std::is_base_of_v<Interface, T>)
			AssertEx(false, L"Factory::CreateButtonInterface() - Interface 타입이 아닌 오브젝트를 생성하려는 시도");

		T* pInterface = CreateObject<T>(_pos, L"Interface", L"", false, _args...);
		pInterface->GetMeshRenderer()->SetMesh(GET_SINGLE(Resources)->LoadRectMesh());

		if (false == _imgPath.empty())
		{
			shared_ptr<Texture> pDefaultTexture = GET_SINGLE(Resources)->Load<Texture>(_imgPath, _imgPath);
			pInterface->GetMeshRenderer()->GetMaterial()->SetTexture(0, pDefaultTexture);
		}

		pInterface->GetTransform()->SetScale(Vec3(_scale.x, _scale.y, 1.f));

		InterfaceAlphaScript* pAlphaScript = pInterface->AddComponent(new InterfaceAlphaScript);
		pInterface->SetAlphaFunction([=](float _alpha) { pAlphaScript->SetAlpha(_alpha); });
		pInterface->SetColorFunction([=](Vec3 _color) { pAlphaScript->SetColor(_color); });

		return pInterface;
	}
	template<typename T, typename ...Types>
	inline T* Factory::CreateButtonInterface(const Vec3& _pos, const Vec2& _scale, const ButtonInfo& _info, const wstring& _imgPath, Types ..._args)
	{
		T* pInterface = CreateInterface<T>(_pos, _scale, _imgPath, _args...);

		InterfaceButtonScript* pButtonScript = pInterface->AddComponent(new InterfaceButtonScript);
		pButtonScript->SetNonHoveredTexture(_info.pNonHoveredTexture);
		pButtonScript->SetHoveredTexture(_info.pHoveredTexture);
		pButtonScript->SetClickedTexture(_info.pClickedTexture);

		pButtonScript->SetNonHoveredCallback(_info.nonHoveredCallback);
		pButtonScript->SetHoveredCallback(_info.hoveredCallback);
		pButtonScript->SetClickedCallback(_info.clickedCallback);

		return pInterface;
	}
	template<typename T, typename ...Types>
	inline SpawnDoor<T>* Factory::SpawnMonster(const Vec3& _pos, const Vec3& _rotation, Types ..._args)
	{
		MonsterType eMonsterType = GetMonsterType<T>();
	
		SpawnDoor<T>* pDoor = CreateSpawnDoor<T>(_pos, _args...);
		switch (eMonsterType)
		{
		case MonsterType::Bat:
			pDoor->SetSpawnFunction(std::bind(&Factory::CreateBat, _pos, _rotation));
			break;
		//case MonsterType::Grimace:
		//	pDoor->SetSpawnFunction(std::bind(&Factory::CreateGrimace, _pos, _rotation));
		//	break;
		//case MonsterType::HeadRoller:
		//	pDoor->SetSpawnFunction(std::bind(&Factory::CreateHeadRoller, _pos, _rotation));
		//	break;
		//case MonsterType::Lurker:
		//	pDoor->SetSpawnFunction(std::bind(&Factory::CreateLurker, _pos, _rotation));
		//	break;
		//case MonsterType::Mage:
		//	pDoor->SetSpawnFunction(std::bind(&Factory::CreateMage, _pos, _rotation));
		//	break;
		default:
			break;
		}
		pDoor->SetPaperBurn();
		//AssertEx(nullptr != pMonster, L"Factory::SpawnMonster() - 몬스터가 생성되지 않음");
		return pDoor;
	}
	template<typename T, typename ...Types>
	inline SpawnDoor<T>* Factory::CreateSpawnDoor(const Vec3& _pos, Types ..._args)
	{
		SpawnDoor<T>* pSpawnDoor = CreateObject<SpawnDoor<T>>(_pos, L"Forward_CullNone", L"..\\Resources\\FBX\\Monster\\SpawnDoor.fbx");
		pSpawnDoor->GetTransform()->SetScale(Vec3(5.f, 5.f, 5.f));
		pSpawnDoor->GetMeshRenderer()->GetMaterial()->SetVec4AllSubset(0, Vec4(1.f, 0.6f, 1.f, 1.f));
		PaperBurnScript* pScript = pSpawnDoor->AddComponent(new PaperBurnScript);
		
		return pSpawnDoor;
	}
	template<typename T>
	inline MonsterType Factory::GetMonsterType()
	{
		if (std::is_same_v<T, Grimace>)
			return MonsterType::Grimace;
		else if (std::is_same_v<T, Bat>)
			return MonsterType::Bat;
		else if (std::is_same_v<T, HeadRoller>)
			return MonsterType::HeadRoller;
		else if (std::is_same_v<T, Mage>)
			return MonsterType::Mage;
		else if (std::is_same_v<T, Lurker>)
			return MonsterType::Lurker;

		else
		{
			AssertEx(false, L"잘못된 타입 전달");
			return MonsterType::End;
		}
	}
}


