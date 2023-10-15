#include "pch.h"
#include "EventSystem.h"

EventSystem* EventSystem::spEventSystem;


EventSystem::EventSystem()
{
	spEventSystem = this;
}

EventSystem::~EventSystem()
{
}

void EventSystem::Initialize()
{

}

EventSystem* EventSystem::GetEventSystem()
{
	return spEventSystem;
}

Component* EventSystem::Clone(GameObject* _pGameObject)
{
	return _pGameObject->AddComponent(new EventSystem);

}
