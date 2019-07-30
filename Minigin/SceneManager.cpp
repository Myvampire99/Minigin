#include "MiniginPCH.h"
#include "SceneManager.h"

void dae::SceneManager::Update(const float elapsedTime)
{
	for(auto scene : mScenes)
	{
		if(scene.first->IsActive())
			scene.first->Update(elapsedTime);
	}

	if (ActiveDelete) {
		for (const auto scene : mScenes)
		{
			if (scene.first->IsActive()) {

				scene.first->Reset();
				ActiveDelete = false;
				break;
			}

		}
	}
}

void dae::SceneManager::Render()
{
	for (const auto scene : mScenes)
	{
		if (scene.first->IsActive())
			scene.first->Render();
	}

	//Debug
	DD::GetInstance().Draw();
	DD::GetInstance().Clear();
	//

}

int dae::SceneManager::GetActiveSceneID() {
	for (const auto scene : mScenes)
	{
		if (scene.first->IsActive())
			return scene.first->ID;
	}
	return -1;
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
	count = {};
	//for (const auto scene : mScenes)
	//{
	//	if (scene.first->IsActive())
	//		scene.first->Initialize();
	//}
}

void dae::SceneManager::ResetActiveScene() {

	ActiveDelete = true;

}

void dae::SceneManager::AddScene(Scene *pScene)
{
	const auto scene = std::shared_ptr<Scene>(pScene);
	mScenes.insert(std::pair<std::shared_ptr<Scene>,bool>(scene, pScene->IsActive()));
	scene->ID = count;
	count++;
}

void dae::SceneManager::AddSubject(Subject * sub) {
	m_Subject = sub;
}

void dae::SceneManager::SetSceneActive(std::string name,bool active)
{
	//bool firstTime = false;

	for(auto &scene : mScenes)
	{
		if(scene.first->GetName() == name)
		{
			

				
			if (!active)
				m_Subject->Notify(Event::EVENT_SWITCH_SCENE_DEACTIVATE);



			scene.first->SetActive(active);
			if (scene.second == false ) {
				scene.first->Initialize();
				scene.second = true;
				//firstTime = true;
			}

			if (active) {
				scene.first->SwitchSceneIni();
			}
			else {
				scene.first->SwitchSceneDec();
			}

			if (active )//&& !firstTime
				m_Subject->Notify(Event::EVENT_SWITCH_SCENE_ACTIVATE);
		}
	}

}
