#include "MiniginPCH.h"
#include "DebugScene.h"


DebugScene::DebugScene(std::string name)
	:Scene(name)
	, m_IntHealth{3}
{
	m_GridManager = new GridManager();
}


DebugScene::~DebugScene()
{
}


void DebugScene::SwitchSceneIni() {

	dae::Singleton<ServiceLocator>::GetInstance().SetHealth(m_IntHealth);
	dae::Singleton<ServiceLocator>::GetInstance().SetPlayerObject(m_Player);

	for (auto snoBee : m_SnoBee) {
		if (!snoBee->GetMarkForDelete())
			dae::Singleton<ServiceLocator>::GetInstance().SetPlayerObject(snoBee);
	}
	
	dae::Singleton<ServiceLocator>::GetInstance().SetSnoBeeRemaining(m_IntSnoBeeRemaining);

}


void DebugScene::SwitchSceneDec() {

	//dae::Singleton<ServiceLocator>::GetInstance().RemovePlayerObject(m_Player);
	dae::Singleton<ServiceLocator>::GetInstance().RemoveAllPlayerObjects();

	m_IntHealth = dae::Singleton<ServiceLocator>::GetInstance().GetHealth();
	m_IntSnoBeeRemaining = dae::Singleton<ServiceLocator>::GetInstance().GetSnoBeeRemaining();


}


