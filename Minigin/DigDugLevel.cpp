#include "MiniginPCH.h"
#include "DigDugLevel.h"


DigDugLevel::DigDugLevel()
	:Scene("DigDugLevel")
{
}


DigDugLevel::~DigDugLevel()
{
}

void DigDugLevel::SceneUpdate() {
	std::pair<bool, bool> VH = m_Player->GetComponent<BaseCharacterComponent>()->GetFlipVertnFlipHor();
	m_Player->GetComponent<dae::SpriteComponent>()->FlipSprite(VH.second || VH.first, false);//TODO: this prob isnt the best way to do it
	
	m_Player->GetComponent<dae::SpriteComponent>()->SetPause(m_Player->GetComponent<BaseCharacterComponent>()->GetDirection() == BaseCharacterComponent::Direction::Idle);


	if (m_PlayerCharacter->IsDigging())
		m_Player->GetComponent<dae::SpriteComponent>()->SetCurrentSprite(1);
	else
		m_Player->GetComponent<dae::SpriteComponent>()->SetCurrentSprite(0);

}

void DigDugLevel::SceneInitialize() {

	int widthGrid = 12;
	int HeightGrid = 12;
	float SizeBlockGrid = 30;

	//Grid
	m_GridLevel = new GridLevel(widthGrid, HeightGrid, SizeBlockGrid, { SizeBlockGrid,SizeBlockGrid });
	auto levelGameObject = std::make_shared<dae::GameObject>();
	levelGameObject->AddComponent(m_GridLevel);
	Add(levelGameObject);
	//

	//Grid Blocks
	auto *lvlObj = new LevelObject("Resources/Textures/Ground.png");
	lvlObj->SetSize(SizeBlockGrid);
	levelGameObject->GetComponent<GridLevel>()->FillLevel(lvlObj);

	auto *Rock = new RockBlock("Resources/Textures/Rock.png", m_GridLevel);
	Rock->SetSize(SizeBlockGrid);
	levelGameObject->GetComponent<GridLevel>()->ChangeBlock(Rock, 17);
	//



	//Input
	m_Inputcomponent = new InputComponent;
	m_Inputcomponent->AssignButton(left, ControllerButton::Dpad_Left);
	m_Inputcomponent->AssignButton(right, ControllerButton::Dpad_Right);
	m_Inputcomponent->AssignButton(up, ControllerButton::Dpad_Up);
	m_Inputcomponent->AssignButton(down, ControllerButton::Dpad_Down);
	m_Inputcomponent->AssignButton(fire, ControllerButton::Button_A);//TODO: Still hardcoded in DiggerCharComp

	
	//

	//Character Component
	m_PlayerCharacter = new DiggerCharacterComponent(m_GridLevel);
	m_PlayerCharacter->AssignButton(left, right, up, down);//TODO: Pls make this better
	m_PlayerCharacter->SetWidth(25); //TODO: Hardcoded
	//

	//Player
	m_Player = std::make_shared<dae::GameObject>();

	m_Player->AddComponent(new dae::SpriteComponent(0, new dae::Sprite("Resources/Sprites/PlayerMove.png", 1,2, 2, 3)));
	m_Player->AddComponent(new GridComponent(m_GridLevel, true));//, { SizeBlockGrid / 2.f,SizeBlockGrid / 2.f }
	m_Player->AddComponent(m_Inputcomponent);
	m_Player->AddComponent(m_PlayerCharacter);

	m_Player->GetTransform()->SetScale(2);

	dae::Singleton<ServiceLocator>::GetInstance().SetPlayerObject(m_Player);
	Add(m_Player);
	//

	//Extra Sprite
	m_Player->GetComponent<dae::SpriteComponent>()->AddSprite(1, new dae::Sprite("Resources/Sprites/DiggingB.png", 1, 2, 2, 3));
	//
}