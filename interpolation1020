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
	int red, green, blue;
	int RGB;
	//Get a console handle
    HWND myconsole = GetConsoleWindow();
    //Get a handle to device context
    HDC mydc = GetDC(myconsole);
	
	for(int i = 0; i < 1020; i++){
		rect4.left = i;
		rect4.top = 100;
		rect4.right = i +1;
		rect4.bottom = 150;
		
		RGB = i;
		if(RGB <= 255){
			blue = (-RGB) + 255;
			red = 0;
			green = 0;
		}else if(RGB >= 255 && RGB <=510){
			blue = 0;
			green = (RGB) - 510;
			red = 0;
		}else if(RGB >510 && RGB <= 765){
			blue = 0;
			red = 0;
			green = (-RGB) + 510;
		}else if(RGB >= 765){
			blue = 0;
			green = 0;
			red = RGB - 1020;
		}
		
		myBrush = CreateSolidBrush(RGB(red, green, blue));
		FillRect(mydc, &rect4, myBrush);
		
	}
	
}