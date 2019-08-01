#pragma once
#include "SceneManager.h"

class ThreadingGameObject;
namespace dae
{
	class GameObject;
	class SceneObject;
	class SceneManager;
	class Scene
	{
	public:
		int ID = -2;
		void Add(const std::shared_ptr<dae::GameObject>& object);

		void Update(const float elapsedTime);
		void Render() const;
		void Initialize();

		ThreadingGameObject *m_ThreadManager;
		void AddThreadGameObject(std::shared_ptr<dae::GameObject>& object);

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
		void Reset();


		void virtual SwitchSceneIni() = 0;
		void virtual SwitchSceneDec() = 0;

	protected: 
		void virtual SceneUpdate() = 0;
		void virtual SceneInitialize() = 0;
		void virtual LocalReset() = 0;
	private:

		std::vector <std::shared_ptr<dae::GameObject>> mObjects{};
		float m_ElapsedTime;

		bool m_IsActive;

		std::string mName{};
	};

}
