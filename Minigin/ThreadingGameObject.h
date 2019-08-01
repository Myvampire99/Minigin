#pragma once
class ThreadingGameObject// : dae::Singleton<ThreadingGameObject>
{
public:
	ThreadingGameObject();
	~ThreadingGameObject();
private:

	//void FunctionThread(std::shared_ptr<dae::GameObject> &gameObject, std::future<float> &futureElsapedTime, std::mutex &mutex, std::condition_variable& condVar);
	
	std::vector<std::promise<float>> m_VP_ElpasedTime;
	std::vector<std::future<float>> m_V_Future;
public:
	void SetElapsedTime(float elapsed);

private:
	std::vector<std::unique_ptr<std::mutex>> m_VI_Mutex; //DEQUE !
	std::vector<std::unique_lock<std::mutex>> m_VM_UniqueLock;
	std::condition_variable m_Cv_ContinueThread;
	std::condition_variable m_Cv_StartThreads;
	std::vector<bool> m_VB_Continue;
public:
	void WaitAndLock();
	void Unlock();
	void StartThreads();
private:
	std::vector<std::thread*> m_Threads;
public:
	void CreateThread(std::shared_ptr<dae::GameObject> &gameObject);
	void DeleteThreads();


};

