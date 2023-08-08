#pragma once
namespace hm
{

	class Event
	{
	public:
		EventType GetEventType() { return meEventType; }

	protected:
		EventType meEventType;
	};

}

