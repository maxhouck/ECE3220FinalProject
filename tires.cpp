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
#include "tires.h"
using namespace std;


Tire::Tire(void) {
	//Should not need anything here.
}

Tire::Tire(location tireLoc, const char* fileLoc) { //opens file, inputs data into temp vectors, closes file
	//file format: outer,middle,inner
	string line;
	char *token;
	ifstream file(fileLoc);
	if(file.is_open()) { //opening input file

		while(getline(file,line)) { //tokenize lines of input over 'c' and add to proper vector
			token = strtok((char*)line.c_str(),",");
			this->addTemp(atoi(token),'o');
			token = strtok(NULL,",");
			this->addTemp(atoi(token),'m');
			token = strtok(NULL,",");
			this->addTemp(atoi(token),'i');
		}
		file.close();
	}
	else {
		cout << "Unable to open file";
		exit(0);
	}
}

Tire::~Tire() { //default destructor
	//Shouldnt need anything here. Vectors will delete themselves.
}

void Tire::addTemp(int temperature, char tempLocation) {
	
	switch(tempLocation) {
		case 'o': this->tempOuterArray.push_back(temperature); break;
		case 'm': this->tempMiddleArray.push_back(temperature); break;
		case 'i': this->tempInnerArray.push_back(temperature); break;
		default: cout << "Error in addTemp" << endl;
			exit(0);
			break;
	}
}

void Tire::printTemps() {
	int i;
	for(i=0;i<tempOuterArray.size();i++)
		cout << tempOuterArray[i] << "," << tempMiddleArray[i]  << "," <<tempInnerArray[i]<< endl;
}

int Tire::getTemp(char tempLocation){
	switch(tempLocation){
		case 'o':
			if(this->tempOuterArray.size() <= 0) throw(badVector(this->tempOuterArray, this->tireLocation, 'o'));
			return(this->tempOuterArray[this->tempOuterArray.size() -1]);
		case 'm':
			return(this->tempMiddleArray[this->tempMiddleArray.size() -1]);
			break;
		case 'i':
			return(this->tempInnerArray[this->tempInnerArray.size() -1]);
			break;
		default:
			cout<< "Error in getTemp()"<<endl;
			exit(0);
			break;
	}//End Switch
}

//Parametric constructor. This will be the only way a badVector is created.
badVector::badVector(vector<int> vect, char tireLoc, char vectorLoc){
	this->size = vect.size();
	this->tireLocation = tireLoc;
	this->vectorLocation = vectorLoc;
}

//Default destructor.
badVector::~badVector(void){
	//Nothing is needed here.
}

//Prints the message corresponding to the error.
void badVector::badVectorMsg_InvalidSize(void){
		string tireName;
		string vectorLocation;
		switch(this->tireLocation){
			case 1:
				tireName = "frontLeft";
				break;
			case 2:
				tireName = "frontRight";
				break;
			case 3:
				tireName = "rearLeft";
				break;
			case 4:
				tireName = "rearRight";
				break;
			default:
				cout<<"Error in badVectorMsg_InvalidSize"<<endl;
				exit(2);
				break;
			
		}//End switch
		switch(this->vectorLocation){
			case 'o':
				vectorLocation = "outer";
				break;
			case 'm':
				vectorLocation = "middle";
			case 'i':
				vectorLocation = "inner";
			default:
				cout<<"Error in badVectorMsd_InvalidSize vectorLocation switch"<<endl;
				exit(3);
				break;
			
		}//End switch
		cout<<"Could not access "<< tireName<< " "<<vectorLocation<< " vector. This vectors size is "<< this->size<<endl;
}