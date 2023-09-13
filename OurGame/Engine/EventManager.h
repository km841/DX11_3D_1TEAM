#pragma once

namespace hm
{
	class Event;
	class SceneChangeEvent;
	class GameObject;

	class RemoveGameObjectsEvent;
	class RemoveGameObjectEvent;
	class DeleteGameObjectsEvent;
	class DeleteGameObjectEvent;
	class ChangeMaterialEvent;


	class EventManager
	{
		DECLARE_SINGLE(EventManager);
	public:

		void PushEvent(Event* _pEvent);
		void PushSceneChangeEvent(SceneType _eSceneType);
		void PushRemoveGameObjectsEvent(SceneType _eSceneType, LayerType _eLayerType);
		void PushDeleteGameObjectsEvent(SceneType _eSceneType, LayerType _eLayerType);
		void PushRemoveGameObjectEvent(SceneType _eSceneType, GameObject* _pGameObject);
		void PushDeleteGameObjectEvent(SceneType _eSceneType, GameObject* _pGameObject);
		void Process();

	private:
		void ProcessChangeScene(SceneChangeEvent* _pEvent);
		void ProcessRemoveGameObjects(RemoveGameObjectsEvent* _pEvent);
		void ProcessRemoveGameObject(RemoveGameObjectEvent* _pEvent);
		void ProcessDeleteGameObjects(DeleteGameObjectsEvent* _pEvent);
		void ProcessDeleteGameObject(DeleteGameObjectEvent* _pEvent);
		void ProcessChangeMaterial(ChangeMaterialEvent* _pEvent);

	private:
		std::queue<Event*> mEventQueue;

	};

}

