/*
 * tires.cpp
 *
 *  Created on: Apr 21, 2017
 *      Author: MizzouRacing
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;


Tire::Tire(void) {

}

Tire::Tire(location tireLoc, char* fileLoc) { //opens file, inputs data into temp vectors, closes file
	//file format: outer,middle,inner
	string line;
	char* cstring;
	ifstream file(fileLoc);
	if(file.is_open()) { //opening input file
		line = strtok(cstring,",");
		while(getline(file,line)) { //tokenize lines of input over 'c' and add to proper vector
			line = strtok(NULL,",");
			addTemp(atoi(cstring),'o');
			line = strtok(NULL,",");
			addTemp(atoi(cstring),'m');
			line = strtok(NULL,",");
			addTemp(atoi(cstring),'i');
		}
		file.close();
	}
	else {
		cout << "Unable to open file";
		exit(0);
	}
}
