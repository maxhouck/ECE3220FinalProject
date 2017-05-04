
#include<windows.h>
#include "tires.h"
#include "SerialClass.h"
#include "CarGraphics.h"

#define LOGGING_RATE .1
#define ACCEPTABLE_PERCENTAGE .05

void programStart(void);
void mainOptionMenu(void);
void dataVisualization(void);
void dataVisualizationWelcomeMessage(void);
void simulation(Car* car, CarGraphics*);
void realTimeDemo(void);
Car* carSetup(void);
void graphicsSetup(CarGraphics*);
void graphicsSetupOptionMenu(void);
void realTimeGraphicsSetup(RealTimeGraphics*);
void realTimeGraphicsSetupOptionMenu(void);


int main() {
	try{
		programStart();
	}
	catch(...){
		cout<<"\nProgram Failed. Catch all Main()"<<endl;
		return(1);
	}
}

void programStart(void){
	string userInput;
	for(int i = 0; i < 60; i++){
		cout<<"#";
	}
	cout<<"\n\nFSAE TIRE TEMPERATURE DATA VISUALIZATION SOFTWARE\n"<<endl;
	for(int i = 0; i < 60; i++){
		cout<<"#";
	}
	cout<<"\n\n\nWelcome to version 1 of the FSAE Tire Temperature Visualization Software!"<<endl;
	while(1){
		mainOptionMenu();
		getline(cin, userInput);
	
		if(userInput == "1"){
			realTimeDemo();
		}else if(userInput == "2"){
			dataVisualization();
		}else if(userInput == "3"){
			return;
		}else{
			cout<<"\n Invalid input!"<<endl;
		}
	}
}

void mainOptionMenu(void){
	cout<<"\n\nPlease select from the following options: "
		<<"\n   1)Real time data sensor visualization"
		<<"\n   2)Data visualization from file and video"
		<<"\n   3)Quit"<<endl;
}

