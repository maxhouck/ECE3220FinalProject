/*

	Program to generate some "smooth data"
*/

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
using namespace std;

int main(void){
	int dataPoints = 1000;
	srand(time(NULL));
	ofstream file1("frontRight.txt", ios::out | ios::trunc);;
	if(!file1.is_open()){
		cout<<"\nCould not open the file"<<endl;
		return(1);
	}
	int incrementor= 1;
	int left = 0;
	int mid = 0;
	int right = 0;
	for(int i = 0; i < 500; i ++){
		mid+= incrementor;
		if(mid %110 == 0)
			incrementor*=-1;
		file1<<left<<" , "<<mid<<" , "<<right<<endl;
			
	}
	incrementor= 1;
	mid = 0;
	right = 0;
	left = 0;
	for(int i = 0; i < 500; i++){
		left+= incrementor;
		right+= incrementor;
		if(left %110 == 0)
			incrementor*=-1;
		file1<<left<<" , "<<mid<<" , "<<right<<endl;
	}
	
	file1.close();
}