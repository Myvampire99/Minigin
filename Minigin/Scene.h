#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class SceneObject;
	class SceneManager;
	class Scene
	{
		//friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object);

		void Update(const float elapsedTime);
		void Render() const;
		void Initialize();

		std::shared_ptr<Scene> GetCoppyIni();
		

		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		explicit Scene(const std::string& name);


		//Get Set
		bool IsActive() const;
		void SetActive(bool active);

		std::string GetName() const;

	protected: 

		std::shared_ptr<Scene> m_CopyIni;
		void virtual SetCopyIni() = 0;
		void virtual SceneUpdate() = 0;
		void virtual SceneInitialize() = 0;

	private:
		float m_ElapsedTime;

		bool m_IsActive;

		std::string mName{};
		std::vector <std::shared_ptr<GameObject>> mObjects{};

		static unsigned int idCounter; //TODO: Check if used
	};

}
