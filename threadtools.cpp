//===========================================================//
// Name: threadtools.cpp
// Purpose: Threading stuff
// Date: 8/11/2019
//===========================================================//  
#include "threadtools.h"
#include <stdlib.h>
#include <memory.h>
#include <errno.h>

//===========================================================//
// 
// CThread
//
//===========================================================//
struct SThreadProcData
{
	ThreadProc_t proc;
	pthread_cond_t* cond;
	mutex_t mutex;
	void* param;
	int* ret;
	bool* exited;
	bool* running;
};

#ifdef _LINUX
void* PosixThreadProc(void* param) 
{
	SThreadProcData* pData = (SThreadProcData*)param;
	int status = 0;
	do{
		pthread_mutex_lock(&pData->mutex);
	} while(status == EBUSY);
	(*pData->running) = true;
	(*pData->ret) = pData->proc(pData->param);
	(*pData->running) = false;
	(*pData->exited) = true;
	return (void*)0;
}
#endif //_LINUX

CThread::CThread(ThreadProc_t proc)
{
#ifdef _WIN32

#elif defined(_LINUX)
	/* Setup the thread */
	pthread_attr_init(&this->m_threadattr);
	pthread_attr_setstacksize(&this->m_threadattr, 1000000);
	/* Setup data descriptor */
	SThreadProcData* data = (SThreadProcData*)malloc(sizeof(SThreadProcData));
	data->ret = &this->m_nReturn;
	data->param = NULL;
	data->proc = proc;
	data->running = &this->m_bRunning;
	data->exited = &this->m_bExited;
	this->m_pData = data;
	/* Init a new mutex and lock it */
	mutex_init(&data->mutex);
	mutex_lock(&data->mutex);
	/* Actually create */
	int status = pthread_create(&this->m_thread, &this->m_threadattr, PosixThreadProc, data);
#endif
}

CThread::~CThread()
{
#ifdef _WIN32

#elif defined(_LINUX)
	void* ret;
	if(!m_bExited)
		pthread_join(this->m_thread, &ret);
	pthread_attr_destroy(&this->m_threadattr);
#endif
}

void CThread::Start(void* param)
{
#ifdef _WIN32

#elif defined(_LINUX)
	/* Set param */
	SThreadProcData* data = (SThreadProcData*)this->m_pData;
	data->param = param;
	/* Signal the condition var */
	pthread_mutex_unlock(&data->mutex);
#endif
}

void CThread::Kill() 
{
#ifdef _WIN32

#elif defined(_LINUX)
	pthread_cancel(this->m_thread);
#endif
}

void CThread::Suspend()
{
#ifdef _WIN32

#elif defined(_LINUX)

#endif
}

void CThread::Resume()
{
#ifdef _WIN32

#elif defined(_LINUX)

#endif
}

bool CThread::IsRunning() const
{
	return m_bRunning;
}

bool CThread::IsPaused() const
{
	return (!m_bRunning && !m_bExited);
}

bool CThread::IsComplete() const
{
	return m_bExited;
}

int CThread::GetReturnCode() const
{
	return m_nReturn;
}

//===========================================================//
// 
// CMutex
//
//===========================================================//
CMutex::CMutex()
{
#ifdef _WIN32

#elif defined(_LINUX)
	pthread_mutex_init(&this->mutex, NULL);
#endif
}

CMutex::~CMutex()
{
#ifdef _WIN32

#elif defined(_LINUX)
	pthread_mutex_destroy(&this->mutex);
#endif
}

int CMutex::Lock()
{
#ifdef _WIN32

#elif defined(_LINUX)
	return pthread_mutex_lock(&this->mutex) == 0;
#endif
}

int CMutex::TryLock()
{
#ifdef _WIN32

#elif defined(_LINUX)
	return pthread_mutex_trylock(&this->mutex) == 0;
#endif
}

void CMutex::Unlock()
{
#ifdef _WIN32

#elif defined(_LINUX)
	pthread_mutex_unlock(&this->mutex);
#endif
}

//===========================================================//
// 
// CSharedMutex
//
//===========================================================//
CSharedMutex::CSharedMutex(int max)
{
	std::atomic_store<int>(&this->m_nThreads, max);
}

CSharedMutex::~CSharedMutex()
{
}

int CSharedMutex::Lock()
{
	int val = std::atomic_load<int>(&this->m_nThreads) - 1;
	int orig = val+1;
	if(std::atomic_compare_exchange_weak<int>(&this->m_nThreads, &orig, val))
	{
		return 1;
	}
	return 0;
}

void CSharedMutex::Unlock()
{
	std::atomic_fetch_add<int>(&this->m_nThreads, 1);
}