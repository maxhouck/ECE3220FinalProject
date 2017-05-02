/*
 * main.cpp
 *
 *  Created on: Apr 21, 2017
 *      Author: MizzouRacing
 */
#include<windows.h>
#include "tires.h"
#include<graphics.h>
#include "SerialClass.h"

void programStart(void);
void mainOptionMenu(void);
void dataVisualization(void);
void dataVisualizationWelcomeMessage(void);
void guiSetup(RECT*, RECT*, RECT*, RECT*);
void simulation(Car* car, RECT*, RECT*, RECT*, RECT*);
void realTimeDemo(void);
Car* carSetup(void);


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
	Serial* SP = new Serial("COM4");
	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	HBRUSH myBrush;
	int red, blue, green;
	int RGB;
	/*
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
	}*/
	
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
	int data1Hold, data2Hold, data3Hold;
	int slope1, slope2;
	RECT rectangle1;
	while(1)
	{
		data1Hold = data1;
		data2Hold = data2;
		data3Hold = data3;
		readResult = SP->ReadData(incomingData,dataLength);
		
		token = strtok(incomingData,",");
		data1 = atoi(token);
		token = strtok(NULL, ",");
		data2 = atoi(token);
		token = strtok(NULL, ",");
		data3 = atoi(token);
		if(data1Hold == 0){
			data1 = data1;
		}else if(data1 > data1Hold*1.5 || data1< data1Hold*(2/3)){
			data1 = data1Hold;
		}
		
		if(data2Hold == 0){
			data2 = data2;
		}else if(data2 > data2Hold*1.5 || data2< data2Hold*(2/3)){
			data2 = data2Hold;
		}
		
		if(data3Hold == 0){
			data3 = data3;
		}else if(data3 > data3Hold*1.5 || data3< data3Hold*(2/3)){
			data3 = data3Hold;
		}
		int boxSize = 510;
		slope1 = (data1 - data2) / (0-100);
		slope2 = (data2 - data3) / (100-200);
		for(int x = 0; x < boxSize; x++){
			//Front left
			rectangle1.left = x + 500;
			rectangle1.top = 300;
			rectangle1.right = rectangle1.left + 1;
			rectangle1.bottom = rectangle1.top - boxSize;
			if(x <= boxSize/2){
				RGB = (510/55)*(data1 +(slope1 * x));
			}else if(x > boxSize/2){
				RGB = (510/55)*(data2 +(slope2 *(x-(boxSize/2))));
			}
			//cout<<" "<<RGB;
			if(RGB <= 255){
				blue = (-RGB) + 255;
				red = 0;
				green = (RGB);
			}else if(RGB >= 255){
				blue = 0;
				green = (-RGB) + 510;
				red = (RGB) - 255;
			}
			myBrush = CreateSolidBrush(RGB(red, green, blue));
			FillRect(mydc, &rectangle1, myBrush);
			DeleteObject(myBrush);
			
			
		}
		Sleep(100);
	}
	
}

void dataVisualization(void){
	string userInput;
	int pixel = 0;
	RECT rectangle1;
	RECT* frontLeft = &rectangle1;
	RECT rectangle2;
	RECT* frontRight = &rectangle2;
	RECT rectangle3;
	RECT* rearLeft = &rectangle3;
	RECT rectangle4;
	RECT* rearRight = &rectangle4;
	
	Car* car = carSetup();
	
	cout<<"\n Car creation and GUI setup complete.\nPress any key to continue"<<endl;
	
	getline(cin, userInput);
	
	simulation(car, frontLeft, frontRight, rearLeft, rearRight);
	
	delete car;
	
}


