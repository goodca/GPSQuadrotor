/*
 * Remotehandler.cpp
 *
 *  Created on: Jan 25, 2013
 *      Author: cooperdl
 */

#include "Remotehandler.h"
#include "RemoteInput.h"

namespace std {




Remotehandler::Remotehandler() {

	this->ch1= new RemoteInput();
	this->ch2= new RemoteInput();
	this->ch3= new RemoteInput();
	this->ch4= new RemoteInput();

	this->ch1->start(remoteChannel1);
	this->ch2->start(remoteChannel2);
	this->ch3->start(remoteChannel3);
	this->ch4->start(remoteChannel4);


}

double Remotehandler::getch1(){

	return this->ch1->get_percent_amount();

}

double Remotehandler::getch2(){

	return this->ch2->get_percent_amount();

}
double Remotehandler::getch3(){

	return this->ch3->get_percent_amount();

}
double Remotehandler::getch4(){

	return this->ch4->get_percent_amount();

}

Remotehandler::~Remotehandler() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
