#include "CarGraphics.h"
#include <iostream>
#include <vector>
using namespace std;

/*****************************************************************************

*****************************************************************************/

/*****************************************************************************
							BaseGraphics
*****************************************************************************/
BaseGraphics::BaseGraphics(){
	//Set a random starting point. If I knew more about consoles and 
	//graphics in general I would grab the midpoint of their window.
	this->x = 500;
	this->y = 500;
}

BaseGraphics::BaseGraphics(int _x, int _y){
	this->x = _x;
	this->y = _y;
}

void BaseGraphics::move(int _x, int _y){
	this->x = _x;
	this->y = _y;
}

/*****************************************************************************
							CarGraphics
*****************************************************************************/
CarGraphics::CarGraphics() : BaseGraphics(){
	this->flRectSize = 50;
	this->frRectSize = 50;
	this->rlRectSize = 50;
	this->rrRectSize = 50;
	this->xCord_offsetStart = 200;
	this->yCord_offsetStart = 200;
	
	this->setDataFrontLeft(0,0,0);
	this->setDataFrontRight(0,0,0);
	this->setDataRearLeft(0,0,0);
	this->setDataRearRight(0,0,0);
	
	this->updateGradients();
	this->updateRectangles();
	this->tempLow = 0;
	this->tempHigh = 110;
	
}

CarGraphics::CarGraphics(int x, int y, int size, int xOffset, int yOffset) : BaseGraphics(x, y){
	this->flRectSize = size;
	this->frRectSize = size;
	this->rlRectSize = size;
	this->rrRectSize = size;
	
	this->xCord_offsetStart = xOffset;
	this->yCord_offsetStart = yOffset;
	
	this->setDataFrontLeft(0,0,0);
	this->setDataFrontRight(0,0,0);
	this->setDataRearLeft(0,0,0);
	this->setDataRearRight(0,0,0);
	
	
	this->updateGradients();
	this->updateRectangles();
	this->tempLow = 0;
	this->tempHigh = 110;
}

void CarGraphics::setDataFrontLeft(double outer, double middle, double inner){
	this->flDataPointOutside = outer - this->tempLow;
	this->flDataPointMiddle = middle - this->tempLow;
	this->flDataPointInside = inner - this->tempLow;
	this->updateGradients();
}

void CarGraphics::setDataFrontRight(double outer, double middle, double inner){
	this->frDataPointOutside = outer - this->tempLow;
	this->frDataPointMiddle = middle - this->tempLow;
	this->frDataPointInside = inner - this->tempLow;
	this->updateGradients();
}

void CarGraphics::setDataRearLeft(double outer, double middle, double inner){
	this->rlDataPointOutside = outer - this->tempLow;
	this->rlDataPointMiddle = middle - this->tempLow;
	this->rlDataPointInside = inner - this->tempLow;
	this->updateGradients();
}
void CarGraphics::setDataRearRight(double outer, double middle, double inner){
	this->rrDataPointOutside = outer - this->tempLow;
	this->rrDataPointMiddle = middle - this->tempLow;
	this->rrDataPointInside = inner - this->tempLow;
	this->updateGradients();
}

void CarGraphics::move(int nx, int ny){
	this->x = nx;
	this->y = ny;
	this->updateGradients();
	this->updateRectangles();
}

vector<double> CarGraphics::calculateGradient(double point1, double point2, double point3, int rectSize){
	double slope1, slope2, slope3, slope4;
	double quaterRect = rectSize / 4;
	double halfRect = rectSize / 2;
	double threeQuaterRect = rectSize *((double)(3) / (double)(4));
	vector<double> slopes;
	slope1 = (0 - point1) / (0 - quaterRect);
	slope2 = (point1 - point2) / (quaterRect - halfRect);
	slope3 = (point2 - point3) / (halfRect - threeQuaterRect);
	slope4 = (point3 - 0) / (threeQuaterRect - rectSize);
	
	slopes.push_back(slope1);
	slopes.push_back(slope2);
	slopes.push_back(slope3);
	slopes.push_back(slope4);
	return(slopes);
}

