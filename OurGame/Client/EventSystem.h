#pragma once

#include "MonoBehavior.h"
#include "GameObject.h"

class EventSystem : public MonoBehavior
{
public: 

	virtual void Initialize();

	void AddEvent(std::string _addEventName) { Event.insert(std::pair<std::string, bool>(_addEventName, false)); }
	void EventOn(std::string _eventName) { Event[_eventName] = true; }
	
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