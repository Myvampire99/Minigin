#include "MiniginPCH.h"
#include "Scene.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) : mName(name), m_IsActive(false) {


}

dae::Scene::~Scene() = default;

void dae::Scene::Add(const std::shared_ptr<dae::GameObject>& object)
{
	mObjects.push_back(object);
}

void dae::Scene::Update(const float elapsedTime)
{

	m_ElapsedTime = elapsedTime;


	SceneUpdate();

	


	for(auto gameObject : mObjects)
	{
		if (gameObject->GetMarkForDelete() && gameObject->GetEnabled()) {
			gameObject->SetEnabled(false);
			if (dynamic_cast<CollisionComponent*>(gameObject->GetComponent<CollisionComponent>())) {
				gameObject->GetComponent<CollisionComponent>()->Remove(gameObject->GetComponent<CollisionComponent>()->GetCollisions()[0]);
				//TODO: remove player from service
			}
			
		}

		if(gameObject != nullptr)
			if(gameObject->GetEnabled())
				gameObject->Update(elapsedTime);
	}

}

void dae::Scene::Render() const
{
	for (const auto gameObject : mObjects)
	{
		if (gameObject->GetEnabled())
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

	SetCopyIni();
}

std::shared_ptr<dae::Scene> dae::Scene::GetCoppyIni() {
	return m_CopyIni;
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