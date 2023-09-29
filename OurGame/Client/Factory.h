#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "Collider.h"
#include "Interface.h"

#include "InterfaceAlphaScript.h"
#include "InterfaceButtonScript.h"

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
		static T* CreateInterface(const Vec3& _pos, const Vec2& _scale, const wstring& _imgPath = L"", Types ... _args);

		template<typename T, typename ... Types>
		static T* CreateButtonInterface(const Vec3& _pos, const Vec2& _scale, const ButtonInfo& _info, const wstring& _imgPath = L"", Types ... _args);

	private:

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
}


