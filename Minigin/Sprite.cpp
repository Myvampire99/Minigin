#include "MiniginPCH.h"
#include "Sprite.h"


dae::Sprite::Sprite(const std::string& path, int nrCols, int nrRows,int maxActs, float framePerSec)
	 
	:m_Cols{ nrCols }
	, m_Rows{ nrRows }
	, m_FrameSec{ framePerSec }
	, m_AccuSec{}
	, m_ActFrame{0}
	, m_CountActs{ maxActs }
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(path);
	m_Width = m_pTexture->GetWidth();
	m_Height = m_pTexture->GetHeight();
}


dae::Sprite::~Sprite()
{
}

void dae::Sprite::Update(float elapsedSec)
{
	m_AccuSec += elapsedSec;
	if((1.f/ m_FrameSec) < m_AccuSec)
	{
		m_AccuSec = 0;
		m_ActFrame++;
		if (m_ActFrame >= m_CountActs)
			m_ActFrame = 0;
	}
}

void dae::Sprite::Draw(const dae::Vector2& pos, float scale)
{

	UNREFERENCED_PARAMETER(scale);//TODO: make scale

	int currentRow, currentCollumn;
	currentCollumn = m_ActFrame / m_Rows;
	currentRow = m_ActFrame % m_Rows;

	float actWidth = m_Width/ m_Rows;
	float actHeight = m_Height / m_Cols;

	dae::Vector2 srcPos = { actWidth*currentRow, actHeight*currentCollumn };

	if (m_pTexture != nullptr)
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos, srcPos,{ actWidth,actHeight },{ actWidth ,actHeight });//Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x,pos.y);
}