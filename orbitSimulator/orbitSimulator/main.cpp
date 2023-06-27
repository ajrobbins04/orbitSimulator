/*************************************************************
 * 1. Name:
 *       Martin Nkala, Amber Robbins
 * 2. Assignment Name:
 *      Lab 07: Orbit Simulator
 * 3. Assignment Description:
 *      Simulate satellites orbiting the earth
 * 4. What was the hardest part? Be as specific as possible.
 *      Getting all the math to work properly, and initializing
 *      the variables successfully in the object constructors.
 * 5. How long did it take for you to complete the assignment?
 *      It took about 9.5 hours to complete.
 *****************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include <iostream>
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"      // for POINT
#include "acceleration.h"
#include "satellite.h"
#include "velocity.h"
#include "testRunner.h"

#define TIME 48
#define FRAME_RATE 80
#define SECONDS_DAY 86400
#define PI 3.141529

using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
   Demo(Position ptUpperRight) :
	  ptUpperRight(ptUpperRight)
   {
 

	  
	 //  ptHubble.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
	 //  ptHubble.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

	  ptSputnik.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
	  ptSputnik.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

	  ptStarlink.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
	  ptStarlink.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

	  ptCrewDragon.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
	  ptCrewDragon.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

	  ptShip.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
	  ptShip.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

	  ptGPS.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
	  ptGPS.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

	  ptStar.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
	  ptStar.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

	   double rate = -(2 * PI / FRAME_RATE);
	   double frameRate = rate * TIME;
	   angleShip = frameRate;
	   angleEarth = frameRate;
	  phaseStar = 0;
   }


   Satellite hubble;
	
   Position ptSputnik;
   Position ptStarlink;
   Position ptCrewDragon;
   Position ptShip;
   Position ptGPS;
   Position ptStar;
   Position ptUpperRight;

   unsigned char phaseStar;

   double angleShip;
   double angleEarth;
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL.
   Demo* pDemo = (Demo*)p;

   //Acceleration a;
   //double angle = a.getAngle();
   //std::cout << angle << std::endl;
   //
   // accept input
   //
   
	//Position ptHubble(21082000, 36515000);
	//Velocity v(-2685, 1550);
	//Acceleration acc(-0.1122, -0.1943);
	
	//pDemo->hubble.reCalculate();
	//pDemo->hubble.update();
	
	Position ptHubble(pDemo->hubble.getPosX(), pDemo->hubble.getPosY());
	
   // move by a little
   if (pUI->isUp())
	  pDemo->ptShip.addPixelsY(1.0);
   if (pUI->isDown())
	  pDemo->ptShip.addPixelsY(-1.0);
   if (pUI->isLeft())
	  pDemo->ptShip.addPixelsX(-1.0);
   if (pUI->isRight())
	  pDemo->ptShip.addPixelsX(1.0);

   //
   // perform all the game logic
   //

   // rotate the earth
   pDemo->angleEarth -= 0.01;
   pDemo->angleShip -= 0.01;
   pDemo->phaseStar++;
	

   //
   // draw everything
   //

   Position pt;
   
   ogstream gout(pt);

   // draw satellites
   gout.drawHubble (ptHubble, pDemo->angleShip);
	
   /*
   gout.drawCrewDragon(pDemo->ptCrewDragon, pDemo->angleShip);

   gout.drawSputnik   (pDemo->ptSputnik,    pDemo->angleShip);
   gout.drawStarlink  (pDemo->ptStarlink,   pDemo->angleShip);
   gout.drawShip      (pDemo->ptShip,       pDemo->angleShip, pUI->isSpace());
   gout.drawGPS       (pDemo->ptGPS,        pDemo->angleShip);
	*/

   // draw parts
   pt.setPixelsX((pDemo->hubble.getPosX()/40) + 20);
   pt.setPixelsY((pDemo->hubble.getPosY()/40) + 20);
	
   /*
   pt.setPixelsX(pDemo->ptCrewDragon.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptCrewDragon.getPixelsY() + 20);
   gout.drawCrewDragonRight(pt, pDemo->angleShip); // notice only two parameters are set
   gout.drawHubbleLeft(pDemo->ptHubble, pDemo->angleShip);      // notice only two parameters are set
  
   pt.setPixelsX(pDemo->ptGPS.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptGPS.getPixelsY() + 20);
   gout.drawGPSCenter(pt, pDemo->angleShip);       // notice only two parameters are set
   pt.setPixelsX(pDemo->ptStarlink.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptStarlink.getPixelsY() + 20);
   gout.drawStarlinkArray(pt, pDemo->angleShip);   // notice only two parameters are set

   // draw fragments
   pt.setPixelsX(pDemo->ptSputnik.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptSputnik.getPixelsY() + 20);
   gout.drawFragment(pt, pDemo->angleShip);
   pt.setPixelsX(pDemo->ptShip.getPixelsX() + 20);
   pt.setPixelsY(pDemo->ptShip.getPixelsY() + 20);
   gout.drawFragment(pt, pDemo->angleShip);
*/
   // draw a single star
   gout.drawStar(pDemo->ptStar, pDemo->phaseStar);

   // draw the earth
   pt.setMeters(0.0, 0.0);

	
   gout.drawEarth(pt, pDemo->angleEarth);
}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
   ptUpperRight.setPixelsX(1000.0);
   ptUpperRight.setPixelsY(1000.0);
   Interface ui(0, NULL,
	  "Demo",   /* name on the window */
	  ptUpperRight);

   // Initialize the demo
   Demo demo(ptUpperRight);

   testRunner();
   // set everything into action
   ui.run(callBack, &demo);


   return 0;
}

