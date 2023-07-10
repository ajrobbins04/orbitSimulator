

#ifndef gpsLeft_h
#define gpsLeft_h


#include "satellitePiece.h"

class GPSLeft : public SatellitePiece
{
public:
	 
	GPSLeft() : SatellitePiece() {}
	GPSLeft(const Satellite &s, double degrees) : SatellitePiece(s, degrees, 8.0)  // radius = 8 px.
	{
		pos.addPixelsY(4.0); // moves GPSLeft 4px. from its point of creation
		velocity.setSpeed(velocity.getDx() + random(5000, 9000), velocity.getDy() + random(5000, 9000));
	}
	
	virtual ~GPSLeft() {}
	
	virtual bool isShip()       const { return false; }
	virtual bool isProjectile() const { return false; }
	virtual bool isPiece()      const { return true;  }
	virtual bool isFragment()   const { return false; }
	
	virtual void move(double time)
	{
		Acceleration aGravity = getGravity();
		
		velocity.updateVelocity(aGravity, time);
		updatePosition(aGravity, time);
	}
	
	virtual void destroy(vector<Satellite*> &satellites)
	{
		kill();
	}
	
	virtual void draw(double rotation, ogstream & gout)
	{
		gout.drawGPSLeft(getPos(), rotation);
	}
};

#endif /* gpsLeft_h */
