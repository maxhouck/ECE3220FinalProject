#include<windows.h>


#ifndef carGraphics_H
#define carGraphics_H

class BaseGraphics{
	protected:
		int x;
		int y;
	public:
		BaseGraphics();
		virtual ~BaseGrapics(){};
		
		//How do we move?
		void move(int, int);
	
};


class CarGraphics : public BaseGraphics{
	private:
		//What shapes are we using?
		RECT frontLeft, frontRight, rearLeft, rearRight;
		//How big are they?
		int rectSize;
		//Where will they be with respect to the center point?
		int xCord_offsetStart;
		int yCord_offsetStart;
		//What will be displayed inside the shapes?
		double flDataPointOutside, flDataPointMiddle, flDataPointInside;
		double frDataPointOutside, frDataPointMiddle, frDataPointInside;
		double rlDataPointOutside, rlDataPointMiddle, rlDataPointInside;
		double rrDataPointOutside, rrDataPointMiddle, rrDataPointInside;
		double flGradient, frGradient, rlGradient, rrGradient;
		//What will we use to paint with?
		HBRUSH myBrush;
		//What is the range of temperature data?
		int tempLow, tempHigh;
	public:
		CarGraphics();
		~CarGraphics(){};
		
		//How do we initialize the location fields?
		CarGraphics(int size, int xOffset, int yOffset);
		
		//How do we obtain the data fields?
		void setDataFrontLeft(double outer, double middle, double inner);
		void setDataFrontRight(double outer, double middle, double inner);
		void setDataRearLeft(double outer, double middle, double inner);
		void setDataRearRight(double outer, double middle, double inner);
		
		//How do we calculate the gradients?
		double calculateGradient(double point1, double point2, double point3);
		
		//How do we change the shape characteristics?
		void resize(int newSize);
		void horizontalShift(int dx);
		void verticalShift(int dy);
		
		//How do we draw the graphics to the screen?
		void drawGraphics(HWND* myconsole, HDC* mydc); 
	
};

#endif