void CarGraphics::updateRectangles(void){
	this->frontLeft.left = this->x - this->xCord_offsetStart;
	this->frontLeft.right = this->frontLeft.left + 1;
	this->frontLeft.top = this->y - this->yCord_offsetStart;
	this->frontLeft.bottom = this->frontLeft.top + this->flRectSize;
	
	this->frontRight.left = this->x + this->xCord_offsetStart;
	this->frontRight.right = this->frontRight.left + 1;
	this->frontRight.top = this->y - this->yCord_offsetStart;
	this->frontRight.bottom = this->frontRight.top + this->frRectSize;
	
	this->rearLeft.left = this->x - this->xCord_offsetStart;
	this->rearLeft.right = this->rearLeft.left + 1;
	this->rearLeft.top = this->y + this->yCord_offsetStart;
	this->rearLeft.bottom = this->rearLeft.top + this->rlRectSize;
	
	this->rearRight.left = this->x + this->xCord_offsetStart;
	this->rearRight.right = this->rearRight.left + 1;
	this->rearRight.top = this->y + this->yCord_offsetStart;
	this->rearRight.bottom = this->rearRight.top + this->rrRectSize;
}

void CarGraphics::updateGradients(void){
	this->flGradient = this->calculateGradient(this->flDataPointOutside,
												this->flDataPointMiddle,
												this->flDataPointInside,
												this->flRectSize);
							
	this->frGradient = this->calculateGradient(this->frDataPointOutside,
												this->frDataPointMiddle,
												this->frDataPointInside,
												this->frRectSize);
											
	this->rlGradient = this->calculateGradient(this->rlDataPointOutside,
												this->rlDataPointMiddle,
												this->rlDataPointInside,
												this->rlRectSize);
												
	this->rrGradient = this->calculateGradient(this->rrDataPointOutside,
												this->rrDataPointMiddle,
												this->rrDataPointInside,
												this->rrRectSize);
}

void CarGraphics::resize(int newSize){
	this->flRectSize = newSize;
	this->frRectSize = newSize;
	this->rlRectSize = newSize;
	this->rrRectSize = newSize;
	
	this->updateGradients();
	this->updateRectangles();
}

void CarGraphics::flResize(int newSize){
	this->flRectSize = newSize;
	this->updateGradients();
	this->updateRectangles();
}

void CarGraphics::frResize(int newSize){
	this->frRectSize = newSize;
	this->updateGradients();
	this->updateRectangles();
}

void CarGraphics::rlResize(int newSize){
	this->rlRectSize = newSize;
	this->updateGradients();
	this->updateRectangles();
}

void CarGraphics::rrResize(int newSize){
	this->rrRectSize = newSize;
	this->updateGradients();
	this->updateRectangles();
}

void CarGraphics::horizontalShift(int dx){
	this->x = this->x + dx;
	this->updateRectangles();
}

void CarGraphics::verticalShift(int dy){
	this->y = this->y + dy;
	this->updateRectangles();
}

void CarGraphics::setRange(int low, int high){
	this->tempLow = low;
	this->tempHigh = high;
	this->updateGradients();
}

void CarGraphics::updateOffset(int nx, int ny){
	this->xCord_offsetStart = nx;
	this->yCord_offsetStart = ny;
	this->updateGradients();
	this->updateRectangles();
}
//Need to implement a moving of rectangles.**********************************************


