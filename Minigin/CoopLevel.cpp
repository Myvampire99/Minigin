#include "MiniginPCH.h"
#include "CoopLevel.h"


CoopLevel::CoopLevel(std::string name)
	:Scene(name)
	, m_IntHealth{ 3 }
{
	m_GridManager = new GridManager();
}

CoopLevel::~CoopLevel()
{
}

void CoopLevel::SwitchSceneIni() {

	dae::Singleton<ServiceLocator>::GetInstance().SetHealth(m_IntHealth);
	dae::Singleton<ServiceLocator>::GetInstance().SetPlayerObject(m_Player);
	dae::Singleton<ServiceLocator>::GetInstance().SetPlayerObject(m_Player2);
	
	for (auto snoBee : m_SnoBee) {
		if (!snoBee->GetMarkForDelete())
			dae::Singleton<ServiceLocator>::GetInstance().SetPlayerObject(snoBee);
	}

	dae::Singleton<ServiceLocator>::GetInstance().SetSnoBeeRemaining(m_IntSnoBeeRemaining);

}

void CoopLevel::SwitchSceneDec() {

	dae::Singleton<ServiceLocator>::GetInstance().RemoveAllPlayerObjects();

	m_IntHealth = dae::Singleton<ServiceLocator>::GetInstance().GetHealth();
	m_IntSnoBeeRemaining = dae::Singleton<ServiceLocator>::GetInstance().GetSnoBeeRemaining();

}

void CoopLevel::SceneInitialize() {

	m_Subject = new Subject();
	dae::Singleton<ServiceLocator>::GetInstance().SetHealth(m_IntHealth);

	m_GridManager->CreateRectGrid(this, number, number, (float)margin);

	MazeGenerator mazegen;
	auto vecTag = mazegen.CreateMaze(number, number);//-2

	for (int i{}; i < (int)vecTag.size(); ++i) {

		if (vecTag[i] == 2)
			CreateAnIceBlock(i);
	}

	CreateWall(0, number, 1);
	CreateWall(number*number - number, number*number, 1);
	CreateWall(0, number*number, number);
	CreateWall(number - 1, number*number, number);

	CreatePlayer(m_Player, 0, { margin *2.f,margin *2.f});
	m_Player->GetComponent<PengoCharacterComponent>()->AddSubject(m_Subject);
	CreatePlayer(m_Player2,1, { margin *3.f,margin *3.f });
	m_Player2->GetComponent<PengoCharacterComponent>()->AddSubject(m_Subject);

	CreateSnoBee({ (float)margin,(float)margin *(number - 2) }, 2);
	CreateSnoBee({ (float)margin*(number - 2),(float)margin*(number - 2) }, 3);
	//CreateSnoBee({ (float)margin*(number - 2),(float)margin }, 3);

	//SCORE
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	TextRendererComponent* text = new TextRendererComponent("Score: ", font);
	m_Score = std::make_shared<dae::GameObject>();
	m_Score->AddComponent(text);
	m_Score->SetPosition(400.f, 300.f);
	Add(m_Score);

	//HEALTH
	TextRendererComponent* text2 = new TextRendererComponent("Health: ", font);
	m_Health = std::make_shared<dae::GameObject>();
	m_Health->AddComponent(text2);
	m_Health->SetPosition(400.f, 400.f);
	Add(m_Health);


	CreateAnIceBlockEgg(rand() % 6 + 25);
	CreateAnIceBlockEgg(rand() % 6 + 49);
	CreateAnIceBlockEgg(rand() % 3 + 63);
}

void CoopLevel::CreateWall(int start, int max, int inc) {
	for (int i{ start }; i < max; i += inc) {
		CollisionComponent* CComponent = new CollisionComponent();
		CollisionObject* BBoxCollision = new CollisionBox({ 200.f, 200.f }, (float)margin - 1, (float)margin - 1, false);
		BBoxCollision->SetIsTrigger(false);

		m_GridManager->AddComponents(CComponent, i);//TODO: Order based
		CComponent->AddCollision(BBoxCollision);

		dae::Sprite *SSprite = new dae::Sprite{ "Resources/Textures/Wall.png",1,1,1,0.f };
		dae::SpriteComponent* SpriteComp = new dae::SpriteComponent{ 1,SSprite };
		m_GridManager->AddComponents(SpriteComp, i);

		m_GridManager->GetNode(i)->tag = 2;
		m_GridManager->GetNode(i)->object->GetTransform()->SetScale(2);

	}
}

