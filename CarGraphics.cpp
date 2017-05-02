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

void BaseGraphics::move(int dx, int dy){
	this->x = _x
	this->y = _y
}

/*****************************************************************************
							CarGraphics
*****************************************************************************/
CarGraphics::CarGraphics() : BaseGraphics(){
	this->rectSize = 50;
	this->xCord_offsetStart = 100;
	this->yCord_offsetStart = 100;
	
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
	this->rectSize = size;
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
	this->flDataPointOutside = outer;
	this->flDataPointMiddle = middle;
	this->flDataPointInside = inner;
	this->updateGradients();
}

void CarGraphics::setDataFrontRight(double outer, double middle, double inner){
	this->frDataPointOutside = outer;
	this->frDataPointMiddle = middle;
	this->frDataPointInside = inner;
	this->updateGradients();
}

void CarGraphics::setDataRearLeft(double outer, double middle, double inner){
	this->rlDataPointOutside = outer;
	this->rlDataPointMiddle = middle;
	this->rlDataPointInside = inner;
	this->updateGradients();
}
void CarGraphics::setDataRearRight(double outer, double middle, double inner){
	this->rrDataPointOutside = outer;
	this->rrDataPointMiddle = middle;
	this->rrDataPointInside = inner;
	this->updateGradients();
}

vector<double> CarGraphics::calculateGradient(double point1, double point2, double point3){
	double slope1, slope2, slope3, slope4;
	vector<double> slopes;
	slope1 = (this->tempLow - point1) / (0 - (this->rectSize / 4));
	slope2 = (point1 - point2) / ((this->rectSize / 4) - (this->rectSize / 2));
	slope3 = (point2 - point3) / ((this->rectSize /2) - (this->rectSize * 3 / 4));
	slope4 = (point3 - this->tempLow) / ((this->rectSize * 3 / 4) - this->rectSize);
	
	slopes.push_back(slope1);
	slopes.push_back(slope2);
	slopes.push_back(slope3);
	slopes.push_back(slope4);
	return(slopes);
}

void CarGraphics::updateRectangles(void){
	this->frontLeft.left = this->x - this->xCord_offsetStart;
	this->frontLeft.right = this->frontLeft.left + 1;
	this->frontLeft.top = this->y + this->yCord_offsetStart;
	this->frontLeft.bottom = this->frontLeft.top + this->rectSize;
	
	this->frontRight.left = this->x + this->xCord_offsetStart;
	this->frontRight.right = this->frontRight.left + 1;
	this->frontRight.top = this->y + this->yCord_offsetStart;
	this->frontLeft.bottom = this->frontRight.top + this->rectSize;
	
	this->rearLeft.left = this->x - this->xCord_offsetStart;
	this->rearLeft.right = this->rearLeft.left + 1;
	this->rearLeft.top = this->y - this->yCord_offsetStart;
	this->rearLeft.bottom = this->rearLeft.top + this->rectSize;
	
	this->rearRight.left = this->x + this->xCord_offsetStart;
	this->rearRight.right = this->rearRight.left + 1;
	this->rearRight.top = this->y - this->yCord_offsetStart;
	this->rearRight.bottom = this->rearRight.top + this->rectSize;
}

void CarGraphics::updateGradients(void){
	this->flGradient = this->calculateGradient(this->flDataPointOutside,
												this->flDataPointMiddle,
												this->flDataPointInside);
							
	this->frGradient = this->calculateGradient(this->frDataPointOutside,
												this->frDataPointMiddle,
												this->frDataPointInside);
											
	this->rlGradient = this->calculateGradient(this->rlDataPointOutside,
												this->rlDataPointMiddle,
												this->rlDataPointInside);
												
	this->rrGradient = this->calculateGradient(this->rrDataPointOutside,
												this->rrDataPointMiddle,
												this->rrDataPointInside);
}

void CarGraphics::resize(int newSize){
	this->rectSize = newSize;
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

//Need to implement a moving of rectangles.**********************************************


void CarGraphics::drawGraphics(HDC* mydc){
	HBRUSH myBrush;
	int RBG;
	int tempRange = this->tempHigh - this->tempLow;
	for(int x = 0; x < this->rectSize; x++)
		this->frontLeft.left = x + ;
		this->frontLeft.top = 300;
		this->frontLeft.right = this->frontLeft.left + 1;
		this->frontLeft.bottom = this->frontLeft.top + boxSize;
	
		if(x <= boxSize/2){
			RGB = (510/tempRange)*(car->getTemperature(frontLeft, outer, i) +(flSlope1 * x));
		}else if(x > boxSize/2){
			RGB = (510/tempRange)*(car->getTemperature(frontLeft, middle, i) +(flSlope2 *(x-(boxSize/2))));
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
		RGB = (510/tempRange)*(car->getTemperature(frontRight, outer, i) +(frSlope1 * x));
	}else if(x > boxSize/2){
		RGB = (510/tempRange)*(car->getTemperature(frontRight, middle, i) +(frSlope2 *(x-(boxSize/2))));
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
		RGB = (510/tempRange)*(car->getTemperature(rearLeft, outer, i) +(rlSlope1 * x));
	}else if(x > boxSize/2){
		RGB = (510/tempRange)*(car->getTemperature(rearLeft, middle, i) +(rlSlope2 *(x-(boxSize/2))));
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
		RGB = (510/tempRange)*(car->getTemperature(rearRight, outer, i) +(rrSlope1 * x));
	}else if(x > boxSize/2){
		RGB = (510/tempRange)*(car->getTemperature(rearRight, middle, i) +(rrSlope2 *(x-(boxSize/2))));
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