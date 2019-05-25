#pragma once
enum class Event {
	EVENT_DIED
	, EVENT_DIEDROCK
};


class Observer
{
public:
	virtual ~Observer();
	virtual void onNotify( dae::GameObject* entity, Event event) = 0;
};