void realTimeDemo(void){
	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	RealTimeGraphics* realTime = new RealTimeGraphics();
	realTimeGraphicsSetup(realTime);
	Serial* SP;
	
	while(1){
		try{
			SP = new Serial("COM4"); //We may need to adjust this as necessary
			break;
		}
		catch(const int x){
			if(x == 1){
				cout<<"\n Please connect the arduino!"<<endl;
				Sleep(3000);
			}else if(x == 2){
				cout<<"\n Unknown error!"<<endl;
			}
		}
		catch(...){
			cout<<"\n Catch all realTimeDemo. Should not be here!"<<endl;
		}
	}
	
	if (SP->IsConnected()){
		cout<<"\n Ardiuno Connected!"<<endl;
	}else{
		cout<<"\n Arduino not connected?.. Terminating!"<<endl;
	}
	char* token;
	string incomingDataString;
	char incomingData[256] = "";
	int dataLength = 255;
	int readResult = 0;
	int data1 = 0;
	int data2 = 0;
	int data3 = 0;
	int bufferSize = 5;
	int bufferHold1,bufferHold2;
	int buf1[bufferSize], buf2[bufferSize], buf3[bufferSize];
	int data1Hold, data2Hold, data3Hold;
	int average1,average2,average3, i;
	
	int slope1, slope2, slope3;
	int estimatedPoint1, estimatedPoint2, estimatedPoint3;
	double percentDiff1, percentDiff2, percentDiff3;
	double averageDelta;
	while(1){

		data1Hold = data1;
		data2Hold = data2;
		data3Hold = data3;
		readResult = SP->ReadData(incomingData,dataLength);
		
		token = strtok(incomingData,","); //parsing serial output from arduino
		data1 = atoi(token);
		token = strtok(NULL, ",");
		data2 = atoi(token);
		token = strtok(NULL, ",");
		data3 = atoi(token);

		if(buf1[0] == 0) { //if buffers are empty
			for(i=0;i<bufferSize;i++) {
				buf1[i] = data1; //fill them completely with first value
				buf2[i] = data2;
				buf3[i] = data3;
			}
		}
		int sum = 0; //calculate averages of buffers and error check
		/*
		for(int i=0;i<bufferSize;i++){
			sum+=buf1[i];
		}
		average1 = sum / bufferSize;
		sum = 0;
		for(int i = 0; i < bufferSize; i++){
			sum += buf1[i] - average1;
		}
		averageDelta = sum / buffersize;
		percentDiff1 = (data1 - average1) / averageDelta;
		if(percentDiff1 > ACCEPTABLE_PERCENTAGE && percentDiff1 < (ACCEPTABLE_PERCENTAGE + .01)
			|| percentDiff1 < ACCEPTABLE_PERCENTAGE  && percentDiff1 > (ACCEPTABLE_PERCENTAGE - .01)){
			data1 *= .9;
		}
		if(percentDiff1 > (ACCEPTABLE_PERCENTAGE + .01) && percentDiff1 < (ACCEPTABLE_PERCENTAGE + .05)
			|| percentDiff1 < (ACCEPTABLE_PERCENTAGE - .01)  && percentDiff1 > (ACCEPTABLE_PERCENTAGE - .05)){
			data1 *= .8;
		}
		if(percentDiff1 > (ACCEPTABLE_PERCENTAGE + .05) && percentDiff1 < (ACCEPTABLE_PERCENTAGE + .1)
			|| percentDiff1 < (ACCEPTABLE_PERCENTAGE - .05)  && percentDiff1 > (ACCEPTABLE_PERCENTAGE - .1)){
			data1 *= .6;
		}
		if(percentDiff1 > (ACCEPTABLE_PERCENTAGE + .1) && percentDiff1 < (ACCEPTABLE_PERCENTAGE + .2)
			|| percentDiff1 < (ACCEPTABLE_PERCENTAGE - .1)  && percentDiff1 > (ACCEPTABLE_PERCENTAGE - .2)){
			data1 *= .;
		}
		*/
		sum = 0;
		for(int i=0;i<bufferSize;i++)
			sum+=buf1[i];
		average1 = sum / bufferSize;
		if (data1 > average1 + 10 | data1 < average1 - 10)
			data1 = average1;
		sum = 0;
		for(int i=0;i<bufferSize;i++)
			sum+=buf2[i];
		average2 = sum / bufferSize;
		if (data2 > average2 + 10 | data2 < average2 - 10)
			data2 = average2;
		sum = 0;
		for(int i=0;i<bufferSize;i++)
			sum+=buf3[i];
		average3 = sum / bufferSize;
		if (data3 > average3 + 10 | data3 < average3 - 10)
			data3 = average3;

		
		 //rotate it in the new values to each buffer
		bufferHold1 = buf1[0];
		buf1[0] = data1;
		for(int i=1;i<bufferSize;i++) {
			bufferHold2 = buf1[i];
			buf1[i] = bufferHold1;
			bufferHold1 = bufferHold2;
		}
		bufferHold1 = buf2[0];
		buf2[0] = data2;
		for(int i=1;i<bufferSize;i++) {
			bufferHold2 = buf2[i];
			buf2[i] = bufferHold1;
			bufferHold1 = bufferHold2;
		}
		bufferHold1 = buf3[0];
		buf3[0] = data3;
		for(int i =1;i<bufferSize;i++) {
			bufferHold2 = buf3[i];
			buf3[i] = bufferHold1;
			bufferHold1 = bufferHold2;
		}

		realTime->setData(data1, data2, data3); //output to graphics
		realTime->draw(&mydc);
		Sleep(150);
		}
	delete realTime;
}
	
	