void DebugScene::SceneInitialize() {

	dae::Singleton<ServiceLocator>::GetInstance().SetHealth(m_IntHealth);

	const float width = 1.f;
	const float height = 1.f;


	//m_GameObject_01 = std::make_shared<dae::GameObject>();

//	CollisionComponent* Coll1 = new CollisionComponent();
//	CollisionObject* CBox = new CollisionBox({ 0.f, 0.f }, width, height, false);
//	CBox->SetIsTrigger(true);



//	m_GameObject_01->AddComponent(Coll1);
//	Coll1->AddCollision(CBox);
//	Add(m_GameObject_01);



	//m_GameObject_02 = std::make_shared<dae::GameObject>();

	//CollisionComponent* Coll2 = new CollisionComponent();
	//CollisionObject* CBox2 = new CollisionBox({200.f, 200.f }, width, height, false);

	//Coll2->AddCollision(CBox2);
	//m_GameObject_02->AddComponent(Coll2);
	//m_GameObject_02->SetPosition(200.f, 200.f);
	//Add(m_GameObject_02);

	const int number = 12;
	const int margin = 32;
	m_GridManager->CreateRectGrid(this, number, number, margin);
	//for (int i{}; i < number*number; ++i) {

		CollisionComponent* tempComponent = new CollisionComponent();
		CollisionObject* tempBoxCollision = new CollisionBox({ 200.f, 200.f }, margin -1, margin - 1, false);
		tempBoxCollision->SetIsTrigger(true);


		m_GridManager->AddComponents(tempComponent, 25);
		tempComponent->AddCollision(tempBoxCollision);



		CollisionComponent* tempComponent2 = new CollisionComponent();
		CollisionObject* tempBoxCollision2 = new CollisionBox({ 200.f, 200.f }, margin - 1, margin - 1, false);
		tempBoxCollision2->SetIsTrigger(true);


		m_GridManager->AddComponents(tempComponent2, 20);
		tempComponent2->AddCollision(tempBoxCollision2);




	//}

		{
			dae::Sprite *sprite = new dae::Sprite{ "Resources/Textures/IceBlock.png",1,1,1,0.f };
			dae::SpriteComponent* spriteComp = new dae::SpriteComponent{ 0,sprite };
			m_GridManager->AddComponents(spriteComp, 25);
			m_GridManager->GetNode(25)->object->GetComponent<CollisionComponent>()->GetCollisions()[0]->SetIsTrigger(false);
			m_GridManager->GetNode(25)->tag = 1;
			m_GridManager->GetNode(25)->object->GetTransform()->SetScale(2);
		}
		{
			dae::Sprite *sprite = new dae::Sprite{ "Resources/Textures/IceBlock.png",1,1,1,0.f };
			dae::SpriteComponent* spriteComp = new dae::SpriteComponent{ 0,sprite };
			m_GridManager->AddComponents(spriteComp, 20);
			m_GridManager->GetNode(20)->object->GetComponent<CollisionComponent>()->GetCollisions()[0]->SetIsTrigger(false);
			m_GridManager->GetNode(20)->tag = 1;
			m_GridManager->GetNode(20)->object->GetTransform()->SetScale(2);
		}



		MazeGenerator mazegen;
		auto vecTag = mazegen.CreateMaze(number , number );//-2

		for (int i{}; i < (int)vecTag.size(); ++i) {

			if (vecTag[i] == 2)
				CreateAnIceBlock(i,margin);
		}









	for (int i{}; i < number; ++i) {
		CollisionComponent* CComponent = new CollisionComponent();
		CollisionObject* BBoxCollision = new CollisionBox({ 200.f, 200.f }, margin - 1, margin - 1, false);
		BBoxCollision->SetIsTrigger(false);

		m_GridManager->AddComponents(CComponent, i);
		CComponent->AddCollision(BBoxCollision);


		dae::Sprite *SSprite = new dae::Sprite{ "Resources/Textures/Wall.png",1,1,1,0.f };
		dae::SpriteComponent* SpriteComp = new dae::SpriteComponent{1,SSprite };
		m_GridManager->AddComponents(SpriteComp, i);


		m_GridManager->GetNode(i)->tag = 2;
		m_GridManager->GetNode(i)->object->GetTransform()->SetScale(2);

	}
	for (int i{ number*number - number }; i < number*number; ++i) {
		CollisionComponent* CComponent = new CollisionComponent();
		CollisionObject* BBoxCollision = new CollisionBox({ 200.f, 200.f }, margin - 1, margin - 1, false);
		BBoxCollision->SetIsTrigger(false);

		m_GridManager->AddComponents(CComponent, i);
		CComponent->AddCollision(BBoxCollision);


		dae::Sprite *SSprite = new dae::Sprite{ "Resources/Textures/Wall.png",1,1,1,0.f };
		dae::SpriteComponent* SpriteComp = new dae::SpriteComponent{ 1,SSprite };
		m_GridManager->AddComponents(SpriteComp, i);


		m_GridManager->GetNode(i)->tag = 2;
		m_GridManager->GetNode(i)->object->GetTransform()->SetScale(2);
	}
	for (int i{ 0 }; i < number*number; i+= number) {
		CollisionComponent* CComponent = new CollisionComponent();
		CollisionObject* BBoxCollision = new CollisionBox({ 200.f, 200.f }, margin - 1, margin - 1, false);
		BBoxCollision->SetIsTrigger(false);

		m_GridManager->AddComponents(CComponent, i);
		CComponent->AddCollision(BBoxCollision);


		dae::Sprite *SSprite = new dae::Sprite{ "Resources/Textures/Wall.png",1,1,1,0.f };
		dae::SpriteComponent* SpriteComp = new dae::SpriteComponent{ 1,SSprite };
		m_GridManager->AddComponents(SpriteComp, i);


		m_GridManager->GetNode(i)->tag = 2;
		m_GridManager->GetNode(i)->object->GetTransform()->SetScale(2);
	}
	for (int i{ number -1 }; i < number*number; i += number) {
		CollisionComponent* CComponent = new CollisionComponent();
		CollisionObject* BBoxCollision = new CollisionBox({ 200.f, 200.f }, margin - 1, margin - 1, false);
		BBoxCollision->SetIsTrigger(false);

		m_GridManager->AddComponents(CComponent, i);
		CComponent->AddCollision(BBoxCollision);


		dae::Sprite *SSprite = new dae::Sprite{ "Resources/Textures/Wall.png",1,1,1,0.f };
		dae::SpriteComponent* SpriteComp = new dae::SpriteComponent{ 1,SSprite };
		m_GridManager->AddComponents(SpriteComp, i);


		m_GridManager->GetNode(i)->tag = 2;
		m_GridManager->GetNode(i)->object->GetTransform()->SetScale(2);
	}



	//=== TEST
///	m_GridManager->GetNode(11)->object->AddComponent(new VelocityComponent(dae::Vector2{ 1.f,0.f }));
	//=== TEST

	{
		//PLAYER
		//
		//
		m_Player = std::make_shared<dae::GameObject>();
		//Collision
		auto collisionComponent = new CollisionComponent();
		auto collisionBox = new CollisionBox({}, 20, 20, 10.f);
		collisionBox->SetIsTrigger(false);
		collisionBox->SetMargin({ 6.f,6.f });

		m_Player->AddComponent(collisionComponent);
		collisionComponent->AddCollision(collisionBox);
		//

		//Input
		m_Inputcomponent = new InputComponent(0);
		m_Inputcomponent->AssignButton(0, ControllerButton::Dpad_Left);
		m_Inputcomponent->AssignButton(1, ControllerButton::Dpad_Right);
		m_Inputcomponent->AssignButton(2, ControllerButton::Dpad_Up);
		m_Inputcomponent->AssignButton(3, ControllerButton::Dpad_Down);
		m_Inputcomponent->AssignButton(4, ControllerButton::Button_A);
		//

		//Character Component
		m_PlayerCharacter = new PengoCharacterComponent(m_GridManager);
		m_PlayerCharacter->AssignButton(0, 1, 2, 3);
		//

		//Player GameObject

		m_Player->AddComponent(new dae::SpriteComponent(0, new dae::Sprite("Resources/Sprites/PlayerMove.png", 1, 2, 2, 3)));
		m_Player->AddComponent(m_Inputcomponent);
		m_Player->AddComponent(m_PlayerCharacter);
		///m_SnoBee1->AddComponent(new GridComponent(m_GridLevel, true));
		m_Player->GetTransform()->SetScale(2);
		m_Player->SetPosition(margin * 2, margin * 2);

		//
		m_GridManager->GetClosestNode({ margin * 2, margin * 2 })->object->MarkForDelete();
		m_GridManager->FreeBlock(m_GridManager->GetClosestNode({ margin * 2, margin * 2 }), std::make_shared<dae::GameObject>());
		//

		dae::Singleton<ServiceLocator>::GetInstance().SetPlayerObject(m_Player);
		//m_SnoBee1->GetComponent<DiggerCharacterComponent>()->SetSubject(m_Subject);



	//	m_Player->AddComponent(new AIStateComponent(m_GridManager, 0));
		m_Player->AddComponent(new GridComponent(m_GridManager));
		Add(m_Player);
		//
		//
		//
	}





	CreateSnoBee({ (float)margin,(float)margin *(number - 2) }, 1);
	CreateSnoBee({ (float)margin*(number - 2),(float)margin*(number - 2) }, 2);
	CreateSnoBee({ (float)margin*(number-2),(float)margin }, 3);


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

	
	CreateAnIceBlockEgg(30,margin);
	CreateAnIceBlockEgg(54, margin);
}

