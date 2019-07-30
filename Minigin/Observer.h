#pragma once
enum class Event {
	EVENT_SWITCH_SCENE_DEACTIVATE,
	EVENT_SWITCH_SCENE_ACTIVATE
};


class Observer
{
public:
	virtual ~Observer();
	virtual void onNotify( Event event) = 0;
};

