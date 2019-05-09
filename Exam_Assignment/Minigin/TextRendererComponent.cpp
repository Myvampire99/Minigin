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
}

void TextRendererComponent::Update(const float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	if (m_TextObject != nullptr) {
		m_TextObject->Update(elapsedTime);
	}
	m_TextObject->Render();//maybe in the render() ??
	m_TextObject->SetPosition(50, 10);//not here
}

void TextRendererComponent::Draw()
{
}

void TextRendererComponent::Initialize()
{
	m_TextObject = new dae::TextObject(m_Text, m_Font);
}

