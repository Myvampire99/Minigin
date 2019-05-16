#include "MiniginPCH.h"
#include "SceneManager.h"

void dae::SceneManager::Update(const float elapsedTime)
{
	for(auto scene : mScenes)
	{
		if(scene.first->IsActive())
			scene.first->Update(elapsedTime);
	}
}

void dae::SceneManager::Render()
{
	for (const auto scene : mScenes)
	{
		if (scene.first->IsActive())
			scene.first->Render();
	}
}

void dae::SceneManager::Initialize()
{
	for (const auto scene : mScenes)
	{
		//if (scene.first->IsActive())
			scene.first->Initialize();
	}
}

void dae::SceneManager::AddScene(Scene *pScene)
{
	const auto scene = std::shared_ptr<Scene>(pScene);
	mScenes.insert(std::pair<std::shared_ptr<Scene>,bool>(scene, pScene->IsActive()));
}

void dae::SceneManager::SetSceneActive(std::string name,bool active)
{
	for(auto scene : mScenes)
	{
		if(scene.first->GetName() == name)
		{
			scene.second = active;
			scene.first->SetActive(active);
		}
	}

}
