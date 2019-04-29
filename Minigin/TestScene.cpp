#include "MiniginPCH.h"
#include "TestScene.h"
#include "Sprite.h"


TestScene::TestScene()//dont forget to give string for real scenes
	:Scene("TestScene")
{
}


void TestScene::SceneUpdate() 
{
	std::string temp = std::to_string(txt->GetComponent<FPSComponent>()->GetFps());
	txt->GetComponent<TextRendererComponent>()->SetText(temp);

}

void TestScene::SceneInitialize()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	go = std::make_shared<dae::GameObject>();
	//go->SetTexture("background.jpg");
	go->SetPosition(20, 20);
	go->AddComponent(new dae::SpriteComponent(0,new dae::Sprite{"Resources/Sprites/character.png",2,8,16,1}));
	Add(go);

	txt = std::make_shared<dae::GameObject>();
	txt->SetPosition(20, 20);
	txt->AddComponent(new FPSComponent);
	txt->AddComponent(new TextRendererComponent("0", font));
	Add(txt);

	

}
