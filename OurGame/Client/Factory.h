#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "RigidBody.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "Collider.h"

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
			Types ... _args);

		template<typename T, typename ... Types>
		static T* CreateObjectHasPhysical(
			const Vec3& _pos,
			PhysicsInfo _physicsInfo = PhysicsInfo(),
			const wstring& _materialName = L"Deferred",
			const wstring& _fbxPath = L"",
			Types ... _args);

	private:

	};


	template<typename T, typename ...Types>
	inline T* Factory::CreateObject(const Vec3& _pos, const wstring& _materialName, const wstring& _fbxPath, Types ..._args)
	{
		T* pObject = new T(_args...);
		Transform* pTransform = pObject->AddComponent(new Transform);
		pTransform->SetPosition(_pos);

		RigidBody* pRigidBody = pObject->AddComponent(new RigidBody);
		MeshRenderer* pMeshRenderer = pObject->AddComponent(new MeshRenderer);
		if (false == _fbxPath.empty())
		{
			shared_ptr<MeshData> pMeshData = GET_SINGLE(Resources)->LoadFBX(_fbxPath, _materialName);
			AssertEx(nullptr != pMeshData, L"Factory::CreateObject() - FBX 파일 주소가 잘못되었음");
			pMeshRenderer->SetMeshData(pMeshData);
		}
		else
		{
			shared_ptr<Material> pMaterial = GET_SINGLE(Resources)->Get<Material>(_materialName);
			AssertEx(nullptr != pMaterial, L"Factory::CreateObject() - Material이 존재하지 않음");

			pMeshRenderer->SetMaterial(pMaterial->Clone());
			pMeshRenderer->SetMesh(GET_SINGLE(Resources)->LoadCubeMesh());
		}

		return pObject;
	}

	template<typename T, typename ...Types>
	inline T* Factory::CreateObjectHasPhysical(const Vec3& _pos, PhysicsInfo _physicsInfo, const wstring& _materialName, const wstring& _fbxPath, Types ..._args)
	{
		T* pObject = CreateObject<T>(_pos, _materialName, _fbxPath, _args...);

		RigidBody* pRigidBody = pObject->GetRigidBody();
		pRigidBody->SetPhysical(_physicsInfo);
		pObject->AddComponent(new Collider);

		return pObject;
	}
}


