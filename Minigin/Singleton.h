#pragma once
namespace dae
{
	class Scene;

	template <typename T>
	class Singleton
	{
	public:
		static T& GetInstanceOOOOO()
		{
			static T instance{};
			return instance;
		}

		static T& GetInstanceScene()
		{
			if (m_Instances[dae::Singleton<dae::SceneManager>::GetInstanceOOOOO().GetActiveScene()] == nullptr)
				m_Instances[dae::Singleton<dae::SceneManager>::GetInstanceOOOOO().GetActiveScene()] = new T;

			return m_Instances[dae::Singleton<dae::SceneManager>::GetInstanceOOOOO().GetActiveScene()];
		}

		virtual ~Singleton() = default;
		Singleton(const Singleton& other) = delete;
		Singleton(Singleton&& other) = delete;
		Singleton& operator=(const Singleton& other) = delete;
		Singleton& operator=(Singleton&& other) = delete;

	protected:
		Singleton() = default;
	private:
		static std::map<std::shared_ptr<Scene>, T*> m_Instances;
	};
}