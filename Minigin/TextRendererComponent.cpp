#include "MiniginPCH.h"
#include "TextObject.h"
#include "Font.h"
#include "TextRendererComponent.h"


TextRendererComponent::TextRendererComponent(const std::string& text, std::shared_ptr<dae::Font> font)
	:m_Text{ text }
	, m_Font{ font }
	, m_TextObject{nullptr}
{}

void TextRendererComponent::SetText(std::string txt)
{
	m_Text = txt;
	m_TextObject->SetText(m_Text);
}

void TextRendererComponent::Update(const float elapsedTime)
{

	if (m_TextObject != nullptr) {
		m_TextObject->Update(elapsedTime);
	}


	
	
}

void TextRendererComponent::Draw()
{//maybe in the render() ??
	m_TextObject->Render();
}

void TextRendererComponent::Initialize()
{
	m_TextObject = new dae::TextObject(m_Text, m_Font);
	m_TextObject->SetPosition(20, 20);//own position <-
}

