#pragma once
#include "Observer.h"
class Subject
{
public:
	Subject();
	~Subject();

	void AddObserver(Observer *observer);
	void RemoveObserver(Observer *observer);
	void Notify(Event event);
private:
	std::vector<Observer*> m_Observer;
};

