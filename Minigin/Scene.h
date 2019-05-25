#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class SceneObject;
	class SceneManager;
	class Scene
	{
	public:
		void Add(const std::shared_ptr<GameObject>& object);

		void Update(const float elapsedTime);
		void Render() const;
		void Initialize();

		

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

	protected: 
		void virtual SceneUpdate() = 0;
		void virtual SceneInitialize() = 0;
		void virtual LocalReset() = 0;
	private:

		std::vector <std::shared_ptr<GameObject>> mObjects{};
		float m_ElapsedTime;

		bool m_IsActive;

		std::string mName{};
	};

}
