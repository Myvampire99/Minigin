#include "MiniginPCH.h"
#include "GameObject.h"

dae::GameObject::~GameObject()
{
	for (auto p : m_pComponents) {
		if (p) {
			delete p;
			p = nullptr;
		}
	}
	m_pComponents.clear();

	delete mTransform;
}

void dae::GameObject::MarkForDelete(bool marked) {
	MarkedForDelete = marked;
}
bool dae::GameObject::GetMarkForDelete() {
	return MarkedForDelete;
}


dae::GameObject::GameObject()
	:m_Enabled{true}
	, MarkedForDelete{false}
{
	mTransform = new dae::Transform();
}

void dae::GameObject::SetEnabled(bool enabled) {
	m_Enabled = enabled;
}

bool dae::GameObject::GetEnabled() {
	return m_Enabled;
}

void dae::GameObject::AddComponent(BaseComponent * cmp)
{

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

