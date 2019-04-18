#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) : mName(name) {}

dae::Scene::~Scene() = default;

void dae::Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	mObjects.push_back(object);
}


void dae::Scene::Update(const float elapsedTime)
{
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
	for (const auto gameObject : mObjects)
	{
		gameObject->Initialize();
	}
}

