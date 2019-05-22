#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include <algorithm>

dae::SpriteComponent::SpriteComponent(int ID, dae::Sprite *sprite)
	: m_CurrentState{ ID }
	, m_FlipSpriteVert{ false }
	, m_FlipSpriteHor{ false }
	, m_Pause{false}
{
	m_Sprites.insert({ ID, sprite });
}

void dae::SpriteComponent::SetPause(bool pause) {
	m_Pause = pause;
}

dae::SpriteComponent::~SpriteComponent()
{
	for (auto sprite : m_Sprites) {
		delete sprite.second;
		sprite.second = nullptr;
	}
	m_Sprites.clear();
}

void dae::SpriteComponent::Update(const float elapsedTime)
{
	if(!m_Pause)
		m_Sprites[m_CurrentState]->Update(elapsedTime);
	else
		m_Sprites[m_CurrentState]->Update(0);
}

void dae::SpriteComponent::Draw()
{
	dae::Vector2 center{ 0.f,0.f};
	center.x += m_Sprites[m_CurrentState]->GetWidth() / 2.f;
	center.y += m_Sprites[m_CurrentState]->GetHeight() / 2.f;

	float scale{};
	scale = m_GameObject->GetTransform()->GetScale();
	m_Sprites[m_CurrentState]->Draw(m_GameObject->GetPos(),scale, m_FlipSpriteVert, m_FlipSpriteHor,m_GameObject->GetTransform()->GetAngle(),center);
}

void dae::SpriteComponent::Initialize()
{
	
}

void dae::SpriteComponent::AddSprite(int ID, dae::Sprite *sprite)
{
	m_Sprites.insert({ ID, sprite });
}

void dae::SpriteComponent::AddSprite(int ID, const std::string& path, int nrCols, int nrRows, int maxActs, float framePerSec)
{
	m_Sprites.insert({ ID, new Sprite{path,nrCols,nrRows,maxActs,framePerSec} });
}

void dae::SpriteComponent::SetCurrentSprite(int ID)
{
	m_CurrentState = ID;
}

void dae::SpriteComponent::FlipSprite(bool flipSpriteV, bool flipSpriteH) {
	m_FlipSpriteHor = flipSpriteH;
	m_FlipSpriteVert = flipSpriteV;
}