/*
 * thread.h
 *
 *  Created on: Jan 3, 2013
 *      Author: chris
 */
#ifdef __cplusplus
extern "C" {
#endif


#ifndef THREAD_H_
#define THREAD_H_

#include <stdio.h>                      // Always include this header
#include <stdlib.h>                     // Always include this header
#include <pthread.h>                    // Be sure this is nptl header w/ proper -I in Makefile!

pthread_t imuThread;

//void *imuThreadReturn;
//void *compassThreadReturn;

#define thread_SUCCESS  0
#define thread_FAILURE -1

// for boolean
#define REALTIME   1
#define TIMESLICE  0

int launch_pthread( pthread_t *hThread_byref, int type, int priority, void *(*thread_fxn)(void *env), void *env );
int *QuadthreadOne(void *envByRef);

int *QuadthreadTwo(void *envByRef);
int launchThreads();

#endif /* THREAD_H_ */
#ifdef __cplusplus
}
#endif
