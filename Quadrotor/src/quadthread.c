/*
 *   thread.c
 */

#include <stdio.h>                              //  Always include this header
#include <stdlib.h>                             //  Always include this header
#include <pthread.h>                            // posix thread definitions
#include "quadthread.h"                             // header file for this module
/**************************************************************************
 *  launch_pthread
 *  --------------
 *  Launches a linux posix thread
 *
 *  INPUTS
 *  int type -- REALTIME or TIMESLICE as defined in thread.h
 *  int priority -- priority if a REALTIME thread, ignored if TIMESLICE
 *              thread. "niceness" set to default 0 for TIMESLICE
 *  (void *)(*thread_fnx)(void *env) -- pointer to the function which
 *              will be associated to the newly created thread
 *  void *env -- pointer to the environment struct which will be passed
 *              to the function "thread_fnx" upon calling
 *
 *  OUTPUTS
 *  pthread_t *hThread_byref -- pthread handle passed by reference
 *             Can be NULL on calling, will point to the handle of the
 *             newly created thread upon return
 *
 *  int (return) -- thread_SUCCESS or thread_FAUILURE as defined in
 *             thread.h
 **************************************************************************/

int launch_pthread(pthread_t *hThread_byref, int type, int priority,
		void *(*thread_fxn)(void *env), void *env) {
//	DBG( "IN thread.c----------------------\n" );
	pthread_attr_t threadAttrs;
	struct sched_param threadParams;
	int status = thread_SUCCESS;

	/* Initialize thread attributes structures */
	if (pthread_attr_init(&threadAttrs)) {
//        ERR( "threadAttrs initialization failed\n" );
		status = EXIT_FAILURE;
		goto cleanup;
	}

	/* This library defaults to inherited scheduling characteristics!   */
	/* If you don't set the inheritance, no changes will take place!    */

	if (pthread_attr_setinheritsched(&threadAttrs, PTHREAD_EXPLICIT_SCHED)) {
//        ERR( "audioThreadAttrs set scheduler inheritance failed\n" );
		status = EXIT_FAILURE;
		goto cleanup;
	}

	/* Setthread scheduling policy to real-time or time-slice           */
	/* SCHED_RR available only to threads running as superuser          */

	if (type == REALTIME) {
		if (pthread_attr_setschedpolicy(&threadAttrs, SCHED_RR)) {
//            ERR( "pthread_attr_setschedpolicy failed\n" );
			status = EXIT_FAILURE;
			goto cleanup;
		}
	} else {
		if (pthread_attr_setschedpolicy(&threadAttrs, SCHED_OTHER)) {
//            ERR( "pthread_attr_setschedpolicy failed\n" );
			status = EXIT_FAILURE;
			goto cleanup;
		}
	}

	/* Set thread priority */
	threadParams.sched_priority = priority;

	if (pthread_attr_setschedparam(&threadAttrs, &threadParams)) {
//        ERR( "pthread_attr_setschedparam failed\n" );
		status = EXIT_FAILURE;
		goto cleanup;
	}

	/*  Create the thread  */
//	DBG( "CREATING THREAD----------------------\n" );
	printf("about to launch thread\n");
	if (pthread_create(hThread_byref, &threadAttrs, thread_fxn, env)) {
//        ERR( "Failed to create thread\n" );
		status = EXIT_FAILURE;
		goto cleanup;
	}
//	DBG( "END OF thread.c----------------------\n" );
	cleanup: return status;

}
int launchThreads(void *envRef) {
	int env = 0;

	int successFirst = launch_pthread(&imuThread, TIMESLICE, 0, QuadthreadOne,
			(void *) &env);
	printf("success variable 1 is: %d\n", successFirst);
	//	launch_pthread(&firstThread, TIMESLICE, 0, thread1, (void *) &env);
//		int successSecond = launch_pthread(&compassThread, TIMESLICE, 0,
//	QuadthreadTwo, (void *) &env);
//	printf("success variable 2 is: %d\n", successSecond);

	sleep(3);

//		pthread_join(imuThread, (void **) &imuThreadReturn);
//		pthread_join(compassThread, (void **) &compassThreadReturn);
}
int *QuadthreadOne(void *envByRef) {
	while (1) {

	}
	return 1;
}

int *QuadthreadTwo(void *envByRef) {
	while (1) {
		printf("In thread 2\n\n");
	}
	return 0;
}
