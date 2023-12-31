/***********************************************************************
 * Header File:
 *    GPS
 * Author:
 *    Amber Robbins, Martin Nkala
 * Summary:
 *	  GPS is a whole satellite, and thus inherits from
 *	  the Satellite class.
 ************************************************************************/

#ifndef gps_h
#define gps_h

#include "satellite.h"
#include "satelliteFragment.h"
#include "gpsCenter.h"
#include "gpsLeft.h"
#include "gpsRight.h"

class GPS : public Satellite
{
public:

	GPS(int idNum): Satellite() {

		switch (idNum) {
				
			case 1:
			{
				pos.setMeters(0.0, 26560000.0);
				velocity.setDxDy(-3880, 0.0);
				setRadius(pos.convertToMeters(12));
				break;
			}
				
			case 2:
			{
				pos.setMeters(23001634.72, 13280000.0);
				velocity.setDxDy(-1940.0, 3360.18);
				setRadius(pos.convertToMeters(12));
				break;
			}
				
			case 3:
			{
				pos.setMeters(23001634.72, -13280000.0);
				velocity.setDxDy(1940, 3360.18);
				setRadius(pos.convertToMeters(12));
				break;
			}
				
			case 4:
			{
				pos.setMeters(0.0, -26560000.0);
				velocity.setDxDy(3880.0, 0.0);
				setRadius(pos.convertToMeters(12));
				break;
			}
				
			case 5:
			{
				pos.setMeters(-23001634.72, -13280000.0);
				velocity.setDxDy(1940.0, -3360.18);
				setRadius(pos.convertToMeters(12));
				break;
			}
				
			case 6:
			{
				pos.setMeters(-23001634.72, 13280000.0);
				velocity.setDxDy(-1940.0, -3360.18);
				setRadius(pos.convertToMeters(12));
				break;
			}
			default:
			{
				pos.setMeters(0.0, 0.0);
				velocity.setDxDy(0.0, 0.0);
				setRadius(pos.convertToMeters(12));
			}
		}
	}
	
	GPS(const GPS &rhs) : Satellite(rhs) {}
	GPS(double x, double y, double radius): Satellite(x, y, radius) {}
	GPS(const Position &pos, const Velocity &velocity): Satellite(pos, 12, velocity) {} // radius = 12 px
 
	
	virtual ~GPS() {}
	
	virtual bool isShip()       const { return false; }
	virtual bool isProjectile() const { return false; }
	virtual bool isPiece()      const { return false; }
	virtual bool isFragment()   const { return false; }
	
	virtual void move(double time)
	{
		Acceleration aGravity = getGravity();
		velocity.updateVelocity(aGravity, time);
		updatePosition(aGravity, time);
		direction.rotate(angularVelocity);
	}
	
	// breaks into 3 pieces & 2 fragments
	virtual void destroy(list<Satellite*> &satellites)
	{
		GPSCenter *gpsCenter = new GPSCenter(*this, random(0, 100));
		satellites.push_back(gpsCenter);
		
		GPSLeft *gpsLeft = new GPSLeft(*this, random(300, 360));
		satellites.push_back(gpsLeft);
		
		GPSRight *gpsRight = new GPSRight(*this, random(150, 2500));
		satellites.push_back(gpsRight);
		
		SatelliteFragment *sFragment1 = new SatelliteFragment(*this, random(300, 360));
		satellites.push_back(sFragment1);
		
		SatelliteFragment *sFragment2 = new SatelliteFragment(*this, random(50, 150));
		satellites.push_back(sFragment2);
	
	}
	
	virtual void draw(ogstream & gout)
	{
		gout.drawGPS(getPos(), getDirectionAngle());
	}

	
private: // inherits pos, direction, radius, angularVelociy, alive,
		 // velocity, age, and lifeSpan
	
};

#endif /* gps_h */
