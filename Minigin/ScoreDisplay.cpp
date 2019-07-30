#include "MiniginPCH.h"
#include "ScoreDisplay.h"


ScoreDisplay::ScoreDisplay()
{
	
}


ScoreDisplay::~ScoreDisplay()
{
}

void ScoreDisplay::onNotify(dae::GameObject *entity, Event event)
{
	UNREFERENCED_PARAMETER(entity);
	int mul = 1;

	switch (event)
	{
	case Event::EVENT_DIEDROCK:
		mul = 2;
	case Event::EVENT_DIED:
		
		//if (dynamic_cast<DiggerCharacterComponent*>(entity->GetComponent<DiggerCharacterComponent>()))
		//{
		//	int lv = entity->GetComponent<DiggerCharacterComponent>()->GetLives();
		//	lv--;
		//	if (lv >= 0) {
		//		entity->GetComponent<DiggerCharacterComponent>()->SetLives(lv);
		//		dae::Singleton<ServiceLocator>::GetInstance().GetHealthGO()->GetComponent<TextRendererComponent>()->SetText(std::to_string(lv));
		//	
		//		entity->GetComponent<DiggerCharacterComponent>()->ResetPosition();
		//	}
		//	else {
		//		//entity->MarkForDelete();
		//		dae::Singleton<dae::SceneManager>::GetInstance().ResetActiveScene();

		//		entity->GetComponent<DiggerCharacterComponent>()->ResetPosition();
		//	}
		//}

	/*	if (dynamic_cast<PookaCharacterComponent*>(entity->GetComponent<PookaCharacterComponent>()))
		{
			dae::Singleton<ServiceLocator>::GetInstance().AddCurrentScore(entity->GetComponent<PookaCharacterComponent>()->GetScore()*mul);
			dae::Singleton<ServiceLocator>::GetInstance().GetScoreGO()->GetComponent<TextRendererComponent>()->SetText(std::to_string(dae::Singleton<ServiceLocator>::GetInstance().GetCurrentScore()));
			entity->MarkForDelete();
		}

		if (dynamic_cast<FygarCharacterComponent*>(entity->GetComponent<FygarCharacterComponent>()))
		{
			dae::Singleton<ServiceLocator>::GetInstance().AddCurrentScore(entity->GetComponent<FygarCharacterComponent>()->GetScore()*mul);
			dae::Singleton<ServiceLocator>::GetInstance().GetScoreGO()->GetComponent<TextRendererComponent>()->SetText(std::to_string(dae::Singleton<ServiceLocator>::GetInstance().GetCurrentScore()));
			entity->MarkForDelete();
		}*/

		break;
	}
}
