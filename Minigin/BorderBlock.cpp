#include "MiniginPCH.h"
#include "BorderBlock.h"


BorderBlock::BorderBlock(CollisionBox* coll)
	:LevelObject("Resources/Textures/point.jpg")//TODO: NOTHING AT ALL
	, m_Coll{ coll }
{
	dae::Singleton<CollisionManager>::GetInstance().AddCollision(new CollisionBox{ *m_Coll });
}

BorderBlock::~BorderBlock()
{
}

void BorderBlock::Update(float elapsedTime) {
	UNREFERENCED_PARAMETER(elapsedTime);
	m_Coll->SetPosition(this->GetPos());
}
void BorderBlock::Initialize() {}