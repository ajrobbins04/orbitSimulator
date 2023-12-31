/***********************************************************************
 * Header File:
 *    Satellite
 * Author:
 *    Amber Robbins, Martin Nkala
 * Summary:
 *	Represent a whole satellite object in the orbit simulator. A satellite
 *	object can be one of the satellites orbiting the earth, the ship that
 *	shoots projectile, or the projectile itself.
 ************************************************************************/
#ifndef satellite_h
#define satellite_h
 
#include <list>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "velocity.h"
#include "spaceObject.h"

const double EARTH_RADIUS = 6378000;
const double GRAVITY = 9.8067;

class TestSatellite;

class Satellite : public SpaceObject
{
public:
	friend TestSatellite;
	
	Satellite() : SpaceObject(0.0, 0.0), velocity(0.0, 0.0), age(0.0), lifeSpan(0.0), alive(true), invisible(false) {}
	
	Satellite(const Satellite &rhs) : SpaceObject(rhs), velocity(rhs.getVelocity()),
	age(rhs.getAge()), lifeSpan(rhs.getLifeSpan()), alive(true), invisible(rhs.isInvisible())  {}
	
	Satellite(const Satellite &s, const Direction &dir) : SpaceObject(s.pos.getMetersX(), s.pos.getMetersY(), 0.0, Direction(dir.getRadians())), velocity(s.velocity.getDx(), s.velocity.getDy()), age(0.0), lifeSpan(0.0),
	    alive(true), invisible(false){}
	
	Satellite(double x, double y): SpaceObject(Position(x, y), 0.0), velocity(0.0, 0.0),
	age(0.0), lifeSpan(0.0), alive(true), invisible(false) {}
	
	Satellite(double x, double y, double radius): SpaceObject(Position(x, y), radius), velocity(0.0, 0.0),
	age(0.0), lifeSpan(0.0), alive(true), invisible(false) {}
	
	Satellite(const Position &pos, double radius, const Velocity &velocity) :
	SpaceObject(pos, radius), velocity(velocity), age(0.0), lifeSpan(0.0), alive(true), invisible(false) {}
	
	Satellite(const Position &pos, double radius, const Velocity &velocity, const Direction &dir) :
	SpaceObject(pos, radius, dir), velocity(velocity), age(0.0), lifeSpan(0.0), alive(true), invisible(false) {}
	
	virtual ~Satellite() {}
	
	void setVelocity(double dx, double dy)
	{
		velocity.setDx(dx);
		velocity.setDy(dy);
	}
	
	void setInvisible(bool status) { invisible = status;  }
	void setAlive(bool status)     { alive = status;      }
	void kill()                    { this->alive = false; }

	void setLifeSpan(double amount) { this->lifeSpan = amount; }
	void computeAngularVelocity();
	
	Acceleration getGravity();
	Velocity getVelocity()      const { return velocity; }
	double getLifeSpan()        const { return lifeSpan; }
	double getAltitude()        const;
	
	void updatePosition(const Acceleration &acGravity, double time);
	void shiftPosition(double distance);
	void explode(double degrees);
	
	void increaseAge()     { age += 1;   }
	double getAge() const  { return age; }
	
	bool isAlive()      const { return alive;          }
	bool isInvisible()  const { return invisible;      }
	bool pastLifeSpan() const { return age > lifeSpan; }
	
	bool hitEarth()     const { return getAltitude() <= 0; }

	virtual bool isShip()       const = 0;
	virtual bool isProjectile() const = 0;
	virtual bool isPiece()      const = 0;
	virtual bool isFragment()   const = 0;
	
	virtual void move(double time) = 0;
	virtual void destroy(list<Satellite*> &satellites) = 0;
	virtual void draw(ogstream & gout)  = 0;
 
 	
protected: // inherits pos, direction, radius, angularVelociy, and alive
	Velocity velocity;
	double age;
	double lifeSpan;
	bool alive;
	bool invisible;
   
};


#endif /* satellite_h */


