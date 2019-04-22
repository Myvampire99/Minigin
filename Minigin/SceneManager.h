#pragma once

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene & CreateScene(const std::string& name);

		void Update(const float elapsedTime);
		void Render();
		void Initialize();

	private:
		std::vector<std::shared_ptr<Scene>> mScenes;
	};

}
