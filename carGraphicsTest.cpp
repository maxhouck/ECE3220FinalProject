/*
	Testing of the CarGraphics.cpp
	
*/


#include "carGraphics.h"
#include <iostream>
#include <windows.h>
using namespace std;


int main(void){
	double slope =(50 - 75)/(double)(100 - 150);
	CarGraphics* car = new CarGraphics(1000, 300, 300, 200, 200);
	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	car->setRange(0, 110);
	car->setDataFrontLeft(25, 50, 75);
	car->setDataFrontRight(50, 100, 30);
	car->setDataRearLeft(0, 100, 0);
	car->setDataRearRight(100, 50, 100);
	car->drawGraphics(&mydc);
	delete car;

}