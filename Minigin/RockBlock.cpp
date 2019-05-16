#include "MiniginPCH.h"
#include "RockBlock.h"


RockBlock::RockBlock(std::string path, GridLevel* m_Level)
	:LevelObject(path)
	, m_Level{ m_Level }
{
}


RockBlock::~RockBlock()
{
}

void RockBlock::Update(float elapsedTime) {

	if ((m_Level->GetID(this) + m_Level->GetWidth()) <= m_Level->GetHeight()*m_Level->GetWidth())
	{
		if (dynamic_cast<EmptyBlock*>(m_Level->GetObjectWithID(m_Level->GetID(this) + m_Level->GetWidth()))) {
			m_Level->ChangeBlock(this, m_Level->GetID(this) + m_Level->GetWidth());
			m_Level->ChangeBlock(new EmptyBlock(), m_Level->GetID(this));
		}
	}
	UNREFERENCED_PARAMETER(elapsedTime);

}


void RockBlock::Initialize() {


}