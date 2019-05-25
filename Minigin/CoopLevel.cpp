#include "MiniginPCH.h"
#include "CoopLevel.h"


CoopLevel::CoopLevel()
	:Scene("CoopLevel")
{
}


CoopLevel::~CoopLevel()
{
	
}

void CoopLevel::SceneUpdate() {
	std::pair<bool, bool> VH = m_Player->GetComponent<BaseCharacterComponent>()->GetFlipVertnFlipHor();
	m_Player->GetComponent<dae::SpriteComponent>()->FlipSprite(VH.second || VH.first, false);

	m_Player->GetComponent<dae::SpriteComponent>()->SetPause(m_Player->GetComponent<BaseCharacterComponent>()->GetDirection() == BaseCharacterComponent::Direction::Idle);


	if (m_PlayerCharacter->IsDigging())
		m_Player->GetComponent<dae::SpriteComponent>()->SetCurrentSprite(1);
	else
		m_Player->GetComponent<dae::SpriteComponent>()->SetCurrentSprite(0);


}

void CoopLevel::LocalReset() {
	
	int widthGrid = 12;
	int HeightGrid = 12;
	float SizeBlockGrid = 30;


	for (int i{ }; i < (HeightGrid + 1)*(widthGrid + 1); ++i) {
		auto *lvlObj = new LevelObject("Resources/Textures/Ground.png");
		lvlObj->SetSize(SizeBlockGrid);
		m_GridLevel->ChangeBlock(lvlObj, i);
	}

	auto *Rock = new RockBlock("Resources/Textures/Rock.png", m_GridLevel, new CollisionBox({ 0.f ,0.f }, SizeBlockGrid, SizeBlockGrid));
	Rock->SetSize(SizeBlockGrid);
	levelGameObject->GetComponent<GridLevel>()->ChangeBlock(Rock, 20);
	levelGameObject->GetComponent<GridLevel>()->SetWalkable(20, false);

	for (int i{ (HeightGrid + 1)*widthGrid }; i < (HeightGrid + 1)*widthGrid + widthGrid + 1; ++i) {
		m_GridLevel->ChangeBlock(new BorderBlock(new CollisionBox({ 0,0 }, SizeBlockGrid, SizeBlockGrid)), i);
	}
	for (int i{  }; i < widthGrid + 1; ++i) {
		m_GridLevel->ChangeBlock(new BorderBlock(new CollisionBox({ 0,0 }, SizeBlockGrid, SizeBlockGrid)), i);
	}
	for (int i{ 0 }; i < HeightGrid*widthGrid; i += widthGrid + 1) {
		m_GridLevel->ChangeBlock(new BorderBlock(new CollisionBox({ 0,0 }, SizeBlockGrid, SizeBlockGrid)), i);
	}
	for (int i{ widthGrid }; i < (HeightGrid + 1)*widthGrid; i += widthGrid + 1) {
		m_GridLevel->ChangeBlock(new BorderBlock(new CollisionBox({ 0,0 }, SizeBlockGrid, SizeBlockGrid)), i);
	}

	m_GridLevel->ChangeBlock(new EmptyBlock, m_GridLevel->GetClosestIDViaPos({ 150.f, 150.f }));
	m_GridLevel->ChangeBlock(new EmptyBlock, m_GridLevel->GetClosestIDViaPos({ 150.f, 150.f }) + 1);
	m_GridLevel->ChangeBlock(new EmptyBlock, m_GridLevel->GetClosestIDViaPos({ 150.f, 150.f }) - 1);


	m_GridLevel->ChangeBlock(new EmptyBlock, m_GridLevel->GetClosestIDViaPos({ 250.f, 250.f }));
	m_GridLevel->ChangeBlock(new EmptyBlock, m_GridLevel->GetClosestIDViaPos({ 250.f, 250.f }) + 1);
	m_GridLevel->ChangeBlock(new EmptyBlock, m_GridLevel->GetClosestIDViaPos({ 250.f, 250.f }) - 1);

	m_GridLevel->ChangeBlock(new EmptyBlock, m_GridLevel->GetClosestIDViaPos({ 300.f, 300.f }));

	m_Player->GetComponent<DiggerCharacterComponent>()->SetLives(3);
	dae::Singleton<ServiceLocator>::GetInstance().GetHealthGO()->GetComponent<TextRendererComponent>()->SetText(std::to_string(3));


	m_Player->SetPosition(300.f, 300.f);
	m_Player2->SetPosition(300.f, 300.f);

	auto FcollisionComponent = new CollisionComponent();
	auto FcollisionBox = new CollisionBox({}, 26, 26);
	FcollisionBox->SetIsTrigger(true);
	FcollisionComponent->AddCollision(FcollisionBox);

	Fygar->SetPosition(150.f, 150.f);
	Fygar->SetEnabled(true);
	Fygar->RemoveComponent<CollisionComponent>();
	Fygar->AddComponent(FcollisionComponent);
	Fygar->RemoveComponent<GridComponent>();
	Fygar->AddComponent(new GridComponent(m_GridLevel, true));


	auto PcollisionComponent = new CollisionComponent();
	auto PcollisionBox = new CollisionBox({}, 26, 26);
	PcollisionBox->SetIsTrigger(true);
	PcollisionComponent->AddCollision(PcollisionBox);

	Pooka->SetPosition(250.f, 250.f);
	Pooka->SetEnabled(true);
	Pooka->RemoveComponent<CollisionComponent>();
	Pooka->AddComponent(PcollisionComponent);

	Pooka->RemoveComponent<GridComponent>();
	Pooka->AddComponent(new GridComponent(m_GridLevel, true));





}


