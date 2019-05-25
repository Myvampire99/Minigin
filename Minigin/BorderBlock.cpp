#include "MiniginPCH.h"
#include "BorderBlock.h"


BorderBlock::BorderBlock(CollisionBox* coll)
	:LevelObject("Resources/Textures/point.jpg")
	, m_Coll{ coll }
{
	dae::Singleton<CollisionManager>::GetInstance().AddCollision( m_Coll );
}

BorderBlock::~BorderBlock()
{
	dae::Singleton<CollisionManager>::GetInstance().Remove(m_Coll);
	
}

void BorderBlock::Update(float elapsedTime) {
	UNREFERENCED_PARAMETER(elapsedTime);
	m_Coll->SetPosition(this->GetPos());
}
void BorderBlock::Initialize() {}
