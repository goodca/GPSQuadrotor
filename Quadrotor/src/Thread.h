/*
 * Thread.h
 *
 *  Created on: Dec 23, 2012
 *      Author: chris
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>		// Be sure this is nptl header w/ proper -I in Makefile!

namespace std {

class Thread {
public:
	Thread();
	virtual ~Thread();
	int launch_pthread( pthread_t *hThread_byref, int type, int priority, void *(*thread_fxn)(void *env), void *env );

private:
	;
};

#define thread_SUCCESS  0
#define thread_FAILURE -1

// for boolean
#define REALTIME   1
#define TIMESLICE  0


} /* namespace std */
#endif /* THREAD_H_ */





