#include "MiniginPCH.h"
#include "SnoBeeEgg.h"


SnoBeeEgg::SnoBeeEgg()
{

}

void SnoBeeEgg::Update(float elapsedTime) { UNREFERENCED_PARAMETER(elapsedTime); }
void SnoBeeEgg::Draw() {}
void SnoBeeEgg::Initialize() {

	dae::Sprite *sprite = new dae::Sprite{ "Resources/Textures/IceBlockEgg.png",1,1,1,0.f };
	dae::SpriteComponent* spriteComp = new dae::SpriteComponent{ 0,sprite };
	m_GameObject->RemoveComponent<dae::SpriteComponent>();
	m_GameObject->AddComponent(spriteComp);
}


SnoBeeEgg::~SnoBeeEgg()
{
	
}