void realTimeGraphicsSetup(RealTimeGraphics* graphics){
	string userInput;
	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	int value;
	while(1){
		
		realTimeGraphicsSetupOptionMenu();
		getline(cin,userInput);
		if(userInput == "1"){
			graphics->draw(&mydc);
			graphics->draw(&mydc);
		}else if(userInput == "2"){
			int value2;
			cout<<"\n Please enter the new X value: "<<endl;
			cin>>value;
			cout<<"\n Please enter the new Y value: "<<endl;
			cin>>value2;
			graphics->move(value, value2);
		}else if(userInput == "3"){
			cout<<"\n Please enter the value you wish to vertically shift the graph by:"<<endl;
			cin>>value;
			graphics->verticalShift(value);
		}else if(userInput == "4"){
			cout<<"\n Please enter the value you wish to horizontally shift the graph by:"<<endl;
			cin>>value;
			graphics->horizontalShift(value);
		}else if(userInput == "5"){
			int value2;
			cout<<"\n Please enter the new length:"<<endl;
			cin>>value;
			cout<<"\n Please enter the new width:"<<endl;
			cin>>value2;
			graphics->resize(value, value2);
		}else if(userInput == "6"){
			int value2;
			cout<<"\n Please enter the lowest temperature:"<<endl;
			cin>>value;
			cout<<"\n Please enter the highest temperature:"<<endl;
			cin>>value2;
			graphics->setRange(value, value2);
		}else if(userInput == "7"){
			break;
		}else{
			cout<<"\n Invalid Input!"<<endl;
		}
	}
	return;
}

void realTimeGraphicsSetupOptionMenu(void){
	cout<<"\n Graphics Setup Options:"
		<<"\n 1)Print"
		<<"\n 2)Move"
		<<"\n 3)Vertical Shift"
		<<"\n 4)Horizontal Shift"
		<<"\n 5)Resize graph"
		<<"\n 6)Set temperature range"
		<<"\n 7)Finish"<<endl;
}

void dataVisualization(void){
	string userInput;
	CarGraphics* graphicsCar = new CarGraphics();
	graphicsSetup(graphicsCar);
	Car* car = carSetup();
			
	cout<<"\n\n\n\n Car creation and GUI setup complete.\nPress any key to continue"<<endl;
	getline(cin, userInput);
	simulation(car, graphicsCar);
	while(1){

		
		cout<<"\n Simulation complete!"
			<<"\n What would you like to do?"
			<<"\n 1)Run the simulation"
			<<"\n 2)Change car data"
			<<"\n 3)Change graphics settings"
			<<"\n 4)Quit to main menu"<<endl;
		getline(cin,userInput);
		
		if(userInput == "1"){
			simulation(car, graphicsCar);
		}else if(userInput == "2"){
			delete car;
			car = carSetup();
		}else if(userInput == "3"){
			graphicsSetup(graphicsCar);
		}else if(userInput == "4"){
			break;
		}
	}
	delete car;
	delete graphicsCar;
	
}

void graphicsSetup(CarGraphics* car){
	string userInput;
	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	int value;
	while(1){
		
		graphicsSetupOptionMenu();
		getline(cin,userInput);
		if(userInput == "1"){
			car->drawGraphics(&mydc);
			car->drawGraphics(&mydc);
			getline(cin, userInput);
		}else if(userInput == "2"){
			int x, y;
			cout<<"\n Please enter the new X value:"<<endl;
			cin>>x;
			cout<<"\n Please enter the new Y value:"<<endl;
			cin>>y;
			car->move(x, y);
		}else if(userInput == "3"){
			cout<<"\n Please enter the value you wish to shift the object vertically by:"<<endl;
			cin>>value;
			car->verticalShift(value);
		}else if(userInput == "4"){
			cout<<"\n Please enter the value you whish to shift the object horizontally by:"<<endl;
			cin>>value;
			car->horizontalShift(value);
		}else if(userInput == "5"){
			cout<<"\n Please enter the new size for the tires:"<<endl;
			cin>>value;
			car->resize(value);
		}else if(userInput == "6"){
			cout<<"\n Please enter the new size for the front left tire:"<<endl;
			cin>>value;
			car->flResize(value);
		}else if(userInput == "7"){
			cout<<"\n Please enter the new size for the front right tire:"<<endl;
			cin>>value;
			car->frResize(value);
		}else if(userInput == "8"){
			cout<<"\n Please enter the new size for the rear left tire:"<<endl;
			cin>>value;
			car->rlResize(value);
		}else if(userInput == "9"){
			cout<<"\n Please enter the new size for the rear right tire:"<<endl;
			cin>>value;
			car->rrResize(value);
		}else if(userInput == "10"){
			cout<<"\n Please enter the new offset value:"<<endl;
			cin>>value;
			car->updateOffset(value, value);
		}else if(userInput == "11"){
			int value2;
			cout<<"\n Please enter the low temperature:"<<endl;
			cin>>value;
			cout<<"\n Please enter the high temperature:"<<endl;
			cin>>value2;
			car->setRange(value, value2);
		}else if(userInput == "12"){
			break;
		}else{
			cout<<"\nInvalid Input!"<<endl;
		}
	}
	return;
}

