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
}


