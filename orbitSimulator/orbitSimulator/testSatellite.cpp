#include "testSatellite.h"

/*********************************************
 * RUN
 * Runs all test cases.
 *********************************************/
void TestSatellite::run()
{
	test_constructor_stationaryNorth();
	
	test_getAltitude_surface();
	test_getAltitude_xAxis();
	test_getAltitude_yAxis();
	
	test_getGravity_surface();
	test_getGravity_500k();
	test_getGravity_2000k();
	
	test_updateVelocity_stationary();
	test_updateVelocity_moving();
	test_updateVelocity_accFromStop();
	test_updateVelocity_accFromStop_longer();
	test_updateVelocity_complex();

	test_updatePosition_stationary();
	test_updatePosition_moving();
	test_updatePosition_movingLonger();
	test_updatePosition_fromStop();
	test_updatePosition_fromStop_longer();
	test_updatePosition_complex();
}

/*********************************************
 * CLOSE ENOUGH
 * Determines if the difference between the actual result and
 * the expected result is within the given tolerance range.
 *********************************************/
bool TestSatellite::closeEnough(double actual, double expected, double tolerance)
{
	double difference = actual - expected;
	
	return ((difference >= - tolerance) && (difference <= tolerance));
}
 
/*********************************************
* TEST - 	CONSTRUCTOR - STATIONARY NORTH
*********************************************/
void TestSatellite::test_constructor_stationaryNorth()
{

	
}
/*********************************************
* TEST - 	GET ALTITUDE - SURFACE
*********************************************/
void TestSatellite::test_getAltitude_surface()
{
	Satellite s(6378000, 0);
	
	double alt = s.getAltitude();
	
	assert(alt == 0);
	
}

/*********************************************
* TEST - 	GET ALTITUDE - X AXIS
*********************************************/
void TestSatellite::test_getAltitude_xAxis()
{
	Satellite s(6379000, 0);
	
	double alt = s.getAltitude();
	
	assert(alt == 1000);
}

/*********************************************
* TEST - 	GET ALTITUDE - Y AXIS
*********************************************/
void TestSatellite::test_getAltitude_yAxis()
{
	Satellite s(0, 6379000);
	
	double alt = s.getAltitude();
	
	assert(alt == 1000);
}

/*********************************************
* TEST - 	GET GRAVITY - SURFACE
*********************************************/
void TestSatellite::test_getGravity_surface()
{
	Satellite s(6378000, 0);
	Acceleration aGravity(0.0, 0.0);
	
	aGravity = s.getGravity();

	assert(closeEnough(aGravity.getDDx(), -9.8066, 0.03));
	assert(closeEnough(aGravity.getDDy(), 0.0, 0.03));
}

/*********************************************
* TEST - 	GET GRAVITY - 500 K
*********************************************/
void TestSatellite::test_getGravity_500k()
{
	Satellite s(6378000 + 500000, 0);
	Acceleration aGravity(0.0, 0.0);
	
	aGravity = s.getGravity();
	
	assert(closeEnough(aGravity.getDDx(), -8.4, 0.05));
	assert(closeEnough(aGravity.getDDy(), 0.0, 0.05));

}

/*********************************************
* TEST - 	GET GRAVITY - 2000 K
*********************************************/
void TestSatellite::test_getGravity_2000k()
{
	Satellite s(6378000 + 2000000, 0);
	Acceleration aGravity(0.0, 0.0);
	
	aGravity = s.getGravity();
	
	assert(closeEnough(aGravity.getDDx(), -5.7, 0.03));
	assert(closeEnough(aGravity.getDDy(), 0.0, 0.03));

}

/*********************************************
* TEST - UPDATE VELOCITY  -
*********************************************/
void TestSatellite::test_updateVelocity_stationary()
{
	Velocity v(0.0, 0.0);
	Acceleration acc;
	double time = 0;
	
	v.updateVelocity(acc, time);
	
	assert(v.getDx() == 0.0 && v.getDy() == 0.0);
	
}