void CarGraphics::drawGraphics(HDC* mydc){
	HBRUSH myBrush;
	RECT tempRect;
	
	double flQuaterRect = this->flRectSize / 4;
	double flHalfRect = this->flRectSize / 2;
	double flThreeQuaterRect = this->flRectSize *((double)(3) / (double)(4));
	
	double frQuaterRect = this->frRectSize / 4;
	double frHalfRect = this->frRectSize / 2;
	double frThreeQuaterRect = this->frRectSize *((double)(3) / (double)(4));
	
	double rlQuaterRect = this->rlRectSize / 4;
	double rlHalfRect = this->rlRectSize / 2;
	double rlThreeQuaterRect = this->rlRectSize *((double)(3) / (double)(4));
	
	double rrQuaterRect = this->rrRectSize / 4;
	double rrHalfRect = this->rrRectSize / 2;
	double rrThreeQuaterRect = this->rrRectSize *((double)(3) / (double)(4));
	
	int red, green, blue;
	int RGB;
	int tempRange = this->tempHigh - this->tempLow;
	for(double i = 0; i < this->flRectSize; i++){
		
		//FrontLeft
		tempRect.left = i + this->frontLeft.left;
		tempRect.top = this->frontLeft.top;
		tempRect.right = tempRect.left + 1;
		tempRect.bottom = this->frontLeft.bottom;
	
		if(i <= flQuaterRect){
			RGB = (510/tempRange)*(0 +(this->flGradient[0] * i));
		}
		else if(i > flQuaterRect && i <= flHalfRect){
			RGB = (510/tempRange)*(this->flDataPointOutside + (this->flGradient[1] *(i - flQuaterRect)));
		}
		else if(i > flHalfRect && i <= flThreeQuaterRect){
			RGB = (510/tempRange)*(this->flDataPointMiddle + (this->flGradient[2] *(i - flHalfRect)));
		}
		else if(i > flThreeQuaterRect){
			RGB = (510/tempRange)*(this->flDataPointInside + (this->flGradient[3] *(i - flThreeQuaterRect)));
		}
		
	    //cout<<"\n "<<i<<" "<<RGB;
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
		FillRect(*mydc, &tempRect, myBrush);
		DeleteObject(myBrush);
	}
	for(double i = 0; i < this->frRectSize; i++){
		//Front Right
		tempRect.left = i + this->frontRight.left;
		tempRect.top = this->frontRight.top;
		tempRect.right = tempRect.left + 1;
		tempRect.bottom = this->frontRight.bottom;
	
		if(i <= frQuaterRect){
			RGB = (510/tempRange)*(0 +(this->frGradient[0] * i));
		}
		else if(i > frQuaterRect && i <= frHalfRect){
			RGB = (510/tempRange)*(this->frDataPointOutside + (this->frGradient[1] *(i - frQuaterRect)));
		}
		else if(i > frHalfRect && i <= frThreeQuaterRect){
			RGB = (510/tempRange)*(this->frDataPointMiddle + (this->frGradient[2] *(i - frHalfRect)));
		}
		else if(i > frThreeQuaterRect){
			RGB = (510/tempRange)*(this->frDataPointInside + (this->frGradient[3] *(i - frThreeQuaterRect)));
		}
		
	    //cout<<"\n "<<i<<" "<<RGB;
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
		FillRect(*mydc, &tempRect, myBrush);
		DeleteObject(myBrush);
	}
	for(double i = 0; i < this->rlRectSize; i++){
		
		//Rear Left
		tempRect.left = i + this->rearLeft.left;
		tempRect.top = this->rearLeft.top;
		tempRect.right = tempRect.left + 1;
		tempRect.bottom = this->rearLeft.bottom;
	
		if(i <= rlQuaterRect){
			RGB = (510/tempRange)*(0 +(this->rlGradient[0] * i));
		}
		else if(i > rlQuaterRect && i <= rlHalfRect){
			RGB = (510/tempRange)*(this->rlDataPointOutside + (this->rlGradient[1] *(i - rlQuaterRect)));
		}
		else if(i > rlHalfRect && i <= rlThreeQuaterRect){
			RGB = (510/tempRange)*(this->rlDataPointMiddle + (this->rlGradient[2] *(i - rlHalfRect)));
		}
		else if(i > rlThreeQuaterRect){
			RGB = (510/tempRange)*(this->rlDataPointInside + (this->rlGradient[3] *(i - rlThreeQuaterRect)));
		}
		
	    //cout<<"\n "<<i<<" "<<RGB;
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
		FillRect(*mydc, &tempRect, myBrush);
		DeleteObject(myBrush);
	}
	for(double i = 0; i < this->rrRectSize; i++){
		//Rear right
		tempRect.left = i + this->rearRight.left;
		tempRect.top = this->rearRight.top;
		tempRect.right = tempRect.left + 1;
		tempRect.bottom = this->rearRight.bottom;
	
		if(i <= rrQuaterRect){
			RGB = (510/tempRange)*(0 +(this->rrGradient[0] * i));
		}
		else if(i > rrQuaterRect && i <= rrHalfRect){
			RGB = (510/tempRange)*(this->rrDataPointOutside + (this->rrGradient[1] *(i - rrQuaterRect)));
		}
		else if(i > rrHalfRect && i <= rrThreeQuaterRect){
			RGB = (510/tempRange)*(this->rrDataPointMiddle + (this->rrGradient[2] *(i - rrHalfRect)));
		}
		else if(i > rrThreeQuaterRect){
			RGB = (510/tempRange)*(this->rrDataPointInside + (this->rrGradient[3] *(i - rrThreeQuaterRect)));
		}
		
	    //cout<<"\n "<<i<<" "<<RGB;
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
		FillRect(*mydc, &tempRect, myBrush);
		DeleteObject(myBrush);
		
	}
}

