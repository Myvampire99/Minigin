#pragma once
#include "BaseComponent.h"
#include "TextObject.h"

class TextRendererComponent : public BaseComponent
{
public:
	TextRendererComponent(const std::string& text, std::shared_ptr<dae::Font> font);
	~TextRendererComponent();

	void SetText(std::string txt);
protected:
	virtual void Update(const float elapsedTime) override;
	virtual void Draw() override;
	virtual void Initialize() override;
private:
	dae::TextObject* m_TextObject;

	std::string m_Text;
	std::shared_ptr<dae::Font> m_Font;
};

