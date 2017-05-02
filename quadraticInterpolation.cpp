#include<windows.h>
#include<iostream>
using namespace std;



int main(void){
	RECT rect4;
	rect4.left = 1000;
	rect4.top = 100;
	rect4.right = 1050;
	rect4.bottom = 150;
	HBRUSH myBrush;
	double red, green, blue;
	int RGB;
	//Get a console handle
    HWND myconsole = GetConsoleWindow();
    //Get a handle to device context
    HDC mydc = GetDC(myconsole);
	
	for(int i = 0; i < 510; i++){
		rect4.left = i;
		rect4.top = 100;
		rect4.right = i +1;
		rect4.bottom = 150;
		
		RGB = i;
		if(RGB < 255){
			blue = (-1/255)*(RGB)^2 + 255;
			green = (-1/255)*(RGB - 255)^2 + 255;
			red = 0;
		}else if(RGB >=255){
			blue = 0;
			green = (-1/255)*(RGB - 255)^2 + 255;
			red = (-1/255)*(RGB - 510)^2 + 255;
		}
		
		myBrush = CreateSolidBrush(RGB(blue, green, red));
		FillRect(mydc, &rect4, myBrush);
		DeleteObject(myBrush);
		
	}
	
}