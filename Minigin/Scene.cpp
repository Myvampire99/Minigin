#include "MiniginPCH.h"
#include "Scene.h"


dae::Scene::Scene(const std::string& name) : mName(name), m_IsActive(false) {


}

dae::Scene::~Scene() {

}

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
			}
			gameObject->MarkForDelete(false);
			
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

}
void  dae::Scene::Reset() {
	//mObjects.clear();
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