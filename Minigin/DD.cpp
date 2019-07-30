#include "MiniginPCH.h"
#include "DD.h"


DD::DD()
{
}


DD::~DD()
{
}

void DD::DrawQuad(const dae::Vector2 &pos1, const dae::Vector2 &WH, int color) {
	m_Quads.push_back(pos1);
	m_Quads.push_back(WH);
	m_quadColor.push_back(color);
	m_quadColor.push_back(color);
}

void DD::DrawLine(const dae::Vector2 &pos1, const dae::Vector2 &pos2){
	m_Lines.push_back(pos1);
	m_Lines.push_back(pos2);
}

void DD::Draw() const {

	for (int i{}; i < (int)m_Quads.size()  ; i += 2) {
		dae::Renderer::GetInstance().DrawQuad(m_Quads[i], m_Quads[i + 1], m_quadColor[i]);
	}
	
	for (int i{}; i < (int)m_Lines.size(); i += 2) {
		dae::Renderer::GetInstance().DrawLine(m_Lines[i], m_Lines[i + 1]);
	}

}

void DD::Clear() {
	m_Lines.clear();
	m_Quads.clear();
}