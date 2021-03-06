#include "MiniginPCH.h"
#include "Subject.h"


Subject::Subject()
:m_Observer {}
{
}


Subject::~Subject()
{/*
	for (auto &p : m_Observer) {
		delete p;
		p = nullptr;
	}*/
	m_Observer.clear();
}

void Subject::AddObserver(Observer * observer)
{
	m_Observer.push_back(observer);
}

void Subject::RemoveObserver(Observer * observer)
{
	m_Observer.erase(std::remove(m_Observer.begin(), m_Observer.end(), observer), m_Observer.end());
}

void Subject::Notify(Event event)
{
	for (unsigned int i = 0; i < m_Observer.size(); i++)
	{
		m_Observer[i]->onNotify(event);
	}
}
