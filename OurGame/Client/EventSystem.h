#pragma once

#include "MonoBehavior.h"
#include "GameObject.h"

class EventSystem : public MonoBehavior
{
public: 

	virtual void Initialize();

	static EventSystem* GetEventSystem();
	static EventSystem* spEventSystem;

	virtual Component* Clone(GameObject* _pGameObject);

	void AddEvent(std::string _addEventName) { Event.insert(std::pair<std::string, bool>(_addEventName, false)); }
	void EventOn(std::string _eventName) { 
		Event[_eventName] = true; 
	}
	
	bool CheckEventOn(std::string _eventName) {
		if (Event[_eventName] == true)
		{
			Event[_eventName] = false;
			return true;
		}
		else
		{
			return false;
		}
	}

private:
	std::map<std::string, bool> Event;
};