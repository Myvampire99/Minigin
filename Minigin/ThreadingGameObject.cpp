#include "MiniginPCH.h"
#include "ThreadingGameObject.h"

bool StopThreading = false;

ThreadingGameObject::ThreadingGameObject()
	:m_VB_Continue{}
{
}


ThreadingGameObject::~ThreadingGameObject()
{
}

void FunctionThread(dae::GameObject * gameObject, std::future<float> &futureElsapedTime, std::mutex &mutex, std::condition_variable &condVar, std::condition_variable &StartCV, std::condition_variable &MainCV,const bool &DoContinue) {

	UNREFERENCED_PARAMETER(DoContinue);
	//gameObject->RemoveComponent<dae::SpriteComponent>();



	{
		std::unique_lock<std::mutex> lock(mutex);
		StartCV.wait(lock);
	}

	gameObject->GetComponent<AIStateComponent>()->IsOnThread = true;
	gameObject->Initialize();
	gameObject->GetComponent<AIStateComponent>()->IsOnThread = true;

	while (!StopThreading) {

		//future
		float elapsedTime = futureElsapedTime.get();

		if (StopThreading)
			break;

		//Wait For Update
		//Update
		if (gameObject->GetMarkForDelete() && gameObject->GetEnabled()) {
			gameObject->SetEnabled(false);
			if (dynamic_cast<CollisionComponent*>(gameObject->GetComponent<CollisionComponent>())) {
				gameObject->GetComponent<CollisionComponent>()->Remove(gameObject->GetComponent<CollisionComponent>()->GetCollisions()[0]);
			}
			gameObject->MarkForDelete(false);

		}

		if (gameObject != nullptr)
			if (gameObject->GetEnabled())
				gameObject->Update(elapsedTime);

		MainCV.notify_all();//one


		{
			std::unique_lock<std::mutex> lock(mutex);
			condVar.wait(lock);
		
		//Tells Ready to udpate Scene
		//Wait For Draw
		//Draw
		///if (gameObject->GetEnabled())
		///	gameObject->Render();

		MainCV.notify_all();//one
		}
	}

}


void ThreadingGameObject::CreateThread(dae::GameObject *gameObject) {
	//UNREFERENCED_PARAMETER(gameObject);

	m_VB_Continue.push_back(true);

	m_VP_ElpasedTime.push_back({});
	m_V_Future.push_back(m_VP_ElpasedTime.back().get_future());

	//m_VI_Mutex.push_back(std::make_unique<std::mutex>());
	//m_VM_UniqueLock.push_back(std::unique_lock<std::unique_ptr<std::mutex>>{m_VI_Mutex.back()});
	//m_VI_Mutex.back()->lock();

	//m_VI_Mutex.emplace(m_VI_Mutex.end(),std::mutex{});
	//m_VM_UniqueLock


	//m_VI_Mutex.push_back(std::make_unique<std::mutex>());
	//auto test = std::unique_lock<std::unique_ptr<std::mutex>>{ m_VI_Mutex.back() };
	//m_VM_UniqueLock.push_back(std::unique_lock<std::mutex>{m_VI_Mutex.back()});
	//m_VI_Mutex.back().lock();

	//FunctionThread(gameObject, m_V_Future.back(), *m_VI_Mutex.back().get(), m_Cv_ContinueThread, m_Cv_StartThreads, m_VB_Continue.back());


//	auto temp = std::unique_lock<std::mutex>{m_Mutex};
//	auto temp2 = std::unique_lock<std::mutex>{ m_Mutex };
	//auto temp3 = std::make_unique<std::unique_lock<std::mutex>>(m_Mutex);
	//m_VM_UniqueLock.push_back(std::make_unique<std::unique_lock<std::mutex>>(m_Mutex));
	///m_Mutex.lock();
	//m_VM_UniqueLock.back().lock();

	// m_VB_Continue.back() !!!!!!!!!! NOT REFRENCED
	// m_VB_Continue.back() !!!!!!!!!! NOT REFRENCED
	// m_VB_Continue.back() !!!!!!!!!! NOT REFRENCED
	// m_VB_Continue.back() !!!!!!!!!! NOT REFRENCED
	std::thread *thread = new std::thread( FunctionThread, std::ref(gameObject), std::ref(m_V_Future.back()), std::ref(m_Mutex), std::ref(m_Cv_ContinueThread), std::ref(m_Cv_StartThreads),std::ref(m_Cv_ContinueMainThread), m_VB_Continue.back());
	m_Threads.push_back(thread);

}

void ThreadingGameObject::WaitAndLock() {
	/*for (size_t i{}; i < m_VM_UniqueLock.size(); ++i) {
		m_VM_UniqueLock.at(i)->lock();
	}*/

	for (size_t i{}; i < m_Threads.size(); ++i) {

		std::unique_lock<std::mutex> Lock(m_Mutex);
		///m_Cv_ContinueMainThread.wait(Lock);
	}	
}

void ThreadingGameObject::Unlock() {
	//for (size_t i{}; i < m_VM_UniqueLock.size(); ++i) {
	//	m_VM_UniqueLock.at(i)->unlock();
	//}

	for (size_t i{}; i < m_Threads.size(); ++i) {
		//m_Mutex.unlock();
	}

	m_Cv_ContinueThread.notify_all();
}

void ThreadingGameObject::SetElapsedTime(float elapsed) {
	UNREFERENCED_PARAMETER(elapsed);

	size_t size = m_VP_ElpasedTime.size();
	for (size_t i{}; i < size; ++i) {
		m_VP_ElpasedTime[i].set_value(elapsed);
	}

	m_VP_ElpasedTime.clear();

	for (size_t i{}; i < size; ++i) {
		m_VP_ElpasedTime.push_back({});
		m_V_Future[i] = m_VP_ElpasedTime[i].get_future();
	}

}

void ThreadingGameObject::StartThreads() {
	m_Cv_StartThreads.notify_all();
}

void ThreadingGameObject::DeleteThreads() {
	for (size_t i{}; i < m_VB_Continue.size(); ++i) {
		m_VB_Continue[i] = false;
	}

	StopThreading = true;

	for (size_t i{}; i < m_VP_ElpasedTime.size(); ++i) {
		m_VP_ElpasedTime[i].set_value(-1.f);
	}

	for (size_t i{}; i < m_Threads.size(); ++i) {
		m_Threads[i]->join();
	}

	for (size_t i{}; i < m_Threads.size(); ++i) {
		delete m_Threads[i];
	}

}