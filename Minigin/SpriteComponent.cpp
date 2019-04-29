#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include <algorithm>

dae::SpriteComponent::SpriteComponent(int ID, dae::Sprite *sprite)
	: m_CurrentState{ ID }
{
	m_Sprites.insert({ ID, sprite });
}


dae::SpriteComponent::~SpriteComponent()
{
}//TODO: delete things

void dae::SpriteComponent::Update(const float elapsedTime)
{
	m_Sprites[m_CurrentState]->Update(elapsedTime);
}

void dae::SpriteComponent::Draw()
{
	m_Sprites[m_CurrentState]->Draw(m_GameObject->GetPos(),0);
}

void dae::SpriteComponent::Initialize()
{
	
}

void dae::SpriteComponent::AddSprite(int ID, dae::Sprite *sprite)
{
	//mabye check if same id or return something if bc map
	m_Sprites.insert({ ID, sprite });
}

void dae::SpriteComponent::AddSprite(int ID, const std::string& path, int nrCols, int nrRows, int maxActs, float framePerSec)
{
	//mabye check if same id or return something if bc map
	m_Sprites.insert({ ID, new Sprite{path,nrCols,nrRows,maxActs,framePerSec} });
}

void dae::SpriteComponent::SetCurrentSprite(int ID)
{
	m_CurrentState = ID;
}