void simulation(Car* car, RECT* fl, RECT* fr, RECT* rl, RECT* rr){
	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	HBRUSH myBrush;
	int red, blue, green;
	int boxSize = 100;
	int RGB; 
	for(int i = 0; i < car->numDataPoints(); i++){
		double flSlope1 = (double)(car->getTemperature(frontLeft, outer, i) - car->getTemperature(frontLeft, middle, i))/(0-(boxSize/2));
		double flSlope2 = (double)(car->getTemperature(frontLeft, middle, i) - car->getTemperature(frontLeft, inner, i))/((boxSize/2)-(boxSize));
		double frSlope1 = (double)(car->getTemperature(frontRight, outer, i) - car->getTemperature(frontRight, middle, i))/(0-(boxSize/2));
		double frSlope2 = (double)(car->getTemperature(frontRight, middle, i) - car->getTemperature(frontRight, inner, i))/((boxSize/2)-(boxSize));
		double rlSlope1 = (double)(car->getTemperature(rearLeft, outer, i) - car->getTemperature(rearLeft, middle, i))/(0-(boxSize/2));
		double rlSlope2 = (double)(car->getTemperature(rearLeft, middle, i) - car->getTemperature(rearLeft, inner, i))/((boxSize/2)-(boxSize));
		double rrSlope1 = (double)(car->getTemperature(rearRight, outer, i) - car->getTemperature(rearRight, middle, i))/(0-(boxSize/2));
		double rrSlope2 = (double)(car->getTemperature(rearRight, middle, i) - car->getTemperature(rearRight, inner, i))/((boxSize/2)-(boxSize));
		//cout<<endl<<car->getTemperature(frontLeft, outer, i)<<" , "<<car->getTemperature(frontLeft, middle, i)<<" , "<<car->getTemperature(frontLeft, inner, i)<<endl;
		for(int x = 0; x < boxSize; x++){
			
			//Front left
			fl->left = x + 500;
			fl->top = 300;
			fl->right = fl->left + 1;
			fl->bottom = fl->top - boxSize;
			
			if(x <= boxSize/2){
				RGB = (510/110)*(car->getTemperature(frontLeft, outer, i) +(flSlope1 * x));
			}else if(x > boxSize/2){
				RGB = (510/110)*(car->getTemperature(frontLeft, middle, i) +(flSlope2 *(x-(boxSize/2))));
			}
			//cout<<" "<<RGB;
			if(RGB <= 255){
				blue = (-RGB) + 255;
				red = 0;
				green = (RGB);
			}else if(RGB >= 255){
				blue = 0;
				green = (-RGB) + 510;
				red = (RGB) - 255;
			}
			myBrush = CreateSolidBrush(RGB(red, green, blue));
			FillRect(mydc, fl, myBrush);
			DeleteObject(myBrush);
			//Front right
			fr->left = x + 650;
			fr->top = 300;
			fr->right = fr->left+1;
			fr->bottom = fr->top + boxSize;
			
			if(x <= boxSize/2){
				RGB = (510/110)*(car->getTemperature(frontRight, outer, i) +(frSlope1 * x));
			}else if(x > boxSize/2){
				RGB = (510/110)*(car->getTemperature(frontRight, middle, i) +(frSlope2 *(x-(boxSize/2))));
			}
			if(RGB <= 255){
				blue = (-RGB) + 255;
				red = 0;
				green = (RGB);
			}else if(RGB >= 255){
				blue = 0;
				green = (-RGB) + 510;
				red = (RGB) - 255;
			}
			myBrush = CreateSolidBrush(RGB(red, green, blue));
			FillRect(mydc, fr, myBrush);
			DeleteObject(myBrush);
			//Rear left
			rl->left = x + 500;
			rl->top = 450;
			rl->right = rl->left+1;
			rl->bottom = rl->top + boxSize;
			
			if(x <= boxSize/2){
				RGB = (510/110)*(car->getTemperature(rearLeft, outer, i) +(rlSlope1 * x));
			}else if(x > boxSize/2){
				RGB = (510/110)*(car->getTemperature(rearLeft, middle, i) +(rlSlope2 *(x-(boxSize/2))));
			}
			if(RGB <= 255){
				blue = (-RGB) + 255;
				red = 0;
				green = (RGB);
			}else if(RGB >= 255){
				blue = 0;
				green = (-RGB) + 510;
				red = (RGB) - 255;
			}
			myBrush = CreateSolidBrush(RGB(red, green, blue));
			FillRect(mydc, rl, myBrush);
			DeleteObject(myBrush);
			//Rear Right
			rr->left = x + 650;
			rr->top = 450;
			rr->right = rr->left+1;
			rr->bottom = rr->top + boxSize;
			
			if(x <= boxSize/2){
				RGB = (510/110)*(car->getTemperature(rearRight, outer, i) +(rrSlope1 * x));
			}else if(x > boxSize/2){
				RGB = (510/110)*(car->getTemperature(rearRight, middle, i) +(rrSlope2 *(x-(boxSize/2))));
			}
			if(RGB <= 255){
				blue = (-RGB) + 255;
				red = 0;
				green = (RGB);
			}else if(RGB >= 255){
				blue = 0;
				green = (-RGB) + 510;
				red = (RGB) - 255;
			}
			myBrush = CreateSolidBrush(RGB(red, green, blue));
			FillRect(mydc, rr, myBrush);
			DeleteObject(myBrush);
		
		
	
		}
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
	
	cout<<"\n Please enter the name the car : "<<endl;
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