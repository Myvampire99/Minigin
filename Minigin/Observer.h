#pragma once
enum class Event {
	EVENT_DIED
};


class Observer
{
public:
	virtual ~Observer();
	virtual void onNotify( dae::GameObject* entity, Event event) = 0;
};

