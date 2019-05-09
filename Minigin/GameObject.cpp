#include "MiniginPCH.h"
#include "GameObject.h"

dae::GameObject::~GameObject() = default;

dae::GameObject::GameObject() {
	mTransform = new dae::Transform();
}

void dae::GameObject::AddComponent(BaseComponent * cmp)
{
	//TODO:
	//logger for all errors!
	//Check if not attached to something else already
	if (cmp) {
		cmp->m_GameObject = this;
		m_pComponents.push_back(cmp);
	}
}

void dae::GameObject::Update(const float elapsedTime){

	for (auto comp : m_pComponents) {
		comp->Update(elapsedTime);
	}

}

void dae::GameObject::Render() const
{
	const auto pos = mTransform->GetPosition();

	for (auto comp : m_pComponents) {
		comp->Draw();
	}

	if(mTexture != nullptr)
		Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y, mTransform->GetAngle());
}

void dae::GameObject::Initialize()
{

	for (auto comp : m_pComponents) {
		comp->Initialize();
	}
}

dae::Transform* dae::GameObject::GetTransform() {
	return mTransform;
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	//TODO: NEED TO CHANGE THIS!!!
	mTexture = nullptr;
	if(filename != "")
		mTexture = ResourceManager::GetInstance().LoadTexture(filename);

}

void dae::GameObject::SetPosition(float x, float y)
{
	mTransform->SetPosition(x, y, 0.0f);
}

dae::Vector2 dae::GameObject::GetPos() const
{

	return { mTransform->GetPosition().x,mTransform->GetPosition().y };
	
}

