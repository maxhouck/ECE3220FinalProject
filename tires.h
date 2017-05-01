#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

#ifndef tires_H
#define tires_H

//Enumeration defining the tire layout
enum tireLocation {frontLeft=1, frontRight=2,rearLeft=3,rearRight=4};
enum sensorLocation {outer = 1, middle = 2, inner = 3};

class Sensor{
	friend class Tire;
	friend class Car;
	private:
		string name;
		vector<int> objTemperature;
		sensorLocation location;
		int ambTemperature;
		int address;
	public:
		Sensor(){};
		Sensor(string newName, sensorLocation sensorLoc,int sensorAddress);
		~Sensor(){};
		void addTemperature(int temperature);
		int getTemperature(void) throw(const int);
		void printInfo(void);
};//Sensor

class Tire{
	friend class Car;
	protected:
		string name;
		tireLocation location;
		vector<Sensor> sensorArray;
		
	public:
		Tire(void){};			//Default constructor
		Tire(tireLocation tireLoc, string newName);		//Parametric constructor given a tire location
		void addSensor(Sensor newSensor);
		void removeSensor(sensorLocation sensorLoc) throw(const int);
		void printInfo(void);
		~Tire(void){};		//Default destructor

};//Tire

class Car{
	protected:
		string name;
	public:
		Car(){};
		Car(string newName);
		~Car(){};
		vector<Tire> tireArray;
		void printInfo(void);
		void addTire(Tire newTire);
		void removeTire(tireLocation tireLoc);
		int getTemperature(tireLocation tireLoc, sensorLocation sensorLoc, int);
		int numDataPoints(void);
	
};//Car


class mlx90614{

	private:
		char address;				//THIS devices I2C address. 0 - 127
		char EEPROMAddress_address; //The EEPROM address that contains the device address
		char RAMAddress_OBJTemp;	//The address in the RAM where the OBJ temperature is
		char RAMAddress_AMBTemp;	//the address in the RAM where the Ambient temperature is

	public:

		mlx90614(void);				//Default constructor
		mlx90614(char);				//Parametric constructor if given the device's address
		~mlx90614(void);			//Default destructor
};//mlx90614

class I2C{
	public:

		char SDA;					//Contains the SDA pin number
		char SCL;					//Contains the SCL pin number
		char V5;					//Contains the 5v pin number
		char GND;					//Contains the GND pin number

		I2C(void);					//Default constructor;
		I2C(char, char, char, char);	//Parametric constructor given the pin numbers
		~I2C(void);					//Default destructor

		char writeBit(bool);			//Member function to write a bit
		char readBit(void);				//Member function to read a bit

		char writeByte(char);			//Member function to write a byte
		char readByte(void);			//Member function to read a byte

		void startCondition(void);		//Member function to send a start condition
		void stopCondition(void);		//Member function to send a stop condition



};//I2C

class badVector{
	private:
		int size;	//Contains the size of the vector trying to be accessed
		char tireLocation; //Contains the location of the tire.
		char vectorLocation; //Contains the vector trying to be accessed.
	public:
		badVector(vector<int> vect, char tireLoc, char vectorLoc);	//Default constructor to set the size.
		void badVectorMsg_InvalidSize(void);		//Outputs the error message concerning size.
		~badVector();					//Defualt destructor. Shouldnt need anything.
};

#endif
