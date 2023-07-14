#ifndef hubbleTelescope_h
#define hubbleTelescope_h

#include "satellitePiece.h"

class HubbleTelescope : public SatellitePiece
{
public:
	 
	HubbleTelescope() : SatellitePiece() {}
	HubbleTelescope(const Satellite &s, double degrees) : SatellitePiece(s, degrees, 10.0) // radius = 10 px.
	{
		setInvisible(true);
		explode();
	}
	
	virtual ~HubbleTelescope() {}
	
	virtual bool isShip()       const { return false; }
	virtual bool isProjectile() const { return false; }
	virtual bool isPiece()      const { return true;  }
	virtual bool isFragment()   const { return false; }
	
	virtual void move(double time)
	{
		if (age >= 3)
			setInvisible(false);
		
		Acceleration aGravity = getGravity();
		velocity.updateVelocity(aGravity, time);
		updatePosition(aGravity, time);
		
		increaseAge();
	}
	
	// breaks into 3 fragments
	virtual void destroy(list<Satellite*> &satellites)
	{
		SatelliteFragment *sFragment1 = new SatelliteFragment(*this, 230);
		satellites.push_back(sFragment1);
		
		SatelliteFragment *sFragment2 = new SatelliteFragment(*this, 10);
		satellites.push_back(sFragment2);
		
		SatelliteFragment *sFragment3 = new SatelliteFragment(*this, 150);
		satellites.push_back(sFragment3);
	}
	
	virtual void draw(ogstream & gout)
	{
		gout.drawHubbleTelescope(getPos(), getAngularVelocity());
	}
};

#endif /* hubbleTelescope_h */
