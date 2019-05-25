#pragma once

#include "Scene.h"

namespace dae
{
	//class dae::Scene;
	//class SceneManager;
	template <typename T>
	class Singleton
	{
	public:
		static T& GetInstance()
		{
			static T instance{};
			return instance;
		}

		static T& GetInstanceScene()
		{
			
			static std::map < std::shared_ptr<dae::Scene>, T> m_Instances{};

			//if (m_Instances[dae::Singleton<dae::SceneManager>::GetInstance().GetActiveScene()] == nullptr)
			//	m_Instances[dae::Singleton<dae::SceneManager>::GetInstance().GetActiveScene()] = new T;

			if (m_Instances.find(dae::Singleton<dae::SceneManager>::GetInstance().GetActiveScene()) == m_Instances.end()) {
				T te{};
				m_Instances[dae::Singleton<dae::SceneManager>::GetInstance().GetActiveScene()] = te;
			}
			

			//std::shared_ptr<dae::Scene> test =dae::Singleton<dae::SceneManager>::GetInstance().GetActiveScene();
			//UNREFERENCED_PARAMETER(test);
			//m_Instances[0];
			return m_Instances[dae::Singleton<dae::SceneManager>::GetInstance().GetActiveScene()];
			//return nullptr;
		}

		virtual ~Singleton() = default;
		Singleton(const Singleton& other) = delete;
		Singleton(Singleton&& other) = delete;
		Singleton& operator=(const Singleton& other) = delete;
		Singleton& operator=(Singleton&& other) = delete;

	
	protected:
		Singleton() = default;
	private:
		
	};
}