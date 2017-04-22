/*
 * main.cpp
 *
 *  Created on: Apr 21, 2017
 *      Author: MizzouRacing
 */

#include "tires.h"

int main() {
	string fileName = "data.txt";
	const char* dataFile = fileName.c_str();
	Tire tire1(frontLeft,dataFile);
	tire1.printTemps();
	int number;
	try{
		number = tire1.getTemp('o');
	}
	catch(badVector & bv){
		bv.badVectorMsg_InvalidSize();
		return(-1);
	}
	
	cout<<number<<endl;
}


