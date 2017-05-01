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
#include "tires.h"
using namespace std;

/**************************************************************************
						TIRE CLASS METHODS
**************************************************************************/
/**************************************************************************
	Tire class parametric constuctor. Takes the location of the new tire as
the tireLocation enum as well as the name of the new tire and sets the
corresponding values in the object.

**************************************************************************/
Tire::Tire(tireLocation tireLoc, string newName){
	this->location = tireLoc;
	this->name = newName;
}

/**************************************************************************
	Tire class addSensor method. Takes a Sensor object as an arguement
and adds it to the sensorArray vector.

**************************************************************************/
void Tire::addSensor(Sensor newSensor){
	this->sensorArray.push_back(newSensor);
}


/**************************************************************************
	Tire class removeSensor method. Accepts the location of the sensor
as a sensorLocation enum and removes the selected sensor from the 
sensorArray vector. It also checks to make sure the senssorArray vector
is not empty. If the vector is empty, it will throw an const int equal to
1.

**************************************************************************/

void Tire::removeSensor(sensorLocation sensorLoc) throw(const int){
	//If the sensor array is empty, throw the number 1
	if(this->sensorArray.size() <= 0){
		throw(1);
	}
	
	for(int i = 0; i < this->sensorArray.size(); i++){
		if(this->sensorArray[i].location == sensorLoc){
			this->sensorArray.erase(this->sensorArray.begin()+i);
			break;
		}
	}
	
}

/**************************************************************************
	Tire class printInfo method. Prints all of the information about the 
tire to the screen.
**************************************************************************/
void Tire::printInfo(void){
	cout<<"\n Name: "<<this->name
		<<"\n Location: "<< this->location<<endl;
	
	
	cout<<" Sensor vector contents: "<<endl;
	if(this->sensorArray.size() <= 0){
		cout<<"  Sensor array is empty!"<<endl;
	}else{
		for(int i = 0; i < this->sensorArray.size(); i++){
			sensorArray[i].printInfo();
		}
	}
}

/**************************************************************************
						SENSOR CLASS METHODS
**************************************************************************/
/**************************************************************************
	Sensor class parametric constructor. Takes the name, the location as a
sensorLoaction enum, and the address as arguements. Sets the corresponding
fields to the given values.

**************************************************************************/
Sensor::Sensor(string newName, sensorLocation sensorLoc, int sensorAddress){
	this->name = newName;
	this->location = sensorLoc;
	this->address = sensorAddress;
	this->ambTemperature = 0;
}

/**************************************************************************
	Sensor class addTemperature method. Takes a temperature as an integer
and adds it to the objTemperature vector.
**************************************************************************/
void Sensor::addTemperature(int temperature){
	this->objTemperature.push_back(temperature);
}

/**************************************************************************
	Sensor class getTemperature method. Returns the most recent
temperature from the objTemperature vector. Checks to make sure the 
objTemperature vector is not empty. If the vector is empty, returns a 
const int equal to 2.
**************************************************************************/
int Sensor::getTemperature(void) throw(const int){
	if(this->objTemperature.size() <= 0){
		throw(2);
	}
	return(this->objTemperature.back());
}

/**************************************************************************
	Sensor class printEverything method. Used for debugging, this method
does exactly what the name implies. It will print everything contained in
the class to the screen.
**************************************************************************/
void Sensor::printInfo(void){
	cout<<"\n  "<<this->name<<" information: "
		<<"\n   Sensor location: "<<this->location
		<<"\n   Ambient temperature: "<<this->ambTemperature
		<<"\n   Address : "<<this->address<<endl;
	
	cout<<"   Temperature vector contents: "<<endl;
	if(this->objTemperature.size() <= 0){
		cout<<"   The vector is empty!"<<endl;
	}else{
		for(int i = 0; i < this->objTemperature.size(); i++){
			cout<<"    "<<this->objTemperature[i];
			if(i % 3 == 0)
				cout<<"\n";
		}
		cout<<"\n-------------------------------------------------------"<<endl;
	}
}

/**************************************************************************
						CAR CLASS METHODS
**************************************************************************/
/**************************************************************************
	Car class parametric constructor. Takes the name of the car as a string
and sets the corresponding field.
**************************************************************************/
Car::Car(string newName){
	this->name = newName;
}

/**************************************************************************
	Car class printInfo method. Prints all of the information about the car
to the screen.
**************************************************************************/
void Car::printInfo(void){
		cout<<"\n"<<this->name<<endl;
		cout<<"Tire vector contents: "<<endl;
		if(this->tireArray.size() <= 0){
			cout<<"Tire array is empty!"<<endl;
		}else{
			for(int i = 0; i < this->tireArray.size(); i++){
					cout<<"\n Tire "<<i<<endl;
					tireArray[i].printInfo();
			}
		}
		cout<<"------------------------------------"<<endl;
}

/**************************************************************************
	Car class getTemperature method. Takes the tire location, 
sensor location (as tireLocation and sensorLocation respectively), and the
index of the temperature value. Returns the temperature at that index as
an integer.
**************************************************************************/
int Car::getTemperature(tireLocation tireLoc, sensorLocation sensorLoc, int index){
	return(this->tireArray[tireLoc-1].sensorArray[sensorLoc-1].objTemperature[index]);
}
/**************************************************************************
	Car class numDataPoints method. Returns the number of data points in
the temperature vectors as an integer.
**************************************************************************/
int Car::numDataPoints(void){
	return(this->tireArray[0].sensorArray[0].objTemperature.size());
}
/**************************************************************************
	Car class addTire method. Takes a Tire object as an arguement and 
adds it to the tire vector.
**************************************************************************/
void Car::addTire(Tire newTire){
	this->tireArray.push_back(newTire);
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