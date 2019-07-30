#pragma once

#include "Subject.h"
namespace dae
{
	class Scene;
	class SceneManager final// : public Singleton<SceneManager>
	{
	public:
		void AddScene(Scene *pScene);

		void Update(const float elapsedTime);
		void Render();
		void Initialize();

		void SetSceneActive(std::string name, bool active);
		void ResetActiveScene();
		std::shared_ptr<Scene> GetActiveScene();
		int GetActiveSceneID();

		bool ActiveDelete;
		void AddSubject(Subject * sub);

	private:
		std::unordered_map<std::shared_ptr<Scene>,bool> mScenes;
		int count;
		Subject *m_Subject;
	};

}
