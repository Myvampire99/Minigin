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
	switch (event)
	{
	case Event::EVENT_DIED:
		
		if (dynamic_cast<DiggerCharacterComponent*>(entity->GetComponent<DiggerCharacterComponent>()))
		{
			int lv = entity->GetComponent<DiggerCharacterComponent>()->GetLives();
			lv--;
			if (lv >= 0) {
				entity->GetComponent<DiggerCharacterComponent>()->SetLives(lv);
				dae::Singleton<ServiceLocator>::GetInstance().GetHealthGO()->GetComponent<TextRendererComponent>()->SetText(std::to_string(lv));
			
				entity->GetComponent<DiggerCharacterComponent>()->ResetPosition();
			}
			else {
				entity->MarkForDelete();
				//dae::Singleton<dae::SceneManager>::GetInstance().ResetActiveScene();
			}
		}

		if (dynamic_cast<PookaCharacterComponent*>(entity->GetComponent<PookaCharacterComponent>()))
		{
			dae::Singleton<ServiceLocator>::GetInstance().AddCurrentScore(entity->GetComponent<PookaCharacterComponent>()->GetScore());
			dae::Singleton<ServiceLocator>::GetInstance().GetScoreGO()->GetComponent<TextRendererComponent>()->SetText(std::to_string(dae::Singleton<ServiceLocator>::GetInstance().GetCurrentScore()));
			dae::Singleton<ServiceLocator>::GetInstance().RemovePlayerObject(entity);
			entity->MarkForDelete();
		}

		if (dynamic_cast<FygarCharacterComponent*>(entity->GetComponent<FygarCharacterComponent>()))
		{
			dae::Singleton<ServiceLocator>::GetInstance().AddCurrentScore(entity->GetComponent<FygarCharacterComponent>()->GetScore());
			dae::Singleton<ServiceLocator>::GetInstance().GetScoreGO()->GetComponent<TextRendererComponent>()->SetText(std::to_string(dae::Singleton<ServiceLocator>::GetInstance().GetCurrentScore()));
			dae::Singleton<ServiceLocator>::GetInstance().RemovePlayerObject(entity);
			entity->MarkForDelete();
		}

		break;
	}
}