void DebugScene::CreateSnoBee(dae::Vector2 pos,int p) {

	std::shared_ptr<dae::GameObject> oldSnoBee = nullptr;

	auto m_SnoBee1 = std::make_shared<dae::GameObject>();
	if ((int)m_SnoBee.size() < p)
		m_SnoBee.push_back(m_SnoBee1);
	else {
		oldSnoBee = m_SnoBee[p-1];
		m_SnoBee[p-1] = m_SnoBee1;
	}
	
	//Collision
	auto collisionComponent = new CollisionComponent();
	auto collisionBox = new CollisionBox({}, 20, 20, 10.f);
	collisionBox->SetIsTrigger(true);
	collisionBox->SetMargin({ 6.f,6.f });

	m_SnoBee1->AddComponent(collisionComponent);
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
	///m_SnoBee1->AddComponent(new GridComponent(m_GridLevel, true));
	m_SnoBee1->GetTransform()->SetScale(2);
	m_SnoBee1->SetPosition(pos);

	//
	m_GridManager->GetClosestNode({ pos })->object->MarkForDelete();
	m_GridManager->FreeBlock(m_GridManager->GetClosestNode({ pos }), std::make_shared<dae::GameObject>());
	//

	if (oldSnoBee) {
	
		dae::Singleton<ServiceLocator>::GetInstance().ChangePlayerObject(p, m_SnoBee1);
	}
	else {
		dae::Singleton<ServiceLocator>::GetInstance().SetPlayerObject(m_SnoBee1);
	}
	
	
	//m_Player->GetComponent<DiggerCharacterComponent>()->SetSubject(m_Subject);



	m_SnoBee1->AddComponent(new AIStateComponent(m_GridManager, p));
	m_SnoBee1->AddComponent(new GridComponent(m_GridManager));
	Add(m_SnoBee1);
	//
	//
	//
}


