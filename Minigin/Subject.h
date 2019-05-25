#pragma once
class Subject
{
public:
	Subject();
	~Subject();

	void AddObserver(Observer *observer);
	void RemoveObserver(Observer *observer);
	void Notify( dae::GameObject* entity, Event event);
private:
	std::vector<Observer*> m_Observer;
};

