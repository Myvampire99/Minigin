#pragma once
#include "SceneManager.h"

namespace dae
{
	//class SceneObject;
	class SceneManager;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<SceneObject>& object);

		void Update(const float elapsedTime);
		void Render() const;
		void Initialize();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		explicit Scene(const std::string& name);
	private: 
		

		std::string mName{};
		std::vector < std::shared_ptr<SceneObject>> mObjects{};

		static unsigned int idCounter; 
	};

}