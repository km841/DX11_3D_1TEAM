#include "pch.h"
#include "EventManager.h"
#include "Event.h"
#include "SceneChangeEvent.h"
#include "SceneManager.h"
#include "RemoveGameObjectsEvent.h"
#include "RemoveGameObjectEvent.h"
#include "DeleteGameObjectsEvent.h"
#include "DeleteGameObjectEvent.h"
#include "ChangeMaterialEvent.h"
#include "MeshRenderer.h"
#include "Resources.h"



namespace hm
{
	EventManager::EventManager()
	{

	}

	EventManager::~EventManager()
	{
		while (!mEventQueue.empty())
		{
			Event* pEvent = mEventQueue.front();
			mEventQueue.pop();
			SAFE_DELETE(pEvent);
		}
	}

	void EventManager::PushEvent(Event* _pEvent)
	{
		mEventQueue.push(_pEvent);
	}
	void EventManager::PushSceneChangeEvent(SceneType _eSceneType)
	{
		mEventQueue.push(new SceneChangeEvent(_eSceneType));
	}
	void EventManager::PushRemoveGameObjectsEvent(SceneType _eSceneType, LayerType _eLayerType)
	{
		mEventQueue.push(new RemoveGameObjectsEvent(_eSceneType, _eLayerType));
	}
	void EventManager::PushDeleteGameObjectsEvent(SceneType _eSceneType, LayerType _eLayerType)
	{
		mEventQueue.push(new DeleteGameObjectsEvent(_eSceneType, _eLayerType));
	}
	void EventManager::PushRemoveGameObjectEvent(SceneType _eSceneType, GameObject* _pGameObject)
	{
		mEventQueue.push(new RemoveGameObjectEvent(_eSceneType, _pGameObject));
	}
	void EventManager::PushDeleteGameObjectEvent(SceneType _eSceneType, GameObject* _pGameObject)
	{
		mEventQueue.push(new DeleteGameObjectEvent(_eSceneType, _pGameObject));
	}
	void EventManager::Process()
	{
		while (!mEventQueue.empty())
		{
			Event* pEvent = mEventQueue.front();
			mEventQueue.pop();

			switch (pEvent->GetEventType())
			{
			case EventType::ChangeScene:
				ProcessChangeScene(static_cast<SceneChangeEvent*>(pEvent));
				break;

			case EventType::RemoveGameObjectsEvent:
				ProcessRemoveGameObjects(static_cast<RemoveGameObjectsEvent*>(pEvent));
				break;

			case EventType::RemoveGameObjectEvent:
				ProcessRemoveGameObject(static_cast<RemoveGameObjectEvent*>(pEvent));
				break;

			case EventType::DeleteGameObjectsEvent:
				ProcessDeleteGameObjects(static_cast<DeleteGameObjectsEvent*>(pEvent));
				break;

			case EventType::DeleteGameObjectEvent:
				ProcessDeleteGameObject(static_cast<DeleteGameObjectEvent*>(pEvent));
				break;

			case EventType::ChangeMaterialEvent:
				ProcessChangeMaterial(static_cast<ChangeMaterialEvent*>(pEvent));
				break;
			}

			SAFE_DELETE(pEvent);
		}
	}
	void EventManager::ProcessChangeScene(SceneChangeEvent* _pEvent)
	{
		GET_SINGLE(SceneManager)->ChangeScene(_pEvent->GetSceneType());
	}
	void EventManager::ProcessRemoveGameObjects(RemoveGameObjectsEvent* _pEvent)
	{
		SceneType eSceneType = _pEvent->GetSceneType();
		Scene* pScene = GET_SINGLE(SceneManager)->GetScene(eSceneType);
		pScene->RemoveGameObjects(_pEvent->GetLayerType());
	}
	void EventManager::ProcessRemoveGameObject(RemoveGameObjectEvent* _pEvent)
	{
		SceneType eSceneType = _pEvent->GetSceneType();
		Scene* pScene = GET_SINGLE(SceneManager)->GetScene(eSceneType);
		pScene->RemoveGameObject(_pEvent->GetGameObject());
	}
	void EventManager::ProcessDeleteGameObjects(DeleteGameObjectsEvent* _pEvent)
	{
		SceneType eSceneType = _pEvent->GetSceneType();
		Scene* pScene = GET_SINGLE(SceneManager)->GetScene(eSceneType);
		pScene->DeleteGameObjects(_pEvent->GetLayerType());
	}
	void EventManager::ProcessDeleteGameObject(DeleteGameObjectEvent* _pEvent)
	{
		SceneType eSceneType = _pEvent->GetSceneType();
		Scene* pScene = GET_SINGLE(SceneManager)->GetScene(eSceneType);
		pScene->DeleteGameObject(_pEvent->GetGameObject());
	}
	void EventManager::ProcessChangeMaterial(ChangeMaterialEvent* _pEvent)
	{
		GameObject* pGameObject = _pEvent->GetGameObject();
		wstring name = _pEvent->GetMaterialName();
		if (name == L"")
		{
			pGameObject->GetMeshRenderer()->SetMaterial(std::move(_pEvent->GetMaterial()));
		}
		else
		{
			pGameObject->GetMeshRenderer()->SetMaterial(GET_SINGLE(Resources)->Get<Material>(name));
		}
		
	}
}