void CoopLevel::CreatePlayer(std::shared_ptr<dae::GameObject> &player,int i, dae::Vector2 pos) {

	player = std::make_shared<dae::GameObject>();
	//Collision
	auto collisionComponent = new CollisionComponent();
	auto collisionBox = new CollisionBox({ pos }, 20, 20, 10.f);
	collisionBox->SetIsTrigger(false);
	collisionBox->SetMargin({ 6.f,6.f });

	player->AddComponent(collisionComponent);//TODO: Order based
	collisionComponent->AddCollision(collisionBox);
	//

	//Input
	auto m_Inputcomponent = new InputComponent(i);
	m_Inputcomponent->AssignButton(0, ControllerButton::Dpad_Left);
	m_Inputcomponent->AssignButton(1, ControllerButton::Dpad_Right);
	m_Inputcomponent->AssignButton(2, ControllerButton::Dpad_Up);
	m_Inputcomponent->AssignButton(3, ControllerButton::Dpad_Down);
	m_Inputcomponent->AssignButton(4, ControllerButton::Button_A);
	//

	//Character Component
	auto m_PlayerCharacter = new PengoCharacterComponent(m_GridManager);
	m_PlayerCharacter->AssignButton(0, 1, 2, 3);
	//

	//Player GameObject

	player->AddComponent(new dae::SpriteComponent(0, new dae::Sprite("Resources/Sprites/PlayerMove.png", 1, 2, 2, 3)));
	player->AddComponent(m_Inputcomponent);
	player->AddComponent(m_PlayerCharacter);
	player->GetTransform()->SetScale(2);
	player->SetPosition(pos);

	//
	m_GridManager->GetClosestNode({ pos })->object->MarkForDelete();
	m_GridManager->FreeBlock(m_GridManager->GetClosestNode({ pos }), std::make_shared<dae::GameObject>());
	//

	dae::Singleton<ServiceLocator>::GetInstance().SetPlayerObject(player);
	player->AddComponent(new GridComponent(m_GridManager));
	Add(player);
}

void CoopLevel::CreateSnoBee(dae::Vector2 pos, int p) {

	std::shared_ptr<dae::GameObject> oldSnoBee = nullptr;

	auto m_SnoBee1 = std::make_shared<dae::GameObject>();
	if ((int)m_SnoBee.size() < p-1)
		m_SnoBee.push_back(m_SnoBee1);
	else {
		oldSnoBee = m_SnoBee[p -2];
		m_SnoBee[p - 2] = m_SnoBee1;
	}

	//Collision
	auto collisionComponent = new CollisionComponent();
	auto collisionBox = new CollisionBox({pos}, 20, 20);
	collisionBox->SetIsTrigger(true);
	collisionBox->SetMargin({ 6.f,6.f });

	m_SnoBee1->AddComponent(collisionComponent);//TODO: Order based
	collisionComponent->AddCollision(collisionBox);
	//

	//Input
	auto input = new InputComponent(p);
	input->AssignButton(0, ControllerButton::Dpad_Left);
	input->AssignButton(1, ControllerButton::Dpad_Right);
	input->AssignButton(2, ControllerButton::Dpad_Up);
	input->AssignButton(3, ControllerButton::Dpad_Down);
	input->AssignButton(4, ControllerButton::Button_A);
	//

	//Character Component
	auto m_SnoBee1Character = new SnoBeeComponent(m_GridManager);
	m_SnoBee1Character->AssignButton(0, 1, 2, 3);
	//

	//Player GameObject

	m_SnoBee1->AddComponent(input);
	m_SnoBee1->AddComponent(m_SnoBee1Character);
	m_SnoBee1->GetTransform()->SetScale(2);
	m_SnoBee1->SetPosition(pos);

	//
	m_GridManager->GetClosestNode({ pos })->object->MarkForDelete();
	m_GridManager->FreeBlock(m_GridManager->GetClosestNode({ pos }), std::make_shared<dae::GameObject>());
	//

	if (oldSnoBee) {

		dae::Singleton<ServiceLocator>::GetInstance().ChangePlayerObject(p, m_SnoBee1);
		m_Subject->RemoveObserver(oldSnoBee->GetComponent<AIStateComponent>());
	}
	else {
		dae::Singleton<ServiceLocator>::GetInstance().SetPlayerObject(m_SnoBee1);
	}

	m_SnoBee1->AddComponent(new AIStateComponent(m_GridManager, p));
	m_SnoBee1->AddComponent(new GridComponent(m_GridManager));

	m_Subject->AddObserver(m_SnoBee1->GetComponent<AIStateComponent>());
	Add(m_SnoBee1);
}

