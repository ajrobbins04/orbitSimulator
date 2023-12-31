/***********************************************************************
 * Header File:
 *    Space Object
 * Author:
 *    Amber Robbins, Martin Nkala
 * Summary:
 *
 ************************************************************************/

#ifndef spaceObject_h
#define spaceObject_h

#include <iostream>
#include <string>
#include "position.h"
#include "direction.h"
#include "uiDraw.h"  

using namespace std;

class SpaceObject
{
public:
	SpaceObject(): pos(0.0, 0.0), radius(0.0), direction(0.0), angularVelocity(0.0) {}
	
	SpaceObject(const SpaceObject &rhs) : pos(rhs.getPos()), direction(rhs.getDirection()),
	radius(rhs.getRadius()), angularVelocity(rhs.getAngularVelocity()) {}
	
	SpaceObject(const Position &pos, double radius):
	pos(pos), radius(0.0), direction(0.0), angularVelocity(0.0)
	{
		// Earth's radius = 6378000 meters
		// All other radius values are given in pixels, and must be converted to meters
		if (radius != 6378000)
			setRadius(pos.convertToMeters(radius));
		else
			setRadius(6378000);
	}
	
	SpaceObject(const Position &pos, double radius, const Direction &dir):
	pos(pos), radius(0.0), direction(dir), angularVelocity(0.0)
	{
		if (radius != 6378000)
			setRadius(pos.convertToMeters(radius));
		else
			setRadius(6378000);
	}

	SpaceObject(double x, double y): pos(x, y), radius(0.0), direction(0.0),
	angularVelocity(0.0) {}
	
	SpaceObject(double x, double y, double radius): pos(x, y), radius(0.0),
	direction(0.0), angularVelocity(0.0)
	{
		if (radius != 6378000)
			setRadius(pos.convertToMeters(radius));
		else
			setRadius(6378000);
	}
	
	SpaceObject(double x, double y, double radius, const Direction &dir): pos(x, y), radius(0.0),
	direction(dir), angularVelocity(0.0)
	{
		if (radius != 6378000)
			setRadius(pos.convertToMeters(radius));
		else
			setRadius(6378000);
	}
	
	virtual ~SpaceObject() {}

	void setRadius(double radius)           { this->radius = radius;          }
	void setDirection(const Direction &dir) { this->direction = dir;          }
	void setAngularVelocity(double amount)  { this->angularVelocity = amount; }
	
	void setPosition(double x, double y)
	{
		pos.setMetersX(x);
		pos.setMetersY(y);
	}

	void rotate(double amount)  { this->direction.rotate(amount); }
	
	double getRadius()          const { return radius;           }
	Position getPos()           const { return pos;              }
	double getPosX()            const { return pos.getMetersX(); }
	double getPosY()            const { return pos.getMetersY(); }
	Direction getDirection()    const { return direction;        }
	
	double getDirectionAngle()  const { return direction.getRadians(); }
	double getAngularVelocity() const { return angularVelocity;        }
	
	
	virtual void draw(ogstream & gout) = 0;
	
protected:
	Position pos;
	Direction direction;
	double angularVelocity;
	double radius;
};
 
#endif
