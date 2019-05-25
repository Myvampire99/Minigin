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

std::shared_ptr<dae::Scene> dae::SceneManager::GetActiveScene() {
	for (const auto scene : mScenes)
	{
		if (scene.first->IsActive())
			return scene.first;
	}
	return nullptr;
}

void dae::SceneManager::Initialize()
{
	for (const auto scene : mScenes)
	{
		//if (scene.first->IsActive())
			scene.first->Initialize();
	}
}

void dae::SceneManager::ResetActiveScene() {
	for (const auto scene : mScenes)
	{
		if (scene.first->IsActive()) {
			auto copyIni = scene.first->GetCoppyIni();
			
			mScenes.erase(scene.first);
			scene.first.~shared_ptr();
			mScenes.insert(std::pair<std::shared_ptr<Scene>, bool>(copyIni, copyIni->IsActive()));
			//copyIni->Initialize();
			//copyIni->SetActive(true);
			break;
		}
			
	}
	Initialize();
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
			//for (auto scene : mScenes) {
			//	scene.second = false;
			//	scene.first->SetActive(false);
			//}
				
			scene.second = active;
			scene.first->SetActive(active);
		}
	}

}
