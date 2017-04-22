#include<windows.h>
#include<iostream>
using namespace std;

void ClearScreen();
int main() 
{
    //Get a console handle
    HWND myconsole = GetConsoleWindow();
    //Get a handle to device context
    HDC mydc = GetDC(myconsole);

    int pixel =0;

    //Choose any color
    COLORREF COLOR= RGB(0,0,255); 
	
	RECT rect1;
	rect1.left = 900;
	rect1.top = 0;
	rect1.right = 950;
	rect1.bottom = 50;
	
	RECT rect2;
	rect2.left = 1000;
	rect2.top = 0;
	rect2.right = 1050;
	rect2.bottom = 50;
	
	RECT rect3;
	rect3.left = 900;
	rect3.top = 100;
	rect3.right = 950;
	rect3.bottom = 150;
	
	RECT rect4;
	rect4.left = 1000;
	rect4.top = 100;
	rect4.right = 1050;
	rect4.bottom = 150;

	HBRUSH myBrush;
	
	for(int i = 0; i < 255; i++){
		myBrush = CreateSolidBrush(RGB(255-i,0,i));
		FillRect(mydc, &rect1, myBrush);
		FillRect(mydc, &rect2, myBrush);
		FillRect(mydc, &rect3, myBrush);
		FillRect(mydc, &rect4, myBrush);
		Sleep(1);
	}
	for(int i = 0; i < 255; i++){
		myBrush = CreateSolidBrush(RGB(i,0,255-i));
		FillRect(mydc, &rect1, myBrush);
		FillRect(mydc, &rect2, myBrush);
		FillRect(mydc, &rect3, myBrush);
		FillRect(mydc, &rect4, myBrush);
		Sleep(1);
	}
	
	int input;
	cin>>input;
	if(input == 1)
    ReleaseDC(myconsole, mydc);
    cin.ignore();
	ClearScreen();
    return 0;
}

void ClearScreen()
  {
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  /* Get the number of cells in the current buffer */
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  /* Fill the entire buffer with spaces */
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Fill the entire buffer with the current colors and attributes */
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Move the cursor home */
  SetConsoleCursorPosition( hStdOut, homeCoords );
  }