void CoopLevel::CreateAnIceBlockEgg(int IDs) {

	CollisionComponent* tempComponent = new CollisionComponent();
	CollisionObject* tempBoxCollision = new CollisionBox({ 200.f, 200.f }, (float)margin - 1, (float)margin - 1, false);
	tempBoxCollision->SetIsTrigger(true);


	m_GridManager->AddComponents(tempComponent, IDs);//TODO: Order based
	tempComponent->AddCollision(tempBoxCollision);

	dae::Sprite *sprite = new dae::Sprite{ "Resources/Textures/IceBlock.png",1,1,1,0.f };
	dae::SpriteComponent* spriteComp = new dae::SpriteComponent{ 0,sprite };
	m_GridManager->AddComponents(spriteComp, IDs);
	m_GridManager->GetNode(IDs)->object->GetComponent<CollisionComponent>()->GetCollisions()[0]->SetIsTrigger(false);
	m_GridManager->GetNode(IDs)->tag = 1;
	m_GridManager->GetNode(IDs)->object->GetTransform()->SetScale(2);

	m_GridManager->AddComponents(new SnoBeeEgg(), IDs);

	m_SnoBeeEgg.push_back(m_GridManager->GetNode(IDs)->object);
	dae::Singleton<ServiceLocator>::GetInstance().SetSnoBeeRemaining(dae::Singleton<ServiceLocator>::GetInstance().GetSnoBeeRemaining() - 1);
}

void CoopLevel::CreateAnIceBlock(int IDs) {


	CollisionComponent* tempComponent = new CollisionComponent();
	CollisionObject* tempBoxCollision = new CollisionBox({ 200.f, 200.f }, (float)margin - 1, (float)margin - 1, false);
	tempBoxCollision->SetIsTrigger(true);


	m_GridManager->AddComponents(tempComponent, IDs);//TODO: Order based
	tempComponent->AddCollision(tempBoxCollision);

	dae::Sprite *sprite = new dae::Sprite{ "Resources/Textures/IceBlock.png",1,1,1,0.f };
	dae::SpriteComponent* spriteComp = new dae::SpriteComponent{ 0,sprite };
	m_GridManager->AddComponents(spriteComp, IDs);
	m_GridManager->GetNode(IDs)->object->GetComponent<CollisionComponent>()->GetCollisions()[0]->SetIsTrigger(false);
	m_GridManager->GetNode(IDs)->tag = 1;
	m_GridManager->GetNode(IDs)->object->GetTransform()->SetScale(2);

}

void CoopLevel::SceneUpdate() {

	//TODO: on its own update
	m_GridManager->Update(0.f);

	std::string score = "Score: ";
	score += std::to_string(dae::Singleton<ServiceLocator>::GetInstance().GetCurrentScore());
	m_Score->GetComponent<TextRendererComponent>()->SetText(score);

	std::string health = "Health: ";
	health += std::to_string(dae::Singleton<ServiceLocator>::GetInstance().GetHealth());
	m_Health->GetComponent<TextRendererComponent>()->SetText(health);

	for (int i{}; i < (int)m_SnoBee.size(); ++i) {
		if (m_SnoBee[i]->GetMarkForDelete()) {
			if (m_SnoBeeEgg.size() != 0) {
				CreateSnoBee(m_SnoBeeEgg.back()->GetPos(), i + 2);
				m_SnoBeeEgg.pop_back();
				m_SnoBee[i]->Initialize();
			}
		}
	}

	bool found = false;
	for (auto egg : m_SnoBeeEgg) {
		if (egg->GetMarkForDelete()) {

			dae::Singleton<ServiceLocator>::GetInstance().SetSnoBeeRemaining(dae::Singleton<ServiceLocator>::GetInstance().GetSnoBeeRemaining() - 1);
			dae::Singleton<ServiceLocator>::GetInstance().SetCurrentScore(dae::Singleton<ServiceLocator>::GetInstance().GetCurrentScore() + 400);
			found = true;

		}
	}

	if (found) {

		auto temp = m_SnoBeeEgg;
		m_SnoBeeEgg.clear();
		for (auto egg : temp) {
			if (!egg->GetMarkForDelete()) {
				m_SnoBeeEgg.push_back(egg);
			}
		}
	}
}

void CoopLevel::LocalReset() {

	delete m_GridManager;
	m_GridManager = new GridManager();
	m_Player = nullptr;
	m_Player2 = nullptr;
	m_SnoBee.clear();
	m_SnoBeeEgg.clear();

	m_Score = nullptr;
	m_Health = nullptr;

	m_IntHealth = 3;
	m_IntSnoBeeRemaining = 1;
	delete m_Subject;

	dae::Singleton<ServiceLocator>::GetInstance().SetCurrentScore(0);
}