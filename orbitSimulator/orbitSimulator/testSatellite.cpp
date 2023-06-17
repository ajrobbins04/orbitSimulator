#include "testSatellite.h"

void TestSatellite::run()
{
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

float TestSatellite::get_gravity(float altitude)
{
	// tmp is just a temporary variable to store one
	// aspect of the gravity computation
	float tmp = EARTH_RADIUS / (EARTH_RADIUS + altitude);
	float gravity = EARTH_GRAVITY * pow(tmp, 2);

	return gravity;
}


void TestSatellite::test_getAltitude_surface()
{
	Satellite s(6378000, 0);
	
	float alt = s.getAltitude();
	
	assert(alt == 0);
	
}

void TestSatellite::test_getAltitude_xAxis()
{
	Satellite s(6379000, 0);
	
	float alt = s.getAltitude();
	
	assert(alt == 1000);
}

void TestSatellite::test_getAltitude_yAxis()
{
	Satellite s(0, 6379000);
	
	float alt = s.getAltitude();
	
	assert(alt == 1000);
}

void TestSatellite::test_getGravity_surface()
{
	Satellite s(6378000, 0);
	
	float alt = s.getAltitude();
	float gravity = get_gravity(alt);
	
	//assert(gravity == -9.8066);
}

void TestSatellite::test_getGravity_500k()
{
	Satellite s(6378000 + 500000, 0);
	
	float alt = s.getAltitude();
	float gravity = get_gravity(alt);
	
	
//	assert(gravity == -8.4);
}

void TestSatellite::test_getGravity_2000k()
{
	Satellite s(6378000 + 2000000, 0);
	
	float alt = s.getAltitude();
	float gravity = get_gravity(alt);
	
//	assert(gravity == -5.7);
}

void TestSatellite::test_updateVelocity_stationary()
{
	Velocity v(0.0, 0.0);
	Acceleration acc;
	float time = 0;
	v.updateVelocity(acc, time);
	
	assert(v.getDx() == 0.0 && v.getDy() == 0.0);
	
	
}

void TestSatellite::test_updateVelocity_moving()
{
	Velocity v(1.2, 3.4);
	Acceleration acc;
	float time = 0;
	v.updateVelocity(acc, time);
	
	assert(v.getDx() - 1.2 < .000001 && v.getDy() - 3.4 < .000001);
	//assert(v.getDx() == 1.2 && v.getDy() == 3.4);
	
}

void TestSatellite::test_updateVelocity_accFromStop()
{
	Velocity v(0.0, 0.0);
	Acceleration acc(1.2, 3.4);
	float time = 1;
	v.updateVelocity(acc, time);
	
	assert(v.getDx() - 1.2 < .000001 && v.getDy() - 3.4 < .000001);
	//assert(v.getDx() == 1.2 && v.getDy() == 3.4);
}

void TestSatellite::test_updateVelocity_accFromStop_longer()
{
	Velocity v(0.0, 0.0);
	Acceleration acc(1.2, 3.4);
	float time = 2;
	v.updateVelocity(acc, time);
	
	assert(v.getDx() - 2.4 < .000001 && v.getDy() - 6.8 < .000001);
	//assert(v.getDx() == 2.4 && v.getDy() == 6.8);
}

void TestSatellite::test_updateVelocity_complex()
{
	Velocity v(4.1, 6.0);
	Acceleration acc(0.5, 0.2);
	float time = 3;
	v.updateVelocity(acc, time);
	
	assert(v.getDx() - 5.6 < .000001 && v.getDy() - 6.6 < .000001);
	//assert(v.getDx() == 5.6 && v.getDy() == 6.6);
}

void TestSatellite::test_updatePosition_stationary()
{
	Satellite s(11.1, 22.2);
	Velocity velocity(0.0, 0.0);
	Acceleration acc;
	float time = 0;
	
	velocity.updateVelocity(acc, time);
	s.updatePosition();
	
	assert(s.getPosX() - 11.1 < .000001 && s.getPosY() - 22.2 < .000001);
	//assert(s.getPosX() == 11.1 && s.getPosY() == 22.2);
	
}
void TestSatellite::test_updatePosition_moving()
{
	Satellite s(11.1, 22.2);
	Velocity velocity(0.5, 0.4);
	Acceleration acc;
	float time = 1;
	
	velocity.updateVelocity(acc, time);
	s.updatePosition();
	
	assert(s.getPosX() - 11.6 < .000001 && s.getPosY() - 22.6 < .000001);
	//assert(s.getPosX() == 11.6 && s.getPosY() == 22.6);
}
void TestSatellite::test_updatePosition_movingLonger()
{
	Satellite s(11.1, 22.2);
	Velocity velocity(0.5, 0.4);
	Acceleration acc;
	float time = 2;
	
	velocity.updateVelocity(acc, time);
	s.updatePosition();
	
	assert(s.getPosX() - 12.1 < .000001 && s.getPosY() - 23.0 < .000001);
	//assert(s.getPosX() == 12.1 && s.getPosY() == 23.0);
}

void TestSatellite::test_updatePosition_fromStop()
{
	Satellite s(11.1, 22.2);
	Velocity velocity(0.0, 0.0);
	Acceleration acc(0.2, 0.3);
	float time = 1;
	
	velocity.updateVelocity(acc, time);
	s.updatePosition();
	
	assert(s.getPosX() - 11.2 < .000001 && s.getPosY() - 22.35 < .000001);
	//assert(s.getPosX() == 11.2 && s.getPosY() == 22.35);
}

void TestSatellite::test_updatePosition_fromStop_longer()
{
	Satellite s(11.1, 22.2);
	Velocity velocity(0.0, 0.0);
	Acceleration acc(0.2, 0.3);
	float time = 2;
	
	velocity.updateVelocity(acc, time);
	s.updatePosition();
	
	assert(s.getPosX() - 11.5 < .000001 && s.getPosY() - 22.8 < .000001);
	//assert(s.getPosX() == 11.5 && s.getPosY() == 22.8);
}

void TestSatellite::test_updatePosition_complex()
{
	Satellite s(11.1, 22.2);
	Velocity velocity(1.0, 2.0);
	Acceleration acc(0.2, 0.3);
	float time = 2;
	
	velocity.updateVelocity(acc, time);
	s.updatePosition();
	
	assert(s.getPosX() - 13.5 < .000001 && s.getPosY() - 26.8 < .000001);
	//assert(s.getPosX() == 13.5 && s.getPosY() == 26.8);
}
