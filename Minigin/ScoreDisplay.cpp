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
				dae::Singleton<ServiceLocator>::GetInstanceScene()->GetHealthGO()->GetComponent<TextRendererComponent>()->SetText(std::to_string(lv));
			
				entity->GetComponent<DiggerCharacterComponent>()->ResetPosition();
			}
			else {
				entity->MarkForDelete();
				dae::Singleton<dae::SceneManager>::GetInstance().ResetActiveScene();
			}
		}

		if (dynamic_cast<PookaCharacterComponent*>(entity->GetComponent<PookaCharacterComponent>()))
		{
			dae::Singleton<ServiceLocator>::GetInstanceScene()->AddCurrentScore(entity->GetComponent<PookaCharacterComponent>()->GetScore());
			dae::Singleton<ServiceLocator>::GetInstanceScene()->GetScoreGO()->GetComponent<TextRendererComponent>()->SetText(std::to_string(dae::Singleton<ServiceLocator>::GetInstanceScene()->GetCurrentScore()));
			//dae::Singleton<ServiceLocator>::GetInstanceScene()->RemovePlayerObject(entity);
			entity->MarkForDelete();
		}

		if (dynamic_cast<FygarCharacterComponent*>(entity->GetComponent<FygarCharacterComponent>()))
		{
			dae::Singleton<ServiceLocator>::GetInstanceScene()->AddCurrentScore(entity->GetComponent<FygarCharacterComponent>()->GetScore());
			dae::Singleton<ServiceLocator>::GetInstanceScene()->GetScoreGO()->GetComponent<TextRendererComponent>()->SetText(std::to_string(dae::Singleton<ServiceLocator>::GetInstanceScene()->GetCurrentScore()));
			//dae::Singleton<ServiceLocator>::GetInstanceScene()->RemovePlayerObject(entity);
			entity->MarkForDelete();
		}

		break;
	}
}