/*****************************************************************************
							Real Time Graphics
*****************************************************************************/
RealTimeGraphics::RealTimeGraphics() : BaseGraphics(){
	this->length = 300;
	this->width = 100;
	
	this->outsideDataPoint = 0;
	this->middleDataPoint = 0;
	this->insideDataPoint = 0;
	
	this->tempLow = 0;
	this->tempHigh = 110;
	
	updateRectangle();
	updateGradient();
	
}

void RealTimeGraphics::setData(double value1, double value2, double value3){
	this->outsideDataPoint = value1;
	this->middleDataPoint = value2;
	this->insideDataPoint = value3;
	updateGradient();
	updateRectangle();
}

vector<double> RealTimeGraphics::calculateGradient(double point1, double point2, double point3, int size){
	double slope1, slope2, slope3, slope4;
	double quaterRect = size / 4;
	double halfRect = size / 2;
	double threeQuaterRect = size *((double)(3) / (double)(4));
	vector<double> slopes;
	slope1 = (0 - point1) / (0 - quaterRect);
	slope2 = (point1 - point2) / (quaterRect - halfRect);
	slope3 = (point2 - point3) / (halfRect - threeQuaterRect);
	slope4 = (point3 - 0) / (threeQuaterRect - size);
	
	slopes.push_back(slope1);
	slopes.push_back(slope2);
	slopes.push_back(slope3);
	slopes.push_back(slope4);
	return(slopes);
}

void RealTimeGraphics::updateRectangle(void){
	this->rectangle.left = this->x;
	this->rectangle.right = this->rectangle.left + 1;
	this->rectangle.top = this->y;
	this->rectangle.bottom = this->rectangle.top + this->width;
}

void RealTimeGraphics::updateGradient(void){
	this->gradient = this->calculateGradient(this->outsideDataPoint,
												this->middleDataPoint,
												this->insideDataPoint,
												this->length);
}

void RealTimeGraphics::resize(int nLength, int nWidth){
	this->length = nLength;
	this->width = nWidth;
	updateGradient();
	updateRectangle();
}

void RealTimeGraphics::horizontalShift(int dx){
	this->x = this->x + dx;
	updateRectangle();
}

void RealTimeGraphics::verticalShift(int dy){
	this->y = this->y + dy;
	updateRectangle();
}

void RealTimeGraphics::setRange(int low, int high){
	this->tempLow = low;
	this->tempHigh = high;
	updateGradient();
}

void RealTimeGraphics::move(int nx, int ny){
	this->x = nx;
	this->y = ny;
	updateRectangle();
	updateGradient();
}

void RealTimeGraphics::draw(HDC* mydc){
	double quaterRect = this->length / 4;
	double halfRect = this->length / 2;
	double threeQuaterRect = this->length *((double)(3) / (double)(4));
	int red, blue, green;
	int RGB;
	RECT tempRect = this->rectangle;
	HBRUSH myBrush;
	int tempRange = this->tempHigh - this->tempLow;
	
	for(double i = 0; i < this->length; i++){
		//Front Right
		tempRect.left = i + this->rectangle.left;
		tempRect.top = this->rectangle.top;
		tempRect.right = tempRect.left + 1;
		tempRect.bottom = this->rectangle.bottom;
	
		if(i <= quaterRect){
			RGB = (510/tempRange)*(0 +(this->gradient[0] * i));
		}
		else if(i > quaterRect && i <= halfRect){
			RGB = (510/tempRange)*(this->outsideDataPoint + (this->gradient[1] *(i - quaterRect)));
		}
		else if(i > halfRect && i <= threeQuaterRect){
			RGB = (510/tempRange)*(this->middleDataPoint + (this->gradient[2] *(i - halfRect)));
		}
		else if(i > threeQuaterRect){
			RGB = (510/tempRange)*(this->insideDataPoint + (this->gradient[3] *(i - threeQuaterRect)));
		}
		
	    //cout<<"\n "<<i<<" "<<RGB;
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
		FillRect(*mydc, &tempRect, myBrush);
		DeleteObject(myBrush);
	}
}
