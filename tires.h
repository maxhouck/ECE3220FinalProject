#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

#ifndef tires_H
#define tires_H

//Enumeration defining the tire layout
enum location {frontLeft=1, frontRight=2,rearLeft=3,rearRight=4};

class Tire{
	private:
		//Temperature vectors for inputing temps from a file.
		vector<int> tempOuterArray;
		vector<int> tempMiddleArray;
		vector<int> tempInnerArray;

		//Temperature integers for pulling from arrays or RT data collection(maybe)
		int tempOuter;
		int tempMiddle;
		int tempInner;
		int loggingRate; //logging rate in Hz

	public:
		//This will define where on the car THIS tire is
		//We will need to come up with a tire addressing system.
		location tireLocation;

		int getTemp(char tempLocation);		//member function to return a temperature from one of the vectors
		void addTemp(int temperature, char tempLocation);	//Member function to add a temperature to the correct vector
		int removeTemp(char tempLocation);	//Member function to remove the most recent temperature from the chosen vector. Returns removed temperature
		void printTemps(); //used mainly for debugging

		Tire(void);			//Default constructor
		Tire(location tireLoc, const char* fileLoc);		//Parametric constructor given a tire location and file location
		~Tire(void);		//Default destructor

};//Tire


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

#endif
