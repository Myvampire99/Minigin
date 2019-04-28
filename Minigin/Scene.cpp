#include "MiniginPCH.h"
#include "Scene.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) : mName(name), m_IsActive(false) {}

dae::Scene::~Scene() = default;

void dae::Scene::Add(const std::shared_ptr<dae::SceneObject>& object)
{
	mObjects.push_back(object);
}


void dae::Scene::Update(const float elapsedTime)
{

	m_ElapsedTime = elapsedTime;


	SceneUpdate();


	for(auto gameObject : mObjects)
	{
		gameObject->Update(elapsedTime);
	}

}

void dae::Scene::Render() const
{
	for (const auto gameObject : mObjects)
	{
		gameObject->Render();
	}
}

void dae::Scene::Initialize()
{

	SceneInitialize();

	for (const auto gameObject : mObjects)
	{
		gameObject->Initialize();
	}

}

bool dae::Scene::IsActive() const
{
	return m_IsActive;
}

void dae::Scene::SetActive(bool active)
{
	m_IsActive = active;
}

std::string dae::Scene::GetName() const
{
	return mName;
}