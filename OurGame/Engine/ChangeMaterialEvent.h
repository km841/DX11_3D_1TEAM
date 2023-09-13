#pragma once
#include "Event.h"
namespace hm
{
	class GameObject;
	class Material;
	class ChangeMaterialEvent :
		public Event
	{
	public:
		ChangeMaterialEvent(const wstring& _matName, GameObject* _pGameObject);
		ChangeMaterialEvent(shared_ptr<Material> _pMaterial, GameObject* _pGameObject);
		GameObject* GetGameObject() { return mpGameObject; }
		const wstring& GetMaterialName() { return mMatName; }
		shared_ptr<Material> GetMaterial() { return std::move(mpMaterial); }

	private:
		GameObject* mpGameObject;
		wstring mMatName;
		shared_ptr<Material> mpMaterial;
	};

}

