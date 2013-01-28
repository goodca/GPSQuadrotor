/*
 * Remotehandler.h
 *
 *  Created on: Jan 25, 2013
 *      Author: cooperdl
 */

#ifndef REMOTEHANDLER_H_
#define REMOTEHANDLER_H_

#include "RemoteInput.h"

#define remoteChannel1 1

#define remoteChannel2 2

#define remoteChannel3 3

#define remoteChannel4 4

namespace std {



class Remotehandler {

	RemoteInput *ch1;
	RemoteInput *ch2;
	RemoteInput *ch3;
	RemoteInput *ch4;

public:
	Remotehandler();
	double getch1();
	double getch2();
	double getch3();
	double getch4();
	virtual ~Remotehandler();
};

} /* namespace std */
#endif /* REMOTEHANDLER_H_ */
