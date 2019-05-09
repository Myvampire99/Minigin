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

	enum Direction
	{
		left,right,up,down
	};


	go = std::make_shared<dae::GameObject>();
	//go->SetTexture("background.jpg");
	go->SetPosition(20, 20);
	//go->AddComponent(new dae::SpriteComponent(0,new dae::Sprite{"Resources/Sprites/character.png",2,8,16,1}));

	auto inputcomponent = new InputComponent;
	inputcomponent->AssignButton(left,ControllerButton::Button_X);
	inputcomponent->AssignButton(right, ControllerButton::Button_B);
	inputcomponent->AssignButton(up, ControllerButton::Button_Y);
	inputcomponent->AssignButton(down, ControllerButton::Button_A);
	go->AddComponent(inputcomponent);

	auto levelcomp = new GridLevel(8, 8, 50, { 50,50 });
	auto level = std::make_shared<dae::GameObject>();
	auto controller = new DiggerCharacterComponent(levelcomp);//new BaseCharacterComponent;
	controller->AssignButton(left, right, up, down);
	go->AddComponent(controller);

	//Add(go);


	txt = std::make_shared<dae::GameObject>();
	txt->SetPosition(20, 20);
	txt->AddComponent(new FPSComponent);
	txt->AddComponent(new TextRendererComponent("0", font));
	Add(txt);

	
	level->AddComponent(levelcomp);

	LevelObject *test = new LevelObject("Resources/Textures/block.jpg");
	test->SetSize(50.f);
	level->GetComponent<GridLevel>()->FillLevel(test);

	LevelObject *test2 = new RockBlock("Resources/Textures/rock.jpg", levelcomp);
	test2->SetSize(50.f);
	level->GetComponent<GridLevel>()->ChangeBlock(test2,17);

	Add(level);

	
	auto snap = std::make_shared<dae::GameObject>();
	dae::Singleton<ServiceLocator>::GetInstance().SetPlayerObject(snap);

	snap->SetTexture("Resources/Textures/point.jpg");
	snap->SetPosition(380, 120);
	snap->AddComponent(new GridComponent(level->GetComponent<GridLevel>()));
	snap->AddComponent(inputcomponent);
	snap->AddComponent(controller);
	Add(snap);
	


}
