#pragma once
enum class Event {
	EVENT_SWITCH_SCENE_DEACTIVATE,
	EVENT_SWITCH_SCENE_ACTIVATE,
	EVENT_PLAYER_DEAD
};


class Observer
{
public:
	virtual ~Observer();
	virtual void onNotify( Event event) = 0;
};

