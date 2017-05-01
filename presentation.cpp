#include<windows.h>
#include<iostream>
using namespace std;



int main(void){

	//Get a console handle
    HWND myconsole = GetConsoleWindow();
    //Get a handle to device context
    HDC mydc = GetDC(myconsole);
	//Create a rectangle
	RECT rect;
	rect.left = 900;
	rect.top = 0;
	rect.right = 950;
	rect.bottom = 50;
	//Brush object
	HBRUSH myBrush;
	int red, green, blue;
	//Set RGB values
	red = 255;
	green = 0;
	blue = 0;
	//Create a solid brush with the color (255, 0, 0);
	myBrush = CreateSolidBrush(RGB(red, green, blue));
	//Fill the rectangle with the solid brush.
	FillRect(mydc, &rect, myBrush);
}