void DebugScene::CreateAnIceBlockEgg(int IDs, float margin) {

	CollisionComponent* tempComponent = new CollisionComponent();
	CollisionObject* tempBoxCollision = new CollisionBox({ 200.f, 200.f }, margin - 1, margin - 1, false);
	tempBoxCollision->SetIsTrigger(true);


	m_GridManager->AddComponents(tempComponent, IDs);
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


void DebugScene::CreateAnIceBlock(int IDs,float margin) {


	CollisionComponent* tempComponent = new CollisionComponent();
	CollisionObject* tempBoxCollision = new CollisionBox({ 200.f, 200.f }, margin - 1, margin - 1, false);
	tempBoxCollision->SetIsTrigger(true);


	m_GridManager->AddComponents(tempComponent, IDs);
	tempComponent->AddCollision(tempBoxCollision);

	dae::Sprite *sprite = new dae::Sprite{ "Resources/Textures/IceBlock.png",1,1,1,0.f };
	dae::SpriteComponent* spriteComp = new dae::SpriteComponent{ 0,sprite };
	m_GridManager->AddComponents(spriteComp, IDs);
	m_GridManager->GetNode(IDs)->object->GetComponent<CollisionComponent>()->GetCollisions()[0]->SetIsTrigger(false);
	m_GridManager->GetNode(IDs)->tag = 1;
	m_GridManager->GetNode(IDs)->object->GetTransform()->SetScale(2);

}




void DebugScene::SceneUpdate() {

	m_GridManager->Update(0.f);
	//
	///dae::Singleton<ServiceLocator>::GetInstance().GetCurrentScore()

	std::string score = "Score: ";
	score += std::to_string( dae::Singleton<ServiceLocator>::GetInstance().GetCurrentScore());
	m_Score->GetComponent<TextRendererComponent>()->SetText(score);

	std::string health = "Health: ";
	health += std::to_string(dae::Singleton<ServiceLocator>::GetInstance().GetHealth());
	m_Health->GetComponent<TextRendererComponent>()->SetText(health);

	for (int i{}; i < (int)m_SnoBee.size();++i) {
		if (m_SnoBee[i]->GetMarkForDelete()) {
			///m_SnoBee[i]->SetEnabled(true);
			//m_SnoBee[i]->SetPosition(m_SnoBeeEgg[m_SnoBeeEgg.size()-1]->GetPos());
			///m_SnoBeeEgg[m_SnoBeeEgg.size() - 1]->MarkForDelete();

			if (m_SnoBeeEgg.size() != 0) {
				CreateSnoBee(m_SnoBeeEgg.back()->GetPos(), i + 1);
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
	


//	int x{}, y{};
//	SDL_GetMouseState(&x, &y);
	//m_GameObject_01->SetPosition((float)x, (float)y);

	
	//if (m_GameObject_01->GetComponent<CollisionComponent>()->GetCollisions()[0]->GetCurrentCollisions().size() > 0){
	//	auto c = m_GameObject_01->GetComponent<CollisionComponent>()->GetCollisions()[0]->GetCurrentCollisions()[0];
	//	auto o = c->GetComponent()->m_GameObject;
	//	auto p = m_GridManager->GetNode(o);// ->Links->up;
	//	if (o) {
	//		///DD::GetInstance().DrawLine({ p->object->GetPos().x + 20 , p->object->GetPos().y + 20 }, { (float)x,(float)y });
	//		//DD::GetInstance().DrawLine({ p->Links->down->object->GetPos().x + 20 , p->Links->down->object->GetPos().y + 20 }, { p->object->GetPos().x + 20 , p->object->GetPos().y + 20 });
	//	}

	//}
	
	///DD::GetInstance().DrawLine({ m_Player->GetPos() }, {m_GridManager->GetClosestNode(m_Player->GetPos())->object->GetPos().x +20, m_GridManager->GetClosestNode(m_Player->GetPos())->object->GetPos().y + 20 });
	
	

	//if (m_GameObject_01->GetComponent<CollisionComponent>()->GetCollisions()[0]->GetCurrentCollisions().size() > 0) {
	//	
	//}



	//DD::GetInstance().DrawLine({ 0.f,0.f }, {100.f,100.f});
	//DD::GetInstance().DrawQuad({ 100.f,100.f }, { 100.f,100.f });
}







void DebugScene::LocalReset() {}