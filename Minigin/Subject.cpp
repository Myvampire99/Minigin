#include "MiniginPCH.h"
#include "Subject.h"


Subject::Subject()
{
}


Subject::~Subject()
{
}

void Subject::AddObserver(Observer * observer)
{
	m_Observer.push_back(observer);
}

void Subject::RemoveObserver(Observer * observer)
{
	m_Observer.erase(std::remove(m_Observer.begin(), m_Observer.end(), observer), m_Observer.end());
}

void Subject::Notify( dae::GameObject * entity, Event event)
{
	for (int i = 0; i < m_Observer.size(); i++)
	{
		m_Observer[i]->onNotify(entity, event);
	}
}
