/*
	Program to generate data values for testing
	
*/

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
using namespace std;

int main(void){
	int dataPoints = 1002;
	int value;
	ofstream file1("frontLeft.txt", ios::out | ios::trunc);;
	ofstream file2("rearLeft.txt", ios::out | ios::trunc);;
	ofstream file3("frontRight.txt", ios::out | ios::trunc);;
	ofstream file4("rearRight.txt", ios::out | ios::trunc);;
	srand(time(NULL));
	if(!file1.is_open() || !file2.is_open() || !file3.is_open() || !file4.is_open()){
		cout<<"\nCould not open the file"<<endl;
		return(1);
	}
	
	for(int i = 0; i < dataPoints; i ++){
		for(int x = 0; x < 3; x++){
			
			value = 30 + rand() %80;
			file1<<value;
			if(x == 0 || x == 1){
				file1<<",";
			}
		}
		file1<<"\n";
	}
	
	for(int i = 0; i < dataPoints; i ++){
		for(int x = 0; x < 3; x++){
			
			value = 30 + rand() %80;
			file2<<value;
			if(x == 0 || x == 1){
				file2<<",";
			}
		}
		file2<<"\n";
	}
	
	for(int i = 0; i < dataPoints; i ++){
		for(int x = 0; x < 3; x++){
			
			value = 30 + rand() %80;
			file3<<value;
			if(x == 0 || x == 1){
				file3<<",";
			}
		}
		file3<<"\n";
	}
	
	for(int i = 0; i < dataPoints; i ++){
		for(int x = 0; x < 3; x++){
			
			value = 30 + rand() %80;
			file4<<value;
			if(x == 0 || x == 1){
				file4<<",";
			}
		}
		file4<<"\n";
	}
	file1.close();
	file2.close();
	file3.close();
	file4.close();
}