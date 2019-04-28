#pragma once

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void AddScene(Scene *pScene);

		void Update(const float elapsedTime);
		void Render();
		void Initialize();

		void SetSceneActive(std::string name, bool active);

	private:
		std::unordered_map<std::shared_ptr<Scene>,bool> mScenes;
	};

}