void CoopLevel::SceneInitialize() {




	dae::Singleton<InputManager>::GetInstance().AssignButton(ControllerButton::Button_B, new ChangeToPlayerC(), 0);
	dae::Singleton<InputManager>::GetInstance().AssignButton(ControllerButton::Button_Y, new ChangeLevelCOOP(), 0);
	dae::Singleton<InputManager>::GetInstance().AssignButton(ControllerButton::Button_X, new ChangeLevelCLASSIC(), 0);


	int widthGrid = 12;
	int HeightGrid = 12;
	float SizeBlockGrid = 30;

	//Observer and subject
	m_ScoreDisplay = new ScoreDisplay;
	m_Subject = new Subject;

	m_Subject->AddObserver(m_ScoreDisplay);
	//






	//Grid
	m_GridLevel = new GridLevel(widthGrid + 1, HeightGrid + 1, SizeBlockGrid, { SizeBlockGrid,SizeBlockGrid });
	levelGameObject = std::make_shared<dae::GameObject>();
	levelGameObject->AddComponent(m_GridLevel);
	Add(levelGameObject);
	//

	//Grid Blocks
	auto *lvlObj = new LevelObject("Resources/Textures/Ground.png");
	lvlObj->SetSize(SizeBlockGrid);
	levelGameObject->GetComponent<GridLevel>()->FillLevel(lvlObj);
	delete lvlObj;

	auto *Rock = new RockBlock("Resources/Textures/Rock.png", m_GridLevel, new CollisionBox({ 0.f ,0.f }, SizeBlockGrid, SizeBlockGrid));
	Rock->SetSize(SizeBlockGrid);
	Rock->SetSubject(m_Subject);
	levelGameObject->GetComponent<GridLevel>()->ChangeBlock(Rock, 20);
	levelGameObject->GetComponent<GridLevel>()->SetWalkable(20, false);

	for (int i{ (HeightGrid + 1)*widthGrid }; i < (HeightGrid + 1)*widthGrid + widthGrid + 1; ++i) {
		m_GridLevel->ChangeBlock(new BorderBlock(new CollisionBox({ 0,0 }, SizeBlockGrid, SizeBlockGrid)), i);
	}
	for (int i{  }; i < widthGrid + 1; ++i) {
		m_GridLevel->ChangeBlock(new BorderBlock(new CollisionBox({ 0,0 }, SizeBlockGrid, SizeBlockGrid)), i);
	}
	for (int i{ 0 }; i < HeightGrid*widthGrid; i += widthGrid + 1) {
		m_GridLevel->ChangeBlock(new BorderBlock(new CollisionBox({ 0,0 }, SizeBlockGrid, SizeBlockGrid)), i);
	}
	for (int i{ widthGrid }; i < (HeightGrid + 1)*widthGrid; i += widthGrid + 1) {
		m_GridLevel->ChangeBlock(new BorderBlock(new CollisionBox({ 0,0 }, SizeBlockGrid, SizeBlockGrid)), i);
	}


	//

	//Collision
	auto collisionComponent = new CollisionComponent();
	auto collisionBox = new CollisionBox({}, 25, 25);
	collisionBox->SetIsTrigger(false);
	collisionComponent->AddCollision(collisionBox);
	//

	//Input
	m_Inputcomponent = new InputComponent(0);
	m_Inputcomponent->AssignButton(left, ControllerButton::Dpad_Left);
	m_Inputcomponent->AssignButton(right, ControllerButton::Dpad_Right);
	m_Inputcomponent->AssignButton(up, ControllerButton::Dpad_Up);
	m_Inputcomponent->AssignButton(down, ControllerButton::Dpad_Down);
	m_Inputcomponent->AssignButton(fire, ControllerButton::Button_A);



	//

	//Character Component
	m_PlayerCharacter = new DiggerCharacterComponent(m_GridLevel);
	m_PlayerCharacter->AssignButton(left, right, up, down);
	m_PlayerCharacter->SetWidth(25); 
	m_PlayerCharacter->SetResetPosition({ 300.f,300.f });
	//

	m_GridLevel->ChangeBlock(new EmptyBlock, m_GridLevel->GetClosestIDViaPos({ 300.f, 300.f }));

	//Player
	m_Player = std::make_shared<dae::GameObject>();

	m_Player->AddComponent(new dae::SpriteComponent(0, new dae::Sprite("Resources/Sprites/PlayerMove.png", 1, 2, 2, 3)));
	m_Player->AddComponent(m_Inputcomponent);
	m_Player->AddComponent(m_PlayerCharacter);
	m_Player->AddComponent(collisionComponent);
	m_Player->AddComponent(new GridComponent(m_GridLevel, true));//, { SizeBlockGrid / 2.f,SizeBlockGrid / 2.f }

	m_Player->GetTransform()->SetScale(2);
	m_Player->SetPosition(300.f, 300.f);

	dae::Singleton<ServiceLocator>::GetInstance().SetPlayerObject(m_Player);
	m_Player->GetComponent<DiggerCharacterComponent>()->SetSubject(m_Subject);
	Add(m_Player);
	//

	//Extra Sprite
	m_Player->GetComponent<dae::SpriteComponent>()->AddSprite(1, new dae::Sprite("Resources/Sprites/DiggingB.png", 1, 2, 2, 3));
	//







	//Score Health
	auto score = std::make_shared<dae::GameObject>();
	auto health = std::make_shared<dae::GameObject>();

	//font
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);


	score->AddComponent(new TextRendererComponent("0", font));
	health->AddComponent(new TextRendererComponent("3", font));

	score->SetPosition(450.f, 50.f);
	health->SetPosition(450.f, 80.f);

	Add(score);
	Add(health);

	dae::Singleton<ServiceLocator>::GetInstance().SetGOScore(score);
	dae::Singleton<ServiceLocator>::GetInstance().SetGOHealth(health);

	//







	//	//Collision
	auto collisionComponent2 = new CollisionComponent();
	auto collisionBox2 = new CollisionBox({}, 25, 25);
	collisionBox2->SetIsTrigger(false);
	collisionComponent2->AddCollision(collisionBox2);
	//

	//Input
	auto m_Inputcomponent2 = new InputComponent(1);
	m_Inputcomponent2->AssignButton(left, ControllerButton::Dpad_Left);
	m_Inputcomponent2->AssignButton(right, ControllerButton::Dpad_Right);
	m_Inputcomponent2->AssignButton(up, ControllerButton::Dpad_Up);
	m_Inputcomponent2->AssignButton(down, ControllerButton::Dpad_Down);
	m_Inputcomponent2->AssignButton(fire, ControllerButton::Button_A);


	//

	//Character Component
	auto m_PlayerCharacter2 = new DiggerCharacterComponent(m_GridLevel);
	m_PlayerCharacter2->AssignButton(left, right, up, down);
	m_PlayerCharacter2->SetWidth(25); 
	m_PlayerCharacter2->SetResetPosition({ 300.f,300.f });
	//

	//Player
	m_Player2 = std::make_shared<dae::GameObject>();

	m_Player2->AddComponent(new dae::SpriteComponent(0, new dae::Sprite("Resources/Sprites/PlayerMove.png", 1, 2, 2, 3)));
	m_Player2->AddComponent(m_Inputcomponent2);
	m_Player2->AddComponent(m_PlayerCharacter2);
	m_Player2->AddComponent(collisionComponent2);
	m_Player2->AddComponent(new GridComponent(m_GridLevel, true));//, { SizeBlockGrid / 2.f,SizeBlockGrid / 2.f }

	m_Player2->GetTransform()->SetScale(2);
	m_Player2->SetPosition(300.f, 300.f);

	dae::Singleton<ServiceLocator>::GetInstance().SetPlayerObject(m_Player2);
	m_Player2->GetComponent<DiggerCharacterComponent>()->SetSubject(m_Subject);
	Add(m_Player2);
	//

	//Extra Sprite
	m_Player2->GetComponent<dae::SpriteComponent>()->AddSprite(1, new dae::Sprite("Resources/Sprites/DiggingB.png", 1, 2, 2, 3));
	//












	//
	auto FInput = new InputComponent(2);
	FInput->AssignButton(left, ControllerButton::Dpad_Left);
	FInput->AssignButton(right, ControllerButton::Dpad_Right);
	FInput->AssignButton(up, ControllerButton::Dpad_Up);
	FInput->AssignButton(down, ControllerButton::Dpad_Down);
	FInput->AssignButton(fire, ControllerButton::Button_A);


	auto FygarCharacter = new FygarCharacterComponent(m_GridLevel);
	FygarCharacter->AssignButton(left, right, up, down);


	auto FcollisionComponent = new CollisionComponent();
	auto FcollisionBox = new CollisionBox({}, 26, 26);
	FcollisionBox->SetIsTrigger(true);
	FcollisionComponent->AddCollision(FcollisionBox);

	Fygar = std::make_shared<dae::GameObject>();
	Fygar->AddComponent(new dae::SpriteComponent(0, new dae::Sprite("Resources/Sprites/Fygar.png", 1, 2, 2, 3)));
	Fygar->AddComponent(new GridComponent(m_GridLevel, true));
	Fygar->AddComponent(FInput);
	Fygar->AddComponent(FygarCharacter);
	Fygar->AddComponent(FcollisionComponent);

	Fygar->GetTransform()->SetScale(2);
	Fygar->SetPosition(150.f, 150.f);

	Fygar->AddComponent(new AIComponent(FInput, FygarCharacter));
	///
	m_GridLevel->ChangeBlock(new EmptyBlock, m_GridLevel->GetClosestIDViaPos({ 150.f, 150.f }));
	m_GridLevel->ChangeBlock(new EmptyBlock, m_GridLevel->GetClosestIDViaPos({ 150.f, 150.f }) + 1);
	m_GridLevel->ChangeBlock(new EmptyBlock, m_GridLevel->GetClosestIDViaPos({ 150.f, 150.f }) - 1);
	///
	Fygar->GetComponent<FygarCharacterComponent>()->SetSubject(m_Subject);
	Fygar->GetComponent<AIComponent>()->GetState()->player = 2;
	Add(Fygar);

	dae::Singleton<ServiceLocator>::GetInstance().SetPlayerObject(Fygar);
	//




	//
	auto PInput = new InputComponent(3);
	PInput->AssignButton(left, ControllerButton::Dpad_Left);
	PInput->AssignButton(right, ControllerButton::Dpad_Right);
	PInput->AssignButton(up, ControllerButton::Dpad_Up);
	PInput->AssignButton(down, ControllerButton::Dpad_Down);
	PInput->AssignButton(fire, ControllerButton::Button_A);

	auto pookaCharacter = new PookaCharacterComponent(m_GridLevel);
	pookaCharacter->AssignButton(left, right, up, down);

	auto PcollisionComponent = new CollisionComponent();
	auto PcollisionBox = new CollisionBox({}, 26, 26);
	PcollisionBox->SetIsTrigger(true);
	PcollisionComponent->AddCollision(PcollisionBox);

	Pooka = std::make_shared<dae::GameObject>();
	Pooka->AddComponent(new dae::SpriteComponent(0, new dae::Sprite("Resources/Sprites/Pooka.png", 1, 2, 2, 3)));
	Pooka->AddComponent(new GridComponent(m_GridLevel, true));
	Pooka->AddComponent(PInput);
	Pooka->AddComponent(pookaCharacter);
	Pooka->AddComponent(PcollisionComponent);

	Pooka->GetTransform()->SetScale(2);
	Pooka->SetPosition(250.f, 250.f);

	Pooka->AddComponent(new AIComponent(PInput, pookaCharacter));
	Pooka->GetComponent<AIComponent>()->GetState()->player = 3;
	///
	m_GridLevel->ChangeBlock(new EmptyBlock, m_GridLevel->GetClosestIDViaPos({ 250.f, 250.f }));
	m_GridLevel->ChangeBlock(new EmptyBlock, m_GridLevel->GetClosestIDViaPos({ 250.f, 250.f }) + 1);
	m_GridLevel->ChangeBlock(new EmptyBlock, m_GridLevel->GetClosestIDViaPos({ 250.f, 250.f }) - 1);
	///
	Pooka->GetComponent<PookaCharacterComponent>()->SetSubject(m_Subject);
	Add(Pooka);

	dae::Singleton<ServiceLocator>::GetInstance().SetPlayerObject(Pooka);
	//


}