
#include <iostream>
#include <wiringPi.h>
using namespace std;

class I2C{
	public:
		int SDA;
		int SCL;
		bool started;
		
		//Hardware specific functions
		void I2CInit(void);
		bool readSCL(void);
		bool readSDA(void);
		void setSCL(void);
		void clearSCL(void);
		void setSDA(void);
		void clearSDA(void);
		
		//i2c specific functions
		bool I2CReadBit(void);
		void I2CWriteBit(bool);
		int I2CWriteByte(bool, bool, unsigned char);
		unsigned char I2CReadByte(bool, bool);
		void I2CStart(void);
		void I2CStop(void);
		void I2CDelay(void);
		
		I2C();
		~I2C();
	
};

//Default Constructor
I2C::I2C(){
	cout<<"I2C Constructor"<<endl;
	this->SDA = 8;
	this->SCL = 9;
	this->started = false;
}

//Default Destructor
I2C::~I2C(){
	cout<<"I2C Destructor"<<endl;
}

void I2C::I2CInit(void){
	//Always starting in master mode
	pinMode(this->SCL, OUTPUT);
	pinMode(this->SDA, OUTPUT);
}

bool I2C::readSCL(void){
	pinMode(this->SCL, INPUT);
	return(digitalRead(this->SCL));
}

bool I2C::readSDA(void){
	pinMode(this->SDA, INPUT);
	return(digitalRead(this->SDA));
}

void I2C::setSCL(void){
	pinMode(this->SCL, OUTPUT);
	digitalWrite(this->SCL, HIGH);
}

void I2C::clearSCL(void){
	pinMode(this->SCL, OUTPUT);
	digitalWrite(this->SCL, LOW);
}

void I2C::setSDA(void){
	pinMode(this->SDA, OUTPUT);
	digitalWrite(this->SDA, HIGH);
}

void I2C::clearSDA(void){
	pinMode(this->SDA, OUTPUT);
	digitalWrite(this->SDA, LOW);
	
}

void I2C::I2CStart(void){
	
	if(started){
		cout<<"Set SDA"<<endl;
		this->setSDA();
		delay(500);
		cout<<"Set SCL"<<endl;
		this->setSCL();
		delay(500);
	}
	
	cout<<"Clear SDA"<<endl;
	this->clearSDA();
	delay(500);
	cout<<"Clear SCL"<<endl;
	this->clearSCL();
	this->started = true;
}

bool I2C::I2CReadBit(void){
	bool bit;
	
	this->setSDA();
	delay(100);
	this->setSCL();
	
	delay(100);
	
	bit = this->readSDA();
	
	this->clearSCL();
	
	return(bit);
}





int main(void){

	cout<<"Begin..."<<endl;
	//Create the i2c bus
	I2C* i2cBus = new I2C;
	
	wiringPiSetup();
	i2cBus->I2CInit();//Sets the SDA and SCL lines as outputs
	delay(500);
	int counter = 0;
	char value = 0;
	while(1){
		if(counter%7 == 0){
			cout<<endl;
		}
		value = i2cBus->I2CReadBit();
		if(value == 0){
			cout<<"0";
		}else if (value == 1){
			cout<<"1";
		}
		delay(500);
	}
}
