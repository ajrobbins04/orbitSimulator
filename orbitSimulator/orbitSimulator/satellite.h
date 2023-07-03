/***********************************************************************
 * Header File:
 *    Satellite
 * Author:
 *    Amber Robbins, Martin Nkala
 * Summary:
 *
 ************************************************************************/
#ifndef satellite_h
#define satellite_h
 
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "velocity.h"
#include "spaceObject.h"

const double earthRadius = 6378000;

class TestSatellite;

class Satellite : public SpaceObject
{
public:
	friend TestSatellite;
	
	Satellite() : SpaceObject(0.0, 0.0), velocity(0.0, 0.0), age(0.0), angularVelocity(0.0) {}
	
	Satellite(const Satellite &s, const Direction &dir) : SpaceObject(s.pos.getMetersX(), s.pos.getMetersY(), 0.0, Direction(dir.getRadians())),
	velocity(s.velocity.getDx(), s.velocity.getDy()), age(0.0), angularVelocity(0.0) {}
	
	Satellite(double x, double y): SpaceObject(Position(x, y), 0.0), velocity(0.0, 0.0),
	age(0.0), angularVelocity(0.0)  {}
	
	Satellite(double x, double y, double radius): SpaceObject(Position(x, y), radius), velocity(0.0, 0.0),
	age(0.0), angularVelocity(0.0) {}
	
	Satellite(const Position &pos, float radius, const Velocity &velocity) :
	SpaceObject(pos, radius), velocity(velocity), age(0.0), angularVelocity(0.0)  {}
	
	Satellite(double x, double y, double radius, const Velocity &velocity): SpaceObject(Position(x, y), radius), velocity(velocity),
	age(0.0), angularVelocity(0.0) {}
	
	Satellite(double x, double y, double radius, double dx, double dy): SpaceObject(Position(x, y), radius), velocity(dx, dy),
	age(0.0), angularVelocity(0.0) {}
   
	void setVelocity(double dx, double dy)
	{
		velocity.setDx(dx);
		velocity.setDy(dy);
	}
	
	double getAltitude();
	Acceleration getGravity();
	double getAngularVelocity() { return angularVelocity; }
	
	void addKick();
	void updatePosition(const Acceleration &acGravity, double time);
	void move(double time);
	void destroy();
 
	virtual void draw(double rotation, ogstream & gout) = 0;
//  virtual void destroy();
 
	
protected: // inherits pos, direction, radius, and alive
	Velocity velocity;
	double angularVelocity;
	double age;
   
};


#endif /* satellite_h */


