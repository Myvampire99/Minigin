#include "MiniginPCH.h"
#include "Scene.h"

#include "ThreadingGameObject.h"

dae::Scene::Scene(const std::string& name) : mName(name), m_IsActive(false) {
	m_ThreadManager = new ThreadingGameObject();

}

dae::Scene::~Scene() {
	delete m_ThreadManager;
	for(int i{};i<(int)mObjects.size();++i)
	{
		mObjects[i]->ClearAllReferenceOfComponents();
	}
	mObjects.clear();

	for (int i{}; i < (int)mObjectsToDelete.size(); ++i)
	{
		mObjectsToDelete[i]->ClearAllReferenceOfComponents();
	}
	mObjectsToDelete.clear();
	
}

void dae::Scene::AddObjectForDeletion(std::shared_ptr<dae::GameObject> object)
{
	mObjectsToDelete.push_back(object);
}

void dae::Scene::AddThreadGameObject(std::shared_ptr<dae::GameObject> object) {
	mObjectsToDelete.push_back(object);
	m_ThreadManager->CreateThread(object.get());
}

void dae::Scene::StopThreading()
{
	m_ThreadManager->DeleteThreads();
}

void dae::Scene::Add(const std::shared_ptr<dae::GameObject>& object)
{
	mObjects.push_back(object);
}

void dae::Scene::Update(const float elapsedTime)
{

	m_ElapsedTime = elapsedTime;


	SceneUpdate();


	//Update Objects
	m_ThreadManager->SetElapsedTime(elapsedTime);

	for(auto gameObject : mObjects)
	{
		if (gameObject->GetMarkForDelete() && gameObject->GetEnabled()) {
			gameObject->SetEnabled(false);
			if (dynamic_cast<CollisionComponent*>(gameObject->GetComponent<CollisionComponent>())) {
				gameObject->GetComponent<CollisionComponent>()->Remove(gameObject->GetComponent<CollisionComponent>()->GetCollisions()[0]);
			}
			gameObject->MarkForDelete(false);
			
		}

		if(gameObject != nullptr)
			if(gameObject->GetEnabled())
				gameObject->Update(elapsedTime);
	}

	m_ThreadManager->WaitAndLock();
	//

}

void dae::Scene::Render() const
{
	
	for (const auto gameObject : mObjects)
	{
		if (gameObject->GetEnabled())
		gameObject->Render();
	}
	m_ThreadManager->Unlock();
	m_ThreadManager->WaitAndLock();
}

void dae::Scene::Initialize()
{

	SceneInitialize();


	m_ThreadManager->StartThreads();
	for (const auto gameObject : mObjects)
	{
		gameObject->Initialize();
	}

}
void  dae::Scene::Reset() {

	m_ThreadManager->DeleteThreads();
	mObjects.clear();
	LocalReset();
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