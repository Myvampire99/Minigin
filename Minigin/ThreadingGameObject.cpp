#include "MiniginPCH.h"
#include "ThreadingGameObject.h"


ThreadingGameObject::ThreadingGameObject()
	:m_VB_Continue{}
{
}


ThreadingGameObject::~ThreadingGameObject()
{
}

//TODO: IMPORTANNT !!!!!!!             CONST OF BOOL ????????????????????? 
//TODO: IMPORTANNT !!!!!!!             CONST OF BOOL ????????????????????? 
//TODO: IMPORTANNT !!!!!!!             CONST OF BOOL ????????????????????? 
//TODO: IMPORTANNT !!!!!!!             CONST OF BOOL ????????????????????? 
void FunctionThread(std::shared_ptr<dae::GameObject> &gameObject, std::future<float> &futureElsapedTime, std::mutex &mutex, std::condition_variable &condVar, std::condition_variable &StartCV,const bool &DoContinue) {

	{
		std::unique_lock<std::mutex> lock(mutex);
		StartCV.wait(lock);
	}
	gameObject->Initialize();
	while (DoContinue) {

		//future
		float elapsedTime = futureElsapedTime.get();

		if (!DoContinue)
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


		{
			std::unique_lock<std::mutex> lock(mutex);
			condVar.wait(lock);
		}
		//Tells Ready to udpate Scene
		//Wait For Draw
		//Draw
		if (gameObject->GetEnabled())
			gameObject->Render();


	}

}


void ThreadingGameObject::CreateThread(std::shared_ptr<dae::GameObject> &gameObject) {
	UNREFERENCED_PARAMETER(gameObject);

	m_VB_Continue.push_back(true);

	m_VP_ElpasedTime.push_back({});
	m_V_Future.push_back(m_VP_ElpasedTime.back().get_future());

	m_VI_Mutex.push_back(std::make_unique<std::mutex>());
	m_VM_UniqueLock.push_back(std::unique_lock<std::unique_ptr<std::mutex>>{m_VI_Mutex.back()});
	m_VI_Mutex.back()->lock();



	//FunctionThread(gameObject, m_V_Future.back(), *m_VI_Mutex.back().get(), m_Cv_ContinueThread, m_Cv_StartThreads, m_VB_Continue.back());


	// m_VB_Continue.back() !!!!!!!!!! NOT REFRENCED
	// m_VB_Continue.back() !!!!!!!!!! NOT REFRENCED
	// m_VB_Continue.back() !!!!!!!!!! NOT REFRENCED
	// m_VB_Continue.back() !!!!!!!!!! NOT REFRENCED
	std::thread *thread = new std::thread( FunctionThread, std::ref(gameObject), std::ref(m_V_Future.back()), std::ref(*m_VI_Mutex.back().get()), std::ref(m_Cv_ContinueThread), std::ref(m_Cv_StartThreads), m_VB_Continue.back());
	m_Threads.push_back(thread);

}

void ThreadingGameObject::WaitAndLock() {
	for (size_t i{}; i < m_VM_UniqueLock.size(); ++i) {
		m_VM_UniqueLock[i].lock();
	}
}

void ThreadingGameObject::Unlock() {
	for (size_t i{}; i < m_VM_UniqueLock.size(); ++i) {
		m_VM_UniqueLock[i].unlock();
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