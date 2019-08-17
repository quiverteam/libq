//===========================================================//
// Name: threadtools.c
// Purpose: Threading stuff
// Date: 8/11/2019
//===========================================================// 
#include "threadtools.h"

//===========================================================//
// 
// Mutex stuff
//
//===========================================================//
void mutex_lock(mutex_t* mutex)
{
	Assert(mutex != NULL);
#ifdef _LINUX
	pthread_mutex_lock(mutex);
#elif defined(_WIN32)

#endif
}

void mutex_init(mutex_t* mutex)
{
	Assert(mutex != NULL);
#ifdef _LINUX
	pthread_mutex_init(mutex, NULL);
#elif defined(_WIN32)

#endif
}

void mutex_trylock(mutex_t* mutex)
{
	Assert(mutex != NULL);
#ifdef _LINUX
	pthread_mutex_trylock(mutex);
#elif defined(_WIN32)

#endif
}

void mutex_unlock(mutex_t* mutex)
{
	Assert(mutex != NULL);
#ifdef _LINUX
	pthread_mutex_unlock(mutex);
#elif defined(_WIN32)

#endif
}

void mutex_destroy(mutex_t* mutex)
{
	Assert(mutex != NULL);
#ifdef _LINUX
	pthread_mutex_destroy(mutex);
#elif defined(_WIN32)

#endif
}