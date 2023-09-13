#include "pch.h"
#include "ChangeMaterialEvent.h"

namespace hm
{
	ChangeMaterialEvent::ChangeMaterialEvent(const wstring& _matName, GameObject* _pGameObject)
		: mpGameObject(_pGameObject)
		, mMatName(_matName)
	{
		meEventType = EventType::ChangeMaterialEvent;
	}

	ChangeMaterialEvent::ChangeMaterialEvent(shared_ptr<Material> _pMaterial, GameObject* _pGameObject)
		: mpGameObject(_pGameObject)
		, mpMaterial(_pMaterial)
	{
		meEventType = EventType::ChangeMaterialEvent;
	}

}