void TestSatellite::test_updateVelocity_moving()
{
	Velocity v(1.2, 3.4);
	Acceleration acc;
	double time = 0;
	v.updateVelocity(acc, time);
 
	assert(closeEnough(v.getDx(), 1.2, 0.01));
	assert(closeEnough(v.getDy(), 3.4, 0.01));
}

void TestSatellite::test_updateVelocity_accFromStop()
{
	Velocity v(0.0, 0.0);
	Acceleration acc(1.2, 3.4);
	double time = 1;
	v.updateVelocity(acc, time);
	
	assert(closeEnough(v.getDx(), 1.2, 0.01));
	assert(closeEnough(v.getDy(), 3.4, 0.01));
}

void TestSatellite::test_updateVelocity_accFromStop_longer()
{
	Velocity v(0.0, 0.0);
	Acceleration acc(1.2, 3.4);
	double time = 2;
	v.updateVelocity(acc, time);
	
	assert(closeEnough(v.getDx(), 2.4, 0.01));
	assert(closeEnough(v.getDy(), 6.8, 0.01));
}

void TestSatellite::test_updateVelocity_complex()
{
	Velocity v(4.1, 6.0);
	Acceleration acc(0.5, 0.2);
	double time = 3;
	v.updateVelocity(acc, time);
	
	assert(closeEnough(v.getDx(), 5.6, 0.01));
	assert(closeEnough(v.getDy(), 6.6, 0.01));
}

void TestSatellite::test_updatePosition_stationary()
{
	Satellite s(11.1, 22.2);
	Velocity velocity(0.0, 0.0);
	Acceleration acc;
	double time = 0;
	
	velocity.updateVelocity(acc, time);
	s.updatePosition();
	
	assert(closeEnough(s.getPosX(), 11.1, 0.01));
	assert(closeEnough(s.getPosY(), 22.2, 0.01));
}

void TestSatellite::test_updatePosition_moving()
{
	Satellite s(11.1, 22.2);
	s.setVelocity(0.5, 0.4);
	Acceleration acc(0.0, 0.0);
	double time = 1;
	
	s.velocity.updateVelocity(acc, time);
	s.updatePosition(time);
	
	assert(closeEnough(s.getPosX(), 11.6, 0.01));
	assert(closeEnough(s.getPosY(), 22.6, 0.01));
}

void TestSatellite::test_updatePosition_movingLonger()
{
	Satellite s(11.1, 22.2);
	s.setVelocity(0.5, 0.4);
	Acceleration acc;
	double time = 2;
	
	s.velocity.updateVelocity(acc, time);
	s.updatePosition(time);
	
	assert(closeEnough(s.getPosX(), 12.1, 0.01));
	assert(closeEnough(s.getPosY(), 23.0, 0.01));
}

void TestSatellite::test_updatePosition_fromStop()
{
	Satellite s(11.1, 22.2);
	s.setVelocity(0.0, 0.0);
	Acceleration acc(0.2, 0.3);
	double time = 1;
	
	s.velocity.updateVelocity(acc, time);
	s.updatePosition(time);
	
	assert(closeEnough(s.getPosX(), 11.2, 1));
	assert(closeEnough(s.getPosY(), 22.35, 1));
}

void TestSatellite::test_updatePosition_fromStop_longer()
{
	Satellite s(11.1, 22.2);
	s.setVelocity(0.0, 0.0);
	Acceleration acc(0.2, 0.3);
	double time = 2;
	
	s.velocity.updateVelocity(acc, time);
	s.updatePosition(time);
	
	assert(closeEnough(s.getPosX(), 11.5, 1));
	assert(closeEnough(s.getPosY(), 22.8, 1));
}

void TestSatellite::test_updatePosition_complex()
{
	Satellite s(11.1, 22.2);
	s.setVelocity(1.0, 2.0);
	Acceleration acc(0.2, 0.3);
	double time = 2;
	
	s.velocity.updateVelocity(acc, time);
	s.updatePosition(time);
	
	assert(closeEnough(s.getPosX(), 13.5, 1));
	assert(closeEnough(s.getPosY(), 26.8, 1));
	 
}