void graphicsSetupOptionMenu(void){
	cout<<"\n Graphics Setup Options:"
		<<"\n 1)Print"
		<<"\n 2)Move"
		<<"\n 3)Vertical Shift"
		<<"\n 4)Horizontal Shift"
		<<"\n 5)Resize Every Tire"
		<<"\n 6)Resize Front Left Tire"
		<<"\n 7)Resize Front Right Tire"
		<<"\n 8)Resize Rear Left Tire"
		<<"\n 9)Resize Rear Right Tire"
		<<"\n 10)Increase Offset From MidPoint"
		<<"\n 11)Set temperature range"
		<<"\n 12)Finish"<<endl;
}


void simulation(Car* car, CarGraphics* graphicsCar){
	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	graphicsCar->setRange(0, 110);
	for(int i = 0; i < car->numDataPoints(); i++){
		graphicsCar->setDataFrontLeft(car->getTemperature(frontLeft, outer, i),
										car->getTemperature(frontLeft, middle, i),
										car->getTemperature(frontLeft, inner, i));
		
		graphicsCar->setDataFrontRight(car->getTemperature(frontRight, outer, i),
										car->getTemperature(frontRight, middle, i),
										car->getTemperature(frontRight, inner, i));
		
		graphicsCar->setDataRearLeft(car->getTemperature(rearLeft, outer, i),
										car->getTemperature(rearLeft, middle, i),
										car->getTemperature(rearLeft, inner, i));
		
		graphicsCar->setDataRearRight(car->getTemperature(rearRight, outer, i),
										car->getTemperature(rearRight, middle, i),
										car->getTemperature(rearRight, inner, i));
		graphicsCar->drawGraphics(&mydc);
		Sleep(20);
	
	
	}
}

void dataVisualizationWelcomeMessage(void){
	string input;
	for(int i = 0; i < 60; i++){
		cout<<"-";
	}
	cout<<"\n Setup Wizard"<<endl;
	cout<<"\n This wizard will guide you through the steps to set up your data for"
		<<"\n visualization. Please follow the steps carefully."
		<<"\n Press any key to continue"<<endl;
		
	getline(cin,input);
}

