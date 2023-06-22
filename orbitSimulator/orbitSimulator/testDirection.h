/***********************************************************************
* Header File:
*    Test Direction : Test the Direction class.
* Author:
*    Amber Robbins, Martin Nkala
* Summary:
*    All the unit tests for Direction.
************************************************************************/

#ifndef testDirection_h
#define testDirection_h

#include <iostream>
#include <cassert>
#include "direction.h"

using namespace std;

/*******************************
* TEST DIRECTION
* A friend class for Direction,
* which contains the Direction unit tests.
********************************/
class TestDirection
{
public:
	void run();
	bool closeEnough(float actual, float expected, float tolerance);
	
	void test_defaultConstructor();
	void test_setUp();
	void test_setDown();
	void test_setRight();
	void test_setLeft();
	void test_reverse();
	
	void test_setRadians_simple();
	void test_setRadians_threeQuarters();
	void test_setRadians_oneLap();
	void test_setRadians_sixLaps();
	void test_setRadians_negative();
	void test_setRadians_negativeThreeQuarters();
	void test_setRadians_negativeOneLap();
	void test_setRadians_negativeSixLaps();
	
};
#endif /* testDirection_h */
