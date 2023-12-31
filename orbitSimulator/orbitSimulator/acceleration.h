/***********************************************************************
 * Header File:
 *    Acceleration
 * Author:
 *	  Amber Robbins, Martin Nkala
 * Summary:
 *
 ************************************************************************/

#ifndef acceleration_h
#define acceleration_h

#include <iostream>
#include "direction.h"

class TestAcceleration;

using namespace std;

class Acceleration
{
public:
	friend TestAcceleration;
	
	Acceleration(): ddx(0.0), ddy(0.0) {}
	Acceleration(double ddx, double ddy): ddx(ddx), ddy(ddy) {}
	Acceleration(double acc, const Direction &dir): ddx(0.0), ddy(0.0)
	{
		setAccelerationDirection(acc, dir);
	}
	
	void setAccelerationDirection(double acc, const Direction &dir);
	void setDDx(double ddx) { this->ddx = ddx; }
	void setDDy(double ddy) { this->ddy = ddy; }
	
	double getDDx() const { return ddx; }
	double getDDy() const { return ddy; }
   
private:
	double ddx; // change in change in x
	double ddy; // change in change in y
   
};

#endif /* acceleration_h */