Car* carSetup(void){
	string userInput;
	dataVisualizationWelcomeMessage();
	ifstream dataFile1, dataFile2, dataFile3, dataFile4;
	
	cout<<"\n Please enter the name of the car : "<<endl;
	getline(cin, userInput);
	
	Car* car = new Car(userInput);
	try{
		
		while(1){
			cout<<"\n Please enter the name of the data file for the Front Left Tire: "<<endl;
			getline(cin, userInput);
			if(userInput == "quit"){
				throw(1);
			}
			dataFile1.open((userInput.c_str()), ios::in);
			if(!dataFile1.is_open()){
				cout<<"\n Could not open the file! Please try again or enter 'quit' to exit"<<endl;
			}else{
				break;
			}
		}
	
		while(1){
			cout<<"\n Please enter the name of the data file for the Front Right Tire: "<<endl;
			getline(cin, userInput);
			if(userInput == "quit"){
				dataFile1.close();
				throw(1);
			}
			dataFile2.open((userInput.c_str()), ios::in);
			if(!dataFile2.is_open()){
				cout<<"\n Could not open the file! Please try again or enter 'quit' to exit"<<endl;
			}else{
				break;
			}
		}
	
		while(1){
			cout<<"\n Please enter the name of the data file for the Rear Left Tire: "<<endl;
			getline(cin, userInput);
				if(userInput == "quit"){
					dataFile1.close();
					dataFile2.close();
					throw(1);
				}
			dataFile3.open((userInput.c_str()), ios::in);
			if(!dataFile3.is_open()){
				cout<<"\n Could not open the file! Please try again or enter 'quit' to exit"<<endl;
			}else{
				break;
			}
		}
	
		while(1){
			cout<<"\n Please enter the name of the data file for the Rear Right Tire: "<<endl;
			getline(cin, userInput);
				if(userInput == "quit"){
					dataFile3.close();
					throw(1);
				}
			dataFile4.open((userInput.c_str()), ios::in);
			if(!dataFile4.is_open()){
				cout<<"\n Could not open the file! Please try again or enter 'quit' to exit"<<endl;
			}else{
				break;
			}
		}
		cout<<"\n Please wait while the Car is created and the data imported..."<<endl;
		string line;
		char* token;
		
		//Front left tire creation
		Tire FL(frontLeft, "FrontLeft");
		Sensor FL_Outer("FL_Outer", outer, 0x5A);
		Sensor FL_Middle("FL_Middle", middle, 0x5A);
		Sensor FL_Inner("FL_Inner", inner, 0x5A);
		//Data for the sensor objects.
		while(getline(dataFile1, line)){
			token = strtok((char*)line.c_str(),",");
			FL_Outer.addTemperature(atoi(token));
			token = strtok(NULL, ",");
			FL_Middle.addTemperature(atoi(token));
			token = strtok(NULL, ",");
			FL_Inner.addTemperature(atoi(token));
		}
		dataFile1.close();
		//Add the sensors to the tire
		FL.addSensor(FL_Outer);
		FL.addSensor(FL_Middle);
		FL.addSensor(FL_Inner);
		
		//Front right tire creation
		Tire FR(frontRight, "FrontRight");
		Sensor FR_Outer("FR_Outer", outer, 0x5A);
		Sensor FR_Middle("FR_Middle", middle, 0x5A);
		Sensor FR_Inner("FR_Inner", inner, 0x5A);
		while(getline(dataFile2, line)){
			token = strtok((char*)line.c_str(),",");
			FR_Outer.addTemperature(atoi(token));
			token = strtok(NULL, ",");
			FR_Middle.addTemperature(atoi(token));
			token = strtok(NULL, ",");
			FR_Inner.addTemperature(atoi(token));
		}		
		dataFile2.close();

		//Add the sensors to the tire
		FR.addSensor(FR_Outer);
		FR.addSensor(FR_Middle);
		FR.addSensor(FR_Inner);
		
		//Rear left tire creation
		Tire RL(rearLeft, "RearLeft");
		Sensor RL_Outer("RL_Outer", outer, 0x5A);
		Sensor RL_Middle("RL_Middle", middle, 0x5A);
		Sensor RL_Inner("RL_Inner", inner, 0x5A);
		while(getline(dataFile3, line)){
			token = strtok((char*)line.c_str(),",");
			RL_Outer.addTemperature(atoi(token));
			token = strtok(NULL, ",");
			RL_Middle.addTemperature(atoi(token));
			token = strtok(NULL, ",");
			RL_Inner.addTemperature(atoi(token));
		}
		dataFile3.close();

		//Add the sensors to the tire
		RL.addSensor(RL_Outer);
		RL.addSensor(RL_Middle);
		RL.addSensor(RL_Inner);
		
		//Rear right tire creation
		Tire RR(rearRight, "RearRight");
		Sensor RR_Outer("RR_Outer", outer, 0x5A);
		Sensor RR_Middle("RR_Middle", middle, 0x5A);
		Sensor RR_Inner("RR_Inner", inner, 0x5A);
		while(getline(dataFile4, line)){
			token = strtok((char*)line.c_str(),",");
			RR_Outer.addTemperature(atoi(token));
			token = strtok(NULL, ",");
			RR_Middle.addTemperature(atoi(token));
			token = strtok(NULL, ",");
			RR_Inner.addTemperature(atoi(token));
		}
		dataFile4.close();
		//Add the sensors to the tire
		RR.addSensor(RR_Outer);
		RR.addSensor(RR_Middle);
		RR.addSensor(RR_Inner);
		
		//Add all of the tires to the car
		car->addTire(FL);
		car->addTire(FR);
		car->addTire(RL);
		car->addTire(RR);
		
		return(car);
	}
	catch(...){
		return(NULL);
	}
}
