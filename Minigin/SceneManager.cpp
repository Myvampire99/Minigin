#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"


void dae::SceneManager::Update(const float elapsedTime)
{
	for(auto scene : mScenes)
	{
		scene->Update(elapsedTime);
	}
}

void dae::SceneManager::Render()
{
	for (const auto scene : mScenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::Initialize()
{
	for (const auto scene : mScenes)
	{
		scene->Initialize();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	mScenes.push_back(scene);
	return *scene